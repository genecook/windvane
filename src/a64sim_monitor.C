#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "a64sim_monitor.h"

#include "a64sim.h"
#include "SimTrace.h"
#include "scaffold.pb.h"
//#include "pbjson.hpp"

#include "TCPServer.h"
#include "a64sim_debug.h"

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#define MAX_BUF_LEN 4096

static TCPServer *my_server = NULL;

static DebugManager dbg_mgr;
 
//****************************************************************************************
// Connect - start simulation 'server'...
//****************************************************************************************

google::protobuf::io::FileOutputStream  *rawop;
google::protobuf::io::FileInputStream   *rawip;

void a64sim_monitor::Connect(const int portno) {
  verbose = true;

  if (verbose) printf("[Connect] port: %d\n",portno);

  if (enabled) { throw std::runtime_error("ERROR/Connect: Server already running???\n"); }

  try {
    my_server = new TCPServer(portno,false);
  }
  catch(const std::runtime_error& ex ) {
     std::cerr << ex.what() << std::endl;
     throw ex;
  }

  if (!my_server) { throw std::runtime_error("ERROR/Connect: No Server???\n"); }

  rawop = new google::protobuf::io::FileOutputStream(my_server->newsockfd);
  rawip = new google::protobuf::io::FileInputStream(my_server->newsockfd);

  enabled = true;

  if (verbose) printf("   connection made.\n");
}

//****************************************************************************************
// Disconnect - shutdown simulation 'server'...
//****************************************************************************************

void a64sim_monitor::Disconnect() {
  if (!Enabled()) return;

  if (verbose) printf("[Disconnect]\n");

  if (!my_server) { throw std::runtime_error("ERROR/Disconnect: No Server???\n"); }

  SendMessage(scaffold_SAPI::Command::HANGUP);

  delete my_server;

  enabled = false;
}

//****************************************************************************************
// encode arbitrary protocol buffer message in unsigned char array, return array length...
//****************************************************************************************

void a64sim_monitor::OutputSerializedMessage(void *msg_ptr) {
  if (verbose) printf("[OutputSerializedMessage] entered...\n");

  google::protobuf::Message *msg = (google::protobuf::Message *) msg_ptr;

  //printf("   msg: '%s'\n",msg->DebugString().c_str());

  int size = msg->ByteSize();

  //printf("[OutputSerializedMessage] msg size: %d\n",size);

  google::protobuf::io::CodedOutputStream coded_output(rawop);

  coded_output.WriteVarint32(size);

  uint8_t* buffer = coded_output.GetDirectBufferForNBytesAndAdvance(size);
  msg->SerializeWithCachedSizesToArray(buffer);

  if (coded_output.HadError()) {
    printf("[OutputSerializedMessage] ERRORS???\n");
  }

  if (verbose) printf("[OutputSerializedMessage] exited.\n");
}

//****************************************************************************************
// SendWaitContinue - send message, wait for response...
//****************************************************************************************

void a64sim_monitor::SendWaitContinue(void *message) {
  if (verbose) printf("     [SendWaitContinue] entered...\n");

  OutputSerializedMessage(message);
  rawop->Flush();


  if (verbose) printf("     [SendWaitContinue] waiting for response...\n");

  unsigned char response[MAX_BUF_LEN]; //<---ignoring response (for now)...

  int numread = read(my_server->newsockfd,response,MAX_BUF_LEN);

  if (numread < 0) { 
    throw std::runtime_error("ERROR reading from socket");
  }

  if (verbose) printf("        response received,rcv len: %d\n",numread);

  google::protobuf::io::ArrayInputStream ais(response,MAX_BUF_LEN);
  google::protobuf::io::CodedInputStream coded_input(&ais);

  unsigned int size = 0;
  coded_input.ReadVarint32(&size);

  if (verbose) printf("        response received,message size: %d\n",size);

  google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(size);

  scaffold_SAPI::Acknowledge my_ack;
  my_ack.ParseFromCodedStream(&coded_input);

  coded_input.PopLimit(msgLimit);

  if (verbose) printf("   acknowledge received, step count: %d\n",my_ack.step_count());

  dbg_mgr.UpdateConditions(my_ack);

  if (verbose) printf("     [SendWaitContinue] exited.\n");
}

//****************************************************************************************
// SendMessage - send command inentifying message, then (already encoded) message...
//****************************************************************************************

void a64sim_monitor::SendMessage(int message_type,const int cpuid,void *message) {
  if (verbose) printf("  [SendMessage] entered...\n");

  if (verbose) printf("    sending 'header' identifying message type...\n");

  scaffold_SAPI::Command my_cmd;
  my_cmd.set_type((scaffold_SAPI::Command_Type) message_type);
  my_cmd.set_cpuid(cpuid);

  SendWaitContinue((void *) &my_cmd);

  if (message) {
    if (verbose) printf("    sending the message...\n");
    SendWaitContinue(message);
  } else {
    if (verbose) printf("    no payload in this message...\n");
  }

  if (verbose) printf("  [SendMessage] exited.\n");
}

//****************************************************************************************
// SendCpuState - send cpu state...
//****************************************************************************************

void a64sim_monitor::SendCpuState(int type,State *_cpu, const int cpuid) {
  scaffold_SAPI::CpuSlice cpu;

  SimTrace st;
  st.RecordCpuState(&cpu,_cpu);

  printf("[SendCpuState] cpu: '%s'\n",cpu.DebugString().c_str());

  SendMessage(type,cpuid,(void *) &cpu);
}

//****************************************************************************************
// Initialize - send cpu initial state...
//****************************************************************************************

void a64sim_monitor::Initialize(State *_cpu, const int cpuid) {
  if (!Enabled()) return;

  if (verbose) printf("[Initialize] entered, cpuid: %d, state?: %s\n",cpuid, (_cpu != NULL ? "yes" : "no!"));

  SendCpuState(scaffold_SAPI::Command::INITIAL_CPU_STATE,_cpu,cpuid);

  if (verbose) printf("[Initialize] exited.\n");
}

//****************************************************************************************
// Finalize - send cpu final state...
//****************************************************************************************

void a64sim_monitor::Finalize(State *_cpu, const int cpuid) {
  if (!Enabled()) return;

  if (verbose) printf("[Finalize] cpuid: %d\n",cpuid);

  SendCpuState(scaffold_SAPI::Command::FINAL_CPU_STATE,_cpu,cpuid);
}

void a64sim_monitor::reset() {
  accesses.erase(accesses.begin(),accesses.end());
}

//****************************************************************************************
// format/send memory access message...
//****************************************************************************************

void a64sim_monitor::SendAccess(struct memAccess &access) {
  if (verbose) printf("[SendAccess] cpuid: %d\n",access.cpu_id);

  scaffold_SAPI::MemoryAccessDebug ma;

  ma.set_cpu_id(access.cpu_id);
  ma.set_la(access.LA);
  ma.set_pa(access.PA);
  ma.set_is_data(access.is_data);
  ma.set_is_write(access.is_write);
  ma.set_is_init(access.is_init);
  ma.set_number_of_bytes(access.number_of_bytes);
  ma.set_memblock((void *) access.memblock,access.number_of_bytes);

  int type = access.is_write ? scaffold_SAPI::Command::WRITE_PHYSICAL_MEMORY : scaffold_SAPI::Command::READ_PHYSICAL_MEMORY;
 
  if (dbg_mgr.Report(ma))
    SendMessage(type,access.cpu_id,(void *) &ma);
}

//****************************************************************************************
//****************************************************************************************

void a64sim_monitor::Record(const unsigned int cpu_id) {
  if (!Enabled()) return;

  if (verbose) printf("[Record]\n");
  reset();
}

//****************************************************************************************
//****************************************************************************************

void a64sim_monitor::Save(const unsigned int cpu_id) {
  if (!Enabled()) return;

  if (verbose) printf("[Save]\n");

  for (unsigned int i = 0; i < accesses.size(); i++) {
     SendAccess(accesses[i]);
  }
}

//****************************************************************************************
//****************************************************************************************

void a64sim_monitor::Abort(const unsigned int cpu_id) {
  if (!Enabled()) return;

  if (verbose) printf("[Abort]\n");
  reset();
}

//****************************************************************************************
// RegionAccess - access memory region. prequal to read/write physical memory...
//****************************************************************************************

void a64sim_monitor::RegionAccess(const unsigned char *buffer,const unsigned int cpu_id,
                                 const unsigned long long LA,const unsigned long long PA,
                                 const bool instr_vs_data,const bool read_vs_write,const int byte_count,
                                 const bool init_if_free) {
  if (!Enabled()) return;

  if (verbose) 
     printf("[RegionAccess] cpuid: %d LA: 0x%llx PA: 0x%llx instr? %s read vs write: %s byte count: %d\n",
            cpu_id,LA,PA,(instr_vs_data ? "INSTR" : "DATA"),(read_vs_write ? "WRITE" : "READ"),byte_count);

  this_access.cpu_id   = cpu_id;
  this_access.LA       = LA;
  this_access.PA       = PA;
  this_access.is_data  = instr_vs_data;
  this_access.is_write = read_vs_write;
  this_access.is_init  = init_if_free;
}

//****************************************************************************************
// WritePhysicalMemory
//****************************************************************************************

void a64sim_monitor::WritePhysicalMemory(const unsigned long long address,
                                        const int number_of_bytes,const unsigned char *buffer) {
  if (!Enabled()) return;

  if (verbose) printf("[WritePhysicalMemory] address: 0x%llx byte count: %d\n",address,number_of_bytes);

  this_access.number_of_bytes = number_of_bytes;
  memcpy(this_access.memblock,buffer,number_of_bytes);

  accesses.push_back(this_access);
}

//****************************************************************************************
// ReadPhysicalMemory
//****************************************************************************************

void a64sim_monitor::ReadPhysicalMemory(const unsigned long long address,
                                       const int number_of_bytes,const unsigned char *buffer,
                                       const bool init_if_free) {
  if (!Enabled()) return;

  if (verbose) printf("[ReadPhysicalMemory] address: 0x%llx byte count: %d\n",address,number_of_bytes);

  this_access.number_of_bytes = number_of_bytes;
  memcpy(this_access.memblock,buffer,number_of_bytes);

  accesses.push_back(this_access);
}

//****************************************************************************************
// Step - always send cpu state along with packet...
//****************************************************************************************

void a64sim_monitor::Step(State *cpu, Memory *memory, Packet *packet, unsigned long long clock, const int cpuid) {
  if (!Enabled()) 
     return;

  if (verbose) 
     printf("[Step] cpuid: %d, clock: 0x%llx\n",cpuid,clock);

  if (dbg_mgr.Report(cpu,packet,clock,cpuid)) {
    SendCpuState(scaffold_SAPI::Command::STEP_CPU_STATE,cpu,cpuid);
    scaffold_SAPI::Packet pkt;
    SimTrace st;
    st.RecordPacket(&pkt,cpu,memory,packet,clock);
    SendMessage(scaffold_SAPI::Command::STEP_PACKET,cpuid,(void *) &pkt);
  }
}

