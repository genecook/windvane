	.file	"semihosting_end_test.s"

	.section text
	.text
	.globl	end_test
	.type	end_test, @function
end_test:
	#svc #0
	# display end-test message...

	mov w0,#4
	adr x1,exit_msg
	hlt #0xf000

	
	# armv8 semihosting 'call' to end-simulation...
	mov w0,#0x18
        mov x1,#0
	hlt #0xf000
	
exit_msg:
	.asciz "Test ends correctly."
	
