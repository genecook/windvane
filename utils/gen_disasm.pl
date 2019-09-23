#!/usr/bin/perl -w

#************************************************************************************************
# gen_disasm.pl
#************************************************************************************************

my $enums_file         = 'derived/a64_instr_enums.h';
my $info_file          = 'derived/v8asm_starter.txt';

my $disasm_file        = 'derived/disasm_include_code.C'; # case statements to include in disasm method
my $fetch_ops_file     = 'derived/fetch_ops_code.C';      # code to queue up fetch-ops requests for each instance
my $writeback_ops_file = 'derived/writeback_ops_code.C';  #     "      "     write-back ops  "         "

my %enums = ();


my @ordered_instance_names = ();

                             #        key               value
                             #------------------   ----------------------
my %instance_names    = ();  # instance-name         instruction name
my %instruction_names = ();  # instruction name      array of instance names
my %notes             = ();  # instance-name         notes text
my %qualifiers        = ();  #      "                qualifier text
my %sections          = ();  #      "                arm-arm section
my %pages             = ();  #      "                   "    page
my %dest_operands     = ();  #      "                array of operands
my %src_operands      = ();  #      "                array of operands
my %assemblys         = ();  #      "                assembly - string
my %printfs           = ();  #      "                printf - string

my %ops2enums = (  # src operand to enum conversion...

    '<Da>'    => 'DA',    # FP/DP reg referenced by Ra 
    '<Dm>'    => 'DM',    # FP/DP reg referenced by Rm
    '<Dn>'    => 'DN',    # FP/DP reg referenced by Rn
    '<Dt1>'   => 'DT',    # FP/DP reg referenced by Rt 
    '<Dt2>'   => 'DT2',   # FP/DP reg referenced by Rt2
    '<Dt>'    => 'DT',    # FP/DP reg referenced by Rt

    '<Sa>'    => 'SA',    # FP/SP reg referenced by Ra
    '<Sm>'    => 'SM',    # FP/SP reg referenced by Rm
    '<Sn>'    => 'SN',    # FP/SP reg referenced by Rn
    '<St1>'   => 'ST',    # FP/SP reg referenced by Rt
    '<St2>'   => 'ST2',   # FP/SP reg referenced by Rt2
    '<St>'    => 'ST',    # FP/SP reg referenced by Rt

    '<Hn>'    => 'HN',    # vector reg referenced by Rn 
    '<Ht>'    => 'HT',    # vector reg referenced by Rt

    '<Vb>'    => 'VN',    # vector reg referenced by Rn
    '<Vd>'    => 'VD',    # vector reg referenced by Rd 
    '<Vm>'    => 'VM',    # vector reg referenced by Rm
    '<Vn>'    => 'VN',    # vector reg referenced by Rn
    '<Vt>'    => 'VT',    # vector reg referenced by Rt
    '<Vt2>'   => 'VT2',   # vector reg referenced by Rt + 1
    '<Vt3>'   => 'VT3',   # vector reg referenced by Rt + 2
    '<Vt4>'   => 'VT4',   # vector reg referenced by Rt + 3

    '<Wa>'     => 'RA',    # GP reg referenced by Ra
    '<Wm>'     => 'RM',    # GP reg referenced by Rm
    '<Rm>'     => 'RM',    # GP reg referenced by Rm    example: LDRSB <Wt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}]
    '<Wn>'     => 'RN',    # GP reg referenced by Rn    NOTE: always fetch full 64 bits.
    '<Ws>'     => 'RS',    # GP reg referenced by Rs          individual instructions may sign extend or zero
    '<Wt1>'    => 'RT',    # GP reg referenced by Rt            extend low order 32 bits as required
    '<Wt2>'    => 'RT2',   # GP reg referenced by Rt2
    '<Wt>'     => 'RT',    # GP reg referenced by Rt
    '<Wn|WSP>' => 'RNSP',  # GP reg or SP referenced by Rn

    '<Xa>'    => 'RA',    # GP reg referenced by Ra
    '<Xm>'    => 'RM',    # GP reg referenced by Ra
    '<Xn>'    => 'RN',    # GP reg referenced by Ra
    '<Xn|SP>' => 'RNSP',  # GP reg or SP referenced by Rn
    '<Xt1>'   => 'RT1',   # GP reg referenced by Rt
    '<Xt2>'   => 'RT2',   # GP reg referenced by Rt2
    '<Xt>'    => 'RT'     # GP reg referenced by Rt
);

my %dops2enums = ( # destination operand to enum conversion...
    '<Dd>' => 'DD',    # FP/DP reg referenced by Rd 
    '<Sd>' => 'SD',    # FP/SP reg referenced by Rd
    '<Hd>' => 'HD',    # vector reg referenced by Rd
    '<Vd>' => 'VD',    # vector reg referenced by Rd
    '<Wd>' => 'XD',    # GP reg referenced by Rd
    '<Xd>' => 'XD',    # GP reg referenced by Rd

    '<Xd|SP>'  => 'XDSP',    # GP reg or SP referenced by Rd
    '<Wd|WSP>' => 'XDSP',    # GP reg or SP referenced by Rd

    '<Xt>' => 'XT',     # GP reg referenced by Rt

    '<St>'  => 'ST',    # VFP reg referenced by St
    '<Dt>'  => 'DT',    # VFP reg referenced by Dt

    '<Bt>'  => 'BT',    # VFP reg referenced by Bt
    '<Ht>'  => 'HT'     # VFP reg referenced by Ht
    );

my %load2enums = (
    '<Xt>'  => 'XT',    # GP reg referenced by Rt
    '<Wt>'  => 'RT',    # GP reg referenced by Rt
    '<Xt1>' => 'RT1',   # GP reg referenced by Rt
    '<Xt2>' => 'RT2',   # GP reg referenced by Rt2
    '<Wt1>' => 'RT',    # GP reg referenced by Rt            extend low order 32 bits as required
    '<Wt2>' => 'RT2',   # GP reg referenced by Rt2

    '<St1>' => 'ST',    # VFP reg referenced by St1
    '<St2>' => 'ST2',   # VFP reg referenced by St2
    '<Dt1>' => 'DT',    # VFP reg referenced by Dt1
    '<Dt2>' => 'DT2',   # VFP reg referenced by Dt2

    '<St>'  => 'ST',    # VFP reg referenced by St
    '<Dt>'  => 'DT',    # VFP reg referenced by Dt

    '<Bt>'  => 'BT',    # VFP reg referenced by Bt
    '<Ht>'  => 'HT'     # VFP reg referenced by Ht
);

my %store2enums = (
    '<Xt>'  => 'XT',    # GP reg referenced by Rt
    '<Wt>'  => 'XT',    # GP reg referenced by Rt
    '<Xt1>' => 'XT',    # GP reg referenced by Rt
    '<Xt2>' => 'XT2',   # GP reg referenced by Rt2
    '<Wt1>' => 'XT',    # GP reg referenced by Rt            extend low order 32 bits as required
    '<Wt2>' => 'XT2',    # GP reg referenced by Rt2

    '<St1>' => 'ST',    # VFP reg referenced by St1
    '<St2>' => 'ST2',   # VFP reg referenced by St2
    '<Dt1>' => 'DT',    # VFP reg referenced by Dt1
    '<Dt2>' => 'DT2',   # VFP reg referenced by Dt2

    '<St>'  => 'ST',    # VFP reg referenced by St
    '<Dt>'  => 'DT',    # VFP reg referenced by Dt

    '<Bt>'  => 'BT',    # VFP reg referenced by Bt
    '<Ht>'  => 'HT'     # VFP reg referenced by Ht
);

&get_enums($enums_file,\%enums);
&get_info($info_file);

#&dump_info_file();
&check_disasm();

&output_disasm($disasm_file,$fetch_ops_file,$writeback_ops_file);

sub output_disasm {
    my($disasm_file,$fetch_ops_file,$writeback_ops_file) = @_;

    print "generating disassembly,fetch-ops,write-back code from info file...";

    open(DISASM,">$disasm_file") or die;
    open(FETCHOPS,">$fetch_ops_file") or die;
    open(WBACK,">$writeback_ops_file") or die;

    my $end_previous_case = 0;

    my %instance_sets = (); #<---each entry is an array of indices into @ordered_instance_names 

    my @unique_instance_names = ();

    for (my $i = 0; $i <= $#ordered_instance_names; $i++) {
        my $instance_name = $ordered_instance_names[$i];
	if (not defined($instance_sets{$instance_name})) {
	    $instance_sets{$instance_name} = [];
            push(@unique_instance_names,$instance_name);
	}
        push(@{$instance_sets{$instance_name}},$i);
    }

    my %all_ops = (); #<---use when generating src or dest enums...

    foreach my $instance_name (@unique_instance_names) {
	my @inst_indices = @{$instance_sets{$instance_name}};
        print DISASM "   case ${instance_name}:\n";
        print FETCHOPS "   case ${instance_name}:\n";
        print WBACK "   case ${instance_name}:\n";
        if ($#inst_indices == 0) {
           my $sole_index = $inst_indices[0]; 
	   print DISASM "      " . $printfs{$sole_index} . "\n";

           my @src_ops = @{$src_operands{$sole_index}};
           my @dest_ops = @{$dest_operands{$sole_index}};

           if ($instance_name eq 'STLR_32') {
	       print "src:" . join(',',@src_ops) . "\n";
	       print "dest: " . join(',',@dest_ops) . "\n";
	   }

           my $is_load = ($instance_name =~ /^LD/);

           my $is_simd_load    = ($instance_name =~ /^SIMD_LD[NPR]/); # NOTE: NOT CURRENTLY HANDLING SIMD 'STRUCTURE' LOADS
           my $quadword_access = ($instance_name =~ /128/);

           foreach my $sop (@src_ops) {
               if (($is_load || $is_simd_load) && defined($load2enums{$sop})) {
                 push(@dest_ops,$sop);
               } else {
	         print FETCHOPS "      packet->mOpsFetch.push_back(" . $ops2enums{$sop} . ");\n" if defined($ops2enums{$sop});
                 #$all_ops{$sop} = $ops2enums{$sop} if defined($ops2enums{$sop});
               }
	   }

           #my @dest_ops = @{$dest_operands{$sole_index}};
           foreach my $dop (@dest_ops) {
               if (($is_load || $is_simd_load) and defined($load2enums{$dop})) {
	         print WBACK "      packet->mOpsWriteback.push_back(" . $store2enums{$dop} . ");\n";
	       } else {
	         print WBACK "      packet->mOpsWriteback.push_back(" . $dops2enums{$dop} . ");\n" if defined($dops2enums{$dop});
	       }
               #$all_ops{$dop} = $dops2enums{$dop} if defined($dops2enums{$dop});
	   }

           if ( $is_simd_load and $quadword_access ) {
               my $is_pair = ($instance_name =~ /^SIMD_LDP/) or ($instance_name =~ /^SIMD_LDNP/);
	       print WBACK "      packet->mOpsWriteback.push_back( QT );\n";
	       print WBACK "      packet->mOpsWriteback.push_back( QT2 );\n" if $is_pair;
           } 
        } else {
           foreach my $index (@inst_indices) {
               my $qualifier = $qualifiers{$index};
	       print DISASM "      if (" . &format_qualifier($qualifier) . ") ". $printfs{$index} . "\n";

               my @src_ops_src = @{$src_operands{$index}};
               my @src_ops = ();
               foreach my $sop (@src_ops_src) {
                  push(@src_ops,$ops2enums{$sop}) if defined($ops2enums{$sop});
	       }
               if ($#src_ops >= 0) {
	          print FETCHOPS "      if (" . &format_qualifier($qualifier) . ") {\n";
                  foreach my $sop (@src_ops) {
	              print FETCHOPS "      packet->mOpsFetch.push_back($sop);\n";
                      #$all_ops{$sop} = $sop;
	          }
                  print FETCHOPS "      }\n";
               }

               my @dest_ops_src = @{$dest_operands{$index}};
               my @dest_ops = ();
               foreach my $dop (@dest_ops_src) {
                  push(@dest_ops,$dops2enums{$dop}) if defined($dops2enums{$dop});
	       }
               if ($#dest_ops >= 0) {
	          print WBACK "      if (" . &format_qualifier($qualifier) . ") {\n";
                  foreach my $dop (@dest_ops) {
	              print WBACK "      packet->mOpsWriteback.push_back($dop);\n";
                      #$all_ops{$dop} = $dop;
	          }
                  print WBACK "      }\n";
               }

	   }
	}
        print DISASM   "      break;\n";
        print FETCHOPS "      break;\n";
        print WBACK    "      break;\n";
    }

    close DISASM;
    close FETCHOPS;
    close WBACK;

    print "done.\n";
    print "    disassembly file:    $disasm_file\n";
    print "    fetch-ops file:      $fetch_ops_file\n";
    print "    write-back-ops file: $writeback_ops_file\n";
 
    foreach my $sop (sort(keys %all_ops)) {
	print $all_ops{$sop} . ",";
    }
    print "\n";
}

sub output_fetch_ops {
    my($fetch_ops_file) = @_;

}

sub output_writeback_ops {
    my($writeback_ops_file) = @_;

}

sub format_qualifier {
    my ($qualifier) = @_;

    $qualifier =~ s/Q/packet\-\>Q/;
    $qualifier =~ s/Rm/packet\-\>Rm\.Value\(\)/;

    return $qualifier;
}

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------

sub get_info {
    my ($info_file) = @_;

    print "reading info file '$info_file'...";

    open(IF,$info_file) or die;

    my $instance_name          = '';
    my $instance_num           = 0;
    my $instruction            = '';
    my $notes                  = '';
    my $qualifier              = '';
    my $section                = '';
    my $page                   = '';
    my @info_dest_operands     = ();   # all src/dest operands
    my @info_src_operands      = ();   #   recorded in info file
    my @instance_dest_operands = ();   # instance-specific
    my @instance_src_operands  = ();   #   src/dest operands
    my $assembly               = '';
    my $printf                 = '';

    while(<IF>) {
        next if /^\s*$/;

        if (/^\'([^\']+)\'\s+\(ALIAS IGNORED\)$/) {
            my $alias = $1;
            next;
        }

	if (/^instance\-name\:\s+(\w+)$/) {
            $instance_name = $1;

            $instance_num           = 0;
            $instruction            = '';
            $notes                  = '';
            $qualifier              = '';
            $section                = '';
            $page                   = '';
            @info_dest_operands     = ();
            @info_src_operands      = ();
            @instance_dest_operands = ();
            @instance_src_operands  = ();
            $assembly               = '';
            $printf                 = '';
            next;
	}
        if (/^instance\-num\:\s+([1234])$/) {
            $instance_num = $1;
            next;
	}
        if (/^alias of\: (\w+)$/) {
            my $alias = $1;
            next;
	}
        if (/^notes\:\s+/) {
            $notes = $';  # '
	    chomp $notes;
            next;
        }
        if (/^qualifier\:\s+/) {
            $qualifier = $';  # '
	    chomp $qualifier;
            next;
	}
        if (/^instruction\:\s+/) {
            $instruction = $';  # '
	    chomp $instruction;
            next;
	}
        if (/^section\:\s+/) {
            $section = $';   # '
            chomp $section;
            next;
        }
        if (/^page\:\s+/) {
            $page = $';   # '
	    chomp $page;
            next;
	}
        if (/^destination operands\:\s+/) {
            my $tbuf = $';   # '
	    chomp $tbuf;
            @info_dest_operands = split(/,/,$tbuf);
            next;
        }
        if (/^source operands\:\s+/) {
            my $tbuf = $';   # '
	    chomp $tbuf;
            @info_src_operands = split(/,/,$tbuf);
            next;
        }
        if (/^assembly\:\s+/) {
            $assembly = $';  # '
	    chomp $assembly;

            # okay, we have the assembly should have all operand info. derive instance operands...

            @instance_dest_operands = ();
            @instance_src_operands  = ();

            my @asm_operands = &extract_operands($assembly);
            foreach my $iop (@asm_operands) {
		foreach my $dop (@info_dest_operands) {
		    push(@instance_dest_operands,$iop) if $iop eq $dop;
		}
		foreach my $sop (@info_src_operands) {
		    push(@instance_src_operands,$iop) if $iop eq $sop;
		}
	    }
            next;
	}
        if (/^printf\:\s+/) {
            $printf = $'; # '
	    chomp $printf;

            # okay, we should have all instance info. record same...

            &record_instance_info($instance_name,$instance_num,$instruction,$notes,$qualifier,
                                   $section,$page,\@instance_dest_operands,
                                   \@instance_src_operands,$assembly,$printf);
            next;
	}

        die("ERROR: unexpected info file entry: $_");
    }

    close IF;

    print "done.\n";
}

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------

sub get_enums {
    my ($enums_file,$enums) = @_;

    print "reading enums file '$enums_file'...";

    open(EF,$enums_file) or die;

    while(<EF>) {
	if (/^\s+(\w+)\=(\d+)\,$/) {
            my $enum = $1;
            my $eval = $2;
            $$enums{$enum} = $eval;
        }
    }

    close EF;

    print "done.\n";
}

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------

sub extract_operands {
    my($assembly) = @_;

    $assembly =~ s/\<R\>\<m\>/\<Rm\>\,/;

    my @ta = split(/\,/,$assembly);

    my @ops = ();

    foreach my $p (@ta) {
	if ($p =~ /(\<[^\>]+\>)/) {
            my $operand = $1;
            push(@ops,$operand);
        }
    }

    return @ops;
}

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------

sub record_instance_info {
    my ($instance_name,$instance_num,$instruction,$notes,$qualifier,
        $section,$page,$instance_dest_operands,
        $instance_src_operands,$assembly,$printf) = @_;

    push(@ordered_instance_names,$instance_name);

    my $inst_id = $#ordered_instance_names;

    $instance_names{$inst_id} = $instruction;

    if (not defined($instruction_names{$instruction})) {
        $instruction_names{$instruction} = [];
    }
    push(@{$instruction_names{$instruction}},$instance_name);

    $sections{$inst_id} = $section;
    $pages{$inst_id} = $page;
    $notes{$inst_id} = $notes;
    $qualifiers{$inst_id} = $qualifier;
    @{$dest_operands{$inst_id}} = @$instance_dest_operands;
    @{$src_operands{$inst_id}}  = @$instance_src_operands;

    $assemblys{$inst_id} = $assembly;
    $printfs{$inst_id} = $printf;
}

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------

sub dump_instance_info {
    my ($instance) = @_;

    print "instance-name: $instance\n";
    print "notes: " . $notes{$instance} . "\n";
    print "qualifier: " . $qualifiers{$instance} . "\n";
    print "instruction: " . $instance_names{$instance} . "\n";
    print "section: " . $sections{$instance} . "\n";
    print "page: " . $pages{$instance} . "\n";
    print "destination operands: " . join(',',@{$dest_operands{$instance}}) . "\n";
    print "source operands: " . join(',',@{$src_operands{$instance}}) . "\n";
    print "assembly: " . $assemblys{$instance} . "\n";
    print "printf: " . $printfs{$instance} . "\n";
}

sub dump_info_file {
    foreach my $inst (@ordered_instance_names) {
	&dump_instance_info($inst);
        print "\n";
    }
}

#-------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------------

sub check_disasm {
    print "checking instance-names from info file against enums...";

    my $inst_count = 0;
    my $dup_instance_count = 0;

    my %instance_counts = ();

    for(my $i = 0; $i <= $#ordered_instance_names; $i++) {
       $inst_count += 1;
       my $instance_name = $ordered_instance_names[$i];
       #print "ordered_instance_names[$i] = '$instance_name'\n";
       if (defined($enums{$instance_name})) {
           # cool. instance name from info file matches enum...
           if (defined($instance_counts{$instance_name})) {
               # duplicate instance-name...
               $dup_instance_count += 1;
               if (defined($qualifiers{$i}) and $qualifiers{$i} ne '') {
                   # duplicate instance-name but there is a qualifier...
               } else {
                   print "OOPS! duplicate instance-name '$instance_name' without qualifier???\n";
	       }
	       $instance_counts{$instance_name} += 1;
	   } else {
	       $instance_counts{$instance_name} = 1;
           }
       } else {
           print "OOPS! instance '$instance_name' not found in enums???\n";
       }       
    }

    print "done.\n";

    print "There are $inst_count instances. There are $dup_instance_count duplicate instance-names.\n";
}
