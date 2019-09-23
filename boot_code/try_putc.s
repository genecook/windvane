	.arch armv8-a+fp+simd
	.file	"try_putc.c"
	.text
	.align	2
	.global	try_putc
	.type	try_putc, %function
try_putc:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	w0, [x29, 28]
	ldr	w0, [x29, 28]
	bl	putchar
	str	w0, [x29, 44]
	ldr	w0, [x29, 44]
	ldp	x29, x30, [sp], 48
	ret
	.size	try_putc, .-try_putc
	.global	ts
	.data
	.align	3
	.type	ts, %object
	.size	ts, 9
ts:
	.string	"hi mom!\n"
	.text
	.align	2
	.global	try_puts
	.type	try_puts, %function
try_puts:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	w0, [x29, 28]
	ldr	w0, [x29, 28]
	bl	putchar
	str	w0, [x29, 44]
	adrp	x0, ts
	add	x0, x0, :lo12:ts
	bl	puts
	mov	w1, w0
	ldr	w0, [x29, 44]
	orr	w0, w0, w1
	str	w0, [x29, 44]
	ldr	w0, [x29, 44]
	ldp	x29, x30, [sp], 48
	ret
	.size	try_puts, .-try_puts
	.ident	"GCC: (crosstool-NG crosstool-ng-1.21.0-110-gb634280) 5.2.0"
	.section	.note.GNU-stack,"",%progbits
