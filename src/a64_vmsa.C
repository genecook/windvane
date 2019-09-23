#include "a64sim.h"
#include "a64_exceptions.h"
#include "a64_vmsa.h"
#include <omp.h>
#include <assert.h>
#include <iostream>

//#define MMU_DEBUG 1
#define IGNORE_UPPER_PA_BITS 1
//#define KERNEL_DEBUG 1

// the issue with tlbs are that tlb maintenance instructions are not implemented
// and thus don't really know when to invalidate tlb entries...
//#define USE_TLB 1
//==================================================================================
// translations...
//==================================================================================

Translation::Translation() : valid(0), mmu_enabled(false), secondstage(false), addressExtended(false) {
}

Translation::Translation(unsigned long long _la,unsigned int _asid,bool _privileged, bool _ns,
                         bool _is_data, bool _wasaligned, int _size, bool _is_write, bool _big_endian) 
  : 
    LA(_la), 
    extLA(_la), 
    IPA(_la), 
    PA(_la), 
    valid(false), 
    Global(false), 
    mmu_enabled(false), 
    secondstage(false), 
    permissioncheck(false),
    addressExtended(false), 
    is_data(_is_data), 
    is_write(_is_write), 
    wasaligned(_wasaligned), 
    size(_size),
    privileged(_privileged),
    ASID(_asid), 
    NS(_ns), 
    BigEndian(_big_endian), 
    topBit(0),
    s1_enabled(false), 
    s2_enabled(false), 
    ttb_base_address(0), 
    tbi(false), 
    readUnprivileged(false),
    writeUnprivileged(false),
    readPrivileged(false),
    writePrivileged(false),
    XN(false), 
    PXN(false), 
    Contiguous(false),
    nG(false), 
    AF(false), 
    memory_type(UNKNOWN_MEMORY),
    device_type(DEVICETYPE_UNKNOWN),
    outer_cache_type(MEMATTR_UNKNOWN), 
    outer_transient(false),
    outer_read_allocate(false),
    outer_write_allocate(false),
    inner_cache_type(MEMATTR_UNKNOWN),
    inner_transient(false),
    inner_read_allocate(false),
    inner_write_allocate(false),
    innershareable(false),
    outershareable(false),
    contiguous(false),
    domain(0), 
    blocksize(-1), 
    unpredictable(false),
    base_address(0), 
    page_offset_mask(0), 
    levels(0) 
{
}

void Translation::updateCacheHints(struct AttrXcacheHints cache_hints) {
  outer_cache_type     = cache_hints.outer_cache_type;
  outer_transient      = cache_hints.outer_transient;
  outer_read_allocate  = cache_hints.outer_read_allocate;
  outer_write_allocate = cache_hints.outer_write_allocate;
  inner_cache_type     = cache_hints.inner_cache_type;
  inner_transient      = cache_hints.inner_transient;
  inner_read_allocate  = cache_hints.inner_read_allocate;
  inner_write_allocate = cache_hints.inner_write_allocate;
}

  // we ASSUME an access is shareable if 'inner' (L1) or 'outer' (L2) shareable... 
bool Translation::Shareable() { 
  return innershareable || outershareable; 
}
 
// we ASSUME an access is cacheable if 'inner' or 'outer' cacheable...
bool Translation::Cacheable() { 
  return inner_cache_type != MEMATTR_NONCACHEABLE || outer_cache_type != MEMATTR_NONCACHEABLE; 
}

std::ostream& operator<< (std::ostream &os, Translation &trans) {
  os << "Translation: \n";
  os << "   valid:                " << trans.valid << "\n";
  os << "   Global:               " << trans.Global << "\n";
  os << "   mmu_enabled:          " << trans.mmu_enabled << "\n";
  os << "   secondstage:          " << trans.secondstage << "\n";
  os << "   permissioncheck:      " << trans.permissioncheck << "\n";
  os << "   addressExtended:      " << trans.addressExtended << "\n";
  os << "   is_data:              " << trans.is_data << "\n";
  os << "   is_write:             " << trans.is_write << "\n";
  os << "   wasaligned:           " << trans.wasaligned << "\n";
  os << "   size:                 " << trans.size << "\n";
  os << "   privileged:           " << trans.privileged << "\n";

  os << "   LA:                   " << std::hex << trans.LA << std::dec << "\n";
  os << "   extLA:                " << std::hex << trans.extLA << std::dec << "\n";
  os << "   IPA:                  " << std::hex << trans.IPA << std::dec << "\n";
  os << "   PA:                   " << std::hex << trans.PA << std::dec << "\n";
  os << "   ASID:                 " << std::hex << trans.ASID << std::dec << "\n";
  os << "   NS:                   " << std::hex << trans.NS << std::dec << "\n";

  os << "   BigEndian:            " << trans.BigEndian << "\n";
  os << "   topBit:               " << trans.topBit << "\n";
  os << "   s1_enabled:           " << trans.s1_enabled << "\n";
  os << "   s2_enabled:           " << trans.s2_enabled << "\n";

  os << "   ttb_base_address:     " << std::hex << trans.ttb_base_address << std::dec << "\n";
  os << "   tbi:                  " << trans.tbi << "\n";

  os << "   readUnprivileged:     " << trans.readUnprivileged << "\n";
  os << "   writeUnprivileged:    " << trans.writeUnprivileged << "\n";
  os << "   readPrivileged:       " << trans.readPrivileged << "\n";
  os << "   writePrivileged:      " << trans.writePrivileged << "\n";

  os << "   XN:                   " << trans.XN << "\n";
  os << "   PXN:                  " << trans.PXN << "\n";
  os << "   Contiguous:           " << trans.Contiguous << "\n";
  os << "   nG:                   " << trans.nG << "\n";
  os << "   AF:                   " << trans.AF << "\n";

  os << "   memory_type:          " << trans.memory_type << "\n";
  os << "   device_type:          " << trans.device_type << "\n";

  os << "   outer_cache_type:     " << trans.outer_cache_type << "\n";
  os << "   outer_transient:      " << trans.outer_transient << "\n";
  os << "   outer_read_allocate:  " << trans.outer_read_allocate << "\n";
  os << "   outer_write_allocate: " << trans.outer_write_allocate << "\n";

  os << "   inner_cache_type:     " << trans.inner_cache_type << "\n";
  os << "   inner_transient:      " << trans.inner_transient << "\n";
  os << "   inner_read_allocate:  " << trans.inner_read_allocate << "\n";
  os << "   inner_write_allocate: " << trans.inner_write_allocate << "\n";

  os << "   outershareable:       " << trans.outershareable << "\n";
  os << "   innershareable:       " << trans.innershareable << "\n";

  os << "   contiguous:           " << trans.contiguous << "\n";
  os << "   domain:               " << trans.domain << "\n";
  os << "   current level:        " << trans.level << "\n";
  os << "   blocksize:            " << trans.blocksize << "\n";

  os << "   unpredictable:        " << trans.unpredictable << "\n";

  os << "   physical base address: " << std::hex << trans.base_address << std::dec << "\n";
  os << "   page offset mask:     " << std::hex << trans.page_offset_mask << std::dec << "\n";

  os << "   #levels:              " << trans.levels << "\n";

  os << "   descriptors:\n";

  if (trans.levels == 0)
    os << "      none???\n";

  for (int i = 0; i < trans.levels; i++) {
     os << trans.descriptors[i] << "\n";
  }

  return os;
}

void Translation::LA2PA(unsigned long long _LA) {
  if (valid) {
    PA = base_address + (_LA & page_offset_mask);
#ifdef MMU_DEBUG
    printf("[Translation::LA2PA] LA: 0x%llx base-address: 0x%llx page-mask: 0x%llx ===>PA: 0x%llx\n",_LA,base_address,page_offset_mask,PA);
#endif
  } else {
    // how did we get here?
    throw INTERNAL_ERROR;
  }
}


//==================================================================================
// TLBs...
//==================================================================================

/* 
  TLBkey - return key to use with TLB table - composed from LA,ASID,Global,NS,is_data...

  key contents:

   bits 63-48 - ASID
   bits 47-12 - LA sans high-address bits (if applicable) and low order 12 bits (assuming smallest 4k page size)
   bit  3     - 1 if Global (0 for non-global)
   bit  2     - 1 if non-secure (0 for secure)
   bit  1     - 1 if data (0 for instruction)
   bit  0     - 1 if high address range (0 if 16 msb bits are zero)
*/

#define HIGH_ADDRESS_RANGE(LA) (LA & 0xffff000000000000ull) != 0
#define SANS_HIGH_ADDRESS_BITS(LA) (LA & 0xffffffffffffull)
#define TOP_BITS(LA) (LA & 0xf000000000000000ull)

unsigned long long Translation::TLBkey() { 
  unsigned long long tlb_key   = LA & 0xfffffffff000ull;                       // start with LA sans high address bits and page offset bits
  unsigned long long asid_bits = Global ? 0 : ((unsigned long long) ASID)<<48; // if global page asid field is zero, else its the asid

  tlb_key |= asid_bits | (HIGH_ADDRESS_RANGE(LA) ? 1ull : 0);                  // add in asid and 'high address bits' indicator
  tlb_key |= (unsigned long long)(Global<<3 | NS<<2 | is_data<<1);             // add in global, NS, and 'data' bits

#ifdef MMU_DEBUG
  printf("[Translation::TLBkey] LA: 0x%llx, key: 0x%llx\n",LA,tlb_key);
#endif

  return tlb_key;
}

// use LA, page size, and byte count to see if page is crossed...

int Translation::PageCrossed(int byte_count) {
  int spill_count = 0;
  
  unsigned long long page_offset1 = LA & page_offset_mask;
  unsigned long long page_offset2 = (LA + byte_count) & page_offset_mask;

  if (page_offset2 < page_offset1) {
    spill_count = (int) page_offset2;
#ifdef MMU_DEBUG
    printf("[Translation::PageCrossed] LA/size: 0x%llx/%d, crosses page. Spill count: %u\n",LA,byte_count,spill_count);
#endif  
  }

  return spill_count;
}

bool TLB::Find(Translation *trans) {
  // lets first look for a global entry...

  trans->Global = true;
  if (FindLiteral(trans)) 
    return true;

  // hmmm. no global entry. lets look again, this time the ASID will come into play...

  trans->Global = false;
  if (FindLiteral(trans))
    return true;

  miss_count += 1;

  return false;
}

// locate tlb entry from translation key. If found, then 'fill out' (copy)
// translation info from tlb table...

bool TLB::FindLiteral(Translation *trans) {
  unsigned long long search_key = trans->TLBkey();

  if (tlbs.find(search_key) != tlbs.end()) {
    *trans = tlbs[search_key];
    hit_count += 1;
    return true;
  }

  return false;
}

// add new tlb entry. if full remove least recently used tlb entry (which is ASSUMED
// to be the oldest entry added) before adding the new entry...

void TLB::Add(Translation *trans) {
  unsigned long long add_key = trans->TLBkey();
 
  if (tlbs.find(add_key) != tlbs.end()) {
    // hmmm. already seem to have this entry. Is that good?...
    hit_count += 1;
    return;
  }

  if (((int) tlbs.size()) >= max_entries) {
    // oops! tlb table is full. remove an entry...
    tlbs.erase(tlb_order.back());
    tlb_order.pop_back(); 
    cast_out_count += 1;   
  } 

  tlbs[add_key] = *trans;
  tlb_order.push_back(add_key);
}

// remove tlb entry indexed by tlb key...

void TLB::Remove(unsigned long long tlb_key) {
  if (tlbs.find(tlb_key) != tlbs.end()) {
    tlbs.erase(tlbs.find(tlb_key));
    for (vector<unsigned long long>::iterator i = tlb_order.begin(); i != tlb_order.end(); i++) {
      if (*i == tlb_key) {
        tlb_order.erase(i);
        break;
      }
    }
  }
}

// remove tlb entry indexed by translation (key)...

void TLB::Remove(Translation &trans) {
  Remove(trans.TLBkey());
}

// Reset - flush tlb table...

void TLB::Reset() {
  tlbs.erase(tlbs.begin(),tlbs.end());
  tlb_order.erase(tlb_order.begin(),tlb_order.end());

  hit_count = 0;
  miss_count = 0;
  cast_out_count = 0;
}


//==================================================================================
// A64Descriptor...
//==================================================================================

#define DESCRIPTOR_ADDRESS_MASK 0xffffffffffffull

A64Descriptor::A64Descriptor() {
};

A64Descriptor::A64Descriptor(Memory *_memory,unsigned long long _address,int _level, int _page_size, 
                             int _stage, bool _big_endian, bool _for_test) 
: address(_address),level(_level),page_size(_page_size),stage(_stage),big_endian(_big_endian),for_test(_for_test),
  NSTable(0),APTable(0),UXNTable(0),PXNTable(0),Contiguous(0),nG(0),AF(0),SH(0),AP(0),NS(0),AttrIndx(0),
  page_offset_mask(0),output_address(0),table_address(0)
 {
  // read descriptor from memory...

  unsigned char tbuf[8];

#ifdef MMU_DEBUG
  printf("Descriptor address: 0x%llx\n",address);
#endif

  if (_memory->ReadPhysicalMemory(address,8,tbuf,false)) { 
    // throw internal error if memory not initialized...
    if (ForTest()) {
       throw GENERATION_ERROR;
    }
  }

  // apply endianness...

  _memory->ApplyEndianness(desc.dbuf,tbuf,big_endian,8,8);

#ifdef MMU_DEBUG
  if (big_endian)
    printf("Descriptor value (after big-endianness applied): 0x%016llx\n",desc.dval);
  else
    printf("Descriptor value (after little-endianness applied): 0x%016llx\n",desc.dval);
#endif

  // determine format...

  format = INVALID;
  format_is_valid = false;

  int format_bits = (int) desc.dval & 3;

  int page_size_index = -1;
  
  switch(page_size) {
    case SIZE_4K:  page_size_index = 0; break;
    case SIZE_16K: page_size_index = 1; break;
    case SIZE_64K: page_size_index = 2; break;
    default: break;
  }
  
  int format_level_combo = (level<<8) | (format_bits<<4) | page_size_index;

#ifdef MMU_DEBUG
  printf("Descriptor format: %d, level/format/page-size(index): 0x%3.3x\n",format_bits,format_level_combo);
#endif

  
  switch(format_level_combo) {
    // table descriptor at level 0 supported for all page sizes EXCEPT page 64k...

    // table descriptor at levels 1,2,3 supported for all page sizes...

    case 0x030: // level 0, table, page 4k
    case 0x130: //   "   1,      "
    case 0x230: //   "   2,      "
    case 0x330: //   "   3,      "
                format = (level == 3) ? PAGE : TABLE;
                page_offset_mask = 0xfffull;
	        break;

    case 0x031: // level 0, table, page 16k
    case 0x131: //   "   1,      "
    case 0x231: //   "   2,      "
    case 0x331: //   "   3,      "
                format = (level == 3) ? PAGE : TABLE;
                page_offset_mask = 0x3fffull;
	        break;

    case 0x132: // level 1, table, page 64k
    case 0x232: //   "   2,      "
    case 0x332: //   "   3,      "
                format = (level == 3) ? PAGE : TABLE;
                page_offset_mask = 0xffffull;
	        break;

    // no block descriptors supported at levels 0 or 3...

    // block descriptor supported at level 1 ONLY for page 4k...

    // block descriptor at level 2 supported for all page sizes...

    case 0x110: // level 1, block, page 4k
                format = BLOCK;
                page_offset_mask = (1ull<<30) - 1ull;
                break;

    case 0x210: // level 2, block, page 4k
                format = BLOCK;
                page_offset_mask = (1ull<<21) - 1ull;
                break;

    case 0x211: // level 2, block, page 16k
                format = BLOCK;
                page_offset_mask = (1ull<<25) - 1ull;
                break;

    case 0x212: // level 2, block, page 64k
                format = BLOCK;
                page_offset_mask = (1ull<<29) - 1ull;
                break;
 
    default:    // error: invalid translation table level, descriptor format, granule size combo...
#ifdef MMU_DEBUG
                printf("Fault: Invalid descriptor format for this translation level and granule size.\n");
#endif 
                if (ForTest()) {
                  throw GENERATION_ERROR;
                }
                break;
  }

  switch(format) {
    case BLOCK:  // set output address, pick off block descriptor attributes...
    case PAGE:   // at level 3, block and page are same descriptor format...
                 output_address = (desc.dval & DESCRIPTOR_ADDRESS_MASK) & ~page_offset_mask;
#ifdef MMU_DEBUG
                 printf("Block (page) descriptor, page offset mask: 0x%llx (0x%llx) output address: 0x%llx\n",
			page_offset_mask,~page_offset_mask,output_address);
#endif
                 UXNTable   = (desc.dval >> 54) & 1;
                 PXNTable   = (desc.dval >> 53) & 1;
                 Contiguous = (desc.dval >> 52) & 1; 
                 nG         = (desc.dval >> 11) & 1;
                 AF         = (desc.dval >> 10) & 1;
                 SH         = (desc.dval >> 8) & 3;
                 AP         = (desc.dval >> 6) & 3;
                 NS         = (desc.dval >> 5) & 1;
                 AttrIndx   = (desc.dval >> 1) & 7;

                 format_is_valid = true;
                 break;

    case TABLE:  // set next table address, pick off table descriptor attributes...
                 table_address = (desc.dval & DESCRIPTOR_ADDRESS_MASK) & ~page_offset_mask;
#ifdef MMU_DEBUG
                 printf("Table descriptor, page offset mask: 0x%llx next table address: 0x%llx\n",page_offset_mask,table_address);
#endif
                 if (stage == 1) {
                   NSTable  = (desc.dval >> 63) & 1;
                   APTable  = (desc.dval >> 61) & 3; // see page D4-1709
                   UXNTable = (desc.dval >> 60) & 1;
                   PXNTable = (desc.dval >> 59) & 1;
		 }

                 format_is_valid = true;
                 break;

    default:     // throw internal error if invalid format...
#ifdef MMU_DEBUG
                 printf("Fault: Invalid descriptor format!!!\n");
#endif 
                 if (ForTest()) {
                   throw GENERATION_ERROR;
                 }
                 break;
  }
};

ostream& operator<< (std::ostream &os, A64Descriptor &dsc) {
   os << "  Descriptor:\n";
   switch(dsc.format) {
     case TABLE:   os << "    type: TABLE\n";   break;
     case BLOCK:   os << "    type: BLOCK\n";   break;
     case PAGE:    os << "    type: PAGE\n";    break;
     default:      os << "    type: INVALID!!! (other descriptor values reported may be BOGUS!)\n"; break;
   }
   os << "   descriptor address: 0x" << std::hex << dsc.address << std::dec << "\n";
   os << "   descriptor value: 0x" << std::hex << dsc.desc.dval << std::dec << " big endian? " << dsc.big_endian << "\n";
   os << "   table address: 0x" << std::hex << dsc.TableAddress() << std::dec << "\n";
   os << "   output address: 0x" << std::hex << dsc.OutputAddress() << std::dec << "\n";
   os << "   page offset mask: 0x" << std::hex << dsc.PageOffsetMask() << std::dec << "\n";
   
   os << "   level:      " << dsc.level << "\n";
   os << "   NSTable:    " << std::hex << dsc.NSTable << std::dec << "\n";
   os << "   APTable:    " << std::hex << dsc.APTable << std::dec << "\n";
   os << "   UXNTable:   " << std::hex << dsc.UXNTable << std::dec << "\n";
   os << "   PXNTable:   " << std::hex << dsc.PXNTable << std::dec << "\n";
   os << "   Contiguous: " << std::hex << dsc.Contiguous << std::dec << "\n";
   os << "   nG:         " << std::hex << dsc.nG << std::dec << "\n";
   os << "   AF:         " << std::hex << dsc.AF << std::dec << "\n";
   os << "   SH:         " << std::hex << dsc.SH << std::dec << "\n";
   os << "   AP:         " << std::hex << dsc.AP << std::dec << "\n";
   os << "   NS:         " << std::hex << dsc.NS << std::dec << "\n";
   os << "   AttrIndx:   " << std::hex << dsc.AttrIndx << std::dec << "\n";

   return os;
}


//==================================================================================
// A64 VMSA...
//==================================================================================

A64_VMSA::A64_VMSA(State *_cpu,Memory *_memory,Packet *_packet, TLB *_itlb,TLB *_dtlb,A64SimMonitor *_monitor) 
: cpu(_cpu),memory(_memory),packet(_packet),itlb(_itlb),dtlb(_dtlb),monitor(_monitor) {

  //assert(_monitor != NULL);
}

bool A64_VMSA::Enabled() {
  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1: return cpu->SCTLR_EL1.M()==1; break;
    case 2: return cpu->SCTLR_EL2.M()==1; break;
    case 3: return cpu->SCTLR_EL3.M()==1; break;
    default: throw INTERNAL_ERROR; break;
  }
}

bool A64_VMSA::ForTest() {
  return packet->ForTest();
}

bool A64_VMSA::Privileged() {
  return cpu->Pstate.EL() > 0;
}

unsigned int A64_VMSA::ASID() {
  unsigned int asid;
  
  if (cpu->Pstate.EL()==EL0 || cpu->Pstate.EL()==EL1) {
    if (cpu->TCR_EL1.AS() == 0)
       asid = cpu->TTBR0_EL1.ASID();
    else
       asid = cpu->TTBR1_EL1.ASID();
  }
  else
    asid = 0; // no ASID field for EL2 or EL3

  return asid;
}

bool A64_VMSA::BigEndian() {
  //printf("[A64_VMSA::BigEndian] EL: %d SCTLR/EE/E0E: %d/%d\n",cpu->Pstate.EL(),cpu->SCTLR_EL1.EE(),cpu->SCTLR_EL1.E0E());

  bool endianness = false; //<--assume little endianness...

  switch((int) cpu->Pstate.EL()) {
    case 0: endianness = cpu->SCTLR_EL1.E0E()==1; break;
    case 1: endianness = cpu->SCTLR_EL1.EE()==1;  break;
    case 2: endianness = cpu->SCTLR_EL2.EE()==1;  break;
    case 3: endianness = cpu->SCTLR_EL3.EE()==1;  break;
    default: throw INTERNAL_ERROR; break;
  }

  return endianness;
}

void A64_VMSA::MemoryAttributes(int &mem_type,int &device_type,struct AttrXcacheHints &cache_hints, int attr_index) {
  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1: cpu->MAIR_EL1.Attributes(mem_type,device_type,cache_hints,attr_index); break;
    case 2: cpu->MAIR_EL2.Attributes(mem_type,device_type,cache_hints,attr_index); break;
    case 3: cpu->MAIR_EL3.Attributes(mem_type,device_type,cache_hints,attr_index); break;
    default: throw INTERNAL_ERROR; break;
  }
}

bool A64_VMSA::Cacheable(bool is_data) {
  bool cacheable = false;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1: cacheable = is_data ? cpu->SCTLR_EL1.C()==1 : cpu->SCTLR_EL1.I()==1; break;
    case 2: cacheable = is_data ? cpu->SCTLR_EL1.C()==1 : cpu->SCTLR_EL2.I()==1; break;
    case 3: cacheable = is_data ? cpu->SCTLR_EL1.C()==1 : cpu->SCTLR_EL3.I()==1; break;
    default: throw INTERNAL_ERROR; break;
  }

  return cacheable;
}

int A64_VMSA::InputAddressSize(unsigned long long LA) { // input address size - see p 1716
  int region_size = 64;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1:  {
              bool tbi_set = false;
              AddrTop(tbi_set,LA);
              region_size = region_size - (tbi_set ? cpu->TCR_EL1.T1SZ() : cpu->TCR_EL1.T0SZ());
             }
             break;
    case 2:  throw INTERNAL_ERROR;
             //region_size = region_size - cpu->TCR_EL2.T0SZ(); 
             break;
    case 3:  region_size = region_size - cpu->TCR_EL3.T0SZ(); 
             break;
    default: throw INTERNAL_ERROR; 
             break;
  }

  return region_size;
}

// physical address size implemented: AA64MMFR0_EL1.PARange()
// physical address size programmed: TCR.PS

// all translation base addresses, table entry addresses must conform to this size
// if address translation disabled then all address sizes must conform to this size

int A64_VMSA::PAMax() {
  return cpu->ID_AA64MMFR0_EL1.physical_memory_size_in_bits();
}

int A64_VMSA::OutputAddressSize() { // used to check that tt entries have address bits above PA size set to zero
  int pa_size = 32;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1: pa_size = cpu->TCR_EL1.physical_memory_size_in_bits(); break;
    case 2: pa_size = cpu->TCR_EL2.physical_memory_size_in_bits();  break;
    case 3: pa_size = cpu->TCR_EL3.physical_memory_size_in_bits();  break;
    default: throw INTERNAL_ERROR; break;
  }

  return pa_size;
}

bool A64_VMSA::ValidatePhysicalAddress(unsigned long long PA, bool translation_enabled) {
  //return true;  // we don't have a physical memory map defined, so anything goes...
  
  int pa_size_implemented = PAMax(); // # of address bits implemented

  int pa_size_allowed = translation_enabled ? OutputAddressSize() : pa_size_implemented; // programmed # of address bits

  unsigned long long allowed_pa_mask = ~( (1ull<<pa_size_allowed) - 1 );

#ifdef MMU_DEBUG
  printf("[A64_VMSA::ValidatePhysicalAddress] pa size: %d, allowed pa mask: 0x%llx\n",pa_size_implemented,allowed_pa_mask);
#endif

#ifdef IGNORE_UPPER_PA_BITS
  // will resolve when physical memory is accessed... 
  return true;
#endif
  
  // # of programmed address bits must always be equal to or less than the # of address bits implemented AND
  // the input physical address must not exceed the programmed addresss size...

  return (pa_size_allowed <= pa_size_implemented) && ((PA & allowed_pa_mask) == 0ull); 
}

bool A64_VMSA::AlignmentChecksEnabled() {
  bool checks_enabled = false;
  
  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1: checks_enabled = cpu->SCTLR_EL1.A(); break;
    case 2: checks_enabled = cpu->SCTLR_EL2.A(); break;
    case 3: checks_enabled = cpu->SCTLR_EL3.A(); break;
    default: throw INTERNAL_ERROR; 
             break;
  }
  
  return checks_enabled;
}

int A64_VMSA::PageSize(unsigned long long LA) { // Granule size
  int page_size = -1;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1:
#ifdef MMU_DEBUG
             printf("[PageSize] TCR_EL1.TG1: %u, TCR_EL1.TG0: %u\n",cpu->TCR_EL1.TG1(),cpu->TCR_EL1.TG0());
#endif
	     if (HIGH_ADDRESS_RANGE(LA)) {
	       // page-size as encoded in TCR_EL1.TG1 is different from TCR_ELx.TG0...
               if (cpu->TCR_EL1.TG1() == 2) page_size = 0;
	       else if (cpu->TCR_EL1.TG1() == 3) page_size = 1;
	       else page_size = 2;
	     } else {
               page_size = cpu->TCR_EL1.TG0();
	     }
             break;
    case 2:
#ifdef MMU_DEBUG
             printf("[PageSize] TCR_EL2.TG1: %u\n",cpu->TCR_EL2.TG0());
#endif
             page_size = cpu->TCR_EL2.TG0(); break;
    case 3:
#ifdef MMU_DEBUG
             printf("[PageSize] TCR_EL3.TG1: %u\n",cpu->TCR_EL3.TG0());
#endif
             page_size = cpu->TCR_EL3.TG0(); break;
    default: throw INTERNAL_ERROR; 
             break;
  }
  
  return page_size;
}

bool A64_VMSA::TranslationTableIsValid(unsigned long long LA) {
  bool is_valid = false;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1:  is_valid = HIGH_ADDRESS_RANGE(LA) ? (cpu->TCR_EL1.EPD1()==0) : (cpu->TCR_EL1.EPD0()==0); 
             break;
    case 2:
    case 3:  is_valid = true; 
             break;
    default: throw INTERNAL_ERROR; 
             break;
  }

  return is_valid;
}

unsigned long long A64_VMSA::TTBaseAddress(unsigned long long LA, bool stage2) {
  unsigned long long ttb_base_addr;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1:  ttb_base_addr = HIGH_ADDRESS_RANGE(LA) ? cpu->TTBR1_EL1.baseAddress() : cpu->TTBR0_EL1.baseAddress(); 
             break;
    case 2:  throw INTERNAL_ERROR;
             //ttb_base_addr = stage2 ? cpu->VTCR_EL2.BADDR() : cpu->TTBR0_EL2.BADDR(); 
             break;
    case 3:  ttb_base_addr = cpu->TTBR0_EL3.baseAddress(); 
             break;
    default: throw INTERNAL_ERROR; 
             break;
  }

  return ttb_base_addr;
}

unsigned int A64_VMSA::TnSZ(unsigned long long LA) {
  unsigned int TnSZ = 0;

  switch((int) cpu->Pstate.EL()) {
    case 0:
    case 1:
#ifdef MMU_DEBUG
      printf("TCR_EL1.T1SZ: %u, TCR_EL1.T0SZ: %u\n",cpu->TCR_EL1.T1SZ(),cpu->TCR_EL1.T0SZ());
#endif 
             TnSZ = HIGH_ADDRESS_RANGE(LA) ? cpu->TCR_EL1.T1SZ() : cpu->TCR_EL1.T0SZ();
             break;
    case 2:  throw INTERNAL_ERROR;
             // TnSZ = cpu->TCR_EL2.T0SZ();
             break;
    case 3:
#ifdef MMU_DEBUG
             printf("TCR_EL3.T1SZ: %u\n",cpu->TCR_EL1.T0SZ());
#endif 
             TnSZ = cpu->TCR_EL3.T0SZ();
             break;
    default: throw INTERNAL_ERROR; 
             break;
  }

  return TnSZ;
}

int A64_VMSA::InitialLevelLookup(unsigned long long LA, int page_size) {
#ifdef MMU_DEBUG
  switch(page_size) {
    case SIZE_4K:  printf("[InitialLevelLookup] LA: 0x%llx, page size: 4K\n",LA);  break;
    case SIZE_16K: printf("[InitialLevelLookup] LA: 0x%llx, page size: 16K\n",LA); break;
    case SIZE_64K: printf("[InitialLevelLookup] LA: 0x%llx, page size: 64\n",LA);  break;
    default: break;
  }
#endif 

  // see section D4.2.5...
  unsigned int tnsz = TnSZ(LA);

#ifdef MMU_DEBUG
  printf("InitialLevelLookup: tnsz: %u\n", tnsz);
#endif 

  int level = -1;

  switch(page_size) {
    case SIZE_4K:
                   if (tnsz < 16) {
                     level = 0;
                   } else if (tnsz <= 24) 
                     level = 0;
                   else if (tnsz <= 33) 
                     level = 1;
                   else
                     level = 2;
		   // level = 3; // no level 3 possible with 4k
                   break;

    case SIZE_16K: if (tnsz <= 16)
		     level = 0;
		   else if (tnsz <= 27)
                     level = 1;
                   else if (tnsz <= 39)
                     level = 2;
                   else
                     level = 3;
                   break;

    case SIZE_64K: if (tnsz <= 21)
		     level = 1;  // no level 0 possible with 64k
		   else if (tnsz <= 34)
                     level = 2;
                   else
                     level = 3;
                   break;

    default:       // invalid page size...
                   break;
  }

  return level;
}


//AddrTop - p1708 - determines whether or not top 8 bit of address are ignored insofar as faults are concerned

// translation fault - vmsa enabled
// address size fault - vmsa NOT enabled

int A64_VMSA::AddrTop(bool &tbi, unsigned long long LA) {
  tbi = false;
  
  if (cpu->UsingAArch32() && !(cpu->Pstate.EL()==EL0 && !cpu->ELUsingAArch32(EL1))) {
    tbi = true;
    return 31;
  }
  
  switch((int) cpu->Pstate.EL()) {
    case EL0:
    case EL1: tbi = ((LA>>55) & 1)==1 ? cpu->TCR_EL1.TBI1()==1 : cpu->TCR_EL1.TBI0()==1; break;
      
    case EL2: tbi = cpu->TCR_EL2.TBI()==1; break;
    case EL3: tbi = cpu->TCR_EL3.TBI()==1; break;
      
    default: throw INTERNAL_ERROR;
  }
  
  return tbi==1 ? 55 : 63;
}

bool A64_VMSA::IsZero(unsigned long long LA,int topBit) {
  bool check_top_bits = ((LA>>topBit)&1) == 1;
  
  bool top_bits_set = TOP_BITS(LA) == 0ull;

  return !(check_top_bits && top_bits_set);
}

//  int pasize = cpu->AA64MMFR0_EL1.physical_memory_size_in_bits(); 1715

// address size configuration - p 1715

// virtual address - p1712
// controlling address translation stages - p1713

bool A64_VMSA::AddressTagEnabled(unsigned long long LA) {
  return false;
}


//***************************************************************************************************************
// LA2PA...
//***************************************************************************************************************

Translation *A64_VMSA::LA2PA(unsigned long long LA,bool NS,bool privileged, bool is_data, bool wasaligned, int size, bool is_write) {
#ifdef MMU_DEBUG
  int ia_size = InputAddressSize(LA);

  printf("[A64_VMSA::LA2PA] entered, input addr size: %d, LA: 0x%llx NS: %d privileged? %d is_data? %d aligned? %d size: %d is_write? %d MMU on? %d\n",
         ia_size,LA,NS,privileged,is_data,wasaligned,size,is_write,Enabled());
  fflush(stdout);
#endif
  // before anything else, allow some external agent a chance to map logical memory...

#ifndef SKIP_USER_SPACE
  if (!UserSpace::MapAddress(cpu,packet,memory,LA,is_data,privileged,is_write,size)) {
    throw INTERNAL_ERROR;
  }
#endif
  
  // create 'starter' translation...
  bool trans_endian = is_data ? BigEndian() : false; // endianness insofar as a translation goes is only relevent for data...
  Translation *trans = new Translation(LA,ASID(),privileged,NS,is_data,wasaligned,size,is_write,trans_endian);

  // complete translation...

  // no tlb table unless mmu is enabled...
  
#ifdef USE_TLB
  TLB *tlb = Enabled() ? (tlb = trans->is_data ? dtlb : itlb) : NULL;
  bool have_tlb_entry = (tlb != NULL) && tlb->Find(trans); // if found, then the transaction will be updated from TLB entry...
#else
  TLB *tlb = NULL;
  bool have_tlb_entry = false;
#endif
  
  if (have_tlb_entry) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::LA2PA] tlb entry is there, translation updated from TLB entry...\n");
    // but still need to fix final PA...
#endif
    trans->LA2PA(LA);
  } else {
    // NOTE: we got here cause no tlb entry was there. mmu may not be enabled!
    // full translation which may include table walk...
#ifdef MMU_DEBUG
    printf("[A64_VMSA::LA2PA] no tlb entry, creating new translation...\n");
#endif
    FullTranslate(trans);
  }

  if (tlb && !have_tlb_entry) tlb->Add(trans); // update tlb table from translation...

  packet->translations.push_back(trans); //<---REALLY SHOULD UPDATE TLB TABLE WHEN PACKET 'COMMIT' HAPPENS!!!

  // check this access against the translation access permissions, etc...

#ifdef MMU_DEBUG
    std::cout << "[A64_VMSA::LA2PA] checking alignment..." << endl;
#endif  
  CheckAlignment(trans);
#ifdef MMU_DEBUG
    std::cout << "[A64_VMSA::LA2PA] checking permissions..." << endl;
#endif  
  CheckPermissions(trans); 
#ifdef MMU_DEBUG
    std::cout << "[A64_VMSA::LA2PA] checking instruction access..." << endl;
#endif  
  CheckInstructionAccess(trans);

#ifdef MMU_DEBUG
  if (trans->mmu_enabled) {
    std::cout << "[A64_VMSA::LA2PA] exited, translation:" << *trans << endl;
  }
  std::cout << "[A64_VMSA::LA2PA] exited, LA: 0x" << std::hex << trans->PA << " PA: 0x" << trans->PA << std::dec << endl;
#endif

  return trans;
}


void A64_VMSA::FullTranslate(Translation *trans) {
  FirstStageTranslate(trans);

  if (cpu->HaveEL(EL2) && !cpu->IsSecure() && cpu->Pstate.EL() != EL2) {
    SecondStageTranslate(trans,false /*s2fs1walk=false*/);
  }
}

void A64_VMSA::FirstStageTranslate(Translation *S1) {
  S1->mmu_enabled     = Enabled();
  S1->IPA             = 0;
  S1->secondstage     = false;   
  S1->permissioncheck = true;
  S1->s1_enabled      = true;

  bool tbi_set;
  S1->topBit = AddrTop(tbi_set,S1->LA); // top bit index - record whether or not mmu is enabled 
  S1->tbi = tbi_set;
  
  if (S1->mmu_enabled) // 1st stage enabled...
    TranslationTableWalk(S1);
  else {
    TranslateAddressS1Off(S1);
    S1->permissioncheck = false;
  }

  // moved to LA2PA to account for possible TLB (translation) entry...
/*
  CheckAlignment(S1);
  CheckPermissions(S1); 
  CheckInstructionAccess(S1);
*/
}

void A64_VMSA::SecondStageTranslate(Translation *S1, bool s2fs1walk) {
  throw INTERNAL_ERROR;
    //trans->s2_enabled = true;
}


// check for unaligned data access to device memory...
void A64_VMSA::CheckAlignment(Translation *S1) {
#ifdef MMU_DEBUG
  printf("[A64_VMSA::CheckAlignment] aligned? %d, device-memory? %d, data? %d, alignment-checks enabled?: %d, address: 0x%llx\n",
         S1->wasaligned, (S1->memory_type == DEVICE_MEMORY), S1->is_data, AlignmentChecksEnabled(), S1->LA);
#endif
  
  // check mis-aligned data accesses if device-memory or alignment-checks are currently enabled...
  
  if (S1->is_data && !S1->wasaligned && ( S1->memory_type == DEVICE_MEMORY || AlignmentChecksEnabled() ) ) {
    // alignment fault...
#ifdef MMU_DEBUG
    printf("[A64_VMSA::CheckAlignment] DATA-ABORT/ALIGNMENT, ADDRESS: 0x%llx\n",S1->LA);
#endif
    packet->recordExceptionCondition(DATA_ABORT,ALIGNMENT);
    throw ARCH_EXCEPTION;
  }
}

// check S1 permissions,level,pa,NS...
void A64_VMSA::CheckPermissions(Translation *S1) {
  if (!S1->permissioncheck) return;

  // check AF (access flag). throw exception if not set...

  bool access_flag_fault = S1->AF == 0;

  if (access_flag_fault) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::CheckPermissions] access flag fault!\n");
#endif
    packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
    throw ARCH_EXCEPTION;
  }

  // if data or (armv8) instruction: check read permissions (unprivileged or privileged)...

  bool read_permission_fail = /* S1->is_data && */ !S1->is_write && ( (Privileged() && !S1->readPrivileged) || (!Privileged() && !S1->readUnprivileged) );

  if (read_permission_fail) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::CheckPermissions] read permissions!\n");
#endif
    packet->recordExceptionCondition(DATA_ABORT,READ_PERMISSIONS);
    throw ARCH_EXCEPTION;
  }

  // if data: check write permissions (unprivileged or privileged)...

  bool write_permission_fail = S1->is_data && S1->is_write && ( (Privileged() && !S1->writePrivileged) || (!Privileged() && !S1->writeUnprivileged) );

  if (write_permission_fail) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::CheckPermissions] write permissions!\n");
#endif
    packet->recordExceptionCondition(DATA_ABORT,WRITE_PERMISSIONS);
    throw ARCH_EXCEPTION;
  }

  // instruction fetch to execute-never region?...

#ifdef KERNEL_DEBUG
  bool execute_never_fail = false;
#else
  bool execute_never_fail = !S1->is_data && ( (Privileged() && S1->PXN) || (!Privileged() && S1->XN) );
#endif

  if (S1->is_data) {
    // not instruction access...
  } else if (cpu->Pstate.EL()==EL0) {
    execute_never_fail = S1->XN;       // UXN at EL0
  } else if (cpu->Pstate.EL()==EL1) {
    execute_never_fail = S1->PXN;      // PXN affects only EL1
  } else {
    execute_never_fail = S1->XN;       // XN bit applies to EL2,EL3
  }
  
  if (execute_never_fail) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::CheckPermissions] EXECUTE NEVER (REGION) FAIL???\n");
#endif
    packet->recordExceptionCondition(INSTRUCTION_ABORT,EXECUTE_NEVER);
    throw ARCH_EXCEPTION;
  }

  // restrictions on secure instruction fetch from non-secure memory?...

  if (cpu->HaveEL(EL3) && cpu->IsSecure() && S1->NS && cpu->SCR_EL3.SIF()==1)
      execute_never_fail = true;

  if (execute_never_fail) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::CheckPermissions] EXECUTE NEVER (NON-SECURE) FAIL???\n");
#endif
    packet->recordExceptionCondition(INSTRUCTION_ABORT,SECURE_INSTRUCTION_FETCH);
    throw ARCH_EXCEPTION;
  }
}

// check for instruction fetches from device memory not marked as execute-never... MMU MAY NOT BE ENABLED...
void A64_VMSA::CheckInstructionAccess(Translation *S1) {
  if (S1->memory_type != DEVICE_MEMORY || S1->is_data)
    return;

    // do something...not sure there is anything to do...
}


// call for stage 1 translation when translation is disabled...
void A64_VMSA::TranslateAddressS1Off(Translation *S1) {
  bool tbi_set;
  S1->topBit = AddrTop(tbi_set,S1->LA); // top bit index
  S1->tbi = tbi_set;

#ifdef MMU_DEBUG
  printf("[A64_VMSA::TranslateAddressS1Off] top-bit: %d, tbi: %d\n",S1->topBit,S1->tbi);
#endif
  
  if (!IsZero(S1->LA,S1->topBit)) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::TranslateAddressS1Off] bits at or above top bit are non-zero, ie, no 'extended' addressing when MMU disabled...\n");
#endif
    S1->level = 0;
    S1->secondstage = false;
    AddressSizeFault(S1); 
  }

  if (cpu->HaveEL(EL2) && !cpu->IsSecure() && (cpu->Pstate.EL() == EL0 || cpu->Pstate.EL() == EL1) 
      && (cpu->HCR_EL2.DC() == 1) ) {
    S1->memory_type          = NORMAL_MEMORY;
    S1->device_type          = DEVICETYPE_UNKNOWN;
    S1->inner_cache_type     = MEMATTR_WB;
    S1->inner_transient      = false;
    S1->inner_read_allocate  = true;
    S1->inner_write_allocate = true;
    S1->innershareable       = false;
    S1->outershareable       = false;
    if (cpu->HCR_EL2.VM() != 1) { // EL2 default cacheability unpredictable when EL2 translation disabled...
      S1->unpredictable = true;
      packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
      throw ARCH_EXCEPTION;
    }
  } else if (S1->is_data) {
    // data access...
    S1->memory_type      = DEVICE_MEMORY;
    S1->device_type      = DEVICETYPE_nGnRnE;
    S1->inner_cache_type = MEMATTR_UNKNOWN;
    S1->innershareable   = true;  // false???
    S1->outershareable   = true;
  } else {
    // instruction access...
    bool cacheable = Cacheable(false);
    S1->memory_type = NORMAL_MEMORY;
    S1->device_type = DEVICETYPE_UNKNOWN;
    if (cacheable) {
      S1->inner_cache_type     = MEMATTR_WT;
      S1->inner_transient      = false;
      S1->inner_read_allocate  = true;
      S1->inner_write_allocate = false;
    } else {
      S1->inner_cache_type = MEMATTR_NONCACHEABLE;
    }
    S1->innershareable = true;
    S1->outershareable = true;
  }

  S1->outer_cache_type     = S1->inner_cache_type;
  S1->outer_transient      = S1->inner_transient; 
  S1->outer_read_allocate  = S1->inner_read_allocate;
  S1->outer_write_allocate = S1->inner_write_allocate;

  S1->readUnprivileged  = true;    //
  S1->writeUnprivileged = true;    //
  S1->readPrivileged    = true;    //
  S1->writePrivileged   = true;    // translation
  S1->XN  = 0;                     //   is disabled,
  S1->PXN = 0;                     //     so perms not enforced...
  
  S1->PA = S1->LA;       // NOPE: as of yet there is no physical address map, so don't strip LA and hope for the best... SANS_HIGH_ADDRESS_BITS(S1->LA);
  S1->NS = cpu->IsSecure() ? 0 : 1;

  if (!ValidatePhysicalAddress(S1->PA,false)) {
#ifdef MMU_DEBUG
    printf("[A64_VMSA::TranslateAddressS1Off] invalid physical address...\n");
#endif
    packet->recordExceptionCondition(ADDRESS_SPACE_ERROR);
    throw ARCH_EXCEPTION;
  }
}

void A64_VMSA::AddressSizeFault(Translation *S1) {
  // DUDE, ADDRESS SIZE FAULT!!!
}


//***************************************************************************************************************
// TranslationTableWalk
//
// 48 bit pa, 4k page size - see p1718
//  512 entries per translation table - mask is 0x1ff
//  9 address bits resolved in one level of lookup
//  page offset: bits 11:0
//***************************************************************************************************************

unsigned long long A64_VMSA::TableIndex(unsigned long long LA, int level, int page_size) {
  int level_address_bits_lo = 0;
  unsigned long long level_index_mask = 0;

#ifdef MMU_DEBUG
  std::string psize = "?";
#endif

  switch(page_size) {
    case SIZE_4K:  switch(level) {
                     case 0: level_address_bits_lo = 39; level_index_mask = 0x1ff; break; // each level resolves 9 bits
		     case 1: level_address_bits_lo = 30; level_index_mask = 0x1ff; break;
		     case 2: level_address_bits_lo = 21; level_index_mask = 0x1ff; break;
		     case 3: level_address_bits_lo = 12; level_index_mask = 0x1ff; break;
		     default: break;
                   }
#ifdef MMU_DEBUG
                   psize = "4k";
#endif
		   break;

    case SIZE_16K: switch(level) {
		     case 0: level_address_bits_lo = 47; level_index_mask = 0x1;   break; // only two entries 
		     case 1: level_address_bits_lo = 36; level_index_mask = 0x7ff; break; // each successive level resolves 11 bits
		     case 2: level_address_bits_lo = 25; level_index_mask = 0x7ff; break;
		     case 3: level_address_bits_lo = 14; level_index_mask = 0x7ff; break;
		     default: break;
                   }
#ifdef MMU_DEBUG
                   psize = "16k";
#endif
		   break;

    case SIZE_64K: switch(level) {
		     case 1: level_address_bits_lo = 42; level_index_mask = 0x3f;   break; // seven bits max level 0 assuming 48 bit address
		     case 2: level_address_bits_lo = 29; level_index_mask = 0x1fff; break; // each successive level resolves 13 bits
		     case 3: level_address_bits_lo = 16; level_index_mask = 0x1fff; break;
		     default: break;
                   }
#ifdef MMU_DEBUG
                   psize = "64k";
#endif
		   break;

    default:       // invalid page size...
                   break;
  }

  unsigned long long table_index = (LA>>level_address_bits_lo) & level_index_mask;

#ifdef MMU_DEBUG
                   printf("   for address 0x%llx, level %d, %s page size: address bits lo: %d table-index: 0x%llx\n",
                          LA,level,psize.c_str(),level_address_bits_lo,table_index);
#endif

  return table_index;
}

//***************************************************************************************************************
// TranslationTableWalk
//***************************************************************************************************************

void A64_VMSA::TranslationTableWalk(Translation *S1) {
#ifdef MMU_DEBUG
  printf("[A64_VMSA::TranslationTableWalk] entered, LA: 0x%llx\n",S1->LA);
#endif

  unsigned long long table_base_address = TTBaseAddress(S1->LA); //<---table base is a physical address

  S1->ttb_base_address = table_base_address;

#ifdef MMU_DEBUG
  printf("   page table base address: 0x%llx\n",table_base_address);
#endif

  if (!TranslationTableIsValid(S1->LA)) {
    packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
    throw ARCH_EXCEPTION; 
  }

#ifdef MMU_DEBUG
  printf("   valid translation table...\n");
#endif

  if (!ValidatePhysicalAddress(table_base_address,true)) {
    packet->recordExceptionCondition(ADDRESS_SPACE_ERROR);
    throw ARCH_EXCEPTION;
  }

#ifdef MMU_DEBUG
  printf("   translation table physical address is valid...\n");
#endif

  bool have_pa = false;

#ifdef MMU_DEBUG
  printf("   page size: %d...\n,",PageSize(S1->LA));
#endif

  // 0, 1, 2, or 3 levels of descriptors...

  int initial_level = InitialLevelLookup(S1->LA, PageSize(S1->LA));

#ifdef MMU_DEBUG
  printf("   initial level: %d\n",initial_level);
#endif

  if (initial_level < 0) {
    packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
    throw ARCH_EXCEPTION; 
  }

#ifdef MMU_DEBUG
    printf("   initial level is valid...\n");
#endif

  for (int i = initial_level; i <= 3 && !have_pa; i++) {
     unsigned long long table_index = TableIndex(S1->LA,i,PageSize(S1->LA));

     unsigned long long descriptor_address = table_base_address + (table_index<<3); //<---descriptor address is dword aligned 

#ifdef MMU_DEBUG
     printf("   for level %d, table-index: 0x%llx, descriptor address: 0x%llx\n",i,table_index,descriptor_address);
#endif

     if (!ValidatePhysicalAddress(descriptor_address,true)) {
       packet->recordExceptionCondition(ADDRESS_SPACE_ERROR);
       throw ARCH_EXCEPTION;
     }

     A64Descriptor desc(memory,descriptor_address,i,PageSize(S1->LA),1,BigEndian(),ForTest()); //reads descriptor from memory, then decodes same...

     S1->descriptors[S1->levels] = desc; //<---translation will include copies of all descriptors accessed...

     S1->levels += 1;

#ifdef MMU_DEBUG
     std::cout << "Descriptor: " << desc << std::endl;
#endif

     if (desc.Invalid()) {
#ifdef MMU_DEBUG
       printf("OOPS! invalid descriptor format: bad format or illegal for this level...\n");
#endif
      packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
      throw ARCH_EXCEPTION; 
     }

     if (desc.Table()) {
        // table address for next level lookup...
        table_base_address = desc.TableAddress();
	// pick off memory attributes from the descriptor...
        GetTableAttributes(S1,desc);
        continue;
     }

     // not an invalid descriptor, and not the address of next table, thus this descriptor terminates the walk...
     // cool, can map the address...
     
#ifdef MMU_DEBUG
     printf("[A64_VMSA::TranslationTableWalk] level %d page offset mask: 0x%llx, la offset: 0x%llx\n",i,
            desc.PageOffsetMask(),(S1->LA & desc.PageOffsetMask())); 
#endif

     S1->PA = desc.OutputAddress() | (S1->LA & desc.PageOffsetMask());

     S1->base_address     = desc.OutputAddress();   // use for other translations within
     S1->page_offset_mask = desc.PageOffsetMask();  //   this translations address space...

     S1->blocksize = desc.BlockSize();
     
     S1->valid = true;                              // valid once we can actually map the address

#ifdef MMU_DEBUG
     printf("[A64_VMSA::TranslationTableWalk] descriptor appears to be valid...\n");
#endif
     
     // pick off memory attributes from the descriptor...

     GetBlockPageAttributes(S1,desc);

#ifdef MMU_DEBUG
     printf("[A64_VMSA::TranslationTableWalk] have block/page attributes...\n");
#endif

     // if translation involves a descriptor with non-global bit set, then ASSUME entire translation is non-global...

     if (desc.nG)
       S1->Global = false;   

     have_pa = true;

     if (!ValidatePhysicalAddress(S1->PA,true)) {
       packet->recordExceptionCondition(ADDRESS_SPACE_ERROR);
       throw ARCH_EXCEPTION;
     }

#ifdef MMU_DEBUG
     printf("[A64_VMSA::TranslationTableWalk] we have a valid translation...\n");
#endif

     S1->valid = true; // if we got here then we have a valid translation
  }

#ifdef MMU_DEBUG
  printf("[A64_VMSA::TranslationTableWalk] exited, LA: 0x%llx\n",S1->LA);
  std::cout << (*S1) << std::endl;
#endif
}

void A64_VMSA::GetTableAttributes(Translation *S1,A64Descriptor &desc) {
  // non-secure table d4-1706 (table is in secure/non-secure address space)
  // a table with NS set sticks, ie, subsequent accesses are also non-secure
  // a table with NS set is non-global, ie, nG bit is ignored

  if (desc.NSTable) 
     S1->NS = true;

  // desc.APTable - access permissions limit d4-1709 (AP[0] SBZ at EL3)
 
  switch((int) desc.APTable) {
    case 0:  // == 0 - no effect on permissions
             break;
    case 1:  // == 1 - no access at EL0
             S1->readUnprivileged  = false;
             S1->writeUnprivileged = false;
             break;
    case 2:  // == 2 - write access not permission at any level
             S1->writeUnprivileged = false;
             S1->writePrivileged   = false;
             break;
    case 3:  // == 3 - write access not permission at any level
             //      - no read access at EL0
             S1->readUnprivileged  = false;
             S1->writeUnprivileged = false;
             S1->writePrivileged   = false;
             break;
    default: throw INTERNAL_ERROR;
             break;
  }
 
  // desc.UXNTable - execute-never limit d4-1712 - sticks

  if (cpu->Pstate.EL()==EL0 && desc.UXNTable)
    S1->XN = true;
  
  // desc.PXNTable - privileged execute never limit d4-1712 (SBZ at EL2,EL3) - sticks

}

void A64_VMSA::GetBlockPageAttributes(Translation *S1,A64Descriptor &desc) {
  if (cpu->Pstate.EL()==EL0 && desc.UXNTable)
    S1->XN = true;
  
  if (cpu->Pstate.EL()==EL1 && desc.PXNTable)
    S1->PXN = true;
  
  S1->Contiguous = desc.Contiguous;
  
  S1->nG = desc.nG;
  S1->AF = desc.AF; // will cause fault if descriptor AF is 0 and this translation is not in the TLB...

  if (desc.NS)
    S1->NS = desc.NS;

  S1->innershareable = false; 
  S1->outershareable = false; 

  switch((int) desc.SH) {
    case 0: break;
    case 2: S1->outershareable = true; break;
    case 3: S1->innershareable = true; break;
    default: // unpredictable...
#ifdef MMU_DEBUG
             printf("[A64_VMSA::GetBlockPageAttributes] unpredictable cache attributes...\n");
#endif
             packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
             throw ARCH_EXCEPTION;
             break;
  }

  S1->readUnprivileged  = false;
  S1->writeUnprivileged = false;
  S1->readPrivileged    = false;
  S1->writePrivileged   = false;

  switch((int) desc.AP) {
    case 0:  S1->readPrivileged  = true;
             S1->writePrivileged = true;
  	     break;
    case 1:  S1->readPrivileged    = true;
             S1->writePrivileged   = true;
             S1->readUnprivileged  = true;
             S1->writeUnprivileged = true;
	     break;
    case 2:  S1->readPrivileged  = true;
             break;
    case 3:  S1->readPrivileged    = true;
             S1->readUnprivileged  = true;
             break;
    default: // no permissions???
#ifdef MMU_DEBUG
             printf("[A64_VMSA::GetBlockPageAttributes] no access permissions?...\n");
#endif
             packet->recordExceptionCondition(S1->is_data ? DATA_ABORT : INSTRUCTION_ABORT);
             throw ARCH_EXCEPTION;
             break;
  }

  struct AttrXcacheHints cache_hints;

  MemoryAttributes(S1->memory_type,S1->device_type,cache_hints,desc.AttrIndx);

#ifdef MMU_DEBUG
  printf("[A64_VMSA::GetBlockPageAttributes] have memory attributes...\n");
#endif
  
  S1->outer_cache_type     = cache_hints.outer_cache_type;     // 
  S1->outer_transient      = cache_hints.outer_transient;      // outer cache attributes
  S1->outer_read_allocate  = cache_hints.outer_read_allocate;  //
  S1->outer_write_allocate = cache_hints.outer_write_allocate; //

  S1->inner_cache_type     = cache_hints.inner_cache_type;     //
  S1->inner_transient      = cache_hints.inner_transient;      // inner cache attributes
  S1->inner_read_allocate  = cache_hints.inner_read_allocate;  //
  S1->inner_write_allocate = cache_hints.inner_write_allocate; //
}
