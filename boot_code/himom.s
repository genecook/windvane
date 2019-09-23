	.arch armv8-a+fp+simd
	.file	"himom.c"
	.section	.rodata
	.align	3
.LC0:
	.string	"w"
	.align	3
.LC1:
	.string	"foobar"
	.align	3
.LC2:
	.string	"baz"
	.text
	.align	2
	.global	foobar
	.type	foobar, %function
foobar:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	adrp	x0, .LC0
	add	x1, x0, :lo12:.LC0
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	fopen
	str	x0, [x29, 24]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	ldr	x3, [x29, 24]
	mov	x2, 3
	mov	x1, 1
	bl	fwrite
	ldr	x0, [x29, 24]
	bl	fclose
	nop
	ldp	x29, x30, [sp], 32
	ret
	.size	foobar, .-foobar
	.ident	"GCC: (crosstool-NG crosstool-ng-1.21.0-110-gb634280) 5.2.0"
	.section	.note.GNU-stack,"",%progbits
