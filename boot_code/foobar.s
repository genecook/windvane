	.arch armv8-a+fp+simd
	.file	"foobar.C"
	.text
	.align	2
	.global	foobar
	.type	foobar, %function
foobar:
.LFB0:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, 12]
.L3:
	ldr	w0, [sp, 12]
	cmp	w0, 31
	bgt	.L4
	ldr	w0, [sp, 12]
	add	w0, w0, 64
	str	w0, [sp, 8]
	ldr	w0, [sp, 12]
	add	w0, w0, 1
	str	w0, [sp, 12]
	b	.L3
.L4:
	nop
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	foobar, .-foobar
	.ident	"GCC: (crosstool-NG crosstool-ng-1.21.0-110-gb634280) 5.2.0"
	.section	.note.GNU-stack,"",%progbits
