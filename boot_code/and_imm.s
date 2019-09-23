	.file	"and_imm.s"

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	# retreive this cores ID, use to form core-specific address...
	mrs x1,mpidr_el1

	#adr X14,0x146cdc/4
	adr X14, 0xffffc
	
	and x1,x1,#0x1
	and x1,x1,#0x2
	and x1,x1,#0x3
	and x1,x1,#0x4
	and x1,x1,#0x6
	and x1,x1,#0x7
	and x1,x1,#0x8
	and x1,x1,#0xf
	and x1,x1,#0x3f
	and x1,x1,#0xff
	and x1,x1,#0x3ff
	and x1,x1,#0x7ff
	and x1,x1,#0xfff
	and x1,x1,#0x1fff
	and x1,x1,#0x3fff
	and x1,x1,#0xffff
	and x1,x1,#0x1ffff
	and x1,x1,#0x3ffff
	and x1,x1,#0x7ffff
	and x1,x1,#0xfffff
	and x1,x1,#0x1fffff
	and x1,x1,#0x3fffff
	and x1,x1,#0x7fffff
	and x1,x1,#0x1ffffff
	and x1,x1,#0x3ffffff
	and x1,x1,#0x7ffffff
	and x1,x1,#0xfffffff
	and x1,x1,#0x1fffffff
	and x1,x1,#0x3fffffff
	and x1,x1,#0x7fffffff
	and x1,x1,#0xffffffff
	wfi
	


	
	


	
