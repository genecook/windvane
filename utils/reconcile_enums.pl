#!/usr/bin/perl -w

# read in decode enums file. derive disasm enums from disasm info file...
# -----------------------------------------------------------------------
my $decode_enums_file = 'a64_instr_enums.h';
my $disasm_info_file  = 'v8asm_starter.txt';

my %decode_enums = ();       # key is enum as read from file. value is base instruction name
my %simd_decode_enums = ();  # key is enum (prefixed by SIMD_). value is base instruction name

my $ecnt = &process_enums_file($decode_enums_file,\%decode_enums,\%simd_decode_enums);

die if $ecnt != 0;


my %disasm_enums = ();
my %simd_disasm_enums = ();

$ecnt = &process_info_file($disasm_info_file,\%disasm_enums,\%simd_disasm_enums);

die if $ecnt != 0;

# now invert enums to allow searches by base instruction name...
# --------------------------------------------------------------
my %decode_bnames = ();  #<---key is decode base instruction
my %simd_decode_bnames = (); #<---ditto, except is SIMD

&invert_enums(\%decode_bnames,\%decode_enums);
&invert_enums(\%simd_decode_bnames,\%simd_decode_enums);

my %disasm_bnames = ();  #<---key is disasm base instruction
my %simd_disasm_bnames = (); #<---ditto, except is SIMD

&invert_enums(\%disasm_bnames,\%disasm_enums);
&invert_enums(\%simd_disasm_bnames,\%simd_disasm_enums);


# now cross-reference base instruction names...
# ---------------------------------------------

&cross_ref_names("base instruction names that appear in disassembly but not in decode",
                 \%disasm_bnames,\%decode_bnames,\%simd_decode_bnames);

&cross_ref_names("SIMD base instruction names that appear in disassembly but not in decode",
                 \%simd_disasm_bnames,\%simd_decode_bnames,\%decode_bnames);

&cross_ref_names("base instruction names that appear in decode but not in disassembly",
                 \%decode_bnames,\%disasm_bnames,\%simd_disasm_bnames);

&cross_ref_names("SIMD base instruction names that appear in decode but not in disassembly",
                 \%simd_decode_bnames,\%simd_disasm_bnames,\%disasm_bnames);


# now for each base instruction name, enumerate each disasm 'enum' that does not appear
# in the decode enums...

# 1st by base instruction name...

my %fixups = ();

&cross_ref_all_names("instruction names that appear in disassembly but not in decode",
                     \%fixups,\%disasm_bnames,\%decode_bnames,\%simd_decode_bnames);

# then by simd instruction name...

&cross_ref_all_names("simd instruction names that appear in disassembly but not in decode",
                     \%fixups,\%simd_disasm_bnames,\%simd_decode_bnames,\%decode_bnames);

open(FUF,">enum_fixups.pl") or die;
foreach my $nm (sort(keys %fixups)) {
    print FUF "   '$nm' => '" . $fixups{$nm} . "',\n";
}
close FUF;

# could do a best fit for names that don't match - break up names, sort, then best fit by # of matches...

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub cross_ref_names {
    my($text,$names_to_check,$ref_names,$simd_ref_names) = @_;

    print "\n${text}...";

    my $bcnt = 0;

    foreach my $iname (sort(keys %$names_to_check)) {
        next if defined($$ref_names{$iname});      # except it here
        next if defined($$simd_ref_names{$iname}); #   but could be in SIMD list
        print "\n     $iname (". join(',',@{$$names_to_check{$iname}}) . ")";
        $bcnt += 1;
    } 

    print "none.\n" if $bcnt == 0;
}

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub match_count {
    my ($name_to_check,$ref_name) = @_;

    my $match_count = 0;

    my @check_parts = sort(split('_',$name_to_check));
    my @ref_parts   = sort(split('_',$ref_name));      

    foreach my $cp (@check_parts) {
	foreach my $rp (@ref_parts) {
	    if ($cp eq $rp) {
                $match_count += 1;
                last;
            }
	}
    }

    return $match_count;
}

sub best_match {
    my ($name_in,$scalar_vs_vector,@ref_names) = @_;

    my $name = $name_in;
    if ($scalar_vs_vector) {
        $name =~ s/SCALAR_VEC/VEC/;
    }

    my $best_count = 0;
    my $best_fit = '';

    foreach my $rn (@ref_names) {
	my $next_count = &match_count($name,$rn);
        if ($next_count > $best_count) {
            $best_count = $next_count;
            $best_fit = $rn;
        }
    }

    return $best_fit;
}

sub cross_ref_all_names {
    my($text,$fixups,$names_to_check,$ref_names,$simd_ref_names) = @_;

    print "\n${text}...";

    my $bcnt = 0;

    foreach my $iname (sort(keys %$names_to_check)) {
        my @ref_names = ();
        if (defined($$ref_names{$iname})) {
	    @ref_names = @{$$ref_names{$iname}};
        }
        if (defined($$simd_ref_names{$iname})) {
            @ref_names = ( @ref_names, @{$$simd_ref_names{$iname}} );
	}
        my @names_to_check = @{$$names_to_check{$iname}};
        my @missing_names = ();
        foreach my $nm (@names_to_check) {
	    my $have_it = 0;
            foreach my $rn (@ref_names) {
		$have_it = 1 if $nm eq $rn;
	    }
            push(@missing_names,$nm) if not $have_it;
        }
        #my $two_vs_two = (($#ref_names==1) and ($#names_to_check==1) and ($#missing_names==1)) ? 1 : 0; #<---to help weed out 'easy' cases???

        if ($#missing_names >= 0) {
            print "\n     for $iname:\n";
            print "          check-names:   " . join(',',@names_to_check) . "\n";
            print "          ref-names:     " . join(',',@ref_names) . "\n";
            print "\n        missing names: ". join(',',@missing_names) . "\n";

            my $scalar_vs_vector = (($#missing_names == 1) and ($missing_names[0] =~ /_SCALAR$/) and ($missing_names[1] =~ /SCALAR_VEC/));
    
            foreach my $mn (@missing_names) {
                my $best_match = &best_match($mn,$scalar_vs_vector,@ref_names);
                my $only_match = (($#ref_names == 0) and ($#names_to_check == 0)) ? '# only one match' : '#  ?multiple choices?';
		print "    '$mn' => '$best_match', $only_match\n";
                $$fixups{$mn} = $best_match;
	    }
	} else {
            #print "\n     $iname checks out!\n";
	}
        $bcnt += 1;
    } 

    print "none.\n" if $bcnt == 0;
}

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub invert_enums {
    my($inverted_enums,$enums) = @_;

    foreach my $enum (keys %$enums) {
        my $base_name = $$enums{$enum};
        #print "<$ni>\n";
        if (not defined($$inverted_enums{$base_name})) {
            $$inverted_enums{$base_name} = ();
	}
        push(@{$$inverted_enums{$base_name}},$enum);
    }
}

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub dump_enums {
    my($enums,$title) = @_;

    print "$title\n";

    foreach my $ni (sort(keys %$enums)) {
        print "     $ni: " . $$enums{$ni} . "\n";
    }
}

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub dump_inverted_enums {
    my($enums,$title) = @_;

    print "$title\n";

    foreach my $ni (sort(keys %$enums)) {
        print "     $ni: " . join(",",@{$$enums{$ni}}) . "\n";
    }
}

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub process_enums_file {
    my ($enums_file,$decode_enums,$simd_decode_enums) = @_;

    print "reading enums file '$enums_file'...";

    my $err_cnt = 0;

    open(DEF,$enums_file) or die;

    while(<DEF>) {
        my $enum = '';
        if (/\s+(\w+)\=\d+/ or /instance\-name\: (\w+)/) {
            $enum = $1;
        } else {
            next;
	}
        next if $enum eq 'A64_UNALLOCATED';
        my $base_instr = '?';
        if ($enum =~ /\_/) {
            # see if base instruction name can be derived...
            my @ta = split(/\_/,$enum);
            $base_instr = ($ta[0] eq 'SIMD') ? $ta[1] : $ta[0];
	} else {
            $base_instr = $enum;
	}
        if ($enum =~ /SIMD_/) {
            if (defined($$simd_decode_enums{$enum})) {
                print "OOPS! duplicate enum: '$enum'\n";
                $err_cnt += 1;
            } else {
                $$simd_decode_enums{$enum} = $base_instr;
            }
	} else {
            if (defined($$decode_enums{$enum})) {
                print "OOPS! duplicate enum: '$enum'\n";
                $err_cnt += 1;
            } else {
                $$decode_enums{$enum} = $base_instr;
            }
        }
    }

    close DEF;

    print "done.\n";

    return $err_cnt;
}

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

sub process_info_file {
    my ($enums_file,$decode_enums,$simd_decode_enums) = @_;

    print "reading info file '$enums_file'...\n";

    my $err_cnt = 0;

    open(DEF,$enums_file) or die;

    my $instance_name = '';
    my $instance_num  = -1;
    my $instr_name    = '';
    my $base_instr    = ''; 
    my $asm           = '';
    
    while(<DEF>) {
        if (/instance\-name\:\s+(\w+)/) {
            $instance_name = $1;
            $instance_num = -1;
            $instr_name = '';            
            $asm = '';
            next;
	}

        if (/instance\-num\:\s+(\d+)/) {
            $instance_num = $1;
            $base_instr = $instr_name if $instance_num == 1;
            next;
	}

        if (/instruction\:\s+(\w+)/) {
            $instr_name = $1;            
            next;
        }

        if (/assembly\: /) {
            $asm = $';
        }

        next if $asm eq '';

        # if we got here then have instance-name, instance-num, and base instr name...

        if (not ($instance_name =~ /$instr_name/)) {
            if ($instr_name =~ /2$/) {
                my $base_instr = $`;
                if (not ($instance_name =~ /$base_instr/)) {
                    print "OOPS! enum '$instance_name' does not contain instruction name '$instr_name'\n";
                }
            } else {
                print "OOPS! enum '$instance_name' does not contain instruction name '$instr_name'\n";
            }
	}

        if (not ($asm =~ /$instr_name/)) {
            print "OOPS! asm for instance '$instance_name' does not contain instruction name '$instr_name'\n";
        }

        my $is_duplicate = $instance_num > 1 ? 1 : 0; #multiple instances of same instruction trated as 'duplicates'

        if ($is_duplicate and $base_instr ne '' and $instr_name ne $base_instr) {
            print "OOPS! instance '$instance_name/$instance_name' with mismatched instruction name '$instr_name' vs '$base_instr'\n";
	} elsif ($instance_name =~ /SIMD_/) {
            if (defined($$simd_decode_enums{$instance_name}) and not $is_duplicate) {
                print "OOPS! duplicate instance name: '$instance_name'\n";
                $err_cnt += 1;
            } else {
                $$simd_decode_enums{$instance_name} = $instr_name;
            }
	} else {
            if (defined($$decode_enums{$instance_name}) and not $is_duplicate) {
                print "OOPS! duplicate instance name: '$instance_name'\n";
                $err_cnt += 1;
            } else {
                $$decode_enums{$instance_name} = $instr_name;
            }
        }

        # completed processing this instance...

        $instance_name = $1;
        $instance_num = -1;
        $instr_name = '';            
        $asm = '';
    }

    close DEF;

    print "done.\n";

    return $err_cnt;
}

