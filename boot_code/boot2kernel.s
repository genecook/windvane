	.file	"boot2kernel.s"

	.section text
	.text
	.align 2
	.globl	main
	.type	main, @function
main:
	ldr x6, =0x8008080000     // lets start stack below the kernel...
        msr sp_el0,x6

	# setup saved pstate to get to el1/sp0...

	mov x1,#0x3c4
	msr spsr_el3,x1

	nop
	
        # load kernel start address, go there...
	
        ldr x0, =0x8008190a60     // device tree blob
	ldr x6, =0x8008080000     // kernel start address

	# move 'return address' to ELR_EL3...

	msr elr_el3,x6

        mrs x1,daif
        msr daifset,#2

        eret
	
