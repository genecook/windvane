	.file	"boot2el0foobar.s"

	.section text
	.text
	.align 2
	.global main, _start
	.type	main, %function
main:
_start:
	# retreive this cores ID, use to form core-specific address...
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	add x1,x1,#1
	lsl x1,x1,#12
	# move 'return address' to ELR_EL3...
	msr elr_el3,x1
	# move also into el0 stack pointer. thus stack will live
	# just below el0 'entry point'...
	msr sp_el0,x1
	# setup saved pstate to get to el0...
	mov x1,#0x3c0
	msr spsr_el3,x1
	# 'return' to el0, at core-unique address...
	eret
	.align 12
	# call C code...
	bl foobar
	
	
