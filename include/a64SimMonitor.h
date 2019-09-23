#ifndef A64_SIMULATION_MONITOR

class State;
class Packet;
class Memory;

class A64SimMonitor {
 public:
  A64SimMonitor() : enabled(false),verbose(false) {};
  virtual ~A64SimMonitor() {};
  
  static const int MAX_BUF_LEN = 8096;

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

     virtual void Connect(const int portno) {};
     virtual void Disconnect() {};

     virtual void Initialize(State *cpu, const int cpuid) {};
     virtual void Finalize(State *cpu, const int cpuid) {};

     // any memory access starts with a region (logical memory) access. record the access info. if then physical memory
     // is accessed the region info will be mated up with the physical info to create (record) a complete access...

     virtual void RegionAccess(const unsigned char *buffer,const unsigned int cpu_id,const unsigned long long LA,
                               const unsigned long long PA,const bool instr_vs_data,const bool read_vs_write,const int byte_count,
                               const bool init_if_free) {};

     virtual void WritePhysicalMemory(const unsigned long long address,const int number_of_bytes,const unsigned char *buffer) {};
     virtual void ReadPhysicalMemory(const unsigned long long address,const int number_of_bytes,const unsigned char *buffer,const bool init_if_free) {};

     virtual void Step(State *cpu, Memory *memory, Packet *packet, unsigned long long clock, const int _cpuid) {};

     // these methods used to acculumate memory accesses during the execution of a single instruction:

     virtual void Record(const unsigned int cpu_id) {};  // start recording, ie, execution of an instruction has started
     virtual void Save(const unsigned int cpu_id) {};    // instruction executed to completion so report any accesses made
     virtual void Abort(const unsigned int cpu_id) {};   // instruction aborted so discard any accesses

     bool Enabled() { return enabled; };
     bool Verbose() { return verbose; };
     
 protected:
     bool enabled;
     bool verbose;
};

#endif

#define A64_SIMULATION_MONITOR 1
