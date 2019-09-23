	.file	"bootasim.s"

	.section text
	.text
	.align 2
	.globl	main
	.type	main, @function

main:
	# retreive this cores ID, use to form core-specific address...
	
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	mov x2,x1

	add x1,x1,#1
	lsl x1,x1,#12
	
	# move 'return address' to ELR_EL3...
	msr elr_el3,x1
	
	# set page table base address for this core, since we have a usable value...
	# force all cores to have same page table base address
	movz x1,#1
	lsl x1,x1,#28
	
	msr ttbr0_el1,x1
	
	# setup saved pstate to get to el0...
	mov x3,#0x3c0
	msr spsr_el3,x3
	
	# setup mmu...
	
	# 1st set TCR_EL1 - same for all cores - value: 0xa8a0a8a0...

	#mov x1 <--- #0xa8a0a8a0

	movz x3,#0x2820
	movk x3,#0xa8a0,lsl #16
	
	msr tcr_el1,x3

	# for 4k page size - maximum trans table size = 512 * 8 = 4096
	
	# TTBR0_EL1 already set - page table base for this core (core ID << 12 (28 - 16) to yield unique ttbr for each core
        
	# (core 0 only) write descriptors covering page zero, then core-specific starting address...

	# descriptor value:
	# bits 0,1 = b01 - block format
	# 63 - 52 - upper block attrs - 0
	# 
	# 47 - 12 - same as LA to be mapped, ie, make it 1 to 1
	# 11 -2 - lower block attrs 0b00 10  ap[2:1] 0

	# 0x00000001 

	#cmp x2,#0
	#bne skip_desc_inits

	# write zero level translation table...

	# x1 - table entry address
	# x2 - table entry (1st level block descriptor address shifted right 16 bits + descriptor id in bits 0,1)

	movz x1,#1
	lsl x1,x1,#12

	add x1,xzr,x1,lsl #16

	orr x2,xzr,x1
	add x2,x2,x2
	add x2,x2,#3
	
	str x2,[x1],#0
	
	# write first level block descriptor...

        add x1,x1,x1
	movz x2,#0xcc0
	add x2,x2,#1
	str x2,[x1],#0
	
	# issue dsb, isb, then enable paging (EL0,EL1 only, secure mode) via SCTLR_EL1 - value: 0x300019b

	dsb #0
	isb #0
	
skip_desc_inits:	
	movz x1,#0x19b
	msr sctlr_el1,x1
	
	# 'return' to el0, to core-unique address...

        eret

	# next instruction address should be aligned to next page, ie, 0x1000...
	
