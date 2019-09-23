//#define INSTRUCTION_GROUPS_COUNT  69
#define INSTRUCTION_GROUPS_COUNT  26
#define BRANCH_ENCODING INSTRUCTION_GROUPS_COUNT - 1

int get_next_encoding(int instr_index,unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {
  switch(instr_index) {
    case 0:  group = "Move wide (immediate) / MOVN 32"; mask = 0xff800000; encoding = (set_mask & ~0xff800000) | 0x12800000; break;
    case 1:  group = "Move wide (immediate) / MOVN 64"; mask = 0xff800000; encoding = (set_mask & ~0xff800000) | 0x92800000; break;
    case 2:  group = "Move wide (immediate) / MOVZ 32"; mask = 0xff800000; encoding = (set_mask & ~0xff800000) | 0x52800000; break;
    case 3:  group = "Move wide (immediate) / MOVZ 32"; mask = 0xff800000; encoding = (set_mask & ~0xff800000) | 0xd2800000; break;
    case 4:  group = "Move wide (immediate) / MOVK 32"; mask = 0xff800000; encoding = (set_mask & ~0xff800000) | 0x72800000; break;
    case 5:  group = "Move wide (immediate) / MOVK 32"; mask = 0xff800000; encoding = (set_mask & ~0xff800000) | 0xf2800000; break;
    case 6:  group = "System / HINT"; mask = 0xfffff01f; encoding = (set_mask & ~0xfffff01f) | 0xd503201f; break;
    case 7:  group = "System / NOP";  mask = 0xffffffff; encoding = 0xd503201f; break;
    case 8:  group = "System / SEVL"; mask = 0xffffffff; encoding = 0xd50320bf; break;
    case 9:  group = "System / SEV";  mask = 0xffffffff; encoding = 0xd503209f; break;
    case 10: group = "System / WFE";  mask = 0xffffffff; encoding = 0xd503205f; break;
    case 11: group = "System / WFI";  mask = 0xffffffff; encoding = 0xd503207f; break;
    case 12: group = "System / YIELD";  mask = 0xffffffff; encoding = 0xd503203f; break;
    case 13: group = "System / DSB"; mask = 0xfffff0ff; encoding = (set_mask & ~0xfffff0ff) | 0xd503309f; break;
    case 14: group = "System / ISB"; mask = 0xfffff0ff; encoding = (set_mask & ~0xfffff0ff) | 0xd50330df; break;
    case 15: group = "System / SYSL"; mask = 0xfff80000; encoding = (set_mask & ~0xfff80000) | 0xd5280000; break;
// for LDR (immediate) allow 64 bit version only to keep from having to check for Xt (Wt) being initialized... 
    case 16: group = "Load/store register (unsigned immediate) / LDR (immediate)"; mask = 0xbfc00000; encoding = (set_mask & ~0xbfc00000) | 0xf9400000; break;
    case 17: group = "Add/subtract (immediate) 32";         mask = 0x1f000000; encoding = (set_mask & ~0x1f000000) | 0x11000000; break;
    case 18: group = "Add/subtract (immediate) 64";         mask = 0x1f000000; encoding = (set_mask & ~0x1f000000) | 0x91000000; break;
    case 19: group = "Add/subtract (extended register) 32"; mask = 0x1f200000; encoding = (set_mask & ~0x1f200000) | 0x0b200000; break;
    case 20: group = "Add/subtract (extended register) 64"; mask = 0x1f200000; encoding = (set_mask & ~0x1f200000) | 0x8b200000; break;
    case 21: group = "Add/subtract (shifted register) 32";  mask = 0x1f200000; encoding = (set_mask & ~0x1f200000) | 0x0b000000; break;
    case 22: group = "Add/subtract (shifted register) 64";  mask = 0x1f200000; encoding = (set_mask & ~0x1f200000) | 0x8b000000; break;
// add subtract with carry hand edited to set opcode2 field correctly 
    case 23: group = "Add/subtract (with carry) 32";        mask = 0x1fe0fc00; encoding = (set_mask & ~0x1fe0fc00) | 0x1a000000; break;
    case 24: group = "Add/subtract (with carry) 64";        mask = 0x1fe0fc00; encoding = (set_mask & ~0x1fe0fc00) | 0x9a000000; break;

// always leave branch encoding as last case... 
    case 25: group = "Unconditional branch (immediate) / B"; mask = 0xfc000000; encoding = (set_mask & ~0xfc000000) | 0x14000000; break;

  default: break;
  }

  return 0;
}

int get_branch_encoding(unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {
  return get_next_encoding(BRANCH_ENCODING,set_mask,group,encoding,mask);
}

// if conditions allow it, tweak instruction encodings to avoid some reserved field cases 
// or cases where some field has restricted value...

void tweak_encoding(int instr_index,unsigned int &encoding) {
  switch(instr_index) {
    case 17: // Add/subtract (immediate) 32
    case 18: // Add/subtract (immediate) 64
             // shift field (bits 22,23) can only be 0 or 1...
             {
             int shift = rand() & 1;
             encoding = (encoding & ~(3<<22)) | (shift<<22);
	     }
             break;

    case 19: // Add/subtract (extended register) 32
    case 20: // Add/subtract (extended register) 64
             // shift field (imm3 or bits 10 thru 12) must be less than 4...
             {
             int imm = rand() & 3;
             encoding = (encoding & ~(7<<10)) | (imm<<10);
	     }
             break;

    case 21: // Add/subtract (shifted register) 32
    case 22: // Add/subtract (shifted register) 64
             // shift field (bits 22,23) cannot be 3...
             {
             int shift = rand() & 7;
             // even distribution of values 0,1,2 (more or less)
             switch(shift) {
             case 0: case 1: case 2: shift = 0; break;
             case 3: case 4: case 5: shift = 1; break;
             default: shift = 2; break;
	     }
             encoding = (encoding & ~(3<<22)) | (shift<<22);
             // correct shift amount if necessary...
             int sf = (encoding>>31) & 1;
             if (sf == 0) {
	       int imm6 = (encoding>>10) & 0x1f; // strip imm6[5]
               encoding = (encoding & ~(0x3f<<10)) | (imm6<<10);
	     }
	     }
             break;

    default: break;
  }

}

