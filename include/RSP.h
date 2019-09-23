#ifndef __RSP__

#include <string>
#include <stdexcept>

//*************************************************************************************
// RSP - GDB Remote Serial Protocol class.
//
//   Methods to decode/encode RSP packets. Virtual methods supplied for common gdb
// commands. Subclass any that are supported by your simulator...
//*************************************************************************************

class RSP {
 public:
  RSP() {};
  virtual ~RSP() {};
  
  std::string Decode(char *packet,int size, bool verbose=false);
  std::string Encode(std::string &src, bool verbose=false);

  std::string Acknowledge(std::string pdata);
  
  std::string Dispatch(std::string pdata, bool verbose=false);

  std::string commandName(int index);
  
  virtual std::string AckBadResponse();
  virtual std::string ReplyEmpty();
  
  virtual std::string ClearBreakpoints();
  
  virtual std::string SetBreakpoints();
  virtual std::string Continue();
  virtual std::string ContinueThread();
  virtual std::string ContinueWithSignal();
  virtual std::string Step();
  virtual std::string StepWithSignal();
  virtual std::string Detach();
  virtual std::string StartActiveThreadsReport();
  virtual std::string EndActiveThreadsReport();
  virtual std::string StartTraceVariablesReport();
  virtual std::string EndTraceVariablesReport();
  virtual std::string FileOperation();
  virtual std::string Interrupt();
  virtual std::string KillTarget();
  virtual std::string LoadBinaryData();
  virtual std::string ReadGPRegisters();
  virtual std::string WriteGPRegisters();
  virtual std::string ReadRegister();
  virtual std::string WriteRegister();
  virtual std::string ReadMemory();
  virtual std::string WriteMemory();
  virtual std::string ReportFeatures();
  virtual std::string ReportOffsets();
  virtual std::string ReportProcess();
  virtual std::string ReportTraceRunning();
  virtual std::string RequestSymbolInfo();
  virtual std::string HaltReport();
  virtual std::string ReportCurrentThread();
  virtual std::string SetThread();
  virtual std::string UsePreviousThread();
  virtual std::string RequestSupportedActions();

 protected:
    enum GDB_SERVER_ACTIONS { ACK_BAD_RESPONSE=0,
			    CLEAR_BREAKPOINT=1,
			    CONTINUE=2,
			    CONTINUE_THREAD=3,
			    CONTINUE_WITH_SIGNAL=4,
			    DETACH=5,
			    END_ACTIVE_THREADS_REPORT=6,
			    END_TRACE_VARIABLES_REPORT=7,
			    FILE_OPERATION=8,
			    INTERRUPT=9,
			    KILL_TARGET=10,
			    LOAD_BINARY_DATA=11,
			    READ_GP_REGISTERS=12,
			    READ_MEMORY=13,
			    READ_REGISTER=14,
			    REPLY_EMPTY=15,
			    REPORT_CURRENT_THREAD=16,
			    REPORT_FEATURES=17,
			    REPORT_OFFSETS=18,
			    REPORT_PROCESS=19,
			    REPORT_TRACE_RUNNING=20, 
                            REQUEST_SYMBOL_INFO=21,
			    SEND_HALT_REPORT=22,
			    SET_BREAKPOINT=23,
			    SET_THREAD=24,
			    START_ACTIVE_THREADS_REPORT=25,
			    START_TRACE_VARIABLES_REPORT=26,
			    STEP=27,
			    STEP_THREAD=28,
			    STEP_WITH_SIGNAL=29,
			    USE_PREVIOUS_THREAD=30,
                            WRITE_GP_REGISTERS=31,
			    WRITE_MEMORY=32,
			    WRITE_REGISTER=33,
			    REQUEST_SUPPORTED_ACTIONS=34
                          };

  std::string pdata;
};

#define __RSP__ 1
#endif
