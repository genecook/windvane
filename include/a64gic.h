#ifndef __A64SIM_GIC__

#include <string>
#include "memmap_device.h"

//--------------------------------------------------------------------------------------------------------------
//
// GICD_TYPER.MBIS - message based SPI support
//
// GICD_* - global settings, SPIs
// GICR_* - SGIs, PPIs
// ICC_*  - cpu interface
//
//      ------------------------
// From Foundation model users guide:
//
// GICD 0x2f00 0000 0x2f00 ffff  - 64kb
// GICR 0x2f10 0000 0x2f1f ffff  - 1mb
//
// IRQ ID  SPI offset*   PPI*  GIC INTID    device or event
// ------  ----------    ---   ---------    ---------------
//   37       5           -       ?*         UART0
//   38       6           -       ?          UART1
//   39       7           -       ?          UART2
//   40       8           -       ?          uart3
//    -       -           13      ?          (secure) physical timer event
//
// *NOTE: Interrupt nomenclature used in Foundation model users manual does NOT jive with
//        GIC arch spec. INTID for SPIs must be in range 32..1029. For PPIs, range is 16..31.
//--------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------
// interrupt state...
//--------------------------------------------------------------------------------------------------------------

class int_state {
 public:
int_state() : SPI_index(-1) { Reset(); };

  int_state(int _SPI_index, std::string _whoami) : SPI_index(_SPI_index), whoami(_whoami) {
    Reset();
  };

  void Reset() {
    group = 0;
    enabled = false;
    pending = false;
    active = false;
    level_sensitive = false;
    routing_info = 0;
  }

  bool IsDefined() { return SPI_index >= 0; };  // only true for registered SPIs

  bool Group0() { return group; };
  bool Group1() { return group; };

  void SetGroup(unsigned int _grp)       { group = (group & 2) | (_grp & 1);         };
  void SetGroupMod(unsigned int _grpmod) { group = (group & 1) | ((_grpmod & 1)<<1); };

  unsigned int Group() { return group & 1; };
  unsigned int GroupMod() { return (group & 2)>>1; };

  bool Enabled() { return enabled; };
  bool Pending() { return pending; };

  bool SetEnabled(bool _enabled) { enabled = _enabled; return enabled;     };
  bool SetPending(bool _pending) { pending = _pending; return pending;     };
  bool SetActive(bool _active)   { active  = _active; return active;       };
  void SetEdgeTriggered()        { level_sensitive = false; };
  void SetLevelSensitive()       { level_sensitive = true;  };
  
  bool Inactive()      { return !pending && !active;   }; 
  bool ActivePending() { return  pending && active;    };
  bool Active()        { return !pending && active;    };

  bool EdgeTriggered()  { return !level_sensitive;     };
  bool LevelSensitive() { return level_sensitive;      };

  void Assert() { pending = true; };  // an interrupt sets the pending state

  void Deassert() { pending = false; }; // deasserting the interrupt clears the pending state

  void Acknowledge() {  // active state entered when interrupt acknowledged. pending state cleared if edge-triggered
    active = true;
    if (EdgeTriggered())
      pending = false;
  };

  void Deactivate() { active = false; }; // deactivating interrupt clears active state

  unsigned int Priority() { return priority; };
  void Priority(unsigned int nval) { priority = nval; };

  unsigned int Config() { return LevelSensitive(); };
  void Config(unsigned int lv) { level_sensitive = lv; };

  unsigned long long RoutingInfo() { return routing_info; };
  void RoutingInfo(unsigned long long _routing_info) { routing_info = _routing_info; };

  int SPI_index;
  std::string whoami;
    
  unsigned int group;  // if > 0 then group1 else group0
  bool enabled; // true if forward to redistributer
  bool pending;
  bool active;
  unsigned int priority;
  unsigned long long routing_info;
  bool level_sensitive; // if true then level-sensitive, else edge-sensitive
};


//--------------------------------------------------------------------------------------------------------------
// GIC - platform 'generic' interrupt controller...
//--------------------------------------------------------------------------------------------------------------

class GIC : public memmap_device {
 public:
  GIC() {};
  
  void init(unsigned long long _base_address,unsigned long long _extent=0xffff) {
    base_address = _base_address;
    extent = _extent;
    Reset();
  };

  void Reset();
  
  bool IsMapped(unsigned long long PA);

  void RegisterName(unsigned long long PA,std::string &rname);

  // define enuns only for SPIs 0 thru 15, and only for memory mapped GICD registers supported in this 'implementation'...
  
  enum DISTRIBUTER_REGISTER_OFFSETS {
    _CTLR=0x0, _TYPER=0x4, _IIDR=0x8, _STATUSR=0x10, _SETSPI_NSR=0x40, _CLRSPI_NSR=0x48, _SETSPI_SR=0x50, _CLRSPI_SR=0x58,

     // all offsets are for SPIs 0..15 (INTIDs 32..47):

    _IGROUPR1=0x84,
    _ISENABLER1=0x104,
    _ICENABLER1=0x184,
    _ISPENDR1=0x204,
    _ICPENDR1=0x284,
    _ISACTIVER1=0x304,
    _ICACTIVER1=0x384,
    
    _IPRIORITYR0=0x480, _IPRIORITYR1=0x484, _IPRIORITYR2 =0x488, _IPRIORITYR3 =0x48C, _IPRIORITYR4 =0x490, _IPRIORITYR5 =0x494, _IPRIORITYR6 =0x498, _IPRIORITYR7 =0x49c,
    _IPRIORITYR8=0x4a0, _IPRIORITYR9=0x4a4, _IPRIORITYR10=0x4a8, _IPRIORITYR11=0x4ac, _IPRIORITYR12=0x4b0, _IPRIORITYR13=0x4b4, _IPRIORITYR14=0x4b8, _IPRIORITYR15=0x4bC,
    
    _ICFGR2=0xc08,_ICFGR3=0xc0c, // each register holds 16 2-bit cfgs
    
    _IGRPMODR1=0xd04,

    // GICD_IROUTER regs are only for SPIs. 1st 16 are implemented...
    
    _IROUTER0  = 0x6100,_IROUTER1  = 0x6108,_IROUTER2  = 0x6110,_IROUTER3  = 0x6118,_IROUTER4  = 0x6120,_IROUTER5  = 0x6128,_IROUTER6  = 0x6130,_IROUTER7  = 0x6138,
    _IROUTER8  = 0x6140,_IROUTER9  = 0x6148,_IROUTER10 = 0x6150,_IROUTER11 = 0x6158,_IROUTER12 = 0x6160,_IROUTER13 = 0x6168,_IROUTER14 = 0x6170,_IROUTER15 = 0x6178,
    
    // 0xffd0 - 0xfffc - ID registers

    // 0xffd0 - 0xffe4 - implementation specific. reserved. read as zeros...
    
    _PIDR2 = 0xffe8
    
    // 0xffec - 0xfffc - implementation specific. reserved. read as zeros...
  };

  bool RegisterWritePending() { return (GICD_CTLR >> 31) & 1; };
  bool EnableWakeup() { return (GICD_CTLR >> 7) & 1; };
  bool AffinityRoutingEnable() { return (GICD_CTLR >> 4) & 1; };
  bool Group1InterruptsEnabled() { return GICD_CTLR & 2; };
  bool Group0InterruptsEnabled() { return GICD_CTLR & 1; };
    
  // each PE can affect changes to GIC state:
  
  int Read(unsigned long long PA,unsigned char *buffer,int access_size);
  int Write(unsigned long long PA,unsigned char *buffer,int access_size);

  int ReadLong(unsigned long long PA,unsigned long long *rval);
  int Read(unsigned long long PA,unsigned int *rval);
  int WriteLong(unsigned long long PA,unsigned long long rval);
  int Write(unsigned long long PA,unsigned int rval);

  // called when changes to shared device interrupt changes detected:

  void Register(int SPI_index, std::string whoami);  // each device that can cause global interrupt must
                                                     //indicate which SPI index to attach to
  void Assert(int SPI_index);      // device asserts, 
  void Deassert(int SPI_index);    //   or deasserts interrupt            

  bool Evaluate();                 // not sure just yet what this should do

  const static int NUM_SPIS = 16;
  const static unsigned int SPI_MASK = NUM_SPIS - 1;

  unsigned int GICD_IGROUP();
  void GICD_IGROUP(unsigned int updates);
  unsigned int GICD_ISENABLER();
  void GICD_ISENABLER(unsigned int enables);
  unsigned int GICD_ICENABLER();
  void GICD_ICENABLER(unsigned int disables);
  unsigned int GICD_ISPENDR();
  void GICD_ISPENDR(unsigned int updates);
  unsigned int GICD_ICPENDR();
  void GICD_ICPENDR(unsigned int updates);
  unsigned int GICD_ISACTIVER();
  void GICD_ISACTIVER(unsigned int updates);
  unsigned int GICD_ICACTIVER();
  void GICD_ICACTIVER(unsigned int updates);
  unsigned int GICD_IPRIORITYR(int spi_index);
  void GICD_IPRIORITYR(int spi_index,int updates);

  unsigned int GICD_ICFGR();
  void GICD_ICFGR(int updates);

  unsigned int GICD_IGRPMODR();
  void GICD_IGRPMODR(unsigned int mods);

  unsigned long long GICD_IROUTER(int spi_index);
  void GICD_IROUTER(int spi_index,unsigned long long _route);
  
 private:
  unsigned int GICD_CTLR;
  unsigned int GICD_TYPER;
  unsigned int GICD_IIDR;
  unsigned int GICD_PIDR2;
  
  int_state SPIs[NUM_SPIS];           // Shared Peripheral Interrupts are managed by distributer.
                                      // peripherals must 'sign in', ie, register SPI index
};

//--------------------------------------------------------------------------------------------------------------
// GIC Redistributer - one per each core...
//--------------------------------------------------------------------------------------------------------------

class gic_redistributer : public memmap_device {
 public:
  gic_redistributer() {};
  void init(unsigned long long _base_address,unsigned long long _extent=0x3ffff);  // WHAT???

  void Reset() {};
  
  enum REDISTRIBUTER_REGISTER_OFFSETS {
    CTLR = 0x0, IIDR = 0x4, TYPER = 0x8, STATUSR = 0x10, WAKER = 0x14, PROPBASER = 0x70, PENDBASR = 0x78,
    
    // 0xffd0 - 0xfffc - ID registers

    // 0xffd0 - 0xffe4 - implementation specific. reserved. read as zeros...  - WE'LL ASSUME ANY ACCESS TO UNSUPPORTED REGISTER (OFFSET) RETURNS ZEROS
    
    PIDR2 = 0xffe8
    
    // 0xffec - 0xfffc - implementation specific. reserved. read as zeros...
  };

  bool IsMapped(unsigned long long PA) { return false; };

  int Read(unsigned long long PA,unsigned char *buffer,int access_size) { return 0; };
  int Write(unsigned long long PA,unsigned char *buffer,int access_size) { return 0; };

  int Read(unsigned long long PA,unsigned int *rval) { return 0; };
  int Write(unsigned long long PA,unsigned int rval) { return 0; };
  
 private:

  unsigned int GICR_CTRL;
  unsigned int GICR_IIDR;
  unsigned int GICR_TYPER;
  unsigned int GICR_STATUSR;
  unsigned int GICR_WAKER;
  unsigned int GICR_PROPBASER;
  unsigned int GICR_PENDBASR;
  unsigned int GICR_PIDR;
};


#define __A64SIM_GIC__
#endif
