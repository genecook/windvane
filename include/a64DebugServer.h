#ifndef __A64_DEBUG_SERVER__

#include <string>
#include <vector>

#include "a64sim.h"
#include "RSP.h"
#include "TCPServer.h"

//***************************************************************************************
//***************************************************************************************

#define __MAX_MSG_LEN__ 8096

class a64DebugServer : public RSP {
 public:
   a64DebugServer(int _portno, unsigned int _core);
   virtual ~a64DebugServer();
  
   bool Enabled() { return server_socket != NULL; };
   
   bool RunPreStepChecks(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt);
   bool RunPostStepChecks(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt);

 protected:
   void Init();
   void Fini();

   bool Poll(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt);

   void AcknowledgeBreakpoint(State *my_cpu, unsigned long long PC);
   void AcknowledgeWatchpoint(State *my_cpu, unsigned long long data_address);
   
   std::string Continue();
   std::string Step();
   std::string KillTarget();
   
   std::string ReadGPRegisters();
   std::string ReadRegister();
   std::string WriteRegister();
   std::string ReadMemory();
   std::string WriteMemory();

   std::string SetBreakpoints();
   std::string ClearBreakpoints();

   static const int MAX_MSG_LEN  = __MAX_MSG_LEN__;
   static const int MAX_BUF_SIZE = __MAX_MSG_LEN__ + 1024;
   
 private:
   struct breakpoint_range {
     unsigned long long address_lo;
     unsigned long long address_hi;
   };
   
   int RegType(unsigned int rindex);
   void show_reg_updates();
   void show_memory_updates(Packet &ipkt);

   void reset_breakpoints();

   bool core_match(unsigned int _core) { return core == _core; };

   int breakpoint_count() { return (int) instr_breakpoints.size(); };
   int watchpoint_count() { return (int) data_breakpoints.size();  };
   
   bool breakpoint_hit(unsigned long long PC);
   bool watchpoint_hit(unsigned long long &matched_address, unsigned long long start_address, int access_size);

   void _add_breakpoint(vector<struct breakpoint_range> &_breakpoints,
			unsigned long long _address_lo, unsigned long long _address_hi);

   bool _breakpoint_match(vector<struct breakpoint_range> &_breakpoints,
			  unsigned long long _input_address);

   bool deferResponse() { bool rcode = defer_response; defer_response = false; return rcode; };


   void setSingleStep() { do_step = true; };
   void clearSingleStep() { do_step = false; };
   bool SingleStep() { return do_step; };
   
   void RecordNextPC(unsigned long long NextPC) { PC = NextPC; };

   // endian-ness related utilities...
   
   void le8(char *encoded_rv,unsigned long long rv);
   bool decoded_le8(const char *encoded_rv,unsigned long long &rv);
   void le4(char *encoded_rv,unsigned int rv);
   bool decoded_le4(const char *encoded_rv,unsigned int &rv);

   int portno;                 // parms input
   unsigned int core;          //   via constructor
   
   TCPServer *server_socket;   // created at init time
   
   bool verbose;               // for debug prints
   bool at_start;              // true until after 1st access
   bool listening;             // mostly true, but clear during 'continue'
   bool defer_response;        // set by step or continue
   bool do_shutdown;           // set when time to shutdown server

   bool do_step;               // set by Step method. cleared in post-step
   
   State *my_cpu;              // public pre/post step
   Memory *my_memory;          //   methods set
   unsigned long long PC;      //     these parms...
   Packet *ipkt;               //

   vector<struct breakpoint_range> instr_breakpoints;
   vector<struct breakpoint_range> data_breakpoints;
};

#endif
#define __A64_DEBUG_SERVER__ 1
