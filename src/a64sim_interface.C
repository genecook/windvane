#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "scaffold.pb.h"

#include "a64sim.h"
#include "SimTrace.h"
#include "a64Scaffold.h"
#include "a64sim_interface.h"

using namespace std;

namespace a64simulator {
  Scaffold *scaffold = NULL; // manage a single simulator instance...
  bool running = false;

  stringstream runlog;
  stringstream errlog;
  stringstream tracelog;
  stringstream debuglog;

  void update_logs(scaffold_SAPI::Response &response) {
    if (!runlog.str().empty())   response.set_runlog(runlog.str());
    if (!errlog.str().empty())   response.set_errlog(errlog.str());
    if (!tracelog.str().empty()) response.set_tracelog(tracelog.str());
    if (!debuglog.str().empty()) response.set_debuglog(debuglog.str());

    runlog.str("");
    errlog.str("");
    tracelog.str("");
    debuglog.str("");
  }

  // allocate new simulator...

  int boot(scaffold_SAPI::Command &parms) {
     scaffold = new Scaffold();
     scaffold->SetLogFiles(&runlog,&errlog,&tracelog,&debuglog);
     return 0;
  }

  // discard simulator...

  int power_down(scaffold_SAPI::Command &parms) {
      scaffold->FreeRunEnd(parms.cpuid());
      delete scaffold;
      runlog.str("Simulator powered down.");  
      return 0;
  }

  // initialize simulator state...

  int init(scaffold_SAPI::Command &parms) {
      scaffold->InitSimulator();
      return 0;
  }

  // enable/disable exceptions...

  int enable_exceptions(scaffold_SAPI::Command &parms) {
      scaffold->SetSimExceptionEnables(/*exc_enables*/);
      return 0;
  }

  int init_freerun(scaffold_SAPI::Command &parms) {
      return scaffold->FreeRunInit(parms.cpuid(),parms.count(),parms.seed(),parms.do_break(),parms.verbose()); 
  }

  int freerun_step(scaffold_SAPI::Command &parms) {
      int rcode = -1;
      int instr_index = parms.step_index();
      if (instr_index >= 0) {
          rcode = scaffold->FreeRunStep(instr_index);   
      }
      return rcode;    
  }

  // return values for specified simulator state...

  int checkpoint(scaffold_SAPI::Command &parms) {
    //int item = parms.item();
    //int cpu  = parms.cpuid();

    int rcode = -1;
/*
    if (item == scaffold_SAPI::Command::CPU) {
      rcode = scaffold->CheckPointCPU(cpu);
    } else if (item == scaffold_SAPI::Command::PACKET) {
      rcode = scaffold->CheckPointPacket(cpu);
    }
*/
    return rcode;    
  }

  int load(scaffold_SAPI::Command &parms) {
    string elf_file = parms.elf_in_file();
    int rcode = scaffold->Load(elf_file);    
    return rcode;    
  }

  int save(scaffold_SAPI::Command &parms) {
    string elf_file = parms.elf_out_file();
    int rcode = scaffold->Save(elf_file);    
    return rcode;    
  }
}

// the 'user interface' consists of a single C entry point: SimulatorQuery...

extern "C" {
  void SimulatorQuery(void *request_buffer, int request_buffer_length, void *response_buffer,int *response_buffer_length) {

    scaffold_SAPI::Command request;

    request.ParseFromArray(request_buffer,request_buffer_length);

    scaffold_SAPI::Response response;

    int rcode = -1;

    switch(request.type()) {
      case 0:  response.set_type(scaffold_SAPI::Response_Type_BOOT);
               rcode = a64simulator::boot(request);
               break;
      case 1:  response.set_type(scaffold_SAPI::Response_Type_INIT);
               rcode = a64simulator::init(request);
               break;
      case 2:  response.set_type(scaffold_SAPI::Response_Type_ENABLE_EXCEPTIONS);
               rcode = a64simulator::enable_exceptions(request);
               break;
      case 3:  response.set_type(scaffold_SAPI::Response_Type_POWER_DOWN);
               rcode = a64simulator::power_down(request);
               break;
      case 4:  response.set_type(scaffold_SAPI::Response_Type_INIT_FREERUN);
               rcode = a64simulator::init_freerun(request);
               break;
      case 5:  response.set_type(scaffold_SAPI::Response_Type_FREERUN_STEP);
               rcode = a64simulator::freerun_step(request);
               break;
      case 6:  response.set_type(scaffold_SAPI::Response_Type_CHECKPOINT);
               rcode = a64simulator::checkpoint(request);
               break;
      case 7:  response.set_type(scaffold_SAPI::Response_Type_LOAD);
               rcode = a64simulator::load(request);
               break;
      case 8:  response.set_type(scaffold_SAPI::Response_Type_SAVE);
               rcode = a64simulator::save(request);
               break;

      default: break;
    }

    response.set_status(rcode);

    a64simulator::update_logs(response);
    
    response.SerializeToArray(response_buffer,response.ByteSize());

    *response_buffer_length = response.ByteSize();
  }
}
