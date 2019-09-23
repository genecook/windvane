	.file	"bootel1toel0.s"

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	# retreive this cores ID, use to form core-specific address...
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	mov x2,x1
	add x1,x1,#1
	lsl x1,x1,#12
	# move 'return address' to ELR_EL1...
	msr elr_el1,x1
	# setup saved pstate to get to el0...
	mov x1,#0x3c0
	msr spsr_el1,x1

	# load address of 'sync' byte in x3...
	movk x3,0x200
	
	# core 0 will decrement the 'sync' byte 'til zero. other cores will wait...
	cbnz x2,not_core0

	# decrement byte at sync address 'til zero...
core0:
decloop:
	ldrb w2,[x3]
	cbz w2,gotoel0
	sub w2,w2,1
	strb w2,[x3]
	b decloop
	# core 0 never gets here

not_core0:
	ldrb w2,[x3]
	cbnz w2,gotoel0
	# fall thru...
gotoel0:
	# 'return' to el0, at core-unique address...
	eret

	.align 9
syncbyte:
        .byte 2


