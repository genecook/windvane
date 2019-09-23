TOOLS_BIN := /usr/bin/

GASM := ${TOOLS_BIN}/aarch64-linux-gnu-as
GCC  := ${TOOLS_BIN}/aarch64-linux-gnu-gcc
LD   := ${TOOLS_BIN}/aarch64-linux-gnu-ld
AR   := ${TOOLS_BIN}/aarch64-linux-gnu-gcc-ar


all: boota64sim.obj boot2el0.elf boot2el0_foundation_model_debug.elf b_0x80000000.obj \
     semihosting_end_test.obj and_imm.obj try_sysop.obj boot2kernel.obj bootel1toel0.obj \
     boot2el0SVC.obj boot2el0SVCnextInstr.obj boot2el0MMUon.obj boot2el0MMUon16K.obj \
     boot2el0MMUon64K.obj try_semihost_op.obj hello_world.C

clean:
	rm -f *.obj *.elf *.lst hello_world.s


boota64sim.obj: boota64sim.s
	${GASM} $< -o $@


boot2el0.obj: boot2el0.s
	${GASM} -a=boot2el0.lst $< -o $@

boot2el0.elf: boot2el0.obj boot2el0.ld
	${LD} -o boot2el0.elf -e 0x80000000 -T ./boot2el0.ld $<


boot2el0_foundation_model_debug.obj: boot2el0_foundation_model_debug.s
	${GASM} -a=boot2el0_foundation_model_debug.lst $< -o $@

boot2el0_foundation_model_debug.elf: boot2el0_foundation_model_debug.obj boot2el0.ld
	${LD} -o boot2el0_foundation_model_debug.elf -e 0x80000000 -T ./boot2el0.ld $<


b_0x80000000.obj: b_0x80000000.s
	${GASM} $< -o $@


semihosting_end_test.obj: semihosting_end_test.s
	${GASM} $< -o $@


and_imm.obj: and_imm.s
	${GASM} -a=and_imm.lst $< -o $@

try_sysop.obj: try_sysop.s
	${GASM} $< -o $@

boot2kernel.obj: boot2kernel.s
	${GASM} $< -o $@

bootel1toel0.obj: bootel1toel0.s
	${GASM} $< -o $@

boot2el0SVC.obj: boot2el0SVC.s
	${GASM} $< -o $@

boot2el0SVCnextInstr.obj: boot2el0SVCnextInstr.s
	${GASM} $< -o $@

boot2el0MMUon.obj: boot2el0MMUon.s
	${GASM} $< -o $@

boot2el0MMUon16K.obj: boot2el0MMUon16K.s
	${GASM} $< -o $@

boot2el0MMUon64K.obj: boot2el0MMUon64K.s
	${GASM} $< -o $@


try_semihost_op.obj: try_semihost_op.s
	${GASM} $< -o $@


hello_world.s: hello_world.C
	${GCC} -S $< -o $@ 




