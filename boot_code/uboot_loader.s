	.file	"uboot_loader.s"

#---------------------------------------------------------------------------------
# some system calls:
	# pass up to six arguments in x0 thru x5. return value is in x0
#	movz w0,#0x16 - SWI: heapinfo
#	hlt #0xf000 or svc #0

#	ldr w1,_hello - load (32 bit?) pointer
#	movz w0,#0x04 - SWI: write0
#	hlt #0xf000
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# register conventions:
#	x30 - link register
#	x29 - frame register
#	x19 - x29 - callee-saved
#	x16 - x18 - scratch
#	x9 - x15 - local registers
#	x8 - indirect return address
#	x0 - x7 - subroutine args
#---------------------------------------------------------------------------------

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	# retreive this cores ID, use to form core-specific address...
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	add x1,x1,#1
	lsl x1,x1,#12
	
	# move 'return address' to ELR_EL1...
	msr elr_el1,x1
	
	# setup (small) stack...
	add sp,x1,2048
	msr sp_el0,x1

	# setup saved pstate to get to el0...
	mov x1,#0x3c0
	msr spsr_el1,x1
	
	# 'return' to el0, at core-unique adress...
	eret
	
	.align 12
initregs:
	# init some regs to keep simulator from sqawking (need to fix simulator!)
	
	mov x0,#0
	mov x1,#0
	mov x2,#0
	mov x3,#0
	mov x4,#0
	mov x5,#0
	mov x6,#0
	mov x7,#0
	mov x8,#0
	mov x9,#0

	mov x10,#0
	mov x11,#0
	mov x12,#0
	mov x13,#0
	mov x14,#0
	mov x15,#0
	mov x16,#0
	mov x17,#0
	mov x18,#0

	mov x19,#0
	mov x20,#0
	mov x21,#0
	mov x22,#0
	mov x23,#0
	mov x24,#0
	mov x25,#0
	mov x26,#0
	mov x27,#0
	mov x28,#0
	mov x29,#0
	mov x30,#0

	# .init...
init:
	stp x29,x30,[sp,-16]!
	mov x29,sp

	# jump to uboot code, cross yer fingers...
	movz x16,#0x50, LSL #16
	blr x16

	# done?...
done:
	wfi

	
