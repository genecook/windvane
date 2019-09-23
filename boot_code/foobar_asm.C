enum SPRS { SP_EL0,SP_EL1,SP_EL2,SP_EL3 };
 
extern "C" {

  void init_msr(int wreg, unsigned int val) {
    register unsigned int foo asm("w2") = val; 
    
    switch(wreg) {
      case 0: asm("msr sp_el0,w2"); break;
      case 1: asm("msr sp_el1,w2"); break;
      case 2: asm("msr sp_el2,w2"); break;
      case 3: asm("msr sp_el3,w2"); break;
    } 
  }

  void init_reg64(int wreg, unsigned long long val) {
    register unsigned long long foo asm("w28") = val; 

    switch(wreg) {
      case 0: asm("msr X0,x28"); break;
      case 1: asm("msr X1,x28"); break;
      case 2: asm("msr X2,x28"); break;
      case 3: asm("msr X3,x28"); break;
    }
  }

  void foobar() {
    for (int i = 0; i < 32; i++) {
       register unsigned int j = i + 64;
       asm volatile("mov %w0,5" : "=r"(j));
    }

    init_msr(SP_EL0,32);  // w0 is 1st arg, w1 is second...

    init_reg64(0,0xffffffffffffffffull);
  }

}
