	.file	"bootel1toel0.s"

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
	# setup saved pstate to get to el0...
	mov x1,#0x3c0
	msr spsr_el1,x1
	# 'return' to el0, at core-unique adress...
	eret
	
