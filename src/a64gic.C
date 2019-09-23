#include "a64gic.h"

//-------------------------------------------------------------------------------------------
// GIC distributer reset values...
//-------------------------------------------------------------------------------------------

void GIC::Reset() {
  GICD_CTLR        = 0x70;       // reset value - one security state, affinity routing enabled
  GICD_TYPER       = 0x800000;   // reset value - 16 IDbits(?), max SPI INTID is 31
  GICD_IIDR        = 0x403b;     // from arm spec
  GICD_PIDR2       = 0x30;       // GICv3

  for (int i = 0; i < NUM_SPIS; i++) {
    SPIs[i].Reset();
  }
}

//-------------------------------------------------------------------------------------------
// is GIC distributer register mapped?...
//-------------------------------------------------------------------------------------------

bool GIC::IsMapped(unsigned long long PA) {
  bool mapped = false;
  if (InRange(PA)) {
    switch((int)(PA & extent)) {
      case _CTLR:
      case _TYPER:
      case _IIDR:
      case _STATUSR:
      case _SETSPI_SR:
      case _CLRSPI_SR:
      case _IGROUPR1:
      case _ISENABLER1:
      case _ICENABLER1:
      case _ISPENDR1:
      case _ICPENDR1:
      case _ISACTIVER1:
      case _ICACTIVER1:
      case _IPRIORITYR0: case _IPRIORITYR1: case _IPRIORITYR2: case _IPRIORITYR3: case _IPRIORITYR4: case _IPRIORITYR5: case _IPRIORITYR6: case _IPRIORITYR7:
      case _IPRIORITYR8: case _IPRIORITYR9: case _IPRIORITYR10: case _IPRIORITYR11: case _IPRIORITYR12: case _IPRIORITYR13: case _IPRIORITYR14: case _IPRIORITYR15:
      case _ICFGR2: case _ICFGR3:
      case _IGRPMODR1:
      case _IROUTER0: case _IROUTER1: case _IROUTER2: case _IROUTER3: case _IROUTER4: case _IROUTER5: case _IROUTER6: case _IROUTER7:
      case _IROUTER8: case _IROUTER9: case _IROUTER10: case _IROUTER11: case _IROUTER12: case _IROUTER13: case _IROUTER14: case _IROUTER15:
      case _PIDR2:  mapped = true;
                    break;
		    
      default: break;
    }
  }
  
  return mapped;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

void GIC::RegisterName(unsigned long long PA,std::string &rname) {
    rname = "GICD_";
    
    switch((int)(PA & extent)) {
      case _CTLR:         rname += "CTLR";           break;
      case _TYPER:        rname += "TYPER";          break;
      case _IIDR:         rname += "IIDR";           break;
      case _STATUSR:      rname += "STATUSR";        break;
      case _SETSPI_SR:    rname += "SETSPI_SR";      break;
      case _CLRSPI_SR:    rname += "CLRSPI_SR";      break;
      case _IGROUPR1:     rname += "IGROUP<1>";      break;
      case _ISENABLER1:   rname += "ISENABLER<1>";   break;
      case _ICENABLER1:   rname += "ICENABLER<1>";   break;
      case _ISPENDR1:     rname += "ISPENDR<1>";     break;
      case _ICPENDR1:     rname += "ICPENDR<1>";     break;
      case _ISACTIVER1:   rname += "ISACTIVER<1>";   break;
      case _ICACTIVER1:   rname += "ICACTIVER<1>";   break;
      case _IPRIORITYR0:  rname += "IPRIORITYR<0>";  break;
      case _IPRIORITYR1:  rname += "IPRIORITYR<1>";  break;
      case _IPRIORITYR2:  rname += "IPRIORITYR<2>";  break;
      case _IPRIORITYR3:  rname += "IPRIORITYR<3>";  break;
      case _IPRIORITYR4:  rname += "IPRIORITYR<4>";  break;
      case _IPRIORITYR5:  rname += "IPRIORITYR<5>";  break;
      case _IPRIORITYR6:  rname += "IPRIORITYR<6>";  break;
      case _IPRIORITYR7:  rname += "IPRIORITYR<7>";  break;
      case _IPRIORITYR8:  rname += "IPRIORITYR<8>";  break;
      case _IPRIORITYR9:  rname += "IPRIORITYR<9>";  break;
      case _IPRIORITYR10: rname += "IPRIORITYR<10>"; break;
      case _IPRIORITYR11: rname += "IPRIORITYR<11>"; break;
      case _IPRIORITYR12: rname += "IPRIORITYR<12>"; break;
      case _IPRIORITYR13: rname += "IPRIORITYR<13>"; break;
      case _IPRIORITYR14: rname += "IPRIORITYR<14>"; break;
      case _IPRIORITYR15: rname += "IPRIORITYR<15>"; break;
      case _ICFGR2:       rname += "ICFGR<2>";       break;
      case _ICFGR3:       rname += "ICFGR<3>";       break;
      case _IGRPMODR1:    rname += "IGRPMODR<1>";    break;
      case _IROUTER0:     rname += "IROUTER<0>";     break;
      case _IROUTER1:     rname += "IROUTER<1>";     break;
      case _IROUTER2:     rname += "IROUTER<2>";     break;
      case _IROUTER3:     rname += "IROUTER<3>";     break;
      case _IROUTER4:     rname += "IROUTER<4>";     break;
      case _IROUTER5:     rname += "IROUTER<5>";     break;
      case _IROUTER6:     rname += "IROUTER<6>";     break;
      case _IROUTER7:     rname += "IROUTER<7>";     break;
      case _IROUTER8:     rname += "IROUTER<8>";     break;
      case _IROUTER9:     rname += "IROUTER<9>";     break;
      case _IROUTER10:    rname += "IROUTER<10>";    break;
      case _IROUTER11:    rname += "IROUTER<11>";    break;
      case _IROUTER12:    rname += "IROUTER<12>";    break;
      case _IROUTER13:    rname += "IROUTER<13>";    break;
      case _IROUTER14:    rname += "IROUTER<14>";    break;
      case _IROUTER15:    rname += "IROUTER<15>";    break;
      case _PIDR2:        rname += "PIDR<2>";        break;
		    
      default: break;
    }
}

//-------------------------------------------------------------------------------------------
// read memory-mapped GIC distributer register...
//-------------------------------------------------------------------------------------------

int GIC::Read(unsigned long long PA,unsigned char *buffer,int access_size) {
  if (access_size == 8)
    return ReadLong(PA,(unsigned long long *) buffer);
  else if (access_size == 4)
    return Read(PA,(unsigned int *) buffer);

  return -1;
}

int GIC::ReadLong(unsigned long long PA,unsigned long long *rval) {
  int rcode = 0;
  *rval = 0;
  
  switch((int)(PA & extent)) {
    case _IROUTER0:    *rval = GICD_IROUTER(0);    break;
    case _IROUTER1:    *rval = GICD_IROUTER(1);    break;
    case _IROUTER2:    *rval = GICD_IROUTER(2);    break;
    case _IROUTER3:    *rval = GICD_IROUTER(3);    break;
    case _IROUTER4:    *rval = GICD_IROUTER(4);    break;
    case _IROUTER5:    *rval = GICD_IROUTER(5);    break;
    case _IROUTER6:    *rval = GICD_IROUTER(6);    break;
    case _IROUTER7:    *rval = GICD_IROUTER(7);    break;
    case _IROUTER8:    *rval = GICD_IROUTER(8);    break;
    case _IROUTER9:    *rval = GICD_IROUTER(9);    break;
    case _IROUTER10:   *rval = GICD_IROUTER(10);   break;
    case _IROUTER11:   *rval = GICD_IROUTER(11);   break;
    case _IROUTER12:   *rval = GICD_IROUTER(12);   break;
    case _IROUTER13:   *rval = GICD_IROUTER(13);   break;
    case _IROUTER14:   *rval = GICD_IROUTER(14);   break;
    case _IROUTER15:   *rval = GICD_IROUTER(15);   break;
    default: rcode = -1;
             break;
  }

  return rcode;
}

int GIC::Read(unsigned long long PA,unsigned int *rval) {
  int rcode = 0;
  *rval = 0;
  
  switch((int)(PA & extent)) {
    case _CTLR:         *rval = GICD_CTLR;           break;
    case _TYPER:        *rval = GICD_TYPER;          break;
    case _IIDR:         *rval = GICD_IIDR;           break;
    case _IGROUPR1:     *rval = GICD_IGROUP();       break;   
    case _ISENABLER1:   *rval = GICD_ISENABLER();    break;
    case _ICENABLER1:   *rval = GICD_ICENABLER();    break;    
    case _ISPENDR1:     *rval = GICD_ISPENDR();      break;
    case _ICPENDR1:     *rval = GICD_ICPENDR();      break;  
    case _ISACTIVER1:   *rval = GICD_ISACTIVER();    break;
    case _ICACTIVER1:   *rval = GICD_ICACTIVER();    break;
    case _IPRIORITYR0:  *rval = GICD_IPRIORITYR(0);  break;
    case _IPRIORITYR1:  *rval = GICD_IPRIORITYR(1);  break;
    case _IPRIORITYR2:  *rval = GICD_IPRIORITYR(2);  break;
    case _IPRIORITYR3:  *rval = GICD_IPRIORITYR(3);  break;
    case _IPRIORITYR4:  *rval = GICD_IPRIORITYR(4);  break;
    case _IPRIORITYR5:  *rval = GICD_IPRIORITYR(5);  break;
    case _IPRIORITYR6:  *rval = GICD_IPRIORITYR(6);  break;
    case _IPRIORITYR7:  *rval = GICD_IPRIORITYR(7);  break;
    case _IPRIORITYR8:  *rval = GICD_IPRIORITYR(8);  break;
    case _IPRIORITYR9:  *rval = GICD_IPRIORITYR(9);  break;
    case _IPRIORITYR10: *rval = GICD_IPRIORITYR(10); break;
    case _IPRIORITYR11: *rval = GICD_IPRIORITYR(11); break;
    case _IPRIORITYR12: *rval = GICD_IPRIORITYR(12); break;
    case _IPRIORITYR13: *rval = GICD_IPRIORITYR(13); break;
    case _IPRIORITYR14: *rval = GICD_IPRIORITYR(14); break;
    case _IPRIORITYR15: *rval = GICD_IPRIORITYR(15); break;
    case _ICFGR2:       *rval = GICD_ICFGR();        break;     
    case _IGRPMODR1:    *rval = GICD_IGRPMODR();     break;
    case _PIDR2:        *rval = GICD_PIDR2;          break;
    default: rcode = -1;
             break;
  }

  return rcode;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

unsigned int GIC::GICD_IGROUP() {
  unsigned int igroup0 = 0;
  
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      igroup0 |= SPIs[i].Group1()<<i;   
  }

  return igroup0;
}
void GIC::GICD_IGROUP(unsigned int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetGroup((updates>>i) & 1);
  }
}

unsigned int GIC::GICD_ISENABLER() {
  unsigned int enables = 0;
  
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      enables |= SPIs[i].Enabled()<<i;   
  }

  return enables;  
}
void GIC::GICD_ISENABLER(unsigned int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetEnabled((updates>>i) & 1);
  }
}

unsigned int GIC::GICD_ICENABLER() {
  return ~GICD_ISENABLER();
}
void GIC::GICD_ICENABLER(unsigned int disables) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetEnabled( !((disables>>i) & 1) );
  }
}

unsigned int GIC::GICD_ISPENDR() {
  unsigned int pendset = 0;
  
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      pendset |= SPIs[i].Pending()<<i;   
  }

  return pendset;  
}
void GIC::GICD_ISPENDR(unsigned int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetPending((updates>>i) & 1);
  }
}

unsigned int GIC::GICD_ICPENDR() {
  return ~GICD_ISPENDR();
}
void GIC::GICD_ICPENDR(unsigned int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetPending( !((updates>>i) & 1) );
  }
}

unsigned int GIC::GICD_ISACTIVER() {
  unsigned int actives = 0;
  
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      actives |= SPIs[i].Active()<<i;   
  }

  return actives;  
}
void GIC::GICD_ISACTIVER(unsigned int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetActive((updates>>i) & 1);
  }
}

unsigned int GIC::GICD_ICACTIVER() {
  return ~GICD_ISACTIVER();
}
void GIC::GICD_ICACTIVER(unsigned int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetActive( !((updates>>i) & 1) );
  }
}

unsigned int GIC::GICD_IPRIORITYR(int spi_index) {
  return SPIs[spi_index].Priority();
}
void GIC::GICD_IPRIORITYR(int spi_index,int updates) {
  SPIs[spi_index].Priority(updates);
}

unsigned int GIC::GICD_ICFGR() {
  unsigned int cfgs = 0;
  
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      cfgs |= SPIs[i].Config()<<(i*2);
  }

  return cfgs;  

}
void GIC::GICD_ICFGR(int updates) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].Config( (updates>>(i*2)) & 0x3);
  }
}

unsigned int GIC::GICD_IGRPMODR() {
  unsigned int mods = 0;
  
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      mods |= SPIs[i].GroupMod()<<i;   
  }

  return mods;    
}
void GIC::GICD_IGRPMODR(unsigned int mods) {
  for (int i = 0; i < NUM_SPIS; i++) {
    if (SPIs[i].IsDefined())
      SPIs[i].SetGroupMod((mods>>i) & 1);
  }
}

unsigned long long GIC::GICD_IROUTER(int spi_index) {
  unsigned long long aff3 = SPIs[spi_index].RoutingInfo()>>24;
  unsigned long long aff2to0 = SPIs[spi_index].RoutingInfo() & 0xffffff;
  return aff3<<32 | aff2to0;
}
void GIC::GICD_IROUTER(int spi_index,unsigned long long _route) {
  unsigned long long aff3 = _route>>32;
  unsigned long long aff2to0 = _route & 0xffffff;
  SPIs[spi_index].RoutingInfo((aff3<<24) | aff2to0);
}

//-------------------------------------------------------------------------------------------
// write memory-mapped GIC distributer register...
//-------------------------------------------------------------------------------------------

int GIC::Write(unsigned long long PA,unsigned char *buffer,int access_size) {
  if (access_size == 8)
    return WriteLong(PA,*( (unsigned long long *) buffer));
  else if (access_size == 4)
    return Write(PA,*( (unsigned int *) buffer));

  return -1;
}

int GIC::WriteLong(unsigned long long PA,unsigned long long rval) {
  int rcode = 0;
  
  switch((int)(PA & extent)) {
    case _IROUTER0:    GICD_IROUTER(0,rval);  break;
    case _IROUTER1:    GICD_IROUTER(1,rval);  break;
    case _IROUTER2:    GICD_IROUTER(2,rval);  break;
    case _IROUTER3:    GICD_IROUTER(3,rval);  break;
    case _IROUTER4:    GICD_IROUTER(4,rval);  break;
    case _IROUTER5:    GICD_IROUTER(5,rval);  break;
    case _IROUTER6:    GICD_IROUTER(6,rval);  break;
    case _IROUTER7:    GICD_IROUTER(7,rval);  break;
    case _IROUTER8:    GICD_IROUTER(8,rval);  break;
    case _IROUTER9:    GICD_IROUTER(9,rval);  break;
    case _IROUTER10:   GICD_IROUTER(10,rval); break;
    case _IROUTER11:   GICD_IROUTER(11,rval); break;
    case _IROUTER12:   GICD_IROUTER(12,rval); break;
    case _IROUTER13:   GICD_IROUTER(13,rval); break;
    case _IROUTER14:   GICD_IROUTER(14,rval); break;
    case _IROUTER15:   GICD_IROUTER(15,rval); break;

    default: rcode = -1;
             break;
  }

  return rcode;
}

int GIC::Write(unsigned long long PA,unsigned int rval) {
  int rcode = 0;
  
  switch((int)(PA & extent)) {
    case _CTLR:        GICD_CTLR = rval;          break;
    case _IGROUPR1:    GICD_IGROUP(rval);         break;
    case _ISENABLER1:  GICD_ISENABLER(rval);      break;
    case _ICENABLER1:  GICD_ICENABLER(rval);      break;
    case _ISPENDR1:    GICD_ISPENDR(rval);        break;   
    case _ICPENDR1:    GICD_ICPENDR(rval);        break;
    case _ISACTIVER1:  GICD_ISACTIVER(rval);      break;      
    case _ICACTIVER1:  GICD_ICACTIVER(rval);      break;
    case _IPRIORITYR0:  GICD_IPRIORITYR(0,rval);  break;
    case _IPRIORITYR1:  GICD_IPRIORITYR(1,rval);  break;
    case _IPRIORITYR2:  GICD_IPRIORITYR(2,rval);  break;
    case _IPRIORITYR3:  GICD_IPRIORITYR(3,rval);  break;
    case _IPRIORITYR4:  GICD_IPRIORITYR(4,rval);  break;
    case _IPRIORITYR5:  GICD_IPRIORITYR(5,rval);  break;
    case _IPRIORITYR6:  GICD_IPRIORITYR(6,rval);  break;
    case _IPRIORITYR7:  GICD_IPRIORITYR(7,rval);  break;
    case _IPRIORITYR8:  GICD_IPRIORITYR(8,rval);  break;
    case _IPRIORITYR9:  GICD_IPRIORITYR(9,rval);  break;
    case _IPRIORITYR10: GICD_IPRIORITYR(10,rval); break;
    case _IPRIORITYR11: GICD_IPRIORITYR(11,rval); break;
    case _IPRIORITYR12: GICD_IPRIORITYR(12,rval); break;
    case _IPRIORITYR13: GICD_IPRIORITYR(13,rval); break;
    case _IPRIORITYR14: GICD_IPRIORITYR(14,rval); break;
    case _IPRIORITYR15: GICD_IPRIORITYR(15,rval); break;
    case _ICFGR2:       GICD_ICFGR(rval);         break;
    case _IGRPMODR1:    GICD_IGRPMODR(rval);      break;
      
    default: rcode = -1;
             break;
  }

  return rcode;
}

//-------------------------------------------------------------------------------------------
  // each device that can cause global interrupt must indicate which SPI index to attach to
//-------------------------------------------------------------------------------------------

void GIC::Register(int SPI_index, std::string whoami) {
  int_state my_int_state(SPI_index,whoami);
  SPIs[SPI_index] = my_int_state;
}

//-------------------------------------------------------------------------------------------
// devices assert/deassert physical interrupts by SPI index...
//-------------------------------------------------------------------------------------------

void GIC::Assert(int SPI_index) {
  SPIs[SPI_index].Assert();
}

void GIC::Deassert(int SPI_index) {
  SPIs[SPI_index].Deassert();
}

//-------------------------------------------------------------------------------------------
// evaluate interrupt state...
//-------------------------------------------------------------------------------------------

bool GIC::Evaluate() {
  // now determine whether or not to pass some interrupt info onto redistributer...

  return false;  
}
