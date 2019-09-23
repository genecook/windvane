	.arch armv8-a+fp+simd
	.file	"try_float.c"
	.text
	.align	2
	.global	foobar
	.type	foobar, %function
foobar:
	sub	sp, sp, #16
	fmov	s0, wzr
	str	s0, [sp, 12]
	ldr	s1, [sp, 12]
	fmov	s0, 1.0e+0
	fadd	s0, s1, s0
	str	s0, [sp, 12]
	nop
	add	sp, sp, 16
	ret
	.size	foobar, .-foobar
	.ident	"GCC: (crosstool-NG crosstool-ng-1.21.0-110-gb634280) 5.2.0"
	.section	.note.GNU-stack,"",%progbits
