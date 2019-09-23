	.file	"bootasim.s"

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	# get current page address...
        adrp x0, main
	
	# retreive this cores ID, use to form core-specific address...
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	add x1,x1,#1
	lsl x1,x1,#12

	add x1,x1,x0
	
	# move 'return address' to ELR_EL3...
	msr elr_el3,x1
	
	# setup saved pstate to get to el0, mask interrupts...
	#mov x1,#0x3c0
	mov x1,#0
	msr spsr_el3,x1
	
	# set hcr_el2, sctlr_el1 to known values...
	msr hcr_el2,xzr
	msr sctlr_el2,xzr
	msr sctlr_el1,xzr

	# set cptr_el3,cpacr_el1,fpcr to known values...
	msr fpcr,xzr
	msr cptr_el3,xzr
	movz x1,#0x30,lsl #16
	msr cpacr_el1,x1
	
	# set scr_el3, bit 10, to insure 64 bit operation at el0, el1, el2...
	mrs x0,scr_el3
	orr x0,x0,#(1<<10)
	msr scr_el3,x0

	# clear out floating pt flags..
	mov x1,#0
	msr fpsr,x1
	# 'return' to el0, at core-unique adress...
	eret
	
