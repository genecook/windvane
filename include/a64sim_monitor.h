#ifndef X64_SIMULATION_MONITOR

#include <vector>

#include "a64SimMonitor.h"

class a64sim_monitor : A64SimMonitor {
 public:
  a64sim_monitor() { enabled = false; verbose = false; };

     // methods to allow simulator debug/monitoring. 

     //    Connect()    - connect to,
     //    Disconnect() -   disconnect from (debug) monitor

     //    Initialize() - called at simulation start with cpu initial state,
     //    Finalize()   -          "             end with cpu final state

     //    Record() - start accumulating memory accesses
     //    Save()   - save all accumulated accesses
     //    Abort()  - discard accesses since last save

     //    RegionAccess - called once virtual memory address has been resolved.

     //    WritePhysicalMemory - called when 
     //    ReadPhysicalMemory  -   physical memory accessed

     //    Step - called on cpu pipeline stages

     void Connect(const int portno);
     void Disconnect();

     void Initialize(State *cpu, const int cpuid);
     void Finalize(State *cpu, const int cpuid);

     // any memory access starts with a region (logical memory) access. record the access info. if then physical memory
     // is accessed the region info will be mated up with the physical info to create (record) a complete access...

     void RegionAccess(const unsigned char *buffer,const unsigned int cpu_id,const unsigned long long LA,
                       const unsigned long long PA,const bool instr_vs_data,const bool read_vs_write,const int byte_count,
                       const bool init_if_free);

     void WritePhysicalMemory(const unsigned long long address,const int number_of_bytes,const unsigned char *buffer);
     void ReadPhysicalMemory(const unsigned long long address,const int number_of_bytes,const unsigned char *buffer,const bool init_if_free);

     void Step(State *cpu, Memory *memory, Packet *packet, unsigned long long clock, const int _cpuid);

     // these methods used to acculumate memory accesses during the execution of a single instruction:

     void Record(const unsigned int cpu_id);  // start recording, ie, execution of an instruction has started
     void Save(const unsigned int cpu_id);    // instruction executed to completion so report any accesses made
     void Abort(const unsigned int cpu_id);   // instruction aborted so discard any accesses

 private:
     // use this struct to record a region access:

     struct memAccess {
       int                cpu_id;
       unsigned long long LA;
       unsigned long long PA;
       bool               is_data;
       bool               is_write;
       bool               is_init;
       int                number_of_bytes;
       unsigned char      memblock[MAX_BUF_LEN];
     };

     void Validate();
     void reset();

     void SendMessage(int message_type,const int cpuid = 0,void *message = NULL);
     void SendWaitContinue(void *msg);
     void SendCpuState(int type,State *_cpu, const int cpuid);
     void OutputSerializedMessage(void *msg_ptr);
     void SendAccess(struct memAccess &access);

     struct memAccess this_access;

     std::vector<struct memAccess> accesses; // accesses accumulated during the execution of a single instruction...
};

#endif

#define X64_SIMULATION_MONITOR 1
