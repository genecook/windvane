include ./Makefile.inc

# with a few exceptions, as noted, here are all the object files to be built:

SIM_SRCS = src/a64sim.C src/a64packet.C src/a64State.C src/a64memory.C src/a64PhysicalMemory.C src/decodeA64.C src/executeA64.C \
           src/executeFloatA64.C src/disasm_utils.C src/disasm.C src/system_registers.C src/a64exceptions.C src/a64_vmsa.C \
           src/a64sim_monitor.C src/SemiHosting.C src/a64SemiHosting.C src/Real.C src/uart.C src/uart_pl011.C src/a64gic.C \
           src/system_counter_module.C src/timer.C src/SimTrace.C src/TCPServer.C src/ELFIO.C src/X64Simulator.C \
           src/a64Scaffold.C src/TCPClient.C src/a64sim_debug.C src/a64DebugServer.C src/RSP.C src/a64sim_user_space.C \
           src/a64simUserSpace.C

SIM_OBJS = $(SIM_SRCS:$(SRC_DIR)/%.C=$(OBJ_DIR)/%.o)
SIM_DEPS = $(SIM_SRCS:$(SRC_DIR)/%.C=$(DEPS_DIR)/%.d)


# a couple of object file sets, used to build particular libs and/or executables:

SIM_OBJSX := obj/a64sim.o obj/a64packet.o obj/a64State.o obj/a64memory.o obj/a64PhysicalMemory.o obj/decodeA64.o obj/executeA64.o \
             obj/executeFloatA64.o obj/executeHalfFloatA64.o obj/vfpMathA64.o obj/vfpFPtoFixed.o \
             obj/disasm_utils.o obj/disasm.o obj/system_registers.o obj/a64exceptions.o obj/a64_vmsa.o \
             obj/a64sim_monitor.o obj/SemiHosting.o obj/a64SemiHosting.o obj/Real.o obj/uart.o obj/uart_pl011.o obj/a64gic.o \
             obj/system_counter_module.o obj/timer.o

SIM_OBJSX_UTILS := obj/elfio.o proto/scaffold.o obj/SimTrace.o obj/TCPServer.o obj/ELFIO.o



# vfpMathA64.o vfpFPtoFixed.o executeHalfFloatA64.o - use special compile options - leave out of general dependencies:

VFP_OBJS = obj/vfpMathA64.o obj/vfpFPtoFixed.o obj/executeHalfFloatA64.o

# elfio.c - C code. leave out of general dependencies:

ELFIO_C_CODE = obj/elfio.o

# general rules for generating dependencies, object-files:

$(DEPS_DIR)/%.d: $(SRC_DIR)/%.C
	$(GPP) $(CPPFLAGS) -MM $(SRC_DIR)/$(*).C | perl -ne 's/^(\w+\.o)/obj\/$$1/;print;' > $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.C $(DEPS_DIR)/%.d
	$(GPP) $(CPPFLAGS) -fPIC -c $< -o $@

.PHONY: all clean test

all: bin/a64sim lib/liba64simUserSpace.so lib/libsimX.a lib/libsimXutils.a bin/show_simtrace bin/show_simtrace_history \
     bin/show_sim_monitor_trace bin/show_memtrace bin/show_memtrace_summary


# a64Sim - mp-enabled simulator wrapper, class + main...

bin/a64sim:  src/X64Sim.C lib/libsimD.a
	g++ $(CFLAGS) -o $@ $< $(PROTOLIBDIRS) $(LIBDIRS) -lsimD -ldl ${STATIC_BOOSTLIB} ${STATIC_PROTOLIB} ${STATIC_LIBELF}

# test - generate/resimulate a single test:
#    rndcode_test - four cores, 1k instrs max per core, boots at el3 but generates/executes random instructions at el0.
#    Generate the test, then resimulate same. Generate simulation trace file.
#    We expect each simulation log to indicate that at least 4k instrs were simulated.
#    The simulated instructions for all cores from each log (sorted) should match.
#    The initial random seed is fixed, but we do expect that any random seed could be employed.
#
#    what are we really doing here? - simply confirming that the simulator produces consistent and expected results.*
#       NOTE: this simple-minded test does NOT confirm that the generated test is architectually valid.

test: bin/a64sim
	cd boot_code;make boot2el0.obj
	rm -f tlog tlog2 tlog.core2 tlog2.core2
	bin/a64sim -N 4 -n 1000 -F -L boot_code/boot2el0.obj --seed 1234567 -D -S rndcode_test.elf -T rndcode_test 1>tlog 2>&1
	wc -l <tlog | /usr/bin/perl -ne 'die if /(\d+)/ and (0 + $$1) < 4000;'
	bin/a64sim -N 4 -n 1000 -L rndcode_test.elf -D 1>tlog2 2>&1
	wc -l <tlog2 | /usr/bin/perl -ne 'die if /(\d+)/ and (0 + $$1) < 4000;'
	grep '  0x' tlog | sort 1>tlog.core2 2>&1
	grep '  0x' tlog2 | sort 1>tlog2.core2 2>&1
	diff tlog.core2 tlog2.core2


# 'user-space' dll...

lib/liba64simUserSpace.so: obj/a64simUserSpace.o
	g++ $(CFLAGS) -shared -o $@ $^

lib/libsimX.a: $(SIM_OBJSX)
	ar rvs lib/libsimX.a $^

lib/libsimXutils.a: $(SIM_OBJSX_UTILS)
	ar rvs lib/libsimXutils.a $^


# sim-trace related tools:

bin/show_simtrace: src/show_simtrace.C lib/libsimD.a
	g++ $(CFLAGS) -o $@ $< $(PROTOLIBDIRS) $(LIBDIRS) -lsimD -lprotobuf

bin/show_simtrace_history: src/show_simtrace_history.C lib/libsimD.a
	g++ $(CFLAGS) -o $@ $< $(PROTOLIBDIRS) $(LIBDIRS) -lsimD -lprotobuf

bin/show_sim_monitor_trace: src/show_a64sim_monitor_summary.C lib/libsimD.a
	g++ $(CFLAGS) -o $@ $< $(PROTOLIBDIRS) $(LIBDIRS) -lsimD -lprotobuf

bin/show_memtrace: src/show_memtrace.C lib/libsimD.a 
	g++ $(CFLAGS) -o $@ $< $(PROTOLIBDIRS) $(LIBDIRS) -lsimD -lprotobuf

bin/show_memtrace_summary: src/show_memtrace_summary.C lib/libsimD.a
	g++ $(CFLAGS) -o $@ $< $(PROTOLIBDIRS) $(LIBDIRS) -lsimD -lprotobuf


# libsimD.a - static linked version of simulator + scaffold. C++ scaffold/simulator 'interface'...

lib/libsimD.a: $(SIM_OBJS) $(VFP_OBJS) $(ELFIO_C_CODE) proto/scaffold.o obj/SimTrace.o ${PBJSON}/src/pbjson.o 
	ar rvs lib/libsimD.a $^

lib/libRSP.o: obj/RSP.o
	ar rvs lib/libRSP.a obj/RSP.o


# script used to generate 'register info' source code from list of supported registers...

derived/A64SIMREG_ENUMS.h derived/A64SIMREG_INITS.C derived/A64SIMREG_CASES.C derived/A64SIMREG_ACCESS_CASES.C derived/A64SIMREG_RESERVE_CASES.C: utils/make_all_regs.pl utils/allregs.txt
	./utils/make_all_regs.pl

clean_utils:
	rm -f derived/A64SIMREG_ENUMS.h derived/A64SIMREG_INITS.C derived/A64SIMREG_CASES.C derived/A64SIMREG_ACCESS_CASES.C derived/A64SIMREG_RESERVE_CASES.C


# some notes on particular source code files:

# a64Scaffold.C - scaffold class includes an instance of the simulator and memory. 
# src/a64sim.C - collection of Packet class methods, most of Control class methods
# src/a64memory.C - Memory class methods - memory + TLB/VMSA instances
# src/a64PhysicalMemory.C - Physical Memory class methods - physical memory
# src/decodeA64.C - Control instruction decoder related methods. Makes use of auto-generated instruction decoder
# src/executeA64.C - Control instruction execution related methods. 
# src/disasm.C - Control/Disassemble method. Makes use of auto-generated instruction disassembler
# src/disasm_utils.C - disassembly related utilities
# src/system_registers.C - State class methods used to manage system registers. All system registers are

#  'State'. A cpu includes 'State'. System registers are accessed via MRS/MSR at the assembly language level,
#  and accessed correspondingly programmatically via the MRS/MSR fields

# src/a64exceptions.C - ExceptionEnables class used to determine at runtime which exceptions to allow/disallow.
#                       Architectual as well as testbed exception classes supported
#                       Control class exception-related methods

# src/a64_vmsa.C - class implementing A64 VMSA. In this 'implementation': 64bit VMSA only, all page sizes


# vfp related code:

obj/vfpMathA64.o: src/vfpMathA64.C include/a64_vfpMath.h
	g++ ${VFP_CFLAGS} -fPIC -c $< -o $@

obj/vfpFPtoFixed.o: src/vfpFPtoFixed.C include/a64_vfpMath.h
	g++ ${VFP_CFLAGS} -fPIC -c $< -o $@

obj/executeHalfFloatA64.o: src/executeHalfFloatA64.C
	g++ ${HALF_VFP_CFLAGS} -fPIC -c $< -o $@


# the lone C file:

obj/elfio.o: src/elfio.c
	$(GCC) ${LIBELF_INCLUDES} -fPIC -c $< -o $@

clean:
	rm -f depends/*.d bin/a64sim bin/show_memtrace bin/show_memtrace_summary bin/show_sim_monitor_trace \
           bin/show_simtrace bin/show_simtrace_history lib/*.a lib/*.so obj/*.o rndcode_test.* tlog* \
	make clean_utils

include $(SIM_DEPS)
