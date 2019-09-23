#!/usr/bin/perl -w

#***********************************************************************************************************
# id_sections.pl - process v8 arm arm. for each (v8 only) instruction extract section, (register) operands,
#                  assembly language encodings. Derive enum for each encoding. Generate machine readable
#                  output.
#***********************************************************************************************************

use Scalar::Util qw(looks_like_number);

my $page_num = '';

my @inames       = ();

my %sections     = ();
my %pages        = ();
my %dest_symbols = ();
my %src_symbols  = ();
my %asms16bit    = ();
my %asms32bit    = ();
my %asms64bit    = ();
my %asmSets      = ();
my %asmScalar    = ();
my %asmVector    = ();
my %asmType      = ();
my %asms         = ();
my %asmSP        = ();
my %asmDP        = ();
my %asmCvtPre    = ();

my %ldr_variants = ();
my %mov_variants = ();
my %ldn_variants = ();

my %is_float   = ();

my %all_operands = ();

# highlight a64 individual instruction sections...

my $in_section = 0;
my $in_operation = 0;
my $in_symbols = 0;
my $in_asm16 = 0;
my $in_asm32 = 0;
my $in_asm64 = 0;
my $in_asm = 0;
my $in_asmV = 0;
my $is_prepostoff = 0;
my $in_asmS = 0;
my $in_asmVct = 0;
my $in_asmT = 0;
my $in_asmSP = 0;
my $in_asmDP = 0;
my $in_cvtpre = 0;
my $in_ldrvariant = 0;
my $ldrvariant_key = '';
my $movvariant_key = '';
my $ldnvariant_key = '';
my $prepostvariant_key = '';

my $iname;

my %aliases = ();

my %aliases_allowed = (
#    'AT' => 1, 
#    'DC' => 1,
#    'IC' => 1, 
#    'TLBI' => 1, 
    'WFI' => 1, 
    'WFE' => 1, 
    'NOP' => 1,
    'SEVL' => 1,
    'SEV' => 1,
    'YIELD' => 1
);

my %op2print = (
   'default'  => '%u',
   '<R>'      => '%c',
   '<Da>'     => 'D%d', 
   '<Dd>'     => 'D%d', 
   '<Dm>'     => 'D%d', 
   '<Dn>'     => 'D%d',
   '<Hd>'     => 'H%d',
   '<Hn>'     => 'H%d',
   '<Ht>'     => 'H%d',
   '<Bt>'     => 'B%d',
   '<Sa>'     => 'S%d',
   '<Sd>'     => 'S%d',
   '<Sm>'     => 'S%d',
   '<Sn>'     => 'S%d',
   '<St>'     => 'S%d',
   '<St1>'    => 'S%d',
   '<St2>'    => 'S%d',
   '<Dt>'     => 'D%d',
   '<Dt1>'    => 'D%d',
   '<Dt2>'    => 'D%d',
   '<Qt>'     => 'Q%d',
   '<Qt1>'    => 'Q%d',
   '<Qt2>'    => 'Q%d',
   '<Qd>'     => 'Q%d', 
   '<Qn>'     => 'Q%d',
   '<T>'      => '%s',
   '<Ta>'     => '%s',
   '<Va>'     => '%s',
   '<Vb>'     => '%s',
   '<Vd>'     => 'V%d',
   '<Vm>'     => 'V%d',
   '<Vn>'     => 'V%d', 
   '<Vn+1>'   => 'V%d', 
   '<Vn+2>'   => 'V%d', 
   '<Vn+3>'   => 'V%d', 
   '<Vt>'     => 'V%d',
   '<Vt2>'    => 'V%d',
   '<Vt3>'    => 'V%d',
   '<Vt4>'    => 'V%d',
    
   '<Wa>'     => '%s',   # 
   '<Wd>'     => '%s',   #
   '<Wm>'     => '%s',   #
   '<Wn>'     => '%s',   #
   '<Ws>'     => '%s',   # could be wzr|xzr
   '<Wt>'     => '%s',   #
   '<Xa>'     => '%s',   #
   '<Xd>'     => '%s',   #
   '<Xm>'     => '%s',   #
   '<Xn>'     => '%s',   #
    
   '<Xn|SP>'  => '%s', 
   '<Xd|SP>'  => '%s', 
   '<Wn|WSP>' => '%s', 
   '<Wd|WSP>' => '%s',
    
   '<Xs>'     => '%s',   #
   '<Xt>'     => '%s',   #
   '<Xt1>'    => '%s',   # could be wzr|xzr
   '<Xt2>'    => '%s',   #
   '<Wt1>'    => '%s',   #
   '<Wt2>'    => '%s',   #
    
   '<V>'      => '%s',
   '<cond>'   => '%s',
   '<imm>'    => '%s',
   '<imm16>'  => '%d', 
   '<imm8>'   => '%d', 
   '<m>'      => '%s',
   '<op1>'    => '%d', 
   '<op2>'    => '%d',
   '<option>' => '%s', 
   '<label>'  => '%lld',
   '<Cm>'     => 'C%u',
   '<Cn>'     => 'C%u',
   '<extend>' => '%s',
   '<simm>'   => '%d',
   '<Ts>'     => '%s',
   'Tscale'   => '%s',
   'Tvect'    => '%s',
   'Ts'       => '%s',
#   's_imm4'   => '%d',
#   's_imm8'   => '%d',
   'float8_exp_const' => '%llu',
   'as_imm_shift' => '%s',
   'eon_reg_shift' => '%s',
   'as_reg_shift' => '%s',
   'imm19_off' => '%lld',
   'imm14_off' => '%lld',
   'sys_reg_read' => '%s',
   'sys_reg_write' => '%s',
   'pstatefield' => '%s',
   'prfop' => '%s',
   't_sp' => '%s',
   '<Tb>' => '%s',
   '<Ta>' => '%s',
   'simd_elem_id' => '%s',
   'simd_elem_id2' => '%s',
   'simd_elem_id3' => '%s',
   'simd_low_byte_num' => '%s',
   'fp_elem_id' => '%s',
   'simd_rshift1' => '%s',
   'simd_rshift4' => '%s',
   'ld1_imm8' => '%u',
   'ld1_imm16' => '%u',
   'ld1_imm32' => '%u',
   'ld1_imm64' => '%u',
   'simd_lshift_sca' => '%s',
   'simd_lshift_vec' => '%s',
   'at_op' => '%s',
   'immRS' => '%llu',
   'imm12' => '%s',
   'imm12_2' => '%s',
   'imm5' => '%d',
   'label1' => '%lld',
   'label2' => '%lld',
   'label3' => '%lld',
   's_imm4'   => '%lld',
   's_imm8'   => '%lld',
   's_imm16'   => '%lld',
);

# for specific instructions expand operands:
my %op2opexp = (
   'SIMD_DUP_SCALAR_ELEM/T' => 'Tscale',
   'SIMD_DUP_SCALAR_VEC_ELEM/T' => 'Tvect',

   'ADD_IMM_32/imm'  => 'imm12_2',
   'ADD_IMM_64/imm'  => 'imm12_2',
   'ADDS_IMM_32/imm' => 'imm12_2',
   'ADDS_IMM_64/imm' => 'imm12_2',
    
   'ADD_IMM_32/shift'  => 'as_imm_shift',
   'ADD_IMM_64/shift'  => 'as_imm_shift',
   'ADDS_IMM_32/shift' => 'as_imm_shift',
   'ADDS_IMM_64/shift' => 'as_imm_shift',

   'ADD_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'ADD_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'ADD_SHIFT_REG_32/amount' => 'as_amount',
   'ADD_SHIFT_REG_64/amount' => 'as_amount',

   'ADDS_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'ADDS_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'ADDS_SHIFT_REG_32/amount' => 'as_amount',
   'ADDS_SHIFT_REG_64/amount' => 'as_amount',

   'AND_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'AND_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'AND_SHIFT_REG_32/amount' => 'as_amount',
   'AND_SHIFT_REG_64/amount' => 'as_amount',

   'ANDS_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'ANDS_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'ANDS_SHIFT_REG_32/amount' => 'as_amount',
   'ANDS_SHIFT_REG_64/amount' => 'as_amount',

   'AND_IMM_32/imm'  => 'immRS',
   'AND_IMM_64/imm'  => 'immRS',
   'ANDS_IMM_32/imm'  => 'immRS',
   'ANDS_IMM_64/imm'  => 'immRS',

   'AT/at_op' => 'at_op',

   'BIC_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'BIC_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'BICS_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'BICS_SHIFT_REG_64/shift'  => 'as_reg_shift',

   'EON_SHIFT_REG_32/shift'  => 'eon_reg_shift',
   'EON_SHIFT_REG_64/shift'  => 'eon_reg_shift',
   'EON_SHIFT_REG_32/amount' => 'as_amount',
   'EON_SHIFT_REG_64/amount' => 'as_amount',

   'EOR_SHIFT_REG_32/shift'  => 'eon_reg_shift',
   'EOR_SHIFT_REG_64/shift'  => 'eon_reg_shift',
   'EOR_SHIFT_REG_32/amount' => 'as_amount',
   'EOR_SHIFT_REG_64/amount' => 'as_amount',

   'ORN_SHIFT_REG_32/shift'  => 'eon_reg_shift',
   'ORN_SHIFT_REG_64/shift'  => 'eon_reg_shift',
   'ORN_SHIFT_REG_32/amount' => 'as_amount',
   'ORN_SHIFT_REG_64/amount' => 'as_amount',

   'ORR_SHIFT_REG_32/shift'  => 'eon_reg_shift',
   'ORR_SHIFT_REG_64/shift'  => 'eon_reg_shift',
   'ORR_SHIFT_REG_32/amount' => 'as_amount',
   'ORR_SHIFT_REG_64/amount' => 'as_amount',

   'SIMD_SHL_SCALAR/shift' => 'shl_shift',
   'SIMD_SHLL_VEC/shift'   => 'shl_shift',
   'SIMD_SHRN_VEC/shift'   => 'shl_shift',

   'BRK/imm'         => '<imm16>',

   'CCMN_IMM_32/imm' => 'imm5',
   'CCMN_IMM_64/imm' => 'imm5',
   'CCMP_IMM_32/imm' => 'imm5',
   'CCMP_IMM_64/imm' => 'imm5',
   'CLREX/imm' => 'immCRm',
   'CMN_IMM/imm' => 'imm_12',
   'CMP_IMM/imm' => 'imm_12',
   'DCPS1/imm' => '<imm16>',
   'DCPS2/imm' => '<imm16>',
   'DCPS3/imm' => '<imm16>',
   'DMB/imm' => 'immCRm',
   'DSB/imm' => 'immCRm',
   'EOR_IMM_32/imm'  => 'immRS',
   'EOR_IMM_64/imm'  => 'immRS',
   'HINT/imm' => 'CRm_op2',
   'HALT/imm'         => '<imm16>',
   'HVC/imm'         => '<imm16>',
   'ISB/imm' => 'immCRm',

   'LDNP_32/imm' => 's_imm4',
   'LDNP_64/imm' => 's_imm8',

   'LDP_REG_POST_32/imm' => 's_imm4',
   'LDP_REG_POST_64/imm' => 's_imm8',
   'LDP_REG_PRE_32/imm'  => 's_imm4',
   'LDP_REG_PRE_64/imm'  => 's_imm8',
   'LDP_REG_OFF_32/imm'  => 's_imm4',
   'LDP_REG_OFF_64/imm'  => 's_imm8',
   
   'LDPSW_REG_OFF/imm'  => 's_imm4',
   'LDPSW_REG_POST/imm' => 's_imm4',
   'LDPSW_REG_PRE/imm'  => 's_imm4',

   'STP_REG_POST_32/imm' => 's_imm4',
   'STP_REG_POST_64/imm' => 's_imm8',
   'STP_REG_PRE_32/imm'  => 's_imm4',
   'STP_REG_PRE_64/imm'  => 's_imm8',
   'STP_REG_OFF_32/imm'  => 's_imm4',
   'STP_REG_OFF_64/imm'  => 's_imm8',

   'LDR_32/label'  => 'imm19_off',
   'LDR_64/label'  => 'imm19_off',

   'LDRSW/label' => 'imm19_off',

   'SIMD_LDR_32/label'  => 'imm19_off',
   'SIMD_LDR_64/label'  => 'imm19_off',
   'SIMD_LDR_128/label' => 'imm19_off',


   'SIMD_SHL_SCALAR/shift'     => 'simd_lshift_sca',
   'SIMD_SHL_SCALAR_VEC/shift' => 'simd_lshift_vec',

   'LD1_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'LD1_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'LD1_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'LD1_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'LD2_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'LD2_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'LD2_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'LD2_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'LD3_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'LD3_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'LD3_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'LD3_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'LD4_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'LD4_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'LD4_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'LD4_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'SIMD_LD1_ONE_REG_MULT_STRUCT_POST_OFF/imm'   => 'ld1_mult1_imm',
   'SIMD_LD1_TWO_REG_MULT_STRUCT_POST_OFF/imm'   => 'ld1_mult2_imm',
   'SIMD_LD1_THREE_REG_MULT_STRUCT_POST_OFF/imm' => 'ld1_mult3_imm',
   'SIMD_LD1_FOUR_REG_MULT_STRUCT_POST_OFF/imm'  => 'ld1_mult4_imm',

   'SIMD_ST1_THREE_REG_MULT_STRUCT_POST_OFF/imm' => 'ld1_mult1_imm',
   'SIMD_ST1_FOUR_REG_MULT_STRUCT_POST_OFF/imm'  => 'ld1_mult2_imm',
   'SIMD_ST1_ONE_REG_MULT_STRUCT_POST_OFF/imm'   => 'ld1_mult3_imm',
   'SIMD_ST1_TWO_REG_MULT_STRUCT_POST_OFF/imm'   => 'ld1_mult4_imm',

   'ST2_MULT_REG_POST_STRUCT/imm'  => 'ld1_mult2_imm',
   'ST3_MULT_REG_POST_STRUCT/imm'  => 'ld1_mult3_imm',
   'ST4_MULT_REG_POST_STRUCT/imm'  => 'ld1_mult4_imm',

   'ST1_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'ST1_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'ST1_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'ST1_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'ST2_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'ST2_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'ST2_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'ST2_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'ST3_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'ST3_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'ST3_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'ST3_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'ST4_SINGLE_STRUCT_8/index'  => 'ld1_imm8',
   'ST4_SINGLE_STRUCT_16/index' => 'ld1_imm16',
   'ST4_SINGLE_STRUCT_32/index' => 'ld1_imm32',
   'ST4_SINGLE_STRUCT_64/index' => 'ld1_imm64',

   'LD2_MULT_REG_POST_STRUCT/imm' => 'ld1_mult2_imm',
   'LD3_MULT_REG_POST_STRUCT/imm' => 'ld1_mult3_imm',
   'LD4_MULT_REG_POST_STRUCT/imm' => 'ld1_mult4_imm',

   'HVC/imm'         => '<imm16>',

   'MOVK_32/imm'         => '<imm16>',
   'MOVK_64/imm'         => '<imm16>',
   'MOVK_32/shift'       => 'hw_shift',
   'MOVK_64/shift'       => 'hw_shift',

   'MOVN_32/imm'         => '<imm16>',
   'MOVN_64/imm'         => '<imm16>',
   'MOVN_32/shift'       => 'hw_shift',
   'MOVN_64/shift'       => 'hw_shift',

   'MOVZ_32/imm'         => '<imm16>',
   'MOVZ_64/imm'         => '<imm16>',
   'MOVZ_32/shift'       => 'hw_shift',
   'MOVZ_64/shift'       => 'hw_shift',

   'MRS/systemreg'       => 'sys_reg_read',
   'MSR_REG/systemreg'   => 'sys_reg_write',
   'MSR_IMM/pstatefield' => 'pstatefield',

   'MSR_IMM/imm' => 'immCRm',

   'ORR_IMM_32/imm'  => 'immRS',
   'ORR_IMM_64/imm'  => 'immRS',

   'PRFM_IMM/prfop' => 'prfop',
   'PRFM/prfop'     => 'prfop',
   'PRFM_REG/prfop' => 'prfop',
   'PRFUM/prfop'    => 'prfop',
   'PRFM/label'     => 'imm19_off',

   'SIMD_DUP_SCALAR_ELEM/index'     => 'simd_elem_id',
   'SIMD_DUP_SCALAR_VEC_ELEM/index' => 'simd_elem_id',
   'SIMD_INS_SCALAR_ELEM/index1'    => 'simd_elem_id',
   'SIMD_INS_SCALAR/index'          => 'simd_elem_id',
   'SIMD_UMOV_32/index'             => 'simd_elem_id',

   'SIMD_UMOV_64/index'             => 'simd_elem_id4',

   'SIMD_INS_SCALAR_ELEM/index2'    => 'simd_elem_id2',

   'SIMD_SMOV_IMM_MOD_32/index'    => 'simd_elem_id2',
   'SIMD_SMOV_IMM_MOD_64/index'    => 'simd_elem_id',

   'SIMD_MLA_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_MLS_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_MUL_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SMLAL_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SMLSL_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SMULL_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMLAL_SCALAR_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMLAL_SCALAR_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMLSL_SCALAR_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMLSL_SCALAR_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMULH_SCALAR_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMULH_SCALAR_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMULL_SCALAR_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQDMULL_SCALAR_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQRDMULH_SCALAR_ELEM/index' => 'simd_elem_id3',
   'SIMD_SQRDMULH_SCALAR_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_UMLAL_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_UMLSL_VEC_ELEM/index' => 'simd_elem_id3',
   'SIMD_UMULL_VEC_ELEM/index' => 'simd_elem_id3',

   'SIMD_RSHRN_VEC/shift' => 'simd_rshift1',
   'SIMD_SSRA_SCALAR/shift' => 'simd_rshift1',

   'SIMD_SQRSHRN_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SQRSHRN_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SQRSHRUN_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SQRSHRUN_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SQSHRN_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SQSHRN_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SQSHRUN_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SQSHRUN_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SRI_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SRI_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SRSHR_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SRSHR_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SRSRA_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SRSRA_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SSHR_SCALAR/shift' => 'simd_rshift2',
   'SIMD_SSHR_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_UQRSHRN_SCALAR/shift' => 'simd_rshift2',
   'SIMD_UQRSHRN_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_UQSHRN_SCALAR/shift' => 'simd_rshift2',
   'SIMD_UQSHRN_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_URSHR_SCALAR/shift' => 'simd_rshift2',
   'SIMD_URSHR_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_URSRA_SCALAR/shift' => 'simd_rshift2',
   'SIMD_URSRA_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_USHR_SCALAR/shift' => 'simd_rshift2',
   'SIMD_USHR_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_USRA_SCALAR/shift' => 'simd_rshift2',
   'SIMD_USRA_SCALAR_VEC/shift' => 'simd_rshift2',
   'SIMD_SSRA_SCALAR_VEC/shift' => 'simd_rshift2',

   'SIMD_SQSHL_IMM_SCALAR/shift' => 'simd_rshift3',
   'SIMD_SQSHL_IMM_SCALAR_VEC/shift' => 'simd_rshift3',
   'SIMD_SQSHLU_SCALAR/shift' => 'simd_rshift3',
   'SIMD_SQSHLU_SCALAR_VEC/shift' => 'simd_rshift3',
   'SIMD_SSHLL_VEC/shift' => 'simd_rshift3',
   'SIMD_UQSHL_IMM_SCALAR/shift' => 'simd_rshift3',
   'SIMD_UQSHL_IMM_SCALAR_VEC/shift' => 'simd_rshift3',

   'SIMD_USHLL_VEC/shift' => 'simd_rshift4',

   'SIMD_EXT_SCALAR/index' => 'simd_low_byte_num',

   'FMLA_SCALAR_ELEM/index'     => 'fp_elem_id',
   'FMLA_SCALAR_VEC_ELEM/index' => 'fp_elem_id',

   'FMLS_SCALAR_ELEM/index'     => 'fp_elem_id',
   'FMLS_SCALAR_VEC_ELEM/index' => 'fp_elem_id',

   'FMUL_SCALAR_ELEM/index'     => 'fp_elem_id',
   'FMUL_SCALAR_VEC_ELEM/index' => 'fp_elem_id',

   'FMULX_SCALAR_ELEM/index'     => 'fp_elem_id',
   'FMULX_SCALAR_VEC_ELEM/index' => 'fp_elem_id',

   'SMC/imm'         => '<imm16>',

   'STNP_32/imm' => 's_imm4',
   'STNP_64/imm' => 's_imm8',

   'SUB_IMM_32/imm'   => 'imm_12',
   'SUB_IMM_64/imm'   => 'imm_12',
   'SUBS_IMM_32/imm'  => 'imm_12',
   'SUBS_IMM_64/imm'  => 'imm_12',
    
   'SUB_IMM_32/shift'  => 'as_imm_shift',
   'SUB_IMM_64/shift'  => 'as_imm_shift',
   'SUBS_IMM_32/shift' => 'as_imm_shift',
   'SUBS_IMM_64/shift' => 'as_imm_shift',

   'SUB_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'SUB_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'SUB_SHIFT_REG_32/amount' => 'as_amount',
   'SUB_SHIFT_REG_64/amount' => 'as_amount',

   'SUBS_SHIFT_REG_32/shift'  => 'as_reg_shift',
   'SUBS_SHIFT_REG_64/shift'  => 'as_reg_shift',
   'SUBS_SHIFT_REG_32/amount' => 'as_amount',
   'SUBS_SHIFT_REG_64/amount' => 'as_amount',

   'SVC/imm'         => '<imm16>',

   'TBNZ/imm'        => 'b5_b40',
   'TBNZ/t'          => 't_sp',
   'TBNZ/label'      => 'imm14_off',

   'TBZ/imm'         => 'b5_b40',
   'TBZ/t'           => 't_sp',
   'TBZ/label'       => 'imm14_off',

   'TST_IMM/imm'  => 'immRS',

   'FMOV_IMM_SINGLE_VEC_FROM_SP/imm' => 'float8_const',
   'FMOV_IMM_VEC_FROM_DP/imm' => 'float8_const',

   'FMOV_IMM_SINGLE_FROM_SP/imm' => 'imm8',
   'FMOV_IMM_FROM_DP/imm' => 'imm8',

   'SIMD_MOVI_IMM_MOD_8/imm8' => 'float8_const',
   'SIMD_MOVI_SHIFT_IMM_MOD_16/imm8' => 'float8_const',
   'SIMD_MOVI_SHIFT_IMM_MOD_32/imm8' => 'float8_const',
   'SIMD_MOVI_SHIFT_IMM_ONES_MOD_32/imm8' => 'float8_const',

   'SIMD_MOVI_IMM_MOD_64/imm' => 'float8_exp_const',
   'SIMD_MOVI_IMM_MOD_VEC_64/imm' => 'float8_exp_const',

   'SIMD_SHLL_SCALAR/shift' => 'shl_shift_scalar',
   'SIMD_SHLL_VEC/shift' => 'shl_shift_vector',
   'SIMD_SHRN_SCALAR/shift' => 'shl_shift_scalar',
   'SIMD_SHRN_VEC/shift' => 'shl_shift_vector',

   'SIMD_SLI_SCALAR/shift' => 'shl_shift_scalar',
   'SIMD_SLI_SCALAR_VEC/shift' => 'shl_shift_vector',

   'ADR/label' => 'label1',
   'ADRP/label' => 'label1',

   'HLT/imm' => 'imm16',

   'B_COND/label' => 'label2',
   'B/label' => 'label3',
   'BL/label' => 'label3',
   'CBNZ_32/label' => 'label2',
   'CBNZ_64/label' => 'label2',
   'CBZ_32/label' => 'label2',
   'CBZ_64/label' => 'label2',

   'LD1_ONE_REG_MULT_REG_POST_STRUCT/imm' => 'Q8_16',
   'LD1_TWO_REG_MULT_REG_POST_STRUCT/imm' => 'Q16_32',
   'LD1_THREE_REG_MULT_REG_POST_STRUCT/imm' => 'Q24_48',
   'LD1_FOUR_REG_MULT_REG_POST_STRUCT/imm' => 'Q32_64',

   'ST1_ONE_REG_MULT_STRUCT/imm' => 'Q8_16',
   'ST1_TWO_REG_MULT_STRUCT/imm' => 'Q16_32',
   'ST1_THREE_REG_MULT_STRUCT/imm' => 'Q24_48',
   'ST1_FOUR_REG_MULT_STRUCT/imm' => 'Q32_64',

   'LD1R/imm' => 'ldr1_imm',
   'LD2R/imm' => 'ldr1_imm',
   'LD3R/imm' => 'ldr1_imm',
   'LD4R/imm' => 'ldr1_imm',

   'SIMD_LDNP_32/imm' => 's_imm4',
   'SIMD_LDNP_64/imm' => 's_imm8',
   'SIMD_LDNP_128/imm' => 's_imm16',

   'SIMD_STNP_32/imm' => 's_imm4',
   'SIMD_STNP_64/imm' => 's_imm8', 
   'SIMD_STNP_128/imm' => 's_imm16',

   'SIMD_LDP_REG_POST_32/imm'  => 's_imm4',  
   'SIMD_LDP_REG_POST_64/imm'  => 's_imm8',
   'SIMD_LDP_REG_POST_128/imm' => 's_imm16',
   'SIMD_LDP_REG_PRE_32/imm'   => 's_imm4',  
   'SIMD_LDP_REG_PRE_64/imm'   => 's_imm8',
   'SIMD_LDP_REG_PRE_128/imm'  => 's_imm16',
   'SIMD_LDP_REG_OFF_32/imm'   => 's_imm4',  
   'SIMD_LDP_REG_OFF_64/imm'   => 's_imm8',
   'SIMD_LDP_REG_OFF_128/imm'  => 's_imm16',

   'SIMD_FMOV_IMM_SINGLE_FROM_SP/imm' => 'imm8',
   'SIMD_FMOV_IMM_FROM_DP/imm'        => 'imm8',

   'SIMD_STP_REG_POST_32/imm'  => 's_imm4',  
   'SIMD_STP_REG_POST_64/imm'  => 's_imm8',
   'SIMD_STP_REG_POST_128/imm' => 's_imm16',
   'SIMD_STP_REG_PRE_32/imm'   => 's_imm4',
   'SIMD_STP_REG_PRE_64/imm'   => 's_imm8',
   'SIMD_STP_REG_PRE_128/imm'  => 's_imm16',
   'SIMD_STP_REG_OFF_64/imm'   => 's_imm8',
   'SIMD_STP_REG_OFF_128/imm'  => 's_imm16',
   'SIMD_STP_REG_OFF_32/imm'   => 's_imm4',

   'SIMD_MOVI_SHIFT_IMM_ONES_MOD_32' => 'float8_const',
   'SIMD_MOVI_SHIFT_IMM_MOD_32'      => 'float8_const',
   'SIMD_MOVI_IMM_MOD_64'            => 'float8_exp_const',
   'SIMD_MOVI_SHIFT_IMM_MOD_16'      => 'float8_const',
   'SIMD_MOVI_IMM_MOD_VEC_64'        => 'float8_exp_const',
   'SIMD_MOVI_IMM_MOD_8'             => 'float8_const'
);

my %op2parm = (
   '<Cm>'     => 'packet->CRm.Value()',
   '<Cn>'     => 'packet->CRm.Value()',
   '<Da>'     => 'packet->Ra.Value()', 
   '<Dd>'     => 'packet->Rd.Value()', 
   '<Dm>'     => 'packet->Rm.Value()', 
   '<Dn>'     => 'packet->Rn.Value()', 
   '<Dt>'     => 'packet->Rt.Value()', 
   '<Hd>'     => 'packet->Rd.Value()',
   '<Hn>'     => 'packet->Rn.Value()',
   '<Ht>'     => 'packet->Rt.Value()',
   '<Bt>'     => 'packet->Rt.Value()',
   '<R>'      => '((packet->option.Value() & 3)==3) ? \'X\' : \'W\'',
   '<Sa>'     => 'packet->Ra.Value()',
   '<Sd>'     => 'packet->Rd.Value()',
   '<Sm>'     => 'packet->Rm.Value()',
   '<Sn>'     => 'packet->Rn.Value()',
   '<St>'     => 'packet->Rt.Value()',
   '<St1>'    => 'packet->Rt.Value()',
   '<St2>'    => 'packet->Rt2.Value()',
   '<Dt>'     => 'packet->Rt.Value()',
   '<Dt1>'    => 'packet->Rt.Value()',
   '<Dt2>'    => 'packet->Rt2.Value()',
   '<Qt>'     => 'packet->Rt.Value()',
   '<Qt1>'    => 'packet->Rt.Value()',
   '<Qt2>'    => 'packet->Rt2.Value()',
   '<Qd>'     => 'packet->Rd.Value()', 
   '<Qn>'     => 'packet->Rn.Value()',
   '<T>'      => 'Tparm(packet->size.Value(),packet->Q.Value()).c_str()',
   '<Ta>'     => 'Ta_parm(packet->size.Value()).c_str()',
   'Tscale'   => 'Tscale(packet->imm5.Value()).c_str()',
   'Tvect'    => 'Tvect(packet->imm5.Value(),packet->Q.Value()).c_str()',
   '<Ts>'     => 'Tscale(packet->imm5.Value()).c_str()',
   '<V>'      => 'simdScalarWidth(packet->size.Value()).c_str()',
   '<d>'      => 'packet->Rd.Value()', 
   '<n>'      => 'packet->Rn.Value()', 
   '<Tb>'     => 'simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str()',
   '<Ta>'     => 'simdArrangementA(packet->size.Value()).c_str()',
   '<Va>'     => '(packet->size.Value()==1) ? "D" : "?"',
   '<Vb>'     => '(packet->size.Value()==1) ? "S" : "?"',
   '<Vd>'     => 'packet->Rd.Value()',
   '<Vm>'     => 'packet->Rm.Value()',
   '<Vn>'     => 'packet->Rn.Value()', 
   '<Vt>'     => 'packet->Rt.Value()', 
   '<Vt2>'    => '(packet->Rt.Value() + 1) % 32',   
   '<Vt3>'    => '(packet->Rt.Value() + 2) % 32',   
   '<Vt4>'    => '(packet->Rt.Value() + 3) % 32',   
   '<Vn+1>'   => '(packet->Rn.Value() + 1) % 32',   
   '<Vn+2>'   => '(packet->Rn.Value() + 2) % 32',   
   '<Vn+3>'   => '(packet->Rn.Value() + 3) % 32',   

   '<Wa>'     => 'XnXZR(packet->Ra.Value(),true).c_str()',
   '<Wd>'     => 'XnXZR(packet->Rd.Value(),true).c_str()',
   '<Wm>'     => 'XnXZR(packet->Rm.Value(),true).c_str()',
   '<Wn>'     => 'XnXZR(packet->Rn.Value(),true).c_str()',
   '<Ws>'     => 'XnXZR(packet->Rs.Value(),true).c_str()',
   '<Wt>'     => 'XnXZR(packet->Rt.Value(),true).c_str()',
   '<Xa>'     => 'XnXZR(packet->Ra.Value(),false).c_str()',
   '<Xd>'     => 'XnXZR(packet->Rd.Value(),false).c_str()',
   '<Xm>'     => 'XnXZR(packet->Rm.Value(),false).c_str()',
   '<Xn>'     => 'XnXZR(packet->Rn.Value(),false).c_str()',
    
   '<Xn|SP>'  => 'XnSP(packet->Rn.Value(),false).c_str()', 
   '<Xd|SP>'  => 'XnSP(packet->Rd.Value(),false).c_str()', 
   '<Wn|WSP>' => 'XnSP(packet->Rn.Value(),true).c_str()', 
   '<Wd|WSP>' => 'XnSP(packet->Rd.Value(),true).c_str()',
 
   '<Xs>'     => 'XnXZR(packet->Rn.Value(),false).c_str()',   #<---USED FOR ROR ENCODING WHICH IS SAME AS EXTR BUT Rm==Rn
    
   '<Xt1>'    => 'XnXZR(packet->Rt.Value(),false).c_str()',
   '<Xt2>'    => 'XnXZR(packet->Rt2.Value(),false).c_str()',
   '<Wt1>'    => 'XnXZR(packet->Rt.Value(),true).c_str()',
   '<Wt2>'    => 'XnXZR(packet->Rt2.Value(),true).c_str()',
   '<Xt>'     => 'XnXZR(packet->Rt.Value(),false).c_str()',

   '<extend>' => 'extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str()',
   '<amount>' => 'packet->imm3.Value()',

   'sys_reg_read'   => 'systemRegisterName(packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value(),true).c_str()',
   'sys_reg_write'  => 'systemRegisterName(packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value(),false).c_str()',
   'pstatefield'    => 'pstateFieldName(packet->op1.Value(),packet->op2.Value()).c_str()',

   'prfop' => 'prfop_name(packet->Rt.Value()).c_str()',

   'at_op' => 'sysop_name(packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value())',

   '<pimm>'   => 'decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value())',
   '<lsb>'    => 'packet->imms.Value()',

   '<immr>'   => 'packet->immr.Value()',
   '<imms>'   => 'packet->imms.Value()',

   '<fbits>'  => 'decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined())',

   'as_reg_shift' => 'as_reg_shift(packet->shift.Value()).c_str()',
   'as_amount'    => 'packet->imm6.Value()',

   'shl_shift_scalar' => '(packet->immh.Value()<<3|packet->immb.Value()) - (8<<3)',
   'shl_shift_vector' => '(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4))',

   'hw_shift' => 'packet->hw.Value()<<4',

   'eon_reg_shift' => 'eon_reg_shift(packet->shift.Value()).c_str()',

   'imm19_off' => 'SignExtend(packet->imm19.Value()<<2,21)',
   'imm14_off' => 'SignExtend(packet->imm14.Value()<<2,16)',

   'ld1_imm8'  => 'simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8)',
   'ld1_imm16' => 'simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16)',
   'ld1_imm32' => 'simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32)',
   'ld1_imm64' => 'simd_ld1_imm(packet->Q.Value(),0,0,64)',

   'ld1_mult1_imm' => '(packet->Q.Value()==1 ? 16 : 8)',
   'ld1_mult2_imm' => '(packet->Q.Value()==1 ? 32 : 16)',
   'ld1_mult3_imm' => '(packet->Q.Value()==1 ? 48 : 24)',
   'ld1_mult4_imm' => '(packet->Q.Value()==1 ? 64 : 32)',

   '<nzcv>'   => 'packet->nzcv.Value()',
   '<cond>'   => 'Bcond(packet->cond.Value()).c_str()',
   '<imm16>'  => 'packet->imm16.Value()', 
   'imm16'    => 'packet->imm16.Value()', 
   '<imm8>'   => 'packet->imm8.Value()', 
   'imm8'     => 'packet->imm8.Value()', 

   'imm12'    => 'ZeroExtend(packet->imm12.Value(),12,packet->shift.Value()).c_str()', #<<<PER INSTRUCTION BASIS...
   'imm12_2'  => 'ZeroExtend(packet->imm12.Value(),12,0).c_str()', #<<<PER INSTRUCTION BASIS...
   'imm5'     => 'packet->imm5.Value()', #<<<PER INSTRUCTION BASIS...

   'immCRm'   => 'packet->CRm.Value()',
   'imm_12'   => 'packet->imm12.Value()',

   'CRm_op2'  => 'packet->CRm.Value()<<3 | packet->op2.Value()',
   'immRS'    => 'DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true)',

   's_imm4'   => 'SignExtend(packet->imm7.Value(),7) * 4',
   's_imm8'   => 'SignExtend(packet->imm7.Value(),7) * 8',
   's_imm16'  => 'SignExtend(packet->imm7.Value(),7) * 16',

   'as_imm_shift' => 'as_imm_shift(packet->shift.Value()).c_str()',

   'simd_rshift1' => 'simd_rshift1(packet->immh.Value(),packet->immb.Value()).c_str()',
   'simd_rshift2' => '(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value())',
   'simd_rshift3' => '(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4))',
   'simd_rshift4' => 'simd_rshift2(packet->immh.Value(),packet->immb.Value()).c_str()',

   'simd_lshift_sca' => 'simd_lshift_scalar(packet->immh.Value(),packet->immb.Value()).c_str()',
   'simd_lshift_vec' => 'simd_lshift_vector(packet->immh.Value(),packet->immb.Value()).c_str()',

   't_sp' => 't_or_sp(packet->Rt.Value()).c_str()',

   'simd_elem_id' => 'simdElementIndex(packet->imm5.Value()).c_str()',
   'simd_elem_id2' => 'simdElementIndex2(packet->imm5.Value(),packet->imm4.Value()).c_str()',
   'simd_elem_id3' => 'simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str()',
   'simd_elem_id4' => 'packet->imm5.Value()>>4',

   'simd_low_byte_num' => 'simdLowByteNum(packet->Q.Value(),packet->imm4.Value()).c_str()',

   'fp_elem_id' => 'fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str()',

   'float8_const' => 'packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value()',

   'float8_exp_const' => 'FP8exp(packet->a.Value(),packet->b.Value(),packet->c.Value(),packet->d.Value(),packet->e.Value(),packet->f.Value(),packet->g.Value(),packet->h.Value())',

   'b5_b40'   => 'packet->b5.Value()<<4 | packet->b40.Value()',

   'Q8_16'    => '8<<packet->Q.Value()',
   'Q16_32'   => '16<<packet->Q.Value()',
   'Q24_48'   => '24<<packet->Q.Value()',
   'Q32_64'   => '32<<packet->Q.Value()',

   'ldr1_imm' => '1<<packet->size.Value()',

   'label1'   => '(packet->op.Value() == 1) ? SignExtend((packet->immhi.Value()<<2 | packet->immlo.Value())<<12,32) : SignExtend(packet->immhi.Value()<<2 | packet->immlo.Value(),21)',
   'label2'   => 'SignExtend(packet->imm19.Value()<<2,21)',
   'label3'   => 'SignExtend(packet->imm26.Value()<<2,28)',

   '<m>'      => 'ZR(packet->Rm.Value()).c_str()', #<--- ADD ADD(extended register)
 
   '<op1>'    => 'packet->op1.Value()', 
   '<op2>'    => 'packet->op2.Value()',
 
   '<option>' => 'barrier_option(packet->CRm.Value(), packet->op2.Value()==6).c_str()', 

   '<simm>'   => '(int) SignExtend(packet->imm9.Value(),9)'
);


while(<>) {
    $page_num = $1 if /(C[67]\-\d+)/;

    if (/(C6\.6\.\d+)\s+([A-Z][A-Za-z0-9\(\)\s\-\,\&\.]+)/) {
        $in_section = 1;
        $in_operation = 0;

        $in_asm16 = 0;
        $in_asm32 = 0;
        $in_asm64 = 0;
        $in_asm = 0;
        $in_asmV = 0; 
        $is_prepostoff = 0;
        $in_asmS = 0;
        $in_asmVct = 0;
        $in_asmT = 0;
        $in_asmSP = 0;
        $in_asmDP = 0;
        $in_cvtpre = 0;

        $ldrvariant_key = '';
        $movvariant_key = '';
        $ldnvariant_key = '';

        $prepostvariant_key = '';

	my $section = $1;
        $iname = $2;
        chomp $iname;
        #print "[$section] '$iname'\n";
        $sections{$iname} = $section;
        $pages{$iname} = $page_num;

        if ($iname eq 'LDPSW' or $iname eq 'LDP' or $iname eq 'STP') {
            my $prefix = $iname;
            $iname = "$prefix (Post-index),$prefix (Pre-index),$prefix (Signed offset)";
            $sections{$iname} = $section;
            $pages{$iname} = $page_num;
 	} 
        elsif ($iname eq 'LDRB (immediate)' or $iname eq 'LDRH (immediate)' or $iname eq 'LDRSB (immediate)' 
               or $iname eq 'LDRSH (immediate)' or $iname eq 'LDRSW (immediate)' or $iname eq 'LDR (immediate)' 
               or $iname eq 'STR (immediate)' or $iname eq 'STRB (immediate)' or $iname eq 'STRH (immediate)'
               or $iname eq 'LDR immediate (SIMD&FP)'
              ) {
            my $prefix = $iname;
            $iname = "$prefix (Post-index),$prefix (Pre-index),$prefix (Unsigned offset)";
            $sections{$iname} = $section;
            $pages{$iname} = $page_num;
 	} 

        push(@inames,$iname);

        $dest_symbols{$iname} = [];
        $src_symbols{$iname} = [];
        $asms16bit{$iname} = '???';
        $asms32bit{$iname} = '???';
        $asms64bit{$iname} = '???';
        $asms{$iname}      = '???';
        $asmSets{$iname}   = [ ];

        $asmScalar{$iname}  = '???';
        $asmVector{$iname}  = '???';
        $asmType{$iname}    = '???';

        $asmSP{$iname}    = '???';
        $asmDP{$iname}    = '???';

        $asmCvtPre{$iname} = [ ];

        $is_float{$iname} = 0;
 
        next;
    }

    if (/(C7\.3\.\d+)\s+([A-Z][A-Za-z0-9\(\)\s\-\,\&\.]+)/) {
        $in_section = 1;
        $in_operation = 0;

        $in_asm16 = 0;
        $in_asm32 = 0;
        $in_asm64 = 0;
        $in_asm = 0;
        $in_asmV = 0; 
        $is_prepostoff= 0;
        $in_asmS = 0;
        $in_asmVct = 0;
        $in_asmT = 0;
        $in_asmSP = 0;
        $in_asmDP = 0;
        $in_cvtpre = 0;

        $ldrvariant_key = '';
        $movvariant_key = '';
        $ldnvariant_key = '';

        $prepostvariant_key = '';

	my $section = $1;
        $iname = $2;
        chomp $iname;
        #print "[$section] '$iname'\n";

        if ($iname =~ /\((immediate|literal|register)\, SIMD\&FP\)/) {
            my $in = $`;
            my $ty = $1;
            $iname = $` . $ty . ' (SIMD&FP)';
	}

        $sections{$iname} = $section;
        $pages{$iname} = $page_num;

        if ($iname =~ 'LDP' or $iname =~ 'STP') {
            my $prefix = $iname;
            $iname = "$prefix (Post-index),$prefix (Pre-index),$prefix (Signed offset)";
            $sections{$iname} = $section;
            $pages{$iname} = $page_num;
 	} 
        if ($iname =~ '(LD|ST)\d \(multiple structures\)') {
            my $prefix = $iname;
            $iname = "$prefix (No offset),$prefix (Post-index)";
            $sections{$iname} = $section;
            $pages{$iname} = $page_num;
 	} 

        push(@inames,$iname);

        $dest_symbols{$iname}   = [];
        $src_symbols{$iname}   = [];
        $asms16bit{$iname} = '???';
        $asms32bit{$iname} = '???';
        $asms64bit{$iname} = '???';
        $asms{$iname}      = '???';
        $asmSets{$iname}   = [ ];

        $asmScalar{$iname}  = '???';
        $asmVector{$iname}  = '???';
        $asmType{$iname}    = '???';

        $asmSP{$iname}    = '???';
        $asmDP{$iname}    = '???';

        $asmCvtPre{$iname} = [ ];

        $is_float{$iname} = 1;
        next;
    }

    next if not $in_section;

    if (/This instruction is an alias of the (\w[\w\s\,\(\)]+) instruction/) {
        $aliases{$iname} = $1;        
        #next;
    }

    if (/Assembler symbols/) {
        #print "AAA '$iname'\n" if $iname =~ /LDP/;
        $in_operation = 0;
        $in_symbols = 1;
        next;
    }

    if (/Operation/) {
        $in_operation = 1;
        $in_symbols = 0;
        next;
    }

    if (/Shared decode for all variants/) {
        #print "END AAA '$iname'\n" if $iname =~ /LDP/;
        $in_symbols = 0;
        $in_asm = 0;
        next;
    }

    #print "DDD ($iname): $_" if $in_symbols and $iname =~ /LDP/;

    if ($in_symbols and (/(\<[HDSTCWXV][dnmtsab]\d*\>)/ or /(\<op\d\>)/ or /(\<cond\>)/ or /(\<label\>)/ or /(\<imm[\d]*\>)/ 
          or /(\<option\>)/ or /(\<Wd\|WSP\>)/ or /(\<Wn\|WSP\>)/ or /(\<Xd\|SP\>)/ or /(\<Xn\|SP\>)/ or /(\<Xt[12]\>)/ or /(\<[Rm]\>)/ or /(\<simm\>)/ or /(\<pimm\>)/ 
          or /(\<[V|T]\>)/ ) ) {
	my $operand = $1;
        my $is_dest = (/destination/) ? 1 : 0;

	push(@{$dest_symbols{$iname}},$operand) if $is_dest;
	push(@{$src_symbols{$iname}},$operand) if not $is_dest;

        #print "ZZZ: '$iname' ($operand)\n" if $iname =~ /LDP/;

        next if not /variant/; #<---OOPS! assembly intersperced with assembly symbols
    }

    if ( $is_float{$iname} and $iname =~ /LD|ST/ and $iname =~ /single structure/ and /((8|16|32|64|128)\-bit variant)/) {
        my $variant = $1;
        if (/(\([^\)]+\))/) {
            my $_enc = $1;
            if ($_enc =~ /opcode \= [01]+/) {
                $variant .= ' ' . $_enc;
                $in_operation = 0;
                $in_symbols = 0;
                $ldrvariant_key = $variant;
                #print "XXXX $iname<<< $variant\n";
                #exit;
                next;
            }
	}
    }

    if ( /((16|32)\-bit variant \(cmode \= [01x]+\))/ and $is_float{$iname} == 1) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        #print "RRR '$ldrvariant_key'\n" if $iname =~ /BIC/;
        next;
    }

    if ( /((8|16|32|64|128)\-bit variant \(size \= [01]+\, opc \= [01]+\))/ and $is_float{$iname} == 1) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        #print "RRR '$ldrvariant_key'\n" if $iname =~ /BIC/;
        next;
    }

    if (/^16\-bit variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asm16 = 1;
        next;
    }

    if ( /((32|64|128)\-bit variant \(opc \= [01]+\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;   #OOPS????????
        $ldrvariant_key = $1 if $is_float{$iname} == 1;
        $ldnvariant_key = $1 if $is_float{$iname} == 0;

        #print "RRR $_" if $iname =~ /LDP/;
        next;
    }

    if ( /((32|64)\-bit variant \(Q \= [01]\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;
        $movvariant_key = $1;
        next;
    }

    if (/^32\-bit variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asm32 = 1;
        next;
    }

    if (/^64\-bit variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asm64 = 1;
        next;
    }

    if (/[BHW] variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmV = 1;
        next;
    }

    if ( /((One|Two|Three|Four) register[s]* variant \(opcode \= \d+\))/) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        next;
    }

    if ( /((8|16|32|64)\-bit\, (immediate|register) offset variant \(Rm [\!]*\= \d+\, opcode \= \d+\))/ and $is_float{$iname}==1) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        #print "QQQQQQQ: $_";
        next;
    }

    if ( /((8|16|32|64)\-bit\, (immediate|register) offset variant \(Rm [\!]*\= \d+\, opcode \= \d+\, size \= [01x]+\))/ and $is_float{$iname}==1) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        #print "QQQQQQQ: $_";
        next;
    }

    if ( /((8|16|32|64)\-bit\, (immediate|register) offset variant \(Rm [\!]*\= \d+\, opcode \= \d+\, S \= \d+\, size \= [01x]+\))/ and $is_float{$iname}==1) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        #print "QQQQQQQ: $_";
        next;
    }

    if ( /((Pre\-index|Post\-index|Signed offset|Unsigned offset)) variant/) {
        my $variant = $1;
        if ($iname =~ /$variant/ and $iname =~ /\,/) {
            $in_operation = 0;
            $in_symbols = 0;
            $in_asmV = $variant;
            next;
        }
    }

    if ( /((One|Two|Three|Four) register[s]*\, (immediate|register) offset variant \(Rm [\!]*\= 11111\, opcode \= \d+\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = $1;
        #print "PPPP '$ldrvariant_key'\n" if $iname =~ /LD1/;
        next;
    }

    if (/No offset variant/ and $is_float{$iname}==1 
        and ($iname =~ /LD\d \(multiple/ or $iname =~ /ST\d \(multiple/ or $iname =~ /LD[1234]R/) ) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = 'No offset';
        #print "PPPP '$ldrvariant_key'\n" if $iname =~ /LD1/;
        next;
    }
    if (/Immediate offset variant/ and $is_float{$iname}==1 
        and ($iname =~ /LD\d \(multiple/ or $iname =~ /ST\d \(multiple/ or $iname =~ /LD[1234]R/) ) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = 'Immediate offset';
        #print "PPPP '$ldrvariant_key'\n" if $iname =~ /LD1/;
        next;
    }
    if (/Register offset variant/ and $is_float{$iname}==1 
        and ($iname =~ /LD\d \(multiple/ or $iname =~ /ST\d \(multiple/ or $iname =~ /LD[1234]R/) ) {
        $in_operation = 0;
        $in_symbols = 0;
        $ldrvariant_key = 'Register offset';
        #print "PPPP '$ldrvariant_key'\n" if $iname =~ /LD1/;
        next;
    }

    if ( /((8|16|32)\-bit (shifted immediate |shifting ones )*variant \(op \= [01]\, cmode \= [01x]+\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;
        $movvariant_key = $1;
        next;
    }

    if ( /((8|16|32)\-bit (shifted immediate |shifting ones )*variant \(cmode \= [01x]+\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;
        $movvariant_key = $1;
        next;
    }

    if ( /(64\-bit (scalar|vector) variant \(Q \= [01]\, op \= 1\, cmode \= 1110\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;
        $movvariant_key = $1;
        next;
    }

    if ( /((Two|Three|Four|Single) register table variant \(len = [01]+\))/ ) {
        $in_operation = 0;
        $in_symbols = 0;
        $movvariant_key = $1;
        next;
    }

    if (/X variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmV = 1;
        next;
    }

    if (/Scalar variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmS = 1;
        next;
    }

    if (/SIMD variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmS = 1;
        next;
    }

    if (/Vector variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmVct = 1;
        next;
    }

    if (/same type variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmT = 1;
        next;
    }

    if (/Single\-precision variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmSP = 1;
        next;
    }

    if (/Double\-precision variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asmDP = 1;
        next;
    }

    if (/ to single\-precision variant/ or / to double\-precision variant/ or / to half\-precision variant/
        or / to 32\-bit variant/ or / to 64\-bit variant/ or / to top half of 128\-bit variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_cvtpre = 1;
        next;
    }

    if (/^Literal variant/ or /is equivalent to/ or /branch offset variant/ or /Integer variant/ or /System variant/ 
        or /No offset variant/ or /\-index variant/ or /igned offset variant/) {
        $in_operation = 0;
        $in_symbols = 0;
        $in_asm = 1;
        next;
    }

    if (/Post\-index/) {
        $is_prepostoff = 1;
        next;
    }
    if (/Pre\-index/) {
        $is_prepostoff = 2;
        next;
    }
    if (/Unsigned offset/) {
        $is_prepostoff = 3;
        next;
    }

    if ($in_asm16 and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asms16bit{$iname} = $asm;
        $in_operation = 0;
        $in_asm16 = 0;
        next;      
    }    

    if ($ldrvariant_key ne '' and /^\s/) {
        my $asm = $';
        chomp $asm;

        my $lookup_name = $iname;

        if ($iname =~ /\,/ and not $iname =~ /vector\, (immediate|register)/) {
            
            my $iname_prefix = $iname;
            if ($iname =~ /\) \(/) {
                $iname_prefix = $` . ')';
            } elsif ($iname =~ / \(/) {
                $iname_prefix = $`;
            }

            if ($asm =~ /\>$/ and $iname =~ /Post\-index/) {
               $lookup_name = "$iname_prefix (Post-index)";
            } elsif ($asm =~ /\!$/ and $iname =~ /Pre\-index/) {
               $lookup_name = "$iname_prefix (Pre-index)";
            } elsif ($iname =~ /Signed offset/) {
               $lookup_name = "$iname_prefix (Signed offset)";
            } elsif ($iname =~ /Unsigned offset/) {
               $lookup_name = "$iname_prefix (Unsigned offset)";
            } elsif ($iname =~ /No offset/) {
               $lookup_name = "$iname_prefix (No offset)";
            } elsif ($iname =~ /Immediate offset/) {
               $lookup_name = "$iname_prefix (Immediate offset)";
            } elsif ($iname =~ /Register offset/) {
               $lookup_name = "$iname_prefix (Register offset)";
            }
	}

        if ($ldrvariant_key eq '16-bit variant (cmode = 10x1)') {
            $asm .= "   ";
	}
        ${$ldr_variants{$lookup_name}}{$asm} = $ldrvariant_key; #<---insert pre/post/off class designation here???

        #${$ldr_variants{$iname}}{$asm} = $ldrvariant_key;

        $ldrvariant_key = '';
    }
 
    if ($ldnvariant_key ne '' and /^\s/) {
        my $asm = $';
        chomp $asm;

        my $lookup_name = $iname;

        if ($iname =~ /\,/ and not $iname =~ /vector\, (immediate|register)/) {
            
            my $iname_prefix = $iname;
            if ($iname =~ /\) \(/) {
                $iname_prefix = $` . ')';
            } elsif ($iname =~ / \(/) {
                $iname_prefix = $`;
            }

            if ($asm =~ /\>$/ and $iname =~ /Post\-index/) {
               $lookup_name = "$iname_prefix (Post-index)";
            } elsif ($asm =~ /\!$/ and $iname =~ /Pre\-index/) {
               $lookup_name = "$iname_prefix (Pre-index)";
            } elsif ($iname =~ /Signed offset/) {
               $lookup_name = "$iname_prefix (Signed offset)";
            } elsif ($iname =~ /Unsigned offset/) {
               $lookup_name = "$iname_prefix (Unsigned offset)";
            }
	}

        ${$ldn_variants{$lookup_name}}{$asm} = $ldnvariant_key; #<---insert pre/post/off class designation here???

        #print "XXX '$in_asmV' {'$lookup_name'}{'$asm'} = '$ldnvariant_key'\n" if $iname =~ /LDP/;
        $ldnvariant_key = '';

        # may as well pick up some symbols incase case they got missed...

        my @ta = split(/ /);
        foreach my $ta (@ta) {
           if ($ta =~ /(\<[HDSTCWXV][dnmtsa]\d*\>)/ or $ta =~ /(\<op\d\>)/ or $ta =~ /(\<cond\>)/ or $ta =~ /(\<label\>)/ or $ta =~ /(\<imm[\d]*\>)/ 
               or $ta =~ /(\<option\>)/ or $ta =~ /(\<Xn\|SP\>)/ or $ta =~ /(\<Xt[12]\>)/ or $ta =~ /(\<[Rm]\>)/ or $ta =~ /(\<simm\>)/ or $ta =~ /(\<pimm\>)/ 
               or $ta =~ /(\<[V|T]\>)/ ) {
	       my $operand = $1;
               my $is_dest = (/destination/) ? 1 : 0;

	       push(@{$dest_symbols{$iname}},$operand) if $is_dest;
	       push(@{$src_symbols{$iname}},$operand) if not $is_dest;
           }
        }

        next;
    }
 
    if ($movvariant_key ne '' and /^\s/) {
        my $asm = $';
        chomp $asm;
        ${$mov_variants{$iname}}{$movvariant_key} = $asm;
        $movvariant_key = '';
    }
 
    if ($in_asm32 and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asms32bit{$iname} = $asm;
        $in_operation = 0;
        $in_asm32 = 0;
        next;      
    }    

    if ($in_asm64 and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asms64bit{$iname} = $asm;
        $in_operation = 0;
        $in_asm64 = 0;
        next;      
    }    

    if ($in_asm and /^\s/) {
        my $asm = $';
        chomp $asm;
        if ($asms{$iname} ne '???') {
           # alias asm already recorded...
        } else {   
           $asms{$iname} = $asm;
        }   
        $in_operation = 0;
        $in_asm = 0;
        next;      
    }    

    if ($in_asmV and /^\s/) {
        my $asm = $';
        chomp $asm;
        if (looks_like_number($in_asmV) and $in_asmV == 1) {
            push(@{$asmSets{$iname}},$asm);
        } else {
            #print "YYY '$iname'\n" if $iname =~ /LDRB/;
            my $iname_prefix = $iname;
            if ($iname =~ /\) \(/) {
                $iname_prefix = $` . ')';
            } elsif ($iname =~ / \(/) {
                $iname_prefix = $`;
            }
            my $iname_mode = "$iname_prefix ($in_asmV)";
            #print "XXX '$iname_mode' >>> '$asm'\n" if $iname =~ /LDRB/;
            push(@{$asmSets{$iname_mode}},$asm);
	}
        $in_operation = 0;
        $in_asmV = 0;
        next;      
    }    

    if ($in_cvtpre and /^\s/) {
        my $asm = $';
        chomp $asm;
        push(@{$asmCvtPre{$iname}},$asm);
        $in_operation = 0;
        $in_cvtpre = 0;
        next;      
    }    

    if ($in_asmT and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asmType{$iname} = $asm;
        $in_operation = 0;
        $in_asmT = 0;
        next;      
    }    

    if ($in_asmS and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asmScalar{$iname} = $asm;
        $in_operation = 0;
        $in_asmS = 0;
        next;      
    }    

    if ($in_asmSP and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asmSP{$iname} = $asm;
        $in_operation = 0;
        $in_asmSP = 0;
        next;      
    }    

    if ($in_asmDP and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asmDP{$iname} = $asm;
        $in_operation = 0;
        $in_asmDP = 0;
        next;      
    }    

    if ($in_asmVct and /^\s/) {
        my $asm = $';
        chomp $asm;
        $asmVector{$iname} = $asm;
        $in_operation = 0;
        $in_asmVct = 0;
        next;      
    }    

}

foreach my $iname (@inames) {
    if ($iname =~ /\,/ and not $iname =~ /(vector|scalar)\, (immediate|register|integer|fixed\-point)/) {
	my @ta = split(/\,/,$iname);
        my $instance_num = 1;
        foreach my $in (@ta) {
            $in =~ s/^\s+//;
            &process_iname($iname,$in,$instance_num);
            $instance_num += 1;
        } 
    } else { 
        &process_iname($iname,$iname,-1);
   }
}

#print "all operands:";
#foreach my $operand (sort(keys %all_operands)) {
#    print " $operand";
#}
#print "\n";

exit;

sub print_iname_header {
    my($iname,$iname_inst,$instance_num) = @_;

    my $alias = defined($aliases{$iname}) ? ' (ALIAS)' : '';

    print "instruction: ${iname_inst}$alias\n";
    print "alias of: " . $aliases{$iname} . "\n" if defined($aliases{$iname});
    print "section: " . $sections{$iname} . "\n";
    print "page: ". $pages{$iname} . "\n";

    my %unique_operands = ();
    foreach my $op (@{$dest_symbols{$iname}}) {
	$unique_operands{$op} = $op;
    }

    print "destination operands: " . join(',',sort(keys %unique_operands)) . "\n";

    %unique_operands = ();
    foreach my $op (@{$src_symbols{$iname}}) {
	$unique_operands{$op} = $op;
    }

    print "source operands: " . join(',',sort(keys %unique_operands)) . "\n";
}

sub print_instance {
    my($iname,$iname_inst,$instr_enum,$asm,$qualifier_in,$instance_num) = @_;

    print "instance-name: $instr_enum\n";
    print "instance-num: $instance_num\n" if $instance_num > 0;

    my $notes = '';
    my $qualifier = '';

    if ($qualifier_in eq '') {
       # no qualifier...
    } else {
       if ($qualifier_in =~ /\(([^\)]+)\)/) {
           $notes = $`;
           $qualifier = $1;
       } else {
           print "QUALIFIER: '$qualifier_in' ???\n";
           exit(-1);
       }
       print "qualifier: $qualifier\n" if $qualifier ne '';
       print "notes: $notes\n" if $notes ne '';
    }

    &print_iname_header($iname,$iname_inst,$instance_num);

    print "assembly: $asm\n";
    print "printf:   " . &expand_to_printf($instr_enum,$asm) . "\n";
    print "\n";
}

sub process_iname {
   my ($iname,$iname_inst,$instance_num) = @_;

   #print "AAA: '$iname' '$iname_inst'\n" if $iname =~ /FCVTL/;

   if (defined($aliases{$iname}) and not defined($aliases_allowed{$iname})) {
      print "\n'$iname_inst' (ALIAS IGNORED)\n\n";
      return;
   }

   if (not defined($sections{$iname})) {
       print "ARTGH!!!!\n";
       exit(1);
   }

   #&print_iname_header($iname,$iname_inst);

   foreach my $op (@{$dest_symbols{$iname}}) {
       $all_operands{$op} = 1;
   }
   foreach my $op (@{$src_symbols{$iname}}) {
       $all_operands{$op} = 1;
   }

   my @asets   = @{$asmSets{$iname}};
   my @asets_inst  = defined($asmSets{$iname_inst}) ? @{$asmSets{$iname_inst}} : ();

   my @ssets   = @{$asmScalar{$iname}};
   my @vsets   = @{$asmVector{$iname}};
   my @cvtsets = @{$asmCvtPre{$iname}};

   if ($asms{$iname} ne '???') {
       #print "   asm (asms): " . $asms{$iname} . "\n" if $iname =~ /LD2/;  
       my $instr_txt = $sections{$iname} . '/' . $iname_inst;
       my $instr_name = '?';
       my $instr_enum = '?';
       &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
       &print_instance($iname,$iname_inst,$instr_enum,$asms{$iname},'',$instance_num);
   } elsif ($#asets > 0) {
       #print "   asm (sets):\n" if $iname =~ /LD2/;
       foreach my $as (@asets) {
           my $instr_txt = $sections{$iname} . '/' . $iname_inst;
           my $instr_name = '?';
           my $instr_enum = '?';
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
	   #print "      $as\n";
	   if ($as =~ /$instr_name/) {
	       #print "   $instr_enum\: $as\n";
               #print "         " . &expand_to_printf($instr_enum,$as) . "\n";
               &print_instance($iname,$iname_inst,$instr_enum,$as,'',$instance_num);
	   }
       }

   } elsif ($#asets_inst >= 0) {
       #print "   asm (sets inst):\n" if $iname =~ /LD2/;
       foreach my $as (@asets_inst) {
           my $instr_txt = $sections{$iname} . '/' . $iname_inst;
           my $instr_name = '?';
           my $instr_enum = '?';
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
	   #print "      $as\n";
	   #print "   $instr_enum\: $as\n";
           #print "         " . &expand_to_printf($instr_enum,$as) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$as,'',$instance_num);
       }

   } elsif ($is_float{$iname} == 1) {
       #print "   asm (float):\n" if $iname =~ /LD2/;

       my $have_asm = (($asmScalar{$iname} ne '???') or ($asmVector{$iname} ne '???') 
            or ($asmType{$iname} ne '???') or ($asms16bit{$iname} ne '???') or ($asmSP{$iname} ne '???') 
            or ($asmDP{$iname} ne '???') or ($#cvtsets > 0) 
            or defined($ldr_variants{$iname_inst}) or defined($ldr_variants{$iname}) 
            or defined($mov_variants{$iname}) ) ? 1 : 0;

       my $instr_txt = $sections{$iname} . '/';

       if (substr($iname_inst,0,1) eq 'F') {
           $instr_txt .= $iname;
       } else {
           $instr_txt .= 'SIMD_' . $iname;
       }

       my $instr_name = '?';
       my $instr_enum = '?';

       if ($asmScalar{$iname} ne '???') {
           $instr_txt .= " Scalar";
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
           #print "   $instr_enum\: " . $asmScalar{$iname} . "\n";
           #print "         " . &expand_to_printf($instr_enum,$asmScalar{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asmScalar{$iname},'',$instance_num);
       }

       if ($asmVector{$iname} ne '???') {
           $instr_txt .= " Vector" if not $instr_txt =~ /[vV]ector/;
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
           #print "   $instr_enum\: " . $asmVector{$iname} . "\n";
           #print "         " . &expand_to_printf($instr_enum,$asmVector{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asmVector{$iname},'',$instance_num);
       }

       if ($asmType{$iname} ne '???') {
           $instr_txt .= " Vector" if not $instr_txt =~ /[vV]ector/;
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
           my $asm = $asmType{$iname};
           if ($asm =~ /(\{2\})/) {
               #my $prfx = $1;
               #$asm = $` . $';
               #print ">>>$iname>>>$iname_inst<<<\n" if $iname =~ /SMLAL/;
               if (substr($iname_inst,length($iname_inst)-1,1) eq '2' or $iname_inst =~ /2 \(vector\)/ ) {
                   $asm =~ s/\{2\}/2/;
                   $asm .= " (Q==1)";
               } else {
                   $asm =~ s/\{2\}//;
                   $asm .= " (Q==0)";
               }
	   }
           #print "   $instr_enum\: " . $asm . "\n";
           #print "         " . &expand_to_printf($instr_enum,$asm) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asm,'',$instance_num);
       }

       if ($asms16bit{$iname} ne '???') {  
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
           #print "   $instr_enum: " . $asms16bit{$iname} . "\n";  
           #print "         " . &expand_to_printf($instr_enum,$asms16bit{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asms16bit{$iname},'',$instance_num);
       }

       if ($asmSP{$iname} ne '???') {  
           my $stxt = $instr_txt . " Single" . " Single\-precision";
           &derive_instr_enum($stxt,\$instr_name,\$instr_enum);
           #print "   $instr_enum:" . $asmSP{$iname} . " (type=00)\n";  
           #print "         " . &expand_to_printf($instr_enum,$asmSP{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asmSP{$iname},'',$instance_num);
       }

       if ($asmDP{$iname} ne '???') {
           $instr_txt .= " Double\-precision";
           #print "TXT: '$instr_txt'\n";
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
           #print "   $instr_enum:" . $asmDP{$iname} . " (type=01)\n";
           #print "         " . &expand_to_printf($instr_enum,$asmDP{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asmDP{$iname},'',$instance_num);
       }

       if ($#cvtsets > 0) {
           foreach my $as (@cvtsets) {
               my $stxt = $instr_txt;
               $stxt .= " Single" if $as =~ /\<S[dn]\>/;
               $stxt .= " Half\-precision" if $as =~ /\<Hn\>/;
               $stxt .= " Single\-precision" if $as =~ /\<Sn\>/;
               $stxt .= " Double\-precision" if $as =~ /\<Dn\>/;
               &derive_instr_enum($stxt,\$instr_name,\$instr_enum);
	       #print "   $instr_enum: $as\n";
               #print "         " . &expand_to_printf($instr_enum,$as) . "\n";
               &print_instance($iname,$iname_inst,$instr_enum,$as,'',$instance_num);
           }          
       }  

       if (defined($ldr_variants{$iname_inst}) or defined($ldr_variants{$iname})) {
           my $lookup_key = defined($ldr_variants{$iname_inst}) ? $iname_inst : $iname; 
           foreach my $key (sort(keys %{$ldr_variants{$lookup_key}})) {
               #my $stxt = $instr_txt;
               my $stxt = $sections{$iname} . '/' . $iname_inst;
               my $asm = ${$ldr_variants{$lookup_key}}{$key};

               #print "ZZZ stxt: '$stxt' inst: '$iname_inst' asm: '$asm'\n" if $iname_inst =~ /LD2/;
               my $qualifier = '';
               if ($asm =~ /\(([^\)]+)\)/) { $qualifier = '(' . $1 . ')'; }

               $stxt .= " One register"    if $asm =~ /One register/;
               $stxt .= " Two registers"   if $asm =~ /Two register/;
               $stxt .= " Three registers" if $asm =~ /Three register/;
               $stxt .= " Four registers"  if $asm =~ /Four register/;

               $stxt .= " immediate offset" if $asm =~ /(One|Two|Three|Four) register[s]*\, immediate offset/;

               my $width = '';
               $width = " 8-bit"   if $asm =~ /8\-bit/   and not $stxt =~ /8\-bit/;
               $width = " 16-bit"  if $asm =~ /16\-bit/  and not $stxt =~ /16\-bit/;
               $width = " 32-bit"  if $asm =~ /32\-bit/  and not $stxt =~ /32\-bit/;
               $width = " 64-bit"  if $asm =~ /64\-bit/  and not $stxt =~ /64\-bit/;
               $width = " 128-bit" if $asm =~ /128\-bit/ and not $stxt =~ /128\-bit/;
               $stxt .= $width;

               #print "TTTTT '$stxt'\n" if $instr_name =~ /LD1/;
               &derive_instr_enum($stxt,\$instr_name,\$instr_enum);
	       #print "   $instr_enum: $key $qualifier\n";
               #print "         " . &expand_to_printf($instr_enum,$key) . " $qualifier\n";
               &print_instance($iname,$iname_inst,$instr_enum,$key,$qualifier,$instance_num);
           }
       }

       if (defined($mov_variants{$iname})) {
           #print "   asm:\n";
           foreach my $key (sort(keys %{$mov_variants{$iname}})) {
               my $stxt = $instr_txt;
               $stxt .= " shift" if $key =~ /shift/;
               $stxt .= " immediate" if not $iname =~ /UMOV/;
               $stxt .= " ones" if $key =~ /ones/;
               $stxt .= " modified" if not $iname =~ /UMOV/;
               $stxt .= " vector" if $key =~ /vector/;
               $stxt .= " 8-bit" if $key =~ /8\-bit/;
               $stxt .= " 16-bit" if $key =~ /16\-bit/;
               $stxt .= " 32-bit" if $key =~ /32\-bit/;
               $stxt .= " 64-bit" if $key =~ /64\-bit/;

               my $asm = ${$mov_variants{$iname}}{$key};
               &derive_instr_enum($stxt,\$instr_name,\$instr_enum);
               #print "   $instr_enum: $asm ( $key )\n";
               #print "         " . &expand_to_printf($instr_enum,$asm) . " ( $key )\n";
               &print_instance($iname,$iname_inst,$instr_enum,$asm,$key,$instance_num);
           }
       }

       print "   asm: ???\n" if not $have_asm;
   } else {
       my $have_asm = (($asms32bit{$iname} ne '???') or ($asms64bit{$iname} ne '???') 
                      or defined($ldn_variants{$iname}) or defined($ldn_variants{$iname_inst})) ? 1 : 0;
       #print "   ASM: '$have_asm' ???\n" if $iname =~ /LDP/;
       if ($asms32bit{$iname} ne '???') {
           my $instr_txt = $sections{$iname} . '/' . $iname_inst . " 32-bit";
           my $instr_name = '?';
           my $instr_enum = '?';
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
	   #print "      $as\n";
	   #print "      $instr_enum\: $asms32bit{$iname}\n";
           #print "         " . &expand_to_printf($instr_enum,$asms32bit{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asms32bit{$iname},'',$instance_num);
       }
       if ($asms64bit{$iname} ne '???') {
           my $instr_txt = $sections{$iname} . '/' . $iname_inst . " 64-bit";
           my $instr_name = '?';
           my $instr_enum = '?';
           &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
	   #print "      $as\n";
	   #print "      $instr_enum\: $asms64bit{$iname}\n";
           #print "         " . &expand_to_printf($instr_enum,$asms64bit{$iname}) . "\n";
           &print_instance($iname,$iname_inst,$instr_enum,$asms64bit{$iname},'',$instance_num);
       }
       if (defined($ldn_variants{$iname_inst}) or defined($ldn_variants{$iname})) {
           my $lookup_key = defined($ldn_variants{$iname_inst}) ? $iname_inst : $iname; 
           #print "   asm:\n";
           foreach my $key (sort(keys %{$ldn_variants{$lookup_key}})) {
               #print "RRR      " . $lookup_key . " (" . ${$ldn_variants{$lookup_key}}{$key} . ")\n" if $lookup_key =~ /LDNP/;
               if (${$ldn_variants{$lookup_key}}{$key} =~ /32\-bit/) {
                   my $instr_txt = $sections{$iname} . '/' . $iname_inst . " 32-bit";
                   my $instr_name = '?';
                   my $instr_enum = '?';
                   &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
	           #print "   $instr_enum\: $key" . " (" . ${$ldn_variants{$lookup_key}}{$key} . ")\n";
                   #print "         " . &expand_to_printf($instr_enum,${$ldn_variants{$lookup_key}}{$key}) . "\n";

                   &print_instance($iname,$iname_inst,$instr_enum,$key,${$ldn_variants{$lookup_key}}{$key},$instance_num);
               } 
               elsif (${$ldn_variants{$lookup_key}}{$key} =~ /64\-bit/) {
                   my $instr_txt = $sections{$iname} . '/' . $iname_inst . " 64-bit";
                   my $instr_name = '?';
                   my $instr_enum = '?';
                   &derive_instr_enum($instr_txt,\$instr_name,\$instr_enum);
	           #print "   $instr_enum\: $key" . " (" . ${$ldn_variants{$lookup_key}}{$key} . ")\n";
                   #print "         " . &expand_to_printf($instr_enum,${$ldn_variants{$lookup_key}}{$key}) . "\n";

                   &print_instance($iname,$iname_inst,$instr_enum,$key,${$ldn_variants{$lookup_key}}{$key},$instance_num);
               } 
               else {
	           print "      " . $key . " (" . ${$ldn_variants{$lookup_key}}{$key} . ")\n";
                   print "         " . &expand_to_printf($key,${$ldn_variants{$lookup_key}}{$key}) . "\n";
                   print "OOPS!!!!\n";
                   exit(-1);
               }
           }
       }
       if (not $have_asm) {
           print "   asm: ???\n" ;
           print "OOPS!!!!\n";
           exit(-1);
       }
   }

}

my %fixup_enum_by_instance = (
  'B_COND'                => 'B_COND_IMM',
  'B'                     => 'B_IMM',
  'CBNZ_32'               => 'CBNZ_IMM_32',
  'CBNZ_64'               => 'CBNZ_IMM_64',
  'CBZ_64'                => 'CBZ_IMM_64',
  'CBZ_32'                => 'CBZ_IMM_32',
  'FABD_SCALAR'           => 'SIMD_FABD_SCALAR',
  'FABD_SCALAR_VEC'       => 'SIMD_FABD_VEC',
  'FABS_VEC'              => 'SIMD_FABS_REG_VEC',
  'FACGE_SCALAR'          => 'SIMD_FACGE_SCALAR',
  'FACGE_SCALAR_VEC'      => 'SIMD_FACGE_VEC',
  'FACGT_SCALAR'          => 'SIMD_FACGT_SCALAR',
  'FACGT_SCALAR_VEC'      => 'SIMD_FACGT_VEC',
  'FADD_VEC'              => 'SIMD_FADD_VEC',
  'FADDP_SCALAR'          => 'SIMD_FADDP',
  'FADDP_VEC'             => 'SIMD_FADDP_VEC',
  'FCMEQ_SCALAR_VEC_ZERO' => 'SIMD_FCMEQ_REG_SCALAR_ZERO',
  'FCMEQ_REG_SCALAR_VEC'  => 'SIMD_FCMEQ_REG_VEC',
  'FCMEQ_REG_SCALAR'      => 'SIMD_FCMEQ_REG_SCALAR',
  'FCMEQ_SCALAR_ZERO'     => 'SIMD_FCMEQ_REG_VEC_ZERO',
  'FCMGE_REG_SCALAR_VEC'  => 'SIMD_FCMGE_REG_VEC',
  'FCMGE_SCALAR_ZERO'     => 'SIMD_FCMGE_REG_SCALAR_ZERO',
  'FCMGE_SCALAR_VEC_ZERO' => 'SIMD_FCMGE_REG_VEC_ZERO',
  'FCMGE_REG_SCALAR'      => 'SIMD_FCMGE_REG_SCALAR'
);


sub derive_instr_enum {
    my ($instr_txt,$instr_name,$instr_enum) = @_;

    #print "DDD: '$instr_txt'\n" if $instr_txt =~ /FCVTL/;

    $$instr_name = '';
    $$instr_enum = '';

    $instr_txt =~ /\/\s*([A-Z])/;
    #my ($section,$instr) = split(/\/[A-Z]/,$instr_txt);
    my $section = $`;
    if (not defined($1)) {
        print "text: '$instr_txt' ???\n";
        exit(1);
    }

    my $instr = $1 . $';

    #print "EEE section: '$section', instr: '$instr'\n" if $instr_txt =~ /FCVTL/;

    $instr =~ /(\w+)/;
    $$instr_name = $1;
    my $enum = $1;

    #print "FFF enum: '$enum' instr: '$instr'\n" if $instr_txt =~ /FCVTL/;

    if ($enum eq 'DRPS' or $enum eq 'ERET' or $enum eq 'BLR' or $enum eq 'RET' 
        or $enum eq 'BR' or $enum eq 'TBZ' or $enum eq 'TBNZ' or $enum eq 'BL') {
        $$instr_enum = $enum;
        return;
    }

    #print "<<<$instr_txt>>>\n" if $enum =~ /LD1/;

    $enum = "SIMD_" . $enum if $instr_txt =~ /SIMD/ and not $enum =~ /SIMD/;

    $enum = "B_COND"     if $instr_txt =~ /B.cond/;
    $enum .= "_SHIFT"    if $instr_txt =~ /shift/;
    $enum .= "_IMM"      if $instr_txt =~ /immediate/;
    $enum .= "_ONES"     if $instr_txt =~ /ones/;
    $enum .= "_MOD"      if $instr_txt =~ /modified/;
    $enum .= "_TWO"      if $instr_txt =~ /Two register/;
    $enum .= "_ONE"      if $instr_txt =~ /One register/;
    $enum .= "_THREE"    if $instr_txt =~ /Three registers/;
    $enum .= "_REG"      if $instr_txt =~ /Register/;

    $enum .= "_FOUR"     if $instr_txt =~ /Four/ and not $enum =~ /_FOUR/;
    $enum .= "_SINGLE"   if $instr_txt =~ /Single/ and not $enum =~ /_SINGLE/;
    $enum .= "_THREE"    if $instr_txt =~ /Three/ and not $enum =~ /_THREE/;
    $enum .= "_REG"      if $instr_txt =~ /register/;

    $enum .= "_REG"      if $instr_txt =~ /Signed offset/;

    $enum .= "_OFF"      if $instr_txt =~ /offset/;
    $enum .= "_SINGLE"   if $instr_txt =~ /single/;
    $enum .= "_MULT"     if $instr_txt =~ /multiple/;
    $enum .= "_REG_PRE"  if $instr_txt =~ /[Pp]re\-index(ed)*/;
    $enum .= "_REG_POST" if $instr_txt =~ /[Pp]ost\-index(ed)*/;
    $enum .= "_SCALAR"   if $instr_txt =~ /Scalar/;
    $enum .= "_VEC"      if $instr_txt =~ /Vector/;
    $enum .= "_VEC"      if $instr_txt =~ /vector/;
    $enum .= "_ELEM"     if $instr_txt =~ /element/;

    $enum .= "_FROM_HP"  if $instr_txt =~ /Half\-precision/;
    $enum .= "_FROM_SP"  if $instr_txt =~ /Single\-precision/;
    $enum .= "_FROM_DP"  if $instr_txt =~ /Double\-precision/;

    $enum .= "_TO_HP"    if $instr_txt =~ /half\-precision/;
    $enum .= "_TO_SP"    if $instr_txt =~ /single\-precision/;
    $enum .= "_TO_DP"    if $instr_txt =~ /double\-precision/;

    $enum .= "_FP"       if $instr_txt =~ /floating\-point/;
    $enum .= "_FIXED"    if $instr_txt =~ /fixed\-point/;

    $enum .= "_ZERO"     if $instr_txt =~ /zero/;
    $enum .= "_STRUCT"   if $instr_txt =~ /structure/;

    $enum .= "_8"        if $instr_txt =~ /8\-bit/ and not $instr_txt =~ /128\-bit/;
    $enum .= "_16"       if $instr_txt =~ /16\-bit/;
    $enum .= "_32"       if $instr_txt =~ /32\-bit/;
    $enum .= "_64"       if $instr_txt =~ /64\-bit/;
    $enum .= "_128"      if $instr_txt =~ /128\-bit/;

    $enum .= "_TO_TOP"   if $instr_txt =~ /to top/;
    $enum .= "_FROM_TOP" if $instr_txt =~ /From top/;

    # some ugly fixup...

    if ($enum =~ /(LD|ST)(\d)_IMM_(ONE|TWO|THREE|FOUR)_REG_OFF_MULT_REG_POST_STRUCT/) {
       my $ldst = $1;
       my $ecnt = $2;
       my $rcnt = $3;
       $enum = 'SIMD_' . $ldst . $ecnt . '_' . $rcnt . '_REG_MULT_STRUCT_POST_OFF';
    } 
    elsif ($enum =~ /(LD|ST)(\d)_(ONE|TWO|THREE|FOUR)_REG_OFF_MULT_STRUCT/) {
       my $ldst = $1;
       my $ecnt = $2;
       my $rcnt = $3;
       $enum = 'SIMD_' . $ldst . $ecnt . '_' . $rcnt . '_REG_MULT_STRUCT_NO_OFF';
    }
    elsif ($enum =~ /(LD|ST)(\d)_(ONE|TWO|THREE|FOUR)_REG_MULT_REG_POST_STRUCT/) {
       my $ldst = $1;
       my $ecnt = $2;
       my $rcnt = $3;
       $enum = 'SIMD_' . $ldst . $ecnt . '_' . $rcnt . '_REG_MULT_STRUCT_POST_REG';
    }
    elsif ($enum =~ /ST(\d)_IMM_(ONE|TWO|THREE|FOUR)_REG_OFF_MULT_STRUCT/) {
       my $ecnt = $1;
       my $rcnt = $2;
       $enum = 'SIMD_ST' . $ecnt . '_' . $rcnt . '_REG_MULT_STRUCT_REG_OFF';
    }


    #print "enum: '$enum'\n";
    #exit;

    $$instr_enum = $enum;
}

sub expand_to_printf {
    my($instr,$asm) = @_;

    my $format = $asm;

    my @ops = ();

    $format =~ s/\<option\>\|\#\<imm\>/\<option\>/; #<<<DMB instruction only

    while ($format =~ /(\<[^\>]+\>)/) {
	my $op = $1;
        push(@ops,$op);

        my $bare_op = ($op =~ /\<([^\>]+)\>/) ? $1 : $op;

        my $rs = $op2print{'default'};

        if (defined($op2opexp{"$instr/$bare_op"})) {
            # instruction specific operand replace string exists...
            my $instr_specific_op = $op2opexp{"$instr/$bare_op"};
            $rs = $op2print{$instr_specific_op} if defined($op2print{$instr_specific_op});
        } elsif (defined($op2print{$op})) {
            $rs = $op2print{$op};      
        }

        $format =~ s/\<[^\>]+\>/$rs/;
    }

    $format =~ s/[\{\}]//g;  #<---strip optional element brackets

    my $tbuf = "printf(\"$format\\n\"";
    foreach my $op (@ops) {
	$tbuf .= &xlate_operand($instr,$op);
    }
    $tbuf .= ");";

    return $tbuf;
}

sub xlate_operand {
    my($instr,$_op) = @_;

    # strip operand 'brackets' from operand name for 1st level lookup...

    my $bare_op = ($_op =~ /\<([^\>]+)\>/) ? $1 : $_op;

    # see if instruction specific operand replace string exists...

    my $instr_specific_op = defined($op2opexp{"$instr/$bare_op"}) ? $op2opexp{"$instr/$bare_op"} : $_op;

    # now get replace string for operand or die trying...

    if (defined($op2parm{$instr_specific_op})) {
        if ($op2parm{$instr_specific_op} ne '') {   
            return ",$op2parm{$instr_specific_op}";
        } else {
            return "";
        }   
    }

    print "[xlate_operand] NO REPLACE PATTERN DEFINED FOR '$instr/$_op' (lookup string: '$instr_specific_op') ???\n";

    #foreach my $key (keys %op2parm) {
    #print "'$key' => '" . $op2parm{$key} . "'\n";
    #}
    #exit(-1);
    return '?';
}


