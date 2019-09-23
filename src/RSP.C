#include "RSP.h"

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//***********************************************************************************************************
// RSP::Decode - decode standard RSP packet. Packet decode done here. Standard bracketed/checksumed RSP
//               packet assumed. Binary data is NOT reconstituted here. Run-length encoded data is NOT
//               handled herein. Single-character controls are NOT recognized herein.
//***********************************************************************************************************

std::string RSP::Decode(char *_packet,int _size, bool verbose) {
  // sanity checks on parameters...

  char tbuf[1024];
  
  if (_packet == NULL)
    throw std::invalid_argument("Call parameter 'packet' is NULL");

  if (_size == 0) {
    sprintf(tbuf,"Short packet size: %d",_size);
    throw std::runtime_error(tbuf);
  }

  char *packet = _packet;
  int size     = _size;

  std::string pdata; //<---will extract packet data to here...
  
  if (packet[0] == '+') {
    packet = &packet[1];
    size   = size - 1;  
    if (verbose) std::cout << " 'ack' character stripped from front of packet..." << std::endl;
  }

  if ((size > 0) && (packet[size - 1] == '+')) {
    size = size - 1;
    if (verbose) std::cout << " 'ack' character stripped from back of packet..." << std::endl;
  }
 
  if (size == 0) {
    // packet is now empty. lets assume it only contained an ack...
    return pdata;
  }

  // if we got here then packet size must be at least four characters...
 
  if (size < 4) {
    sprintf(tbuf,"Short packet size: %d",size);
    throw std::runtime_error(tbuf);
  }
  
  // is packet bracketed okay?...
  
  if (packet[0] != '$') {
    sprintf(tbuf,"Packet data not prefixed with '$' (instead '%c' seen).",packet[0]);
    throw std::runtime_error(tbuf);
  }
  
  if (packet[size - 3] != '#') {
    if (verbose) printf(tbuf,"Packet data not suffixed with '#' ?\n");
    for (int i = size - 1; i >= 0; i--) {
      if (verbose) printf("   packet[%d]: 0x%02x '%c'\n", i, packet[i], isprint(packet[i]) ? packet[i] : '?'); 
    }
    sprintf(tbuf,"Packet data not suffixed with '#' (instead %x seen?).",packet[size - 3]);
    throw std::runtime_error(tbuf);
  }

  // we expect the packet to contain ascii, ie, printable, characters only...

  for (int i = 0; i < size; i++) {
    if (isprint(packet[i])) continue;
    sprintf(tbuf,"Packet contains unprintable character: packet[%d] = 0x%x.\n",i,packet[i]);
    throw std::runtime_error(tbuf);
  }

  // pick off packet checksum...
  
  unsigned int expected_checksum = 0;
  
  if (sscanf(&packet[size - 2],"%2x",&expected_checksum) != 1) {
    sprintf(tbuf,"Problems parsing packet checksum. Checksum chars: 0x%x,0x%x",packet[size - 2],packet[size - 1]);
    throw std::runtime_error(tbuf);
  }
  
  // packet appears to be valid. we have an expected checksum...
  
  unsigned int observed_checksum = 0;

  bool do_escape = false;

  for (int i = 1; i < size - 3; i++) {
    char dc = packet[i];

    //printf("   packet[%d]: 0x%02x '%c'\n", i, dc, isprint(dc) ? dc : '?'); 

    if (do_escape) {
      dc = dc ^ 0x20;
      if (verbose) printf("   >>>exclusive or 'escaped' character with 0x20 to restore original value...\n");
    } else if (dc == '}') {
      do_escape = true;
      if (verbose) printf("   >>>escape character seen...\n");
      continue;
    }

    // sanity check: did we see an unescaped packet control char???
    
    if (!do_escape && ( (dc == '#') || (dc == '}') ) ) {
      sprintf(tbuf,"Unescaped control char in packet. Packet[%d] = '%c'",i,dc);
      throw std::runtime_error(tbuf);
    }
    
    // accumulate the next data value, update the checksum...

    pdata += dc;
    observed_checksum = (observed_checksum + dc) & 0xff; // checksum is sum of all chars, modulo 256...

    do_escape = false; // reset escape flag
  }

  // checksums match?...
  
  if (observed_checksum != expected_checksum) {
    throw std::runtime_error(tbuf);
    sprintf(tbuf,"Checksum on packet data (0x%x) does not match expected checksum (0x%x).",observed_checksum,expected_checksum);
  }
  
  
  // packet successfully decoded. return the data...
 
  return pdata;
}

//***********************************************************************************************************
// if a packet decoded into an actual request, ie, a non-zero length string, then send ack...
//***********************************************************************************************************

std::string RSP::Acknowledge(std::string packet_decoded) {
  std::string ack = (packet_decoded.size() > 0) ? "+" : "";
  return ack;
}


//***********************************************************************************************************
// RSP::Encode() - encode string in RSP Packet...
//***********************************************************************************************************

std::string RSP::Encode(std::string &src, bool verbose) {
  if (verbose)
    printf("[RSP::Encode] src: '%s', len: %d\n",src.c_str(),(int) src.size()); 
 
  unsigned int checksum = 0;

  for (int i = 0; i < (int) src.size(); i++) {
    char dc = src[i];
    checksum = (checksum + dc) & 0xff; // checksum is sum of all chars, modulo 256...    
  }

  if (verbose)
    printf("[RSP::Encode] checksum: %x\n",checksum);
  
  char chksum[128];
  sprintf(chksum,"%02x",checksum);

  std::string packet = "$" + src + "#" + chksum;

  if (verbose)
    printf("[RSP::Encode] packet: '%s'\n",packet.c_str());
  
  return packet;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::Dispatch(std::string _pdata, bool verbose) {
  std::string response;
  
  pdata = _pdata;

  if (pdata.size() == 0) {
    // zero length packet? ignore? send '?'...
    return(response); // we'll ignore...
  }
 
  response = "+";  // 'ack' all valid client requests
 
  int cmd_case = -1;

  if (pdata.find("qSupported") != std::string::npos) {
    cmd_case = REPORT_FEATURES;
  } else if (pdata.find("vMustReplyEmpty") != std::string::npos) {
    cmd_case = REPLY_EMPTY;
  } else if ( (pdata.substr(0,2) == "Hg") && isdigit(pdata[2]) ) {
    cmd_case = SET_THREAD; // set thread???
  } else if ( (pdata.substr(0,3) == "Hc-") && isdigit(pdata[4]) ) {
    cmd_case = SET_THREAD; // set active thread???
  } else if (pdata.find("qTStatus") != std::string::npos) {
    cmd_case = REPORT_TRACE_RUNNING;
  } else if (pdata.find("qTf") != std::string::npos) {   // qTfV or qTfP
    cmd_case = START_TRACE_VARIABLES_REPORT;
  } else if (pdata.find("qTs") != std::string::npos) {  // qTsV or qTsP
    cmd_case = END_TRACE_VARIABLES_REPORT;
  } else if (pdata.find("qfThreadInfo") != std::string::npos) {
    cmd_case = START_ACTIVE_THREADS_REPORT;    
  } else if (pdata.find("qsThreadInfo") != std::string::npos) {
    cmd_case = END_ACTIVE_THREADS_REPORT;    
  } else if (pdata.substr(0,2) == "qC") {
    cmd_case = USE_PREVIOUS_THREAD;
  } else if (pdata.find("qAttached") != std::string::npos){
    cmd_case = REPORT_PROCESS;
  } else if (pdata.find("qOffsets") != std::string::npos) {
    cmd_case = REPORT_OFFSETS;
  } else if (pdata == "?") {
    cmd_case = ACK_BAD_RESPONSE;
  } else if (pdata == "g") {
    cmd_case = READ_GP_REGISTERS;
  } else if (pdata[0] == 'm') {
    cmd_case = READ_MEMORY;
  } else if (pdata.find("vFile") != std::string::npos) {
    cmd_case = FILE_OPERATION;
  } else if (pdata.find("qSymbol::") != std::string::npos) {
    cmd_case = REQUEST_SYMBOL_INFO;
  } else if ( pdata[0] == 'Z') {
    cmd_case = SET_BREAKPOINT;
  } else if (pdata.find("vCont?") != std::string::npos) {
    cmd_case = REQUEST_SUPPORTED_ACTIONS;
  } else if (pdata.find("vCont") != std::string::npos) {
    cmd_case = CONTINUE_THREAD;
  } else if (pdata.find("vStep") != std::string::npos) {
    cmd_case = STEP_THREAD;
  } else if (pdata.find("vKill") != std::string::npos) {
    cmd_case = KILL_TARGET;
  } else if ( pdata[0] == 'D') {
    cmd_case = DETACH;
  } else if ( pdata[0] == 'G') {
    cmd_case = WRITE_GP_REGISTERS;
  } else if ( pdata[0] == 'k') {
    cmd_case = KILL_TARGET;
  } else if (pdata[0] == 'M') {
    cmd_case = WRITE_MEMORY;
  } else if (pdata[0] == 'p') {
    cmd_case = READ_REGISTER;
  } else if (pdata[0] == 'P') {
    cmd_case = WRITE_REGISTER;
  } else if (pdata[0] == 'X') {
    cmd_case = LOAD_BINARY_DATA;
  } else if ( pdata[0] == 'z') {
    cmd_case = CLEAR_BREAKPOINT;
  } else if ( pdata[0] == 'c') {
    cmd_case = CONTINUE;
  } else if ( pdata[0] == 's') {
    cmd_case = STEP;
  } else if ( pdata[0] == 'C') {
    cmd_case = CONTINUE_WITH_SIGNAL;
  } else if ( pdata[0] == 'S') {
    cmd_case = STEP_WITH_SIGNAL;
    
  } else {
    // what???
  }

  if (verbose)
    printf("[RSP::Dispatch] cmd-index: %d (%s)\n",cmd_case,commandName(cmd_case).c_str());
  
  switch(cmd_case) {
    case ACK_BAD_RESPONSE:             response = AckBadResponse();            break;
    case REPLY_EMPTY:                  response = ReplyEmpty();                break;
    case CLEAR_BREAKPOINT:             response = ClearBreakpoints();          break;
    case SET_BREAKPOINT:               response = SetBreakpoints();            break;
    case CONTINUE:                     response = Continue();                  break;
    case STEP:                         response = Step();                      break;
    case DETACH:                       response = Detach();                    break;
    case START_ACTIVE_THREADS_REPORT:  response = StartActiveThreadsReport();  break;
    case END_ACTIVE_THREADS_REPORT:    response = EndActiveThreadsReport();    break;
    case START_TRACE_VARIABLES_REPORT: response = StartTraceVariablesReport(); break;
    case END_TRACE_VARIABLES_REPORT:   response = EndTraceVariablesReport();   break;
    case FILE_OPERATION:               response = FileOperation();             break;
    case INTERRUPT:                    response = Interrupt();                 break;
    case KILL_TARGET:                  response = KillTarget();                break;
    case LOAD_BINARY_DATA:             response = LoadBinaryData();            break;
    case READ_GP_REGISTERS:            response = ReadGPRegisters();           break;
    case WRITE_GP_REGISTERS:           response = WriteGPRegisters();          break;
    case READ_REGISTER:                response = ReadRegister();              break;
    case WRITE_REGISTER:               response = WriteRegister();             break;
    case READ_MEMORY:                  response = ReadMemory();                break;
    case WRITE_MEMORY:                 response = WriteMemory();               break;
    case REPORT_FEATURES:              response = ReportFeatures();            break;
    case REPORT_OFFSETS:               response = ReportOffsets();             break;
    case REPORT_PROCESS:               response = ReportProcess();             break;
    case REPORT_TRACE_RUNNING:         response = ReportTraceRunning();        break;
    case REQUEST_SYMBOL_INFO:          response = RequestSymbolInfo();         break;
    case SEND_HALT_REPORT:             response = HaltReport();                break;
    case REPORT_CURRENT_THREAD:        response = ReportCurrentThread();       break;
    case SET_THREAD:                   response = SetThread();                 break;
    case USE_PREVIOUS_THREAD:          response = UsePreviousThread();         break;
    case CONTINUE_THREAD:              response = ContinueThread();            break;
    case CONTINUE_WITH_SIGNAL:         response = ContinueWithSignal();        break;
    case STEP_WITH_SIGNAL:             response = StepWithSignal();            break;
    case REQUEST_SUPPORTED_ACTIONS:    response = RequestSupportedActions();   break;
      
    default:
      if (verbose)
        printf("[RSP::Dispatch] unknown command, packet data: '%s'\n",pdata.c_str());
      break;
  }

  if (verbose)
    printf("[RSP::Dispatch] response: '%s'\n",response.c_str());
  
  return Encode(response);
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::commandName(int cmd_index) {
  std::string cmd_name;

  switch(cmd_index) {
    case ACK_BAD_RESPONSE:             cmd_name = "ACK_BAD_RESPONSE";             break;
    case REPLY_EMPTY:                  cmd_name = "REPLY_EMPTY";                  break;
    case CLEAR_BREAKPOINT:             cmd_name = "CLEAR_BREAKPOINT";             break;
    case SET_BREAKPOINT:               cmd_name = "SET_BREAKPOINT";               break;
    case CONTINUE:                     cmd_name = "CONTINUE";                     break;
    case STEP:                         cmd_name = "STEP";                         break;
    case DETACH:                       cmd_name = "DETACH";                       break;
    case START_ACTIVE_THREADS_REPORT:  cmd_name = "START_ACTIVE_THREADS_REPORT";  break;
    case END_ACTIVE_THREADS_REPORT:    cmd_name = "END_ACTIVE_THREADS_REPORT";    break;
    case START_TRACE_VARIABLES_REPORT: cmd_name = "START_TRACE_VARIABLES_REPORT"; break;
    case END_TRACE_VARIABLES_REPORT:   cmd_name = "END_TRACE_VARIABLES_REPORT";   break;
    case FILE_OPERATION:               cmd_name = "FILE_OPERATION";               break;
    case INTERRUPT:                    cmd_name = "INTERRUPT";                    break;
    case KILL_TARGET:                  cmd_name = "KILL_TARGET";                  break;
    case LOAD_BINARY_DATA:             cmd_name = "LOAD_BINARY_DATA";             break;
    case READ_GP_REGISTERS:            cmd_name = "READ_GP_REGISTERS";            break;
    case WRITE_GP_REGISTERS:           cmd_name = "WRITE_GP_REGISTERS";           break;
    case READ_REGISTER:                cmd_name = "READ_REGISTER";                break;
    case WRITE_REGISTER:               cmd_name = "WRITE_REGISTER";               break;
    case READ_MEMORY:                  cmd_name = "READ_MEMORY";                  break;
    case WRITE_MEMORY:                 cmd_name = "WRITE_MEMORY";                 break;
    case REPORT_FEATURES:              cmd_name = "REPORT_FEATURES";              break;
    case REPORT_OFFSETS:               cmd_name = "REPORT_OFFSETS";               break;
    case REPORT_PROCESS:               cmd_name = "REPORT_PROCESS";               break;
    case REPORT_TRACE_RUNNING:         cmd_name = "REPORT_TRACE_RUNNING";         break;
    case REQUEST_SYMBOL_INFO:          cmd_name = "REQUEST_SYMBOL_INFO";          break;
    case SEND_HALT_REPORT:             cmd_name = "SEND_HALT_REPORT";             break;
    case REPORT_CURRENT_THREAD:        cmd_name = "REPORT_CURRENT_THREAD";        break;
    case SET_THREAD:                   cmd_name = "SET_THREAD";                   break;
    case USE_PREVIOUS_THREAD:          cmd_name = "USE_PREVIOUS_THREAD";          break;
    case CONTINUE_THREAD:              cmd_name = "CONTINUE_THREAD";              break;
    case CONTINUE_WITH_SIGNAL:         cmd_name = "CONTINUE_WITH_SIGNAL";         break;
    case STEP_WITH_SIGNAL:             cmd_name = "STEP_WITH_SIGNAL";             break;
    case REQUEST_SUPPORTED_ACTIONS:    cmd_name = "REQUEST_SUPPORTED_ACTIONS";    break;
    default: break;
  }

  return cmd_name;
}


//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::AckBadResponse() {
  std::string my_response = "S05";   // stopped on Trap?
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReplyEmpty() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
// z type,addr,kind - clear 'type' breakpoint at address 'addr' of kind 'kind'
//***********************************************************************************************************

std::string RSP::ClearBreakpoints() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
// Z type,addr,kind - set 'type' breakpoint at address 'addr' of kind 'kind'
//***********************************************************************************************************

std::string RSP::SetBreakpoints() {
  std::string my_response = "";
/*
  unsigned long long maddr;
  int msize;
  sscanf(pdata.substr(1).c_str(),"%llx",&maddr);	
  std::cout << "BREAKPOINT ADDRESS: 0x" << std::hex << maddr << std::dec << std::endl;

  my_response = "OK"; // if supported...
*/
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::Continue() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::Step() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ContinueThread() {
  std::string my_response = ""; 
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ContinueWithSignal() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::StepWithSignal() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::Detach() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::StartActiveThreadsReport() {
  std::string my_response = "m0";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::EndActiveThreadsReport() {
  std::string my_response = "l";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::StartTraceVariablesReport() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::EndTraceVariablesReport() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::FileOperation() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::Interrupt() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::KillTarget() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::LoadBinaryData() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReadGPRegisters() {
  std::string my_response = "";

  // X0 thru X30, SP, pc, CPSR, FPSR, FPCR...
  for (int i = 0; i < 36; i++) {
     my_response += "0000000000000000";
  }

  // Q0 thru Q31 + FPSR,FPCR...
/*
  for (int i = 0; i < 31; i++) {
     my_response += "00000000000000000000000000000000";
  }
*/
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::WriteGPRegisters() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReadRegister() {
  std::string my_response = "";

  unsigned int rindex = 0;

  if (sscanf(pdata.substr(1).c_str(),"%x",&rindex) != 1) {
    my_response = "E 1"; // malformed read register packet...
    return my_response;
  }

  // read simulator register value, encode and return...
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::WriteRegister() {
  std::string my_response = "OK";
  
  unsigned int rindex = 0;

  if (sscanf(pdata.substr(1).c_str(),"%x",&rindex) != 1) {
    my_response = "E 1"; // malformed write register packet...
    return my_response;
  }

  std::size_t pos = pdata.find("=");

  if (pos == std::string::npos) {
    my_response = "E1"; // malformed write-register packet...
    return my_response;
  }
  
  // scan supplied register value, ASSUMING 2 hex digits per byte...

  int rsize = 4;   // <---register index dictates how many bytes to scan
  
  unsigned long long rval = 0;

  for (int i = 0; i < rsize; i++) {
     unsigned int bval;
     if (sscanf(pdata.substr(pos + 1).c_str(),"%2x",&bval) != 1) {
        my_response = "E2"; // malformed write-register packet...
        return my_response;
     }
     rval = (rval<<8) + bval; //<---we ASSUME register value bytes are MSB to LSB ordered?
  }

  // write simulator register value...
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReadMemory() {
  std::string my_response = ""; // return 'E 0' for uninitialized memory

  unsigned long long maddr;
  int msize;

  if (sscanf(pdata.substr(1).c_str(),"%llx,%d",&maddr,&msize) != 2) {
    my_response = "E1"; // malformed read/write-memory packet...
    return my_response;
  }

  // faking memory read...

  for (int i = 0; i < msize; i++) {
     my_response += "00";
  }
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::WriteMemory() {
  std::string my_response = "OK"; // will assume success...

  unsigned long long maddr;
  int msize;

  if (sscanf(pdata.substr(1).c_str(),"%llx,%d",&maddr,&msize) != 2) {
    my_response = "E1"; // malformed read/write-memory packet...
    return my_response;
  }

  std::size_t pos = pdata.find(":");

  if (pos == std::string::npos) {
    my_response = "E1"; // malformed read/write-memory packet...
    return my_response;
  }
  
  // scan supplied memory value, ASSUMING 2 hex digits per byte...

  unsigned int mbytes[msize];

  for (int i = 0; i < msize; i++) {
    if (sscanf(pdata.substr(pos + 1).c_str(),"%2x",&mbytes[i]) != 1) {
        my_response = "E2"; // malformed write-memory packet...
        return my_response;
     }
  }

  // write simulator memory - i guess the only real error that could result
  //                          would be if the address(es) were outside of physical memory?
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReportFeatures() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReportOffsets() {
  std::string my_response = "Text=0;Data=0;Bss=0";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReportProcess() {
  std::string my_response = "l";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReportTraceRunning() {
  std::string my_response = "T0";  // 1 if running...
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::RequestSymbolInfo() {
  std::string my_response = "OK";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::HaltReport() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::ReportCurrentThread() {
  std::string my_response = "OK";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::SetThread() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
//***********************************************************************************************************

std::string RSP::UsePreviousThread() {
  std::string my_response = "";
  
  return my_response;
}

//***********************************************************************************************************
// request list of actions supported by 'vCont' packet...
//***********************************************************************************************************

std::string RSP::RequestSupportedActions() {
  std::string my_response = "";
  
  return my_response;
}

