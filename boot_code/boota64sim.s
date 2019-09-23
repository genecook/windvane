	.file	"bootasim.s"

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	add x1,x1,#1
	lsl x1,x1,#12
	br  x1
