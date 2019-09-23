	.file	"b_0x80000000.s"

	.section text, "ax"
	.text
	.globl	main
	.type	main, @function
main:
	# force data alignment?...

	#mrs x1,sctlr_el3
	#orr x1,x1,#2
	#msr sctlr_el3,x1

	mov x1,#0x80000000
	br  x1
