#ifndef __A64_VMSA__

#include <unordered_map>
#include <vector>
#include <string.h>

// A64Descriptor - VMSA descriptor - A64 mode

enum PAGE_SIZES { SIZE_4K=0, SIZE_16K=2, SIZE_64K=1 };
enum { INVALID, BLOCK=1, TABLE=3, PAGE };
enum { LEVEL0, LEVEL1, LEVEL2, LEVEL3 };

class Memory;
class A64SimMonitor;

class A64Descriptor {
 public:
  A64Descriptor();
  A64Descriptor(Memory *_memory,unsigned long long _address,int _level,int _page_size,
                int _state, bool _big_endian, bool _for_test);

  bool ForTest() { return for_test; };

  bool Invalid() { return (format == INVALID) || !format_is_valid; };
  bool Table()   { return format == TABLE;   };
  bool Block()   { return format == BLOCK;   };

  unsigned long long TableAddress()   { return table_address;    }; 
  unsigned long long OutputAddress()  { return output_address;   }; 
  unsigned long long PageOffsetMask() { return page_offset_mask; };
  unsigned long long BlockSize()      { return page_offset_mask + 1; };

  unsigned long long Value() { return desc.dval; };

  void MemValue(unsigned char *tbuf) { memcpy(tbuf,desc.dbuf,8); };
  
  friend std::ostream& operator<< (std::ostream &os, A64Descriptor &desc);

  unsigned long long address;               // address of the descriptor itself
  int                level;                 // descriptor level
  int                page_size;             // 4kb vs 16kb vs 64kb - so called 'granule' size
  int                stage;                 // stage 1 vs stage 2
  bool               big_endian;            // descriptor endianness
  bool               for_test;              // set to cause internal errors to throw exception, etc

  int                format;                // descriptor format (see enum above)
  bool               format_is_valid;       // whether or not format is correct for a level

  unsigned           NSTable;               // non-secure table d4-1706
  unsigned           APTable;               // access permissions limit d4-1709
  unsigned           UXNTable;              // execute-never limit d4-1712
  unsigned           PXNTable;              // privileged execute never limit d4-1712

  unsigned           Contiguous;            // p d4-1718
  unsigned           nG;                    // non-global
  unsigned           AF;                    // access flag d4-1714
  unsigned           SH;                    // shareability d4-1714
  unsigned           AP;                    // AP[2:1] D4-1707
  unsigned           NS;                    // non-secure - affects output address
  unsigned           AttrIndx;              // AttrIndx[2:0] MAIR_ELx - D4-1715

 protected:
  unsigned long long page_offset_mask;
  unsigned long long output_address;
  unsigned long long table_address;

  // descriptor value read from memory, after endianness applied:

  union {
    unsigned char dbuf[8]; 
    unsigned long long dval;
  } desc;
};



// TLBRecord - page 1746
// memory data type definitions - D4-1697

class Translation {
 public:
 Translation();
 Translation(unsigned long long _la,unsigned int _asid,bool _privileged, bool _ns,bool _is_data, bool _wasaligned, int _size, bool _is_write, bool _big_endian);
 Translation(Translation &src_trans,int byte_count);
  ~Translation() {};

  unsigned long long TLBkey(/* LA,ASID,Global,NS,is_data */);  // return key to use with TLB table

  int PageCrossed(int byte_count);

  void updateCacheHints(struct AttrXcacheHints);

  unsigned long long PageOffsetMask() { return page_offset_mask; };

  bool MMU_Enabled() { return mmu_enabled; };
  bool Shareable();
  bool Cacheable();

  void LA2PA(unsigned long long _LA);      // translate a particular address once the translation is established
 
  friend std::ostream& operator<< (std::ostream &os, Translation &trans); // dump TLB key too!

  // inputs:
  unsigned long long LA;                   // input logical memory address
  unsigned long long extLA;                // input logical memory address - when address extention applied
  unsigned long long IPA;                  // intermediate physical memory address - when stage 2 translation present
  unsigned long long PA;                   // final physical memory address

  unsigned int       valid;                // mark translation as valid after filling out same

  bool               Global;               // set if global, ie, ignore ASID

  bool               mmu_enabled;          // mmu enabled?
  bool               secondstage;          // stage 2 enabled? (not in this implementation)
  bool               permissioncheck;      // permission checks enabled

  bool               addressExtended;      // is address extension enabled?

  bool               is_data;              // false for instr, true for data
  bool               is_write;             // true for data/write 
 
  bool               wasaligned;           // aligned access?
  int                size;                 // # of bytes
  bool               privileged;           // privileged access?
  
  unsigned int       ASID;                 // 8 or 16 bit ASID
  bool               NS;                   // set if non-secure access

  bool               BigEndian;            // data endianness (not when Translation used as TLB entry)

  // these fields filled during table walk:

  int                topBit;               // set for address extension (addrtop, p1708)

  bool               s1_enabled;           // stage 1 translation enabled
  bool               s2_enabled;           //   "   2      "        "

  unsigned long long ttb_base_address;     // base address for translation - TTBR0, etc
  bool               tbi;                  // address tag enable

  bool               readUnprivileged;     // each access will either be
  bool               writeUnprivileged;    //  unprivileged (EL0)

  bool               readPrivileged;       // or privileged
  bool               writePrivileged;      //   (EL1 or greater)

  bool               XN;                   // execute-never
  bool               PXN;                  // privileged execute-never
  bool               Contiguous;           // needed?
  bool               nG;                   // non-global
  bool               AF;                   // access flag
 
  int                memory_type;          // memory type - normal vs device - page 1697
  int                device_type;          // device memory type

  int                outer_cache_type;     // 
  bool               outer_transient;      // outer cache attributes
  bool               outer_read_allocate;  //
  bool               outer_write_allocate; //

  int                inner_cache_type;     //
  bool               inner_transient;      // inner cache attributes
  bool               inner_read_allocate;  //
  bool               inner_write_allocate; //

  bool               innershareable;       // if both clear
  bool               outershareable;       //   then non-shareable

  bool               contiguous;           // (stupid) contiguous pages flag
  int                domain;               // domain?
  int                level;                // translate level?
  int                blocksize;            // page (granule) size

  bool               unpredictable;        //

  unsigned long long base_address;         // after table walk, here is final physical page address
  unsigned long long page_offset_mask;     //   + mask to use to page offset from LA

  int                levels;               // levels - # of levels involved in a translation.
  A64Descriptor      descriptors[4];       // indexed from 0 to levels-1...
};


class TLB {
 public: 
 TLB(int _max_entries = 256) : max_entries(_max_entries),hit_count(0),miss_count(0),cast_out_count(0) {};

  void Add(Translation *trans);
  void Remove(unsigned long long tlb_key);
  void Remove(Translation &trans);
  bool Find(Translation *trans);
  bool FindLiteral(Translation *trans);
  void Reset();

  unsigned long long HitCount() { return hit_count; };
  unsigned long long MissCount() { return miss_count; };
  unsigned long long CastOutCount() { return cast_out_count; };
  
  friend std::ostream& operator<< (std::ostream &os, TLB &tlbs); // dump TLB table

 protected:
  unordered_map<unsigned long long, Translation> tlbs;

  vector<unsigned long long> tlb_order; // <---use to know which entry can be 'cast out' 
                                        //      when tlb table becomes full

  int max_entries;

  unsigned long long hit_count;
  unsigned long long miss_count;
  unsigned long long cast_out_count;
};


class State;
class Packet;

// A64_VMSA - similar to the Control class, its 'state' is passed in thru the constructor...

class A64_VMSA {
 public:
  A64_VMSA(State *_cpu,Memory *_memory,Packet *_packet,TLB *_itlb,TLB *_dtlb,A64SimMonitor *monitor);
  ~A64_VMSA() {};

  bool ForTest();

  bool Enabled();
  bool Privileged();
  unsigned int ASID();
  bool BigEndian();  // address translation endianness  
  bool TranslationTableIsValid(unsigned long long LA);
  unsigned long long TTBaseAddress(unsigned long long LA, bool stage2=false);
  unsigned int TnSZ(unsigned long long LA);
  int InitialLevelLookup(unsigned long long LA, int page_size);
  int InputAddressSize(unsigned long long LA);
  int OutputAddressSize();
  int PAMax();
  bool ValidatePhysicalAddress(unsigned long long PA, bool translation_enabled);
  int PageSize(unsigned long long LA);
  bool Cacheable(bool is_data);
  void MemoryAttributes(int &mem_type,int &device_type,struct AttrXcacheHints &cache_hints, int attr_index);

  Translation *LA2PA(unsigned long long _la,bool _ns,bool _privileged, bool _is_data, bool wasligned, int size, bool is_write);

  int AddrTop(bool &tbi, unsigned long long LA);
  bool AddressTagEnabled(unsigned long long LA);
  bool IsZero(unsigned long long LA,int topBit);

  bool AlignmentChecksEnabled();

 protected:
  void FullTranslate(Translation *trans);
  void FirstStageTranslate(Translation *trans);
  void SecondStageTranslate(Translation *trans, bool s2fs1walk);
  void TranslationTableWalk(Translation *S1);
  void TranslateAddressS1Off(Translation *S1);
  void CheckAlignment(Translation *S1);
  void CheckPermissions(Translation *S1);
  void CheckInstructionAccess(Translation *S1);

  void AddressSizeFault(Translation *S1);

  void GetTableAttributes(Translation *S1,A64Descriptor &desc);
  void GetBlockPageAttributes(Translation *S1,A64Descriptor &desc);
  unsigned long long TableIndex(unsigned long long LA, int level, int page_size);

 private:
  State         *cpu;
  Memory        *memory;
  Packet        *packet;
  TLB           *itlb;
  TLB           *dtlb;
  A64SimMonitor *monitor;
};

#define __A64_VMSA__
#endif
