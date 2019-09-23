	.file	"bootasim.s"

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
	# move 'return address' to ELR_EL3...
	msr elr_el3,x1
	# setup saved pstate to get to el0...
	mov x1,#0x3c0
	msr spsr_el3,x1

	# should be S1E1R...
	sys #0, c7, c8, #0  
        # alias too...
        at s1e1r, x15

	# end test...
	wfi
