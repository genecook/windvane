	.file	"try_semihost.s"

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	mov x0,3
	mov x1,'\n'
	hlt #0xf000

	mov x0,3
	mov x1,'H'
	hlt #0xf000
	mov x0,3
	mov x1,'E'
	hlt #0xf000
	mov x0,3
	mov x1,'L'
	hlt #0xf000	
	mov x0,3
	mov x1,'L'
	hlt #0xf000
	mov x0,3
	mov x1,'O'
	hlt #0xf000

	mov x0,3
	mov x1,' '
	hlt #0xf000

	mov x0,3
	mov x1,'W'
	hlt #0xf000

	mov x0,3
	mov x1,'O'
	hlt #0xf000

	mov x0,3
	mov x1,'R'
	hlt #0xf000

	mov x0,3
	mov x1,'L'
	hlt #0xf000

	mov x0,3
	mov x1,'D'
	hlt #0xf000

	mov x0,3
	mov x1,'!'
	hlt #0xf000

	mov x0,3
	mov x1,'\n'
	hlt #0xf000
	
	wfi
	
