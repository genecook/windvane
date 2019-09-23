	.file	"bootasim.s"

	.section text
	.text
	.globl	main
	.type	main, @function
main:
	# get current page address...
        adrp x0, main
	
	# setup el3,el1 vbar - needed for processing exceptions...
	#msr vbar_el3,x0
	msr vbar_el1,x0
	
	# retreive this cores ID, use to form core-specific address...
	mrs x1,mpidr_el1
	and x1,x1,#0x7f
	add x1,x1,#1
	lsl x1,x1,#13

	add x1,x1,x0
	
	# move 'return address' to ELR_EL3...
	msr elr_el3,x1
	
	# setup saved pstate to get to el0, mask interrupts...
	#mov x1,#0x3c0
	mov x1,#0
	msr spsr_el3,x1
	
	# set hcr_el2, sctlr_el1 to known values...
	msr hcr_el2,xzr
	msr sctlr_el2,xzr
	msr sctlr_el1,xzr

	# set cptr_el3,cpacr_el1,fpcr to known values...
	msr fpcr,xzr
	msr cptr_el3,xzr
	movz x1,#0x30,lsl #16
	msr cpacr_el1,x1
	
	# set scr_el3, bit 10, to insure 64 bit operation at el0, el1, el2...
	mrs x0,scr_el3
	orr x0,x0,#(1<<10)
	msr scr_el3,x0
	mov x0,xzr

	# clear out floating pt flags..
	mov x1,#0
	msr fpsr,x1

	# enable/setup debug software step...
	bl enable_single_step

	# clear out flags...
	mov x1,#0
	msr nzcv,x1

	eret
	
	# any exception that occurs at el0 should here:
	.align 10

//	bl dumpexc
	mov x26,x30
	bl dumpexc_single_step
	mov x30,x26
	eret
	
	mov w0,#0x18
	mov x1,#0
	hlt #0xf000


#====================================================================
# Dump exception state...	
#====================================================================

	# -------------------------------------------------------------
	# hex_prefix - output '0x' before hex number (of course)...
	#   x0 - scratch*
	#   x1 - scratch
	#
	# *NOTE: any register noted as 'scratch' WILL be overwritten!!!
	# -------------------------------------------------------------
	.macro hex_prefix
        movz x0,#3
	adr x1,digits
	hlt #0xf000
	
        movz x0,#3
	adr x1,cX
	hlt #0xf000

	.endm

	# -------------------------------------------------------------
	# newline macro...
	# -------------------------------------------------------------
	.macro newline
	movz x0,#3
	adr x1,nl
	movz x0,'\n      // HACK HACK - NEED TO RESTRICT ADDRESS SPACE
	strb w0,[x1]     //  HACK HACK...  BASED ON PRIVILEGE LEVEL!!!!!
	movz x0,#3
	hlt #0xf000
	.endm

	# -------------------------------------------------------------
	# slash macro...
	# -------------------------------------------------------------
	.macro slash
	movz x0,#3
	adr x1,sl
	hlt #0xf000
	.endm

	# -------------------------------------------------------------
	# push/pop/peek macros...
	# -------------------------------------------------------------
	.macro push rname
	str \rname,[SP,#-8]!
	.endm
	.macro pop rname
	ldr \rname,[SP],#8
	.endm
	.macro peek rname
	ldr \rname,[SP]
	.endm
	
	# -------------------------------------------------------------
	# callsub - call subroutine, saving/restoring current return
	#           address (x30), to allow nested calls...
	# -------------------------------------------------------------
	.macro callsub subname
	push x30
	bl \subname
	pop x30
	.endm

	# -------------------------------------------------------------
	# save_app_regs - save off x0..x30, sp...
	#
	# *NOTE: X27, X28 values are trashed!
	# -------------------------------------------------------------

	.macro save_app_registers_small
	mrs x27,sp_el0       // save SP value
	
	adr x28,exc_stack    // load 'local'
	mov sp,x28           //   stack pointer

	push x0              //
	push x1              // save scratch register
	push x2              //   contents
	push x3              //
	push x4              //

	push x29             // save 'frame pointer',
	push x30             //   return-address reg
	
	mov x29,sp           // now can access the saved state as necessary
	.endm

	.macro peek_sp dreg
	mov \dreg,x27
	.endm
	
	.macro peek_x30 dreg
	mov \dreg,x26
	.endm

	.macro peek_x29 dreg
	ldr \dreg,[x29,#8]
	.endm
	.macro peek_x4 dreg
	ldr \dreg,[x29,#16]
	.endm
	.macro peek_x3 dreg
	ldr \dreg,[x29,#24]
	.endm
	.macro peek_x2 dreg
	ldr \dreg,[x29,#32]
	.endm
	.macro peek_x1 dreg
	ldr \dreg,[x29,#40]
	.endm
	.macro peek_x0 dreg
	ldr \dreg,[x29,#48]
	.endm


	.macro restore_app_registers_small
	pop x30            // restore return address reg,
	pop x29            //   frame pointer,
	pop x4             //
	pop x3             //
	pop x2             //  scratch registers,
	pop x1             //
	pop x0             //
	msr sp_el0,x27     // restore SP
	.endm


	
	.macro save_app_registers
	mov x27,sp           // save SP value
	
	adr x28,exc_stack    // load 'local'
	mov sp,x28           //   stack pointer

	// save x4..x29...
	push x4
	push x5
	push x6
	push x7
	push x8
	push x9
	
	push x10
	push x11
	push x12
	push x13
	push x14
	push x15
	push x16
	push x17
	push x18
	push x19
	
	push x20
	push x21
	push x22
	push x23
	push x24
	push x25
	push x26
	push x27
	push x28
	push x29

	// save x0..x3 - using these regs, so make it easier
	//   to access their saved values...
	push x0      // x29 + 24
	push x1      // x29 + 16
	push x2      // x29 + 8
	push x3      // x29
	
	mov x29,sp      // now can access the saved state as necessary,
	.endm

	.macro restore_app_registers
	pop x29
	pop x28
	pop x27
	pop x26
	pop x25
	pop x24
	pop x23
	pop x22
	pop x21
	pop x20
	
	pop x19
	pop x18
	pop x17
	pop x16
	pop x15
	pop x14
	pop x13
	pop x12
	pop x11
	pop x10
	
	pop x9
	pop x8
	pop x7
	pop x6
	pop x5
	pop x4
	
	pop x3
	pop x2
	pop x1
	pop x0

	mov sp,x27         // restore SP
	.endm
	
	# -------------------------------------------------------------
	# putull - output register (x3) contents in hex...
	#
	#   x2 - value to print
	#   x3 - low-order bit of left-most hex digit to start at
	# -------------------------------------------------------------

putull:
	hex_prefix       // print '0x'

putull_loop:	
	mov x0,x2        //
	lsr x0,x0,x3     //
	and x0,x0,#0xf   // isolate next hex digit to print,
	
	adr x1,digits    //   use as index 
	add x1,x1,x0     //      into hex digits string
	
	movz x0,#3       // print
	hlt #0xf000      //   it
	
	sub x3,x3,#4     //
	cmp x3,#0        // loop 'til count underflows...
	bge putull_loop  //

	ret

	# -------------------------------------------------------------
	# putstr - output string.
	#
	#   x1 - pointer to string
	#   x2 - number of characters to print
	# -------------------------------------------------------------

putstr:

ps_loop:
	movz x0,#3      // output 
	hlt #0xf000     //   next character

	add x1,x1,#1    // advance str pointer,
        sub x2,x2,#1	//   decrement count

	cmp w2,#0       // loop
	bne ps_loop     //   'til done...

	ret             // return


	# -------------------------------------------------------------
	# do_xreg - print indexed register - X0..X30
	#
	#   x2 - value to print
	#   x3 - register index 
	# -------------------------------------------------------------
do_xreg:
	push x3
	push x2
	
	adr x1,xregnames   //
	lsl x3,x3,2        // form pointer to
	add x1,x1,x3       //   register name prefix, 
	mov x2,#4          // always four characters
	
	callsub putstr     // print register name

	peek x2            // retreive value to print
	
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret

	# -------------------------------------------------------------
	# do_vreg - print indexed SIMD register - V0..V31
	#
	#   x2 - Q register index
	#   x3 - Q register, lo order 64 bits
	#   x4 -     "       hi      "
	# -------------------------------------------------------------
do_vreg:
	push x3
	push x2

	adr x1,vregnames   //
	lsl x2,x2,2        // form pointer to
	add x1,x1,x2       //   register name prefix, 
	mov x2,#4          // always four characters
	
	callsub putstr     // print register name

	mov x2,x3          // print lo order 64 bits	
	mov x3,#60
	callsub putull

	slash              // output '/'

	mov x2,x4          // print hi order 64 bits
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret
	
do_elr:
	push x3
	push x2
	
	adr x1,elr_prefix
	mov x2,#8
	callsub putstr

	mrs x2,elr_el1
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret
	
do_spsr:
	push x3
	push x2
	
	adr x1,spsr_prefix
	mov x2,#9
	callsub putstr

	mrs x2,spsr_el1
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret
	
do_esr:
	push x3
	push x2
	
	adr x1,esr_prefix
	mov x2,#8	
	callsub putstr

	mrs x2,esr_el1
	mov x3,#28
	callsub putull

	adr x1,ec_prefix
	mov x2,#6	
	callsub putstr

	mrs x2,esr_el1
	lsr x2,x2,#26
	mov x3,#4
	callsub putull
	
	newline          // output newline

	pop x2
	pop x3
	ret

do_spsel:
	push x3
	push x2
	
	adr x1,spsel_prefix
	mov x2,#6
	callsub putstr

	mrs x2,spsel
	mov x3,#0
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret

do_fpsr:
	push x3
	push x2
	
	adr x1,fpsr_prefix
	mov x2,#5
	callsub putstr

	mrs x2,fpsr
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret

do_currentel_prefix:
	push x3
	push x2
	
	adr x1,currentel_prefix
	mov x2,#12
	callsub putstr

	mrs x2,currentel
	mov x3,#0
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret
	
do_saved_pc:
	push x3
	push x2
	
	adr x1,pc_prefix
	mov x2,#3
	callsub putstr

	adr x1,saved_pc
	ldr x2,[x1]
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret
	
do_saved_flags:
	push x3
	push x2
	
	adr x1,flags_prefix
	mov x2,#5
	callsub putstr

	adr x1,saved_flags
	ldr x2,[x1]
	mov x3,#60
	callsub putull

	newline          // output newline

	pop x2
	pop x3
	ret
	

	.macro display_rval sindex
	mov x3,#\sindex
	callsub do_xreg
	.endm
	
	.macro display_reg sreg, sindex
	mov x2,\sreg
	mov x3,#\sindex
	callsub do_xreg
	.endm
	
	.macro display_vreg vlo, vhi, vindex
	mov x2,\vindex	
	fmov x3,\vlo
	fmov x4,\vhi
	callsub do_vreg
	.endm

dump_app_registers_int:
	peek_x0 x2
	display_rval 0
	
	peek_x1 x2
	display_rval 1
	
	peek_x2 x2
	display_rval 2
	
	peek_x3 x2
	display_rval 3

	peek_x4 x2
	display_rval 4

	display_reg x5,5
	display_reg x6,6
	display_reg x7,7
	display_reg x8,8
	display_reg x9,9

	display_reg x10,10
	display_reg x11,11
	display_reg x12,12
	display_reg x13,13
	display_reg x14,14
	display_reg x15,15
	display_reg x16,16
	display_reg x17,17
	display_reg x18,18
	display_reg x19,19

	display_reg x20,20
	display_reg x21,21
	display_reg x22,22
	display_reg x23,23
	display_reg x24,24
	display_reg x25,25

	# x26, x27, x28 used in exception handler as scratch. don't display...
	#display_reg x26,26
	#display_reg x27,27
	#display_reg x28,28

	peek_x29 x2
	display_rval 29

	peek_x30 x2
	display_rval 30

	peek_sp x2
	display_rval 31
	
	ret

dump_app_registers_fp:
	display_vreg d0, v0.d[1], 0
	display_vreg d1, v1.d[1], 1
	display_vreg d2, v2.d[1], 2
	display_vreg d3, v3.d[1], 3
	display_vreg d4, v4.d[1], 4
	display_vreg d5, v5.d[1], 5
	display_vreg d6, v6.d[1], 6
	display_vreg d7, v7.d[1], 7
	display_vreg d8, v8.d[1], 8
	display_vreg d9, v9.d[1], 9

	display_vreg d10, v10.d[1], 10
	display_vreg d11, v11.d[1], 11
	display_vreg d12, v12.d[1], 12
	display_vreg d13, v13.d[1], 13
	display_vreg d14, v14.d[1], 14
	display_vreg d15, v15.d[1], 15
	display_vreg d16, v16.d[1], 16
	display_vreg d17, v17.d[1], 17
	display_vreg d18, v18.d[1], 18
	display_vreg d19, v19.d[1], 19

	display_vreg d20, v20.d[1], 20
	display_vreg d21, v21.d[1], 21
	display_vreg d22, v22.d[1], 22
	display_vreg d23, v23.d[1], 23
	display_vreg d24, v24.d[1], 24
	display_vreg d25, v25.d[1], 25
	display_vreg d26, v26.d[1], 26
	display_vreg d27, v27.d[1], 27
	display_vreg d28, v28.d[1], 28
	display_vreg d29, v29.d[1], 29

	display_vreg d30, v30.d[1], 30
	display_vreg d31, v31.d[1], 31
	ret
	
dumpexc:

	save_app_registers

	callsub do_elr
	callsub do_esr
	callsub do_spsel

	callsub dump_app_registers_int
	callsub dump_app_registers_fp

exit_dumpexc:
	restore_app_registers
	ret

#====================================================================
# 	
#====================================================================

enable_single_step:
	mov x1,#0               // clear out MDCR_EL3
	msr mdcr_el3,x0         //

	movz x1,#0              // OSLAR.OSLK = 0 (unlock debug degisters)
	msr oslar_el1,x1        //

	msr osdlr_el1,x1        // OSDLR.CLK = 0 (OS Double Lock unlocked)
	
	mrs x0,mdscr_el1        //
	mov x1,#(1 | (1<<13))   //
	orr x0,x0,x1            // MDSCR_EL1.SS = 1, KDE = 1
	msr mdscr_el1,x1        //
	
	mrs x0,spsr_el3         //
	movz x1,#(1<<9)         // set D(ebug) flag,
	movk x1,#0x20,lsl #16   //   single-step state
	orr x0,x0,x1            //  
	msr spsr_el3,x0         //

	// will ASSUME ELR_EL3, SPSR_EL3 have already been setup!
	
	// update saved pc from elr_el3...

	mrs x0,elr_el3
	adr x1,saved_pc
	str x0,[x1]

	// prime stop count...

	adr x0,stop_count
	mov x1,#100
	str x1,[x0]

	// update saved flags from spsr_el3...

	mrs x0,spsr_el3
	ror x0,x0,#28
	and x0,x0,#0xf
	adr x1,saved_flags
	str x0,[x1]
	ret

#====================================================================
# dump state - single-step
# process:
#    1. print 'saved' PC, PSTATE (FLAGS)
#    2. update saved PC, PSTATE	(FLAGS)
#    3. reename single-step	
#====================================================================
	
dumpexc_single_step:
	save_app_registers_small

	// update saved flags from spsr_el1...
	
	mrs x0,spsr_el1
	ror x0,x0,#28
	and x0,x0,#0xf
	adr x1,saved_flags
	str x0,[x1]

	// display 'saved' pc, flags...

	callsub do_saved_pc
	callsub do_saved_flags
	callsub do_spsr
	callsub do_elr
	callsub do_esr
	callsub do_fpsr
	callsub do_currentel_prefix

	// display 'application' registers...

	callsub dump_app_registers_int
	callsub dump_app_registers_fp
	
	// update saved pc from elr_el1...

	mrs x0,elr_el1
	adr x1,saved_pc
	str x0,[x1]

	// update/check stop count...

	adr x0,stop_count
	ldr x1,[x0]
	subs x1,x1,#1
	beq stop_now
	
	// return if this exception is not due to single-step...

	mrs x0,esr_el1
	lsr x0,x0,#26
	cmp x0,#0x32
	beq keep_going

stop_now:
	mov w0,#0x18
	mov x1,#0
	hlt #0xf000

	// set single-step state...
keep_going:
	mrs x0,spsr_el1
	movz x1,#0x20,lsl #16
	orr x0,x0,x1
	msr spsr_el1,x0

	restore_app_registers_small
	ret


	.align 3
stop_count:
	.fill 1,8
	
	.align 3
elr_prefix: .asciz "ELR_EL1:"
	
	.align 3
esr_prefix: .asciz "ESR_EL1:"

	.align 3
spsr_prefix: .asciz "SPSR_EL1:"

	.align 3
ec_prefix: .asciz " EX: "
	
	.align 3
spsel_prefix: .asciz "SPSEL:"
	
	.align 3
pc_prefix: .asciz "PC:"

	.align 3
flags_prefix: .asciz "NZCV:"

	.align 3
fpsr_prefix: .asciz "FPSR:"

	.align 3
currentel_prefix: .asciz "CURRENT EL:"
	
	.align 3
digits:	.asciz "0123456789abcdef"
	
	.align 3
c0:	.byte '0

	.align 3
cX:	.byte 'x
	
	.align 3
nl:	.byte '\n

	.align 3
sl:	.byte '/

	.align 3
saved_pc:
	.fill 1,8
	
	.align 3
saved_flags:
	.fill 1,8

	.align 3
xregnames:
	.asciz " X0: X1: X2: X3: X4: X5: X6: X7: X8: X9:X10:X11:X12:X13:X14:X15:X16:X17:X18:X19:X20:X21:X22:X23:X24:X25:X26:X27:X28:X29:X30: SP:" 

	.align 3
vregnames:
	.asciz " V0: V1: V2: V3: V4: V5: V6: V7: V8: V9:V10:V11:V12:V13:V14:V15:V16:V17:V18:V19:V20:V21:V22:V23:V24:V25:V26:V27:V28:V29:V30:V31:" 
	
	.align 3
simd_num:
	.fill 4,8

	.align 3
exc_stack_bottom:	
	.fill 128,8
exc_stack:	
