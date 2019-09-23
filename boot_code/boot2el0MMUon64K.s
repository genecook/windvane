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
	
	# setup saved pstate to get to el0...
	
	mov x3,#0x3c0
	msr spsr_el3,x3

	
	# setup mmu...
	
	# set page table base address for this core, since we have a usable value...
	# all cores to have same page table base address

	movz x1,#0x8000,lsl #16
	msr ttbr0_el1,x1
	
	# set TCR_EL1 - same for all cores

	# TCR_EL1.TG0=1 - page_size 64k
	
	movz x3,#0x4020
	movk x3,#0x8080,lsl #16
	
	msr tcr_el1,x3

        #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        #!!!   NO DESCRIPTORS - REQUIRES PAGE-MAPPER !!!
        #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	movz x1,#0x19b
	msr sctlr_el1,x1
	isb
	
	# mmu should be enabled at el0/el1 after eret...
	
	
	# 'return' to el0, to core-unique address...

        eret

	# next instruction address should be aligned to next page, ie, 0x1000...
	
