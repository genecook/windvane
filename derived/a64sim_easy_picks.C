#define SAFE_INSTRUCTION_GROUPS_COUNT 7

int get_next_safe_encoding(int instr_index,unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {
  int rcode = 0;
  switch(instr_index) {
    // MOVN but not MOVZ or MOVK...
    case 0: group = "Move wide (immediate)/MOVN 32-bit"; mask = 0xff800000; encoding = (set_mask & ~0xffe00000) | 0x12800000; break;
    case 1: group = "Move wide (immediate)/MOVN 64-bit"; mask = 0xff800000; encoding = (set_mask & ~0xffe00000) | 0x92800000; break;
    // MOVZ but not MOVN or MOVK...
    case 2: group = "Move wide (immediate)/MOVZ 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~0xffc00000) | 0x52800000; break;
    case 3: group = "Move wide (immediate)/MOVZ 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~0xffc00000) | 0xd2800000; break;
    case 4: group = "PC-relative addressing/ADR -"; mask = 0x9f000000; encoding = (set_mask & ~0x9f000000) | 0x10000000; break;
    case 5: group = "PC-relative addressing/ADRP -"; mask = 0x9f000000; encoding = (set_mask & ~0x9f000000) | 0x90000000; break;
    case 6: group = "System/NOP -"; mask = 0xffffffff; encoding = (set_mask & ~0xffffffff) | 0xd503201f; break;
    default: rcode = -1;
             break;
  }
  return rcode;
}
