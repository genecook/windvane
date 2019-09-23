package simtrace_viewer;

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.lang.Integer;
import java.io.File;

//Long l1 = Long.parseUnsignedLong("17916881237904312345");
//String l1Str = Long.toUnsignedString(l1)
//System.out.println(l1Str);

public class RegisterDecode {
    public void RegisterDecode() {
    }

    static String pstateCommon(long pstate) {
	long NZCV = (pstate>>28) & 0x0f;
        long D    = (pstate>>11) & 1;
        long IL   = (pstate>>17) & 1;
        long SS   = (pstate>>10) & 1;
        long A    = (pstate>>8) & 1;
        long I    = (pstate>>7) & 1;
        long F    = (pstate>>6) & 1;
        long EL   = (pstate>>2) & 3;
        long SP   = (pstate & 1)==1 ? EL : 0;
    
        //return String.format("NZCV=0x%x D=%d IL=%d SS=%d A=%d I=%d F=%d EL%d/SP%d\n",NZCV,D,IL,SS,A,I,F,EL,SP);
        return String.format("NZCV=0x%x EL%d/SP%d D=%d IL=%d SS=%d A=%d I=%d F=%d",NZCV,EL,SP,D,IL,SS,A,I,F);
    }

    public static String sctlr(long sctlr, boolean do_el1) {
	String sctlr_str;
	
        long EE = (sctlr >> 25)  & 1;
        long I  = (sctlr >> 12)  & 1;
        long SA = (sctlr >> 3)  & 1;
        long C  = (sctlr >> 2)  & 1;
        long A  = (sctlr >> 1)  & 1;
        long M  = sctlr & 1;
    
	if (do_el1) {
	  long UCI     = (sctlr >> 26)  & 1;
	  long E0E     = (sctlr >> 24)  & 1;
          long WXN     = (sctlr >> 19)  & 1;
          long nTWE    = (sctlr >> 18)  & 1;
          long nTWI    = (sctlr >> 16)  & 1;
          long UCT     = (sctlr >> 15)  & 1;
          long DZE     = (sctlr >> 14)  & 1;
	  long UMA     = (sctlr >> 9)  & 1;
          long SED     = (sctlr >> 8)  & 1;
          long ITD     = (sctlr >> 7)  & 1;
          long CP15BEN = (sctlr >> 5)  & 1;
          long SA0     = (sctlr >> 4)  & 1;

	  sctlr_str = String.format("UCI=%d, EE=%d, E0E=%d, WXN=%d, nTWE=%d, nTWI=%d, UCT=%d, DZE=%d, I=%d, UMA=%d, SED=%d, ITD=%d, CP15BEN=%d, SA=%d, C=%d, A=%d, M=%d",
				    UCI,EE,E0E,WXN,nTWE,nTWI,UCT,DZE,I,UMA,SED,ITD,CP15BEN,SA,C,A,M);
	} else {
	    sctlr_str = String.format("EE=%d, I=%d, SA=%d, C=%d, A=%d, M=%d",EE,I,SA,C,A,M);
	}
	
        return sctlr_str;
    }

    public static String SCR_EL3(long scr_el3) {
          long TWE = (scr_el3 >> 13) & 0x1;
          long TWI = (scr_el3 >> 12) & 0x1;
          long ST  = (scr_el3 >> 11) & 0x1;
          long RW  = (scr_el3 >> 10) & 0x1;
          long SIF = (scr_el3 >> 9) & 0x1;
          long HCE = (scr_el3 >> 8) & 0x1;
          long SMD = (scr_el3 >> 7) & 0x1;
          long EA  = (scr_el3 >> 3) & 0x1;
          long FIQ = (scr_el3 >> 2) & 0x1;
          long IRQ = (scr_el3 >> 1) & 0x1;
          long NS  = scr_el3 & 0x1;

          return String.format("TWE=%d,TWI=%d,ST=%d,RW=%d,SIF=%d,HCE=%d,SMD=%d,EA=%d,FIQ=%d,IRQ=%d,NS=%d",TWE,TWI,ST,RW,SIF,HCE,SMD,EA,FIQ,IRQ,NS); 
    }
    
    
    public static String Pstate(long pstate) {
	return pstateCommon(pstate);
    }

    public static String SPSR_EL1(long spsr) {
	return pstateCommon(spsr);
    }
    public static String SPSR_EL2(long spsr) {
	return pstateCommon(spsr);
    }
    public static String SPSR_EL3(long spsr) {
	return pstateCommon(spsr);
    }
    
    public static String SCTLR_EL1(long sctlr) {
        return sctlr(sctlr, true);
    }
    public static String SCTLR_EL2(long sctlr) {
        return sctlr(sctlr, false);
    }
    public static String SCTLR_EL3(long sctlr) {
        return sctlr(sctlr, false);
    }
    
    public static String ID_AA64DFR0_EL1(long dval) {
        long CTX_CMPs = (dval >> 28) & 0xf;
        long WRPs     = (dval >> 20) & 0xf;
        long BRPs     = (dval >> 12) & 0xf;
        long PMUVer   = 0;
        long TraceVer = 0;
        long DebugVer = dval & 0xf;

	return String.format("CTX_CMPs=%d,WRPs=%d,BRPs=%d,PMUVer=%d,TraceVer=%d,DebugVer=0x%x",
			     CTX_CMPs,WRPs,BRPs,PMUVer,TraceVer,DebugVer);
    }
    
    public static String ID_AA64MMFR0_EL1(long dval) {
        long TGran4    = (dval >> 28) & 0xf;
        long TGran64   = (dval >> 24) & 0xf;
        long TGran16   = (dval >> 20) & 0xf;
        long BigEndEL0 = (dval >> 16) & 0xf;
        long SNSMem    = (dval >> 12) & 0xf;
        long BigEnd    = (dval >> 8) & 0xf;
        long ASIDBits  = (dval >> 4) & 0xf;
        long PARange   = dval & 0xf;

	String pmem_size;
	switch((int) PARange) {
          case 0: pmem_size = "32 bits"; break;
          case 1: pmem_size = "36 bits"; break;
          case 2: pmem_size = "40 bits"; break;
          case 3: pmem_size = "42 bits"; break;
          case 4: pmem_size = "44 bits"; break;
          case 5: pmem_size = "48 bits"; break;
	default: pmem_size = "?"; break;
	}

	return String.format("TGran4=0x%x,TGran64=0x%x,TGran16=0x%x,BigEndEL0=0x%x,SNSMem=0x%x,BigEnd=0x%x,ASIDBits=0x%x,PARange=0x%x (%s)",
			     TGran4,TGran64,TGran16,BigEndEL0,SNSMem,BigEnd,ASIDBits,PARange,pmem_size);
    }

    public static String ID_AA64PFR0_EL1(long dval) {
       long GIC     = (dval >> 24) & 0xf;
       long AdvSIMD = (dval >> 20) & 0xf;
       long FP      = (dval >> 16) & 0xf;
       long EL3     = (dval >> 12) & 0xf;
       long EL2     = (dval >> 8) & 0xf;
       long EL1     = (dval >> 4) & 0xf;
       long EL0     = dval & 0xf;

       boolean gic_present = GIC != 0;
       boolean simd_present = AdvSIMD != 0;
       boolean fp_present = FP != 0;

       String el3 = "EL3 not implemented";
       if (EL3 == 1) el3 = "EL3 - 64-bit only";
       else el3 = "EL3 - 64 and 32 bit modes";

       String el2 = "EL2 not implemented";
       if (EL2 == 1) el2 = "EL2 - 64-bit only";
       else el2 = "EL2 - 64 and 32 bit modes";

       String el1 = "EL1 not implemented)";
       if (EL1 == 1) el1 = "EL1 - 64-bit only";
       else el1 = "EL1 - 64 and 32 bit modes";

       String el0 = "EL0 not implemented";
       if (EL0 == 1) el0 = "EL0 - 64-bit only";
       else el0 = "EL0 - 64 and 32 bit modes";

       return String.format("GIC=0x%x (%s),AdvSIMD=0x%x (%s),FP=0x%x (%s),EL3=0x%x (%s),EL2=0x%x (%s),EL1=0x%x (%s),EL0=0x%x (%s)",
			    GIC,gic_present,AdvSIMD,simd_present,FP,fp_present,EL3,el3,EL2,el2,EL1,el1,EL0,el0);
    }
    
    public static String ID_AA64ISAR0_EL1(long dval) {
       long CRC32 = (dval >> 16) & 0xf;
       long SHA2  = (dval >> 12) & 0xf;
       long SHA1  = (dval >> 8) & 0xf;
       long AES   = (dval >> 4) & 0xf;

       String crc32 = (CRC32 != 0) ? "CRC32 present" : "CRC32 not present";
       String sha2  = (SHA2 != 0)  ? "SHA2 present"  : "SHA2 not present";
       String sha1  = (SHA1 != 0)  ? "SHA1 present"  : "SHA1 not present";
       String aes   = (AES != 0)   ? "AES present"   : "AES not present";

       return String.format("CRC32=0x%x (%s),SHA2=0x%x (%s),SHA1=0x%x (%s),AES=0x%x (%s)",
			    CRC32,crc32,SHA2,sha2,SHA1,sha1,AES,aes);
    }
    
    public static String MIDR_EL1(long dval) {
      long Implementer  = (dval >> 24) & 0xff;
      long Variant      = (dval >> 20) & 0xf;
      long Architecture = (dval >> 16) & 0xf;
      long PartNum      = (dval >> 4) & 0xfff;
      long Revision     = dval & 0xf;

      String who = "?";
      switch((int) Implementer) {
        case 0x41: who = "ARM"; break;
        case 0x42: who = "Broadcom"; break;
        case 0x43: who = "Cavium"; break;
        case 0x44: who = "DEC"; break;
        case 0x49: who = "Infineon"; break;
        case 0x4d: who = "Motorola"; break;
        case 0x4e: who = "NVIDIA"; break;
        case 0x50: who = "AMCC"; break;
        case 0x51: who = "Qualcom"; break;
        case 0x56: who = "Marvell"; break;
        case 0x69: who = "Intel"; break;
        case 0x99: who = "Tuleta Software Co."; break;
        default: break;
      }

      String arch = (Architecture == 0xf) ? "CPUID defined" : "ARM v4/v5/v6...";
      if (Architecture < 8) arch = "?";

      return String.format("Implementer=0x%x (%s),Variant=0x%x,Architecture=0x%x (%s),PartNum=0x%x,Revision=0x%x",
			   Implementer,who,Variant,Architecture,arch,PartNum,Revision);
    }

    static long exp2(long a) {
       long result = 1;
       for (int i = 1; i <= a; i++) {
          result *= 2;
       }
       return result;
    }
    
    public static String CTR_EL0(long dval) {
       long CWG       = (dval >> 24) & 0xf;
       long ERG       = (dval >> 20) & 0xf;
       long DminLine  = (dval >> 16) & 0xf;
       long L1Ip      = (dval >> 14) & 0x3;
       long IminLine  = dval & 0xf;

       String cwg;
       if (CWG > 0)
	   cwg = String.format("Cache writeback buffer size = %d",exp2(CWG));
       else if (CWG == 0)
	   cwg = "Not specified. 512? Cache line size? N/A?";
       else
	   cwg = "Reserved value?";
       
       String erg;
       if (ERG > 0)
	   erg = String.format("Exclusive op block size = %d",exp2(CWG));
       else if (ERG == 0)
	   erg = "Not specified. 512? ";
       else
	   erg = "Reserved value?";

       String dminline = String.format("Minimum data cache line size: %d",exp2(DminLine));

       String icache_policy;
       switch((int) L1Ip) {
       case 1:  icache_policy = "ASID-tagged Virtual Index, Virtual Tag"; break;
       case 2:  icache_policy = "Virtual Index, Physical Tag"; break;
       case 3:  icache_policy = "Physical Index, Physical Tag"; break;
       default: icache_policy = "Reserved value?";
       }

       String iminline = String.format("Minimum instr cache line size: %d",exp2(IminLine));
       
       return String.format("CWG=0x%x (%s),ERG=0x%x (%s),DminLine=0x%x (%s),L1Ip=0x%x (%s),IminLine=0x%x (%s)",
			    CWG,cwg,ERG,erg,DminLine,dminline,L1Ip,icache_policy,IminLine,iminline);
    }

    public static String DCZID_EL0(long dval) {
       long DZP = (dval >> 4) & 0x1;
       long BS  = dval & 0xf;

       String dzp = (DZP != 0) ? "DC ZVA prohibited" : "DC ZVA allowed";
       String bs  = String.format("DC ZVA block size: %d",exp2(BS));
       
       return String.format("DZP=%d (%s),BS=0x%x (%s)", DZP,dzp,BS,bs);
    }
    
    public static String VPIDR_EL2(long dval)  { return ""; }
    public static String AFSR0_EL1(long dval)  { return ""; }
    public static String AFSR0_EL2(long dval)  { return ""; }
    public static String AFSR0_EL3(long dval)  { return ""; }
    public static String AFSR1_EL1(long dval)  { return ""; }
    public static String AFSR1_EL2(long dval)  { return ""; }
    public static String AFSR1_EL3(long dval)  { return ""; } 
    public static String REVIDR_EL1(long dval) { return ""; }
    public static String VBAR_EL1(long dval)   { return ""; }
    public static String VBAR_EL2(long dval)   { return ""; }
    public static String VBAR_EL3(long dval)   { return ""; }
   
    public static String MPIDR_EL1(long dval) {
       long Aff3 = (dval >> 32) & 0xff;
       long U    = (dval >> 30) & 0x1;
       long MT   = (dval >> 24) & 0x1;
       long Aff2 = (dval >> 16) & 0xff;
       long Aff1 = (dval >> 8) & 0xff;
       long Aff0 = dval & 0xff;

       String u = (U==1) ? "Uniprocessor config" : "Multiprocessor config";
       String mt = (MT==1) ? "Multi-threaded config" : "No multithreading";
       
       return String.format("Aff3=0x%x (Affinity level 3),U=%d (%s),MT=%d (%s),Aff2=0x%x (Affinity level 2),Aff1=0x%x (Affinity level 1 - cluster ID),Aff0=0x%x (Affinity level 3 - core ID)",
			    Aff3,U,u,MT,mt,Aff2,Aff1,Aff0);
    }

    public static String VMPIDR_EL2(long dval) {
	return MPIDR_EL1(dval);
    }

    public static String CPACR_EL1(long dval) {
        long TTA  = (dval >> 28) & 0x1;
        long FPEN = (dval >> 20) & 0x3;

	String tta = (TTA == 1) ? "Trap accesses to Trace functionality to EL1" : "Do not trap accesses to Trace functionality";
	String fpen = "?";
	switch((int) FPEN) {
          case 0: fpen = "Trap FP/ASID - EL0, EL1"; break;
	  case 1: fpen = "Trap FP/ASID - EL0 only"; break;
	  case 2: fpen = "Trap FP/ASID - EL0, EL1"; break;
	  case 3: fpen = "Do not trap FP/ASID"; break;
	}
	
	return String.format("TTA=%d (%s),FPEN=%d (%s)",TTA,tta,FPEN,fpen);
    }

    public static String CPTR(long dval, String trapEL) {
        long TCPAC = (dval >> 31) & 0x1;
        long TTA   = (dval >> 20) & 0x1;
        long TFP   = (dval >> 10) & 0x1;

	String tcpac = (TCPAC == 1) ? "Trap CPACR_EL1 accesses to " : "Do not trap CPACR_EL1 accesses to ";
	String tta = (TTA == 1) ? "Trap accesses to Trace functionality to EL2" : "Do not trap accesses to Trace functionality to ";
	String tfp = (TFP == 1) ? "Trap FP/ASID accesses to " : "Do not trap FP/ASID to ";
	
	return String.format("TCPAC=%d (%s %s), TTA=%d (%s %s), TFP=%d (%s %s)", TCPAC,tcpac,trapEL,TTA,tta,trapEL,TFP,tfp,trapEL);
    }

    public static String CPTR_EL2(long dval) {
	return CPTR(dval,"EL2");
    }

    public static String CPTR_EL3(long dval) {
	return CPTR(dval,"EL3");
    }
    
    public static String FPCR(long dval) {
        long AHP   = (dval >> 26) & 0x1;
        long DN    = (dval >> 25) & 0x1;
        long FZ    = (dval >> 24) & 0x1;
        long RMode = (dval >> 22) & 0x3;
        long IDE   = (dval >> 15) & 0x1;
        long IXE   = (dval >> 12) & 0x1;
        long UFE   = (dval >> 11) & 0x1;
        long OFE   = (dval >> 10) & 0x1;
        long DZE   = (dval >> 9) & 0x1;
        long IOE   = (dval >> 8) & 0x1;

	String ahp = (AHP == 1) ? "Alternative half-precision format" : "IEEE half-precision";
	String dn  = (DN == 1)  ? "Return default NaN" : "Propagate NaN";
	String fz  = (FZ == 1)  ? "Flush-to-zero enabled" : "Flush-to-zero disabled";
	String rmode = "?";
        switch((int) RMode) {
	  case 0: rmode = "RN - Round to Nearest"; break;
	  case 1: rmode = "RP - Round towards Plus Infinity"; break;
	  case 2: rmode = "RP - Round towards Minus Infinity"; break;
	  case 3: rmode = "RZ - Round towards Zero"; break;
	}
	return String.format("AHP=%d (%s),DN=%d (%s),FZ=%d (%s), RMode=%d (%s), traps: IDE=%d,IXE=%d,UFE=%d,OFE=%d,DZE=%d,IOE=%d",
			     AHP,ahp,DN,dn,FZ,fz,RMode,rmode,IDE,IXE,UFE,OFE,DZE,IOE);
    }

    public static String FPSR(long dval, boolean verbose) {
        long QC   = (dval >> 27) & 0x1;
        long IDC  = (dval >> 7) & 0x1;
        long IXC  = (dval >> 4) & 0x1;
        long UFC  = (dval >> 3) & 0x1;
        long OFC  = (dval >> 2) & 0x1;
        long DZC  = (dval >> 1) & 0x1;
        long IOC  = dval & 0x1;

	if (verbose) {
          return String.format("Floating pt. cumulative exception bits: QC=%d,IDC=%d,IXC=%d,UFC=%d,OFC=%d,DZC=%d,IOC=%d",
	  		       QC,IDC,IXC,UFC,OFC,DZC,IOC);
	}
	
        return String.format("QC=%d,IDC=%d,IXC=%d,UFC=%d,OFC=%d,DZC=%d,IOC=%d",QC,IDC,IXC,UFC,OFC,DZC,IOC);	    
    }

    static String DecodeEC(long EC, boolean full_desc) {
        String ec_brief = "";
        String ec_descr = "";
	
	switch((int) EC) {
	// auto-generated entries:
        case 0:  // EC = 000000
	         ec_brief = "Unknown.";
	         ec_descr = "Unknown or Uncategorized Reason - generally used for exceptions as a result of erroneous execution.";
                 break;
        case 1:  // EC = 000001
                 ec_brief = "WFE/WFI";
                 ec_descr = "Exceptions from WFE/WFI from either AArch32 or AArch64 as a result of configurable traps, enables, or disables. Conditional WFE and WFI instructions that fail their condition code check do not cause an exception.";
                 break;
        case 3:  // EC = 000011
                 ec_brief = "MCR/MRC to CP15.";
                 ec_descr = "Exceptions from MCR/MRC to CP15 from AArch32 as a result of configurable traps, enables, or disables that do not use code 0b000000.";
                 break;
        case 4:  // EC = 000100
                 ec_brief = "MCRR/MRRC to CP15.";
                 ec_descr = "Exceptions from MCRR/MRRC to CP15 from AArch32 as a result of configurable traps, enables, or disables that do not use code 0b000000.";
                 break;
        case 5:  // EC = 000101
                 ec_brief = "MCR/MRC to CP14.";
                 ec_descr = "Exceptions from MCR/MRC to CP14 from AArch32 as a result of configurable traps, enables, or disables that do not use code 0b000000.";
                 break;
        case 6:  // EC = 000110
                 ec_brief = "LDC/STC to CP14.";
                 ec_descr = "Exceptions from LDC/STC to CP14 from AArch32 as a result of configurable traps, enables, or disables.";
                 break;
        case 7:  // EC = 000111
                 ec_brief = "ASIMD/Floating Point.";
                 ec_descr = "Exceptions from access to Advanced SIMD or Floating Point as a result of configurable traps, enables, or disables.";
                 break;
        case 8:  // EC = 001000
                 ec_brief = "MRC or VMRS.";
                 ec_descr = "Exceptions from MRC (or VMRS) to CP10 for MVFR0, MVFR1, MVFR2, or FPSID of ID Group traps from AArch32 unless reported using code 0b000111.";
                 break;
        case 12: // EC = 001100
                 ec_brief = "MCRR/MRRC to CP14.";
                 ec_descr = "Exceptions from MCRR/MRRC to CP14 from AArch32 as a result of configurable traps, enables, or disables.";
                 break;
        case 14: // EC = 001110
                 ec_brief = "PSTATE.IL == 1.";
                 ec_descr = "Exceptions that occur because the value of PSTATE.IL is 1.";
                 break;
        case 17: // EC = 010001
                 ec_brief = "SVC";
                 ec_descr = "SVC executed in AArch32.";
                 break;
        case 18: // EC = 010010
                 ec_brief = "HVC";
                 ec_descr = "HVC that is not disabled executed in AArch32.";
                 break;
        case 19: // EC = 010011
                 ec_brief = "SMC";
                 ec_descr = "SMC that is not disabled executed in AArch32.";
                 break;
        case 21: // EC = 010101
                 ec_brief = "SVC";
                 ec_descr = "SVC executed in AArch64.";
                 break;
        case 22: // EC = 010110
                 ec_brief = "HVC";
                 ec_descr = "HVC that is not disabled executed in AArch64.";
                 break;
        case 23: // EC = 010111
                 ec_brief = "SMC";
                 ec_descr = "SMC that is not disabled executed in AArch64.";
                 break;
        case 24: // EC = 011000
                 ec_brief = "MSR, MRS, or System AArch64 instruction.";
                 ec_descr = "Exceptions as a result of MSR, MRS, or System AArch64 instructions as a result of configurable traps, enables, or disables, except those using codes 0b000000, 0b000001, or 0b000111.";
                 break;
        case 32: // EC = 100000
                 ec_brief = "Instruction Abort.";
                 ec_descr = "Instruction Abort that caused entry from a lower exception level (AArch32 or AArch64). Used for instruction access generated MMU faults and synchronous external aborts, including synchronous parity errors. Not used for debug related exceptions.";
                 break;
        case 33: // EC = 100001
                 ec_brief = "Instruction Abort.";
                 ec_descr = "Instruction Abort that caused entry from a current exception level (AArch64). Used for instruction access generated MMU faults and synchronous external aborts, including synchronous parity errors. Not used for debug related exceptions.";
                 break;
        case 34: // EC = 100010
                 ec_brief = "PC Alignment Exception.";
                 ec_descr = "PC Alignment Exception.";
                 break;
        case 36: // EC = 100100
                 ec_brief = "Data Abort.";
                 ec_descr = "Data Abort that caused entry from a lower exception level (AArch32 or AArch64). Used for data access generated MMU faults, alignment faults other than those caused by the Stack Pointer misalignment, and synchronous external aborts, including synchronous parity errors.";
                 break;
        case 37: // EC = 100101
                 ec_brief = "Data Abort.";
                 ec_descr = "Data Abort that caused entry from a current exception level (AArch64). Used for data access generated MMU faults, alignment faults other than those caused by the Stack Pointer misalignment, and synchronous external aborts, including synchronous parity errors.";
                 break;
        case 38: // EC = 100110
                 ec_brief = "Stack Pointer Alignment Exception.";
                 ec_descr = "Stack Pointer Alignment Exception.";
                 break;
        case 40: // EC = 101000
                 ec_brief = "Floating-point exception.";
                 ec_descr = "Exceptions as a result of Floating-point exception (optional feature) from AArch32.";
                 break;
        case 44: // EC = 101100
                 ec_brief = "Floating-point exception.";
                 ec_descr = "Exceptions as a result of Floating-point exception from AArch64.";
                 break;
        case 47: // EC = 101111
                 ec_brief = "SError Interrupt.";
                 ec_descr = "SError Interrupt.";
                 break;
        case 48: // EC = 110000
                 ec_brief = "Breakpoint debug event.";
                 ec_descr = "Breakpoint debug event that caused entry from a lower exception level.";
                 break;
        case 49: // EC = 110001
                 ec_brief = "Breakpoint debug event.";
                 ec_descr = "Breakpoint debug event that caused entry from a current exception level.";
                 break;
        case 50: // EC = 110010
                 ec_brief = "Software step debug event.";
                 ec_descr = "Software step debug event that caused entry from a lower exception level.";
                 break;
        case 51: // EC = 110011
                 ec_brief = "Software step debug event.";
                 ec_descr = "Software step debug event that caused entry from a current exception level.";
                 break;
        case 52: // EC = 110100
                 ec_brief = "Watchpoint debug event.";
                 ec_descr = "Watchpoint debug event that caused entry from a lower exception level.";
                 break;
        case 53: // EC = 110101
                 ec_brief = "Watchpoint debug event.";
                 ec_descr = "Watchpoint debug event that caused entry from a current exception level.";
                 break;
        case 56: // EC = 111000
                 ec_brief = "BKPT instruction.";
                 ec_descr = "BKPT instruction executed in AArch32 state.";
                 break;
        case 58: // EC = 111010
                 ec_brief = "Vector catch debug event.";
                 ec_descr = "AArch32 state Vector catch debug event.";
                 break;
        case 60: // EC = 111100
                 ec_brief = "BRK instruction.";
                 ec_descr = "BRK instruction executed in AArch64 state.";
                 break;
		 
        default: // what the he?!...
	         ec_brief = "Unknown.";
	         ec_descr = "Unknown or Uncategorized Reason.";
                 break;
	}
	
	if (full_desc)
	    return ec_descr;
	
	return ec_brief;
    }

    public static String ECsummary(long EC) { return DecodeEC(EC, false); }
    public static String ECdescription(long EC) { return DecodeEC(EC, true); }
    
    public static String ESR(long dval) {
        long EC  = (dval>>26) & 0x3f;
        long IL  = (dval>>25) & 1;
        long ISS = dval & 0x1ffffff;

	String ec  = ECsummary(EC);
	String il  = "";
	String iss = "";
	
	return String.format("EC=0x%x (%s),IL=0x%x (%s),ISS=0x%x (%s)",EC,ec,IL,il,ISS,iss);
    }

    public static String ESR_EL1(long dval) { return ESR(dval); }
    public static String ESR_EL2(long dval) { return ESR(dval); }
    public static String ESR_EL3(long dval) { return ESR(dval); }

    static String phys_mem_size(long IPS) {
        String size;
        switch((int) IPS) {
          case 0: size = "32 bits"; break;
          case 1: size = "36 bits"; break;
          case 2: size = "40 bits"; break;
          case 3: size = "42 bits"; break;
          case 4: size = "44 bits"; break;
          case 5: size = "48 bits"; break;
          default: size = "?"; break;
        } 
        return size;
    }
    
    public static String TCR_EL1(long dval) {
        long TBI1  = (dval >> 38) & 0x1;
        long TBI0  = (dval >> 37) & 0x1;
        long AS    = (dval >> 36) & 0x1;
        long IPS   = (dval >> 32) & 0x7;
        long TG1   = (dval >> 30) & 0x3;
        long SH1   = (dval >> 28) & 0x3;
        long ORGN1 = (dval >> 26) & 0x3;
        long IRGN1 = (dval >> 24) & 0x3;
        long EPD1  = (dval >> 23) & 0x1;
        long A1    = (dval >> 22) & 0x1;
        long T1SZ  = (dval >> 16) & 0x3f;
        long TG0   = (dval >> 14) & 0x3;
        long SH0   = (dval >> 12) & 0x3;
        long ORGN0 = (dval >> 10) & 0x3;
        long IRGN0 = (dval >> 8)  & 0x3;
        long EPD0  = (dval >> 7) & 0x1;
        long T0SZ  = dval & 0x3f;

	return String.format("TBI1=%d,TBI0=%d,AS=%d,IPS=0x%x (%s),TG1=%d,SH1=%d,ORGN1=%d,IRGN1=%d,EPD1=%d,A1=%d,T1SZ=0x%x,TG0=%d,SH0=%d,ORGN0=%d,IRGN0=%d,EPD0=%d,T0SZ=0x%x",
			     TBI1,TBI0,AS,IPS,phys_mem_size(IPS),TG1,SH1,ORGN1,IRGN1,EPD1,A1,T1SZ,TG0,SH0,ORGN0,IRGN0,EPD0,T0SZ);
    }

    public static String TCR_EL2_3(long dval) {
        long TBI   = (dval >> 20) & 0x1;
        long PS    = (dval >> 16) & 0x3f;
        long TG0   = (dval >> 14) & 0x3;
        long SH0   = (dval >> 12) & 0x3;
        long ORGN0 = (dval >> 10) & 0x3;
        long IRGN0 = (dval >> 8)  & 0x3;
        long T0SZ  = dval & 0x3f;

	return String.format("TBI=%d,PS=0x%x (%s),TG0=%d,SH0=%d,ORGN0=%d,IRGN0=%d,T0SZ=%d",
			     TBI,PS,phys_mem_size(PS),TG0,SH0,ORGN0,IRGN0,T0SZ);
    }

    public static String TCR_EL2(long dval) { return TCR_EL2_3(dval); }
    public static String TCR_EL3(long dval) { return TCR_EL2_3(dval); }
    
    static String mem_type(long Attr) {
	if ( (Attr & 0xf0) == 0)
	    return "Device";
        return "Normal";
    }
    
    public static String MAIR(long dval) {
        long Attr7 = (dval>>56) & 0xff;
        long Attr6 = (dval>>48) & 0xff;
        long Attr5 = (dval>>40) & 0xff;
        long Attr4 = (dval>>32) & 0xff;
        long Attr3 = (dval>>24) & 0xff;
        long Attr2 = (dval>>16) & 0xff;
        long Attr1 = (dval>>8)  & 0xff;
        long Attr0 = dval & 0xff;

	return String.format("Attr7=0x%x (%s),Attr6=0x%x (%s),Attr5=0x%x (%s),Attr4=0x%x (%s),Attr3=0x%x (%s),Attr2=0x%x (%s),Attr1=0x%x (%s),Attr0=0x%x (%s)",
			     Attr7,mem_type(Attr7),Attr6,mem_type(Attr7),Attr5,mem_type(Attr7),Attr4,mem_type(Attr7),Attr3,mem_type(Attr7),Attr2,mem_type(Attr7),
			     Attr1,mem_type(Attr7),Attr0,mem_type(Attr7));
    }

    public static String MAIR_EL1(long dval) { return MAIR(dval); }
    public static String MAIR_EL2(long dval) { return MAIR(dval); }
    public static String MAIR_EL3(long dval) { return MAIR(dval); }

    public static String TTBR0(long dval) {
        long ASID  = (dval >> 48) & 0xffff;
        long BADDR = dval & 0xffffffffffffL;

	return String.format("ASID=0x%x,BADDR=0x%x",ASID,BADDR);
    }

    public static String TTBR0_EL1(long dval) { return TTBR0(dval); }
    public static String TTBR1_EL1(long dval) { return TTBR0(dval); }
    public static String TTBR0_EL2(long dval) { return TTBR0(dval); }
    public static String TTBR0_EL3(long dval) { return TTBR0(dval); }
    
    public static String HCR_EL2(long dval) {
        long TGE = (dval >> 27) & 0x1;
        long DC  = (dval >> 12) & 0x1;
        long VM  = dval & 0x1;

	return String.format("TGE=%d,DC=%d,VM=%d",TGE,DC,VM);
    }

    public static String PAR_EL1(long dval) { return ""; }

    public static String RMR_EL1(long dval) { return ""; }
    public static String RMR_EL2(long dval) { return ""; }
    public static String RMR_EL3(long dval) { return ""; }

    public static String TPIDR_EL0(long dval) { return ""; }
    public static String TPIDR_EL1(long dval) { return ""; }
    public static String TPIDR_EL2(long dval) { return ""; }
    public static String TPIDR_EL3(long dval) { return ""; }
}

