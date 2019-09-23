#!/usr/bin/perl

my %main_encodings = ();
my $main_text = '';

my %branch_encodings = ();
my $branch_text = '';

my %load_store_encodings = ();
my $load_store_text = '';

my %dp_imm_encodings = ();
my $dp_imm_text = '';

my %dp_reg_encodings = ();
my $dp_reg_text = '';

my %dp_simd_fp_encodings = ();
my $dp_simd_fp_text = '';

my %all_instructions = ();

my %all_encodings = ();
my %all_masks = ();
my %all_fields = ();

my %instrs_to_enums_dp       = ();
my %instrs_to_enums_log      = ();
my %instrs_to_enums_mov      = ();
my %instrs_to_enums_pcrel    = ();
my %instrs_to_enums_br       = ();
my %instrs_to_enums_ls       = ();
my %instrs_to_enums_ls_excl  = ();
my %instrs_to_enums_exc      = ();
my %instrs_to_enums_sys      = ();
my %instrs_to_enums_simd     = ();
my %instrs_to_enums_asimd    = ();
my %instrs_to_enums_asimd_ls = ();
my %instrs_to_enums_fp       = ();
my %instrs_to_enums_fp_ls    = ();

my $start_encoding = 0;
my $in_encodings = 0;

my $table_text = '';

my $section = '';
my $section_title = '';

# don't have any floating pt instrs implemented yet (sigh)...

my @encodings_to_skip = (
      'Advanced SIMD',
      'Cryptographic',
      'Floating-point'
);

my @vfp_encodings = (
      'Floating-point'
);

while(<>) {
    if (/(Table C4-1 A64 main encoding table)/) {
        &record_encodings(\%main_encodings,\$main_text,0);
        #&dump_encodings(\%main_encodings,$main_text);
        #exit;

        next;
    }

    if (/(Table C4-2 Encoding table for the Branches, Exception Generating and System instructions functional group)/) {
        &record_encodings(\%branch_encodings,\$branch_text,0);
        &process_encodings(\%branch_encodings,$main_text);
        next;
    }

    if (/(Table C4-3 Encoding table for the Loads and Stores functional group)/) {
        &record_encodings(\%load_store_encodings,\$load_store_text,0);
        &process_encodings(\%load_store_encodings,$main_text);
        next;
    }

    if (/(Table C4-4 Encoding table for the Data Processing - Immediate functional group)/) {
        &record_encodings(\%dp_imm_encodings,\$dp_imm_text,0);
        &process_encodings(\%dp_imm_encodings,$main_text);
        next;
    }

    if (/(Table C4-5 Encoding table for the Data Processing - Register functional group)/) {
        &record_encodings(\%dp_reg_encodings,\$dp_reg_text,0);
        &process_encodings(\%dp_reg_encodings,$main_text);
        next;
    }

    if (/(Table C4-6 Encoding table for the Data Processing - Scalar Floating-Point and Advanced SIMD functional group)/) {
        &record_encodings(\%dp_simd_fp_encodings,\$dp_simd_fp_text,0);
        &process_encodings(\%dp_simd_fp_encodings,$main_text);
        #exit;
        next;
    }

    if (/(C\d.\d.\d)\s+([A-Z][\w\-\&\(\)\/\s]+)$/ or /(C\d.\d.\d\d)\s+([A-Z][\w\-\&\(\)\/\s]+)$/) {
        $section = $1;
        $section_title = $2;
        #print "Processing " . $_; 
        chomp $section_title;
	&process_section($section,$section_title,\%all_instructions,\%all_encodings,\%all_masks,\%all_fields,0);
        #exit;
    }
}

&output_encodings();



sub derive_instr_enum {
    my ($instr_txt,$instr_name,$instr_enum) = @_;

    #print "text: '$instr_txt'\n";

    $instr_txt =~ /\/([A-Z])/;
    #my ($section,$instr) = split(/\/[A-Z]/,$instr_txt);
    my $section = $`;
    my $instr = $1 . $';

    #print "section: '$section', instr: '$instr'\n";

    $instr =~ /(\w+)/;

    $$instr_name = $1;
    $enum = $1;

    if ($enum eq 'DRPS' or $enum eq 'ERET' or $enum eq 'BLR' or $enum eq 'RET' 
        or $enum eq 'BR' or $enum eq 'TBZ' or $enum eq 'TBNZ' or $enum eq 'BL') {
        $$instr_enum = $enum;
        return;
    }

    $enum = "SIMD_" . $enum if $instr_txt =~ /SIMD/;

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

    $enum .= "_OFF"      if $instr_txt =~ /offset/;
    $enum .= "_SINGLE"   if $instr_txt =~ /single/;
    $enum .= "_MULT"     if $instr_txt =~ /multiple/;
    $enum .= "_PRE"      if $instr_txt =~ /pre\-indexed/;
    $enum .= "_POST"     if $instr_txt =~ /post\-indexed/;
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
    $enum .= "_8"        if $instr_txt =~ /8\-bit/;
    $enum .= "_16"       if $instr_txt =~ /16\-bit/;
    $enum .= "_32"       if $instr_txt =~ /32\-bit/;
    $enum .= "_64"       if $instr_txt =~ /64\-bit/;
    $enum .= "_128"      if $instr_txt =~ /128\-bit/;
    $enum .= "_TO_TOP"   if $instr_txt =~ /to top/;
    $enum .= "_FROM_TOP" if $instr_txt =~ /From top/;

    #print "enum: '$enum'\n";
    #exit;

    $$instr_enum = $enum;
}

sub categorize_enum {
    my ($instr,$enum) = @_;

    if ($instr =~ /Advanced SIMD/) {
        if ($instr =~ /load\/store/) {
	   $instrs_to_enums_asimd_ls{$instr} = $enum;
        } else {
	   $instrs_to_enums_asimd{$instr} = $enum;
	}
    } 
    elsif ($instr =~ /ranch/) {
	$instrs_to_enums_br{$instr} = $enum;
    }
    elsif ($instr =~ /Data\-processing/) {
	$instrs_to_enums_dp{$instr} = $enum;
    }
    elsif ($instr =~ /Logical/) {
	$instrs_to_enums_log{$instr} = $enum;
    }
    elsif ($instr =~ /Exception generation/) {
	$instrs_to_enums_exc{$instr} = $enum;
    }
    elsif ($instr =~ /Move wide/) {
	$instrs_to_enums_mov{$instr} = $enum;
    }
    elsif ($instr =~ /PC\-relative/) {
	$instrs_to_enums_pcrel{$instr} = $enum;
    }
    elsif ($instr =~ /System/) {
	$instrs_to_enums_sys{$instr} = $enum;
    }
    elsif ($instr =~ /Load\/store exclusive/) {
	$instrs_to_enums_ls_excl{$instr} = $enum;
    }
    elsif ($instr =~ /Load register/) {
        if ($instr =~ /SIMD\&FP/) {
	   $instrs_to_enums_fp_ls{$instr} = $enum;
	} else {
	   $instrs_to_enums_ls{$instr} = $enum;
        }
    }
    elsif ($instr =~ /Load\/store/) {
        if ($instr =~ /SIMD\&FP/) {
	   $instrs_to_enums_fp_ls{$instr} = $enum;
	} else {
	   $instrs_to_enums_ls{$instr} = $enum;
        }
    }
    elsif ($instr =~ /Add\/subtract/) {
	$instrs_to_enums_dp{$instr} = $enum;
    }
    elsif ($instr =~ /Conditional/) {
	$instrs_to_enums_dp{$instr} = $enum;
    }
    elsif ($instr =~ /Extract/) {
	$instrs_to_enums_dp{$instr} = $enum;
    }
    elsif ($instr =~ /Bitfield/) {
	$instrs_to_enums_dp{$instr} = $enum;
    }
    elsif ($instr =~ /SIMD\&FP/) {
	$instrs_to_enums_simd{$instr} = $enum;
    }
    elsif ($instr =~ /loating\-point/) {
	$instrs_to_enums_fp{$instr} = $enum;
    }
    elsif ($instr =~ /Cryptographic/) {
	$instrs_to_enums_simd{$instr} = $enum;
    }
    else {
	print "ERROR: what is '$instr'?\n";
    }
}

# --------------------------------------------------------------------------------------------------------------
#  %all_instructions - keys are specific instruction 'names' (section/instruction)
#  %all_encodings    - key is instruction name, value is encoding
#  %all_masks        -          "             , value is bit-mask indicating which encoding bits are of interest
#  %all_fields       -          "             , value are operands and bit positions
# --------------------------------------------------------------------------------------------------------------

# lets start by creating a list of all masks, sorted by the number of set bits in the mask...

my %unique_masks = ();

foreach my $instr (keys %all_masks) {
    my $mask = $all_masks{$instr};
    $unique_masks{$mask} = $mask if not defined $unique_masks{$mask};
}

my %masks_by_size = ();

foreach my $instr (keys %unique_masks) {
    my $mask = $unique_masks{$instr};
    my $bit_count = 0;
    for (my $i = 0; $i < 32; $i++) {
	my $next_bit = 1<<$i;
	$bit_count += 1 if ($mask & $next_bit);
    }
    if (defined($masks_by_size{$bit_count})) {
        push(@{$masks_by_size{$bit_count}},$mask);
    } else {
	$masks_by_size{$bit_count} = [ $mask ];
    }
}

my @sorted_mask_sizes = ();

for (my $i = 32; $i > 0; $i--) {
    push(@sorted_mask_sizes,$i) if defined($masks_by_size{$i});
}

#print "sorted masks:";
#foreach my $m (@sorted_mask_sizes) {
#    print " $m";
#}
#print "\n";
#exit;

# now lets dump out all instructions and encodings for each mask...

#  %all_encodings    - key is instruction name, value is encoding
#  %all_masks        -          "             , value is bit-mask indicating which encoding bits are of interest
#  %all_fields       -          "             , value are operands and bit positions

my @enums = ();
my @inames = ();
my $enum_id = 0;


#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
open(A64UNITTEST,">derived/test_a64sim_all_instr_encodings.C");

print A64UNITTEST "int get_next_instr_encoding(int instr_index,unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {\n";
print A64UNITTEST "switch(instr_index) {\n";

my $caseno = 0;

foreach my $bcnt (@sorted_mask_sizes) {
    foreach my $mask (@{$masks_by_size{$bcnt}}) {
        my @instrs = ();
        foreach my $next_instr (sort(keys %all_masks)) {
	    push(@instrs,$next_instr) if $all_masks{$next_instr} == $mask;
        }
        foreach my $instr (@instrs) {
            my $instr_name,$enum;
            &derive_instr_enum($instr,\$instr_name,\$enum);
            &categorize_enum($instr,$enum);
            printf A64UNITTEST "  case %s\: group = \"%s\"; mask = 0x%08x; encoding = (set_mask & ~mask) | 0x%x; break; // %s\n",
                   $enum, $instr, $mask, $all_encodings{$instr};
            $caseno += 1;
        }
    }
}

print A64UNITTEST "default: return -1; break;\n";
print A64UNITTEST "}\n";
print A64UNITTEST "return 0;\n";
print A64UNITTEST "}\n";

close A64UNITTEST;

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

open(A64DECODE,">derived/a64_instr_decode.C");

print A64DECODE "  packet->A64InstrIndex = A64_UNALLOCATED;\n\n";

foreach my $bcnt (@sorted_mask_sizes) {
    foreach my $mask (@{$masks_by_size{$bcnt}}) {
	#printf("for mask 0x%08x...\n",$mask);
        printf A64DECODE "  if (packet->A64InstrIndex==A64_UNALLOCATED) {\n    switch(packet->Opcode & 0x%08x) {\n",$mask;

        # identify all instructions with this mask...

        my @instrs = ();
        foreach my $next_instr (sort(keys %all_masks)) {
	    push(@instrs,$next_instr) if $all_masks{$next_instr} == $mask;
        }
        my %operands;
        foreach my $instr (@instrs) {
            my $instr_name,$enum;
            &derive_instr_enum($instr,\$instr_name,\$enum);
            &categorize_enum($instr,$enum);
            push(@enums,"$enum=$enum_id");
            push(@inames,"$enum=$instr_name");
            $enum_id += 1;
            printf A64DECODE "      // 0x%08x, %s: '%s' - '%s'\n",$all_encodings{$instr},$enum,$all_fields{$instr},$instr;
            printf A64DECODE "      case 0x%08x: packet->A64InstrIndex = %s;\n",$all_encodings{$instr},$enum;

            @fields = split(/ /,$all_fields{$instr});
            foreach my $field (@fields) {
               my $opname,$shift_count,$bit_mask;
               if (&is_operand($field,\$opname,\$shift_count,\$bit_mask)) {
                  #$operands{$field} = 1;
                  if ($shift_count > 0) {
                      printf A64DECODE "          packet->%s = (packet->Opcode >> %d) & 0x%x;\n",$opname,$shift_count,$bit_mask; 
                  } else {
                      printf A64DECODE "          packet->%s = packet->Opcode & 0x%x;\n",$opname,$bit_mask; 
                  }
               }
            }

            printf A64DECODE "          break;\n";

        }
        #print "\n";
        print A64DECODE "    default: break;\n";
        print A64DECODE "    }\n";

        #printf A64DECODE "    if (packet->A64InstrIndex!=A64_UNALLOCATED) {\n";
        #foreach my $field (keys %operands) {
        #   my $opname,$shift_count,$bit_mask;
        #   if (&is_operand($field,\$opname,\$shift_count,\$bit_mask)) {
        #      if ($shift_count > 0) {
        #          printf A64DECODE "        packet->%s = (packet->Opcode >> %d) & 0x%x;\n",$opname,$shift_count,$bit_mask; 
        #      } else {
        #          printf A64DECODE "        packet->%s = packet->Opcode & 0x%x;\n",$opname,$bit_mask; 
        #      }
        #   }
        #}
        #print A64DECODE "    }\n";

        print A64DECODE "  }\n";
    }
}

close A64DECODE;



sub dump_instr_enums {
    my ($instr_enums,$title) = @_;
    print A64EXEC "// ${title}...\n";
    foreach my $key (sort(keys %{$instr_enums})) {
	print A64EXEC "    " . $$instr_enums{$key} . ": //$key\n";
    }
    print A64EXEC "\n";

}


open(A64EXEC,">derived/a64_instr_exec.C");

&dump_instr_enums(\%instrs_to_enums_dp,       "A64 Data Processing");
&dump_instr_enums(\%instrs_to_enums_log,      "A64 Logical");
&dump_instr_enums(\%instrs_to_enums_mov,      "A64 Move Wide");
&dump_instr_enums(\%instrs_to_enums_pcrel,    "A64 PC Relative");
&dump_instr_enums(\%instrs_to_enums_br,       "A64 PC Branch");
&dump_instr_enums(\%instrs_to_enums_ls,       "A64 Load/Store");
&dump_instr_enums(\%instrs_to_enums_ls_excl,  "A64 Load/Store Exclusive");
&dump_instr_enums(\%instrs_to_enums_exc,      "A64 Exception");
&dump_instr_enums(\%instrs_to_enums_sys,      "A64 System");
&dump_instr_enums(\%instrs_to_enums_simd,     "A64 SIMD");
&dump_instr_enums(\%instrs_to_enums_asimd,    "A64 ASIMD");
&dump_instr_enums(\%instrs_to_enums_asimd_ls, "Advanced SIMD load/store");
&dump_instr_enums(\%instrs_to_enums_fp,       "A64 Floating point");
&dump_instr_enums(\%instrs_to_enums_fp_ls,    "A64 SIMD\&FP Load/Store");

close A64EXEC;

open(A64ENUMS,">derived/a64_instr_enums.h");
print A64ENUMS "enum {\n";
foreach my $edef (@enums) {
   print A64ENUMS "   ${edef},\n";
}
print A64ENUMS "   A64_UNALLOCATED=$enum_id\n";
print A64ENUMS "};\n";
close A64ENUMS;

open(A64INAMES,">derived/a64_instr_names.C");
foreach my $iname (@inames) {
    my @ta = split(/\=/,$iname);
    print A64INAMES "   case $ta[0]\: iname = \"$ta[1]\"; break;\n"; 
}
close A64INAMES;

open(A64ENAMES,">derived/a64_instr_enum_names.C");
foreach my $iname (@inames) {
    my @ta = split(/\=/,$iname);
    print A64ENAMES "   case $ta[0]\: iname = \"$ta[0]\"; break;\n"; 
}
close A64ENAMES;

sub is_operand {
    my ($field,$opname,$shift_count,$bit_mask) = @_;

    #print "is_operand: '$field'\n";

    return 0 if not $field =~ /\=/;

    $$opname = $`;

    my $bit_range = $';
   
    #print "bit range: '$bit_range'\n";

    if (not $bit_range =~ /\,/) {
        #print "one bit field...\n";
        $$shift_count = $bit_range;
	$$bit_mask = 1;
        return 1;
    }

    my ($start,$end) = split(/\,/,$bit_range);

    #print "start: $start, end: $end\n";

    $$shift_count = $end;

    my $mask = 0;
    for (my $i = $start; $i >= $end; $i--) {
       $mask = ($mask<<1) | 1;
    }

    $$bit_mask = $mask;

    return 1;
}



sub process_section {
    my($section,$title,$all_instructions,$all_encodings,$all_masks,$all_fields,$dump) = @_;

    print "\nsection($section): '$title'\n" if $dump;

    my $nl = <STDIN>;
    print $nl if $dump;

    my %bits_fields = ();

    my $fields_txt = '';

    my @ta = split(' ',$nl);
    foreach my $ta (@ta) {
	my ($field_or_bit,$bit_field_or_range) = split(/\=/,$ta);
        if ($field_or_bit eq '0' or $field_or_bit eq '1') {
            $bits_fields{$bit_field_or_range} = $field_or_bit;
        } else {
	    $bits_fields{$field_or_bit} = $bit_field_or_range;
            $fields_txt .= " $ta";
        }
    }

    if ($dump) {
      print "bit fields:";
      foreach my $key (keys %bits_fields) {
  	print " $key=" . $bits_fields{$key};
      }
      print "\n";
    }

    print "fields only: $fields_txt\n" if $dump;

    my $bits = <STDIN>;
    chomp $bits;
    print "bits: $bits\n" if $dump;

    if (not $bits =~ /[\d\s]+/) {
	print "ERROR: unexpected input: $bits ???\n";
        exit(1);
    }

    my $dtxt = <STDIN>;
    if (not $dtxt =~ /Decode fields/) {
        print "ERROR: unexpected input: $dtxt ???\n";
        exit(1);
    }

    $dtxt = <STDIN>;
    if (not $dtxt =~ /Instruction Page Variant/) {
        print "ERROR: unexpected input: $dtxt ???\n";
        exit(1);
    }

    $dtxt = <STDIN>;
    chomp $dtxt;
    my @replace_fields = split(/\s/,$dtxt);
    print "replace fields: " . join(" ",@replace_fields) . "\n" if $dump;

    while(<>) {
	return if /^\s*$/;

        if (/^([\d\s\-x\!\=]+)/) {
            my %fixups = ();
 
            print "\n" if $dump;
            my $ibit_txt = $1;
            my $instr = $';
            chomp $instr;
            my @ibits = split(/\s+/,$ibit_txt);
            print "$instr, ibits: " . join(",",@ibits) . "\n" if $dump;
            if ($#replace_fields != $#ibits) {
              print "MISMATCH ON REPLACE FIELDS???\n";
              exit(1);
            }
            for (my $i = 0; $i <= $#replace_fields; $i++) {
               if ($ibits[$i] =~ /\!\=/) {
                  print "--->skipping replace field '$replace_fields[$i]' with value '$ibits[$i]'\n" if $dump;
               } else { 
                  $fixups{$replace_fields[$i]} = $ibits[$i];
               }
            }

            if ($dump) {
              print "fixups:";
              foreach my $key (keys %fixups) {
                print " $key=" . $fixups{$key};
              }
              print "\n";
            }

            my %ifields = %bits_fields;
            foreach my $rf (keys %fixups) {
              my $bit_position = $ifields{$rf};
              $ifields{$bit_position} = $fixups{$rf};
            }
            if ($dump) {
              print "instr: $instr, fields:";
              foreach my $key (keys %ifields) {
                print " $key=" . $ifields{$key};
              }
              print "\n";
            }

            #expand multi-bit fields with fixed values...
            foreach my $key (keys %ifields) {
               if (($key =~ /\,/) and ($ifields{$key} =~ /[01]+/)) {
                 my ($start_index,$end_index) = split(/\,/,$key);
                 my @bit_values = split(//,$ifields{$key});
                 print "start/end: $start_index/$end_index, bits: " , join(',',@bit_values) . "\n" if $dump;
                 for (my $i = $start_index, $j = 0; $i >= $end_index; $i--, $j++) {
                    $ifields{$i} = $bit_values[$j];
                 }
               }
            }     

            if ($dump) {
              print "instr: $instr, fields (after expanding):";
              foreach my $key (keys %ifields) {
                print " $key=" . $ifields{$key};
              }
              print "\n";
            }

            # now build fixed instruction encoding and mask...
            my @encoding = ();
            my @mask = ();
            for (my $i = 31; $i >= 0; $i--) {
               $encoding[$i] = 0;
               $mask[$i] = 'x';
            }
            foreach my $if (keys %ifields) {
               if ($ifields{$if} eq '0' or $ifields{$if} eq '1') {
                 my $bit_index = 0 + $if;
                   $encoding[$bit_index] = 0 + $ifields{$if};
                   $mask[$bit_index] = 1;
                   #print "for bit $bit_index, bit-value: $encoding[$bit_index], mask-value: $mask[$bit_index]\n";  
               }
            }
            my $opcode = 0;
            my $opcode_mask = 0;
            for (my $i = 31; $i >= 0; $i--) {
               $opcode |= $encoding[$i]<<$i;
               $opcode_mask |= (1<<$i) if $mask[$i] ne 'x';
            }

            my $instr_index = "$section_title/$instr";

            printf "section: '$section_title', instr: '$instr', encoding: 0x%08x, mask: 0x%08x\n",$opcode,$opcode_mask if $dump;

            if (defined($$all_instructions{$instr_index})) {
                print "Duplicate instruction '$instr_index'???\n";
                exit(1);
            }

            $$all_instructions{$instr_index} = 1;
            $$all_encodings{$instr_index}    = $opcode;
            $$all_masks{$instr_index}        = $opcode_mask;
            $$all_fields{$instr_index}       = $fields_txt;

            #exit if  $instr =~ /LD3 \(single structure\) 64\-bit, register offset/;
        } else {
	    print "ERROR: unexpected input: $_";
            exit(1);
	}
    }
}

sub dump_encodings {
    my ($encodings,$encoding_text) = @_;

    print "$encoding_text\n";

    foreach my $grp (keys %$encodings) {
       print "group: $grp\n";
       foreach my $bit (keys %{$$encodings{$grp}}) {
	   print " $bit=" . $$encodings{$grp}{$bit};
       }
       print "\n";
    } 

    print "end of $encoding_text\n";
}

my %master_encodings = ();

sub skip_encoding {
    my ($encoding) = @_;

    foreach my $se (@encodings_to_skip) {
       return 1 if $encoding =~ /$se/;
    }

    return 0;
}

sub vfp_encoding {
    my ($encoding) = @_;

    foreach my $se (@vfp_encodings) {
       return 1 if $encoding =~ /$se/;
    }

    return 0;
}

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

sub skip_this_group {
    my ($group) = @_;

    #print ">>>$group<<<\n";

    return 1 if $group =~ /Cryptographic/;
    return 1 if $group =~ /Advanced SIMD/;
    return 0;
}
    
sub output_encodings {
    open TUTILS,">derived/test_a64sim_utils.C";

    #print "MASKS:\n";
    #foreach my $key (keys %all_masks) {
    #printf "'%s' = 0x%08x\n",$key,$all_masks{$key};
    #}
	
    my $cnt = 0;
    my $branch_imm_encoding_index = -1;

    #foreach my $key (sort(keys %master_encodings)) {
    #    next if &skip_this_group($key);
    #    $branch_imm_encoding_index = $cnt if ($key =~ /Unconditional branch \(immediate\)/);
    #    $cnt += 1;
    #}

    foreach my $instr (sort(keys %all_encodings)) {
	next if &skip_this_group($instr);
        $branch_imm_encoding_index = $cnt if ($instr =~ /Unconditional branch \(immediate\)\/B \-/);
        $cnt += 1;
    }
    
    print "# of encodings: $cnt\n\n";
    print "Index of branch immediate encoding: $branch_imm_encoding_index\n";

    print TUTILS "#define INSTRUCTION_GROUPS_COUNT  $cnt\n";
    print TUTILS "#define BRANCH_ENCODING $branch_imm_encoding_index\n\n";

    print TUTILS "int get_next_encoding(int instr_index,unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {\n";
    print TUTILS "switch(instr_index) {\n";

    my $case_id = 0;

    foreach my $instr (sort(keys %all_encodings)) {
	next if &skip_this_group($instr);
        my $opcode = $all_encodings{$instr};  # BUT NOT 'Advanced SIMD'
	my $mask = $all_masks{$instr}; #(~$opcode) & 0xffffffff;
	#printf "%s = 0x%08x (mask: 0x%08x)\n",$instr,$opcode,$mask;
        printf TUTILS "  case %d: group = \"%s\"; mask = 0x%08x; encoding = (set_mask & ~0x%08x) | 0x%08x; break;\n",
                      $case_id,$instr,$mask,$mask,$opcode;
        $case_id += 1;
	
    }

    #foreach my $group (sort(keys %master_encodings)) {
    #    next if &skip_this_group($group);
    #    my @ta = split(/\//,$master_encodings{$group});
    #    my $encoding = $ta[0];
    #    my $mask = $ta[1];
    #    print TUTILS "  case ${case_id}: group = \"$group\"; mask = $mask; encoding = (set_mask & ~$mask) | $encoding; break;\n";
    #    $case_id += 1;
    #}

    
    print TUTILS "  }\n\n";
    print TUTILS "  return 0;\n";
    print TUTILS "}\n\n";

    print TUTILS 'int get_branch_encoding(unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {' . "\n";
    print TUTILS "  return get_next_encoding(BRANCH_ENCODING,set_mask,group,encoding,mask);\n";
    print TUTILS "}\n\n";

    print TUTILS 'void tweak_encoding(int /*instr_index*/,unsigned int & /*encoding*/) {' . "\n";
    print TUTILS "}\n";

    print TUTILS "\n";

    $cnt = 0;

    foreach my $key (sort(keys %master_encodings)) {
        next if not &vfp_encoding($key);
	$cnt += 1;
    }
    print "# of vfp encodings: $cnt\n\n";

    print TUTILS "#define VFP_INSTRUCTION_GROUPS_COUNT $cnt\n\n";

    print TUTILS "int get_next_vfp_encoding(int instr_index,unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {\n";
    print TUTILS "switch(instr_index) {\n";

    my $case_id = 0;
   
    foreach my $group (sort(keys %master_encodings)) {
        next if not &vfp_encoding($group);
        my @ta = split(/\//,$master_encodings{$group});
        my $encoding = $ta[0];
        my $mask = $ta[1];
        print TUTILS "  case ${case_id}: group = \"$group\"; mask = $mask; encoding = (set_mask & ~$mask) | $encoding; break;\n";
        $case_id += 1;
    }

    print TUTILS "  }\n\n";
    print TUTILS "  return 0;\n";
    print TUTILS "}\n\n";

    close TUTILS; 
}

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


sub process_encodings {
    my ($encodings,$encoding_text) = @_;

    foreach my $grp (keys %$encodings) {
	my $next_encoding = 0;
        my $next_mask = 0;

        my $sbit = 0;
        my $ebit = 0;

        foreach my $bit (keys %{$$encodings{$grp}}) {
	    if ($$encodings{$grp}{$bit} eq '!0') {
		if ($sbit == 0) {
		    $sbit = $bit;
                } else {
                    $ebit = $bit;
                }
	    } elsif ($$encodings{$grp}{$bit} eq '-') {
               #a dont care...
	    } else {
 	       my $bit_value = $$encodings{$grp}{$bit};
               $next_encoding |= $bit_value << $bit;
	    }
            $next_mask |= (1 << $bit) if ($$encodings{$grp}{$bit} ne '-');
            if ($sbit > 0) {
		for (my $i = 0; $i < 16; $i++) {
		    my $expanded_encoding = $next_encoding |= $i << $ebit;
                    my $expanded_grp = "$grp - $i";
                    $master_encodings{$grp} = "$next_encoding/$next_mask";
		}
	    } else {
               $master_encodings{$grp} = sprintf "0x%08x/0x%08x",$next_encoding,$next_mask;
	    }
        }
    }
}

sub record_encodings {
    my ($encodings,$encoding_text,$dump) = @_;

    $$encoding_text = $1;

    print "$$encoding_text\n" if $dump;

    $start_encoding = 1;

    while(<>) {
      if ($start_encoding and /^31/) {
  	  $in_encodings = 1;
	  next;
      }

      if ($in_encodings and not /^[\-01]/) {
          $start_encoding = 0;
          $in_encodings = 0;

          print "end of $$encoding_text\n" if $dump;
	  return;
      }

      # HANDLE != CASE!

      if ($in_encodings) {
          chomp;
	  if (/([\-\s\!\=01]+)/) {
	      my $bits_text = $1;
              my $group_text = $';
              print "    bits: '$bits_text' text: '$group_text'\n" if $dump;
              my @bits = split(/ /,$bits_text);
              my $bit_index = 31;
              my $do_skip = 0;
              foreach my $bit (@bits) {
                 if ($bit eq '!=') {
                   $do_skip = 4;
                 } elsif ($do_skip > 0) {
                   $$encodings{$group_text}{$bit_index} = '!0';
                   $do_skip = $do_skip - 1;
                 } else {
                   $$encodings{$group_text}{$bit_index} = $bit;
                 }
                 $bit_index = $bit_index - 1;
              }
	  }
      }
    }
}

