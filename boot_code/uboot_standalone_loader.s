	.file	"uboot_standalone_loader.s"

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
	add sp,x1,8192
	msr sp_el0,x1

	# setup saved pstate to get to el0...
	mov x1,#0x3c0
	msr spsr_el1,x1
	
	# 'return' to el0, at core-unique address...
	eret
	
	.align 12
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

	# store runtime 'table' entry for printf...
	movz x18,#0x21b8
	movz x1,#0x20c8
	str x1,[x18]
	movz x18,#0x20f0
	movz x1,#0x2000
	str x1,[x18]

	
	stp x29,x30,[sp,-16]!
	mov x29,sp

	# jump to uboot code, cross yer fingers...
	movz x16,#0xc10, LSL #16
	blr x16

	# done?...
	wfi

	.align 12
# address is now 0x2000
	svc 0
	ret x30
	

	#table offset - what is is...
	0	exit
	8	getc
	16	tstc
	24	putc
	32	puts
	40	printf
	48	install_hdlr
	56 	free_hdlr
	64	malloc
	72	free
	80	udelay
	88	get_timers
	96	vprintf
	104	do_reset
	112	getenv
	120	setenv
	128	simple_strtoul
	136	strict_strtoul
	144	simple_strtol
	152	strcmp
	160	i2c_write
	168	i2c_read
	176	spi_init
	184	spi_setup_slave
	192	spi_free_slave
	200	spi_claim_bus
	208	spi_release_bus
	216	spi_xfer
	224	ustrtoul
	232	ustrtoull
	240	strcpy
	248	mdelay
	
	
