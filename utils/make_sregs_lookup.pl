#!/usr/bin/perl

my $sregs_decode_file = 'derived/v8_sregs_decode.C';
my $sregs_map_file    = 'derived/v8_sregs_map_entries.C';
 
print "V8 system registers decode file:      '$sregs_decode_file'\n";
print "V8 system registers map entries file: '$sregs_map_file'\n";

my $op0 = 0;
my $op1 = 0;
my $crn = 0;
my $crm = 0;
my $op2 = 0;

my $order = 0;

my %sys_regs = ();
my %sys_regs_info = ();

my @all_regs = ();

my %sreg_ids = ();

while(<>) {
    next if /^\s*\#/;

    if (/^op0 \= 0b10/) {
	$op0 = 2;
        next;
    }
    if (/^op0 \= 0b11/) {
	$op0 = 3;
        next;
    }
    if (/Op1 CRn CRm Op2/) {
        $op1 = 0;
        $crn = 0;
        $crm = 0;
        $op2 = 0;
        $order = 1;   # expecting /Op1 CRn CRm Op2/ with op0 implied... 
        next;
    }

    if (/CRn Op1 CRm Op2/) {
        $op1 = 0;
        $crn = 0;
        $crm = 0;
        $op2 = 0;
        $order = 2;   # expecting /CRn Op1 CRm Op2/ with op0 implied... 
        next;
    }

    if (/CRn \=\= 4/) {
        $op1 = 0;
        $crn = 4;
        $crm = 0;
        $op2 = 0;
        $order = 3;   # expecting /Op1 CRm Op2/ with op0 implied... 
        next;
    }

    if (/CRn \=\= 11/) {
        $op1 = 0;
        $crn = 11;
        $crm = 0;
        $op2 = 0;
        $order = 3;   # expecting /Op1 CRm Op2/ with op0 implied... 
        next;
    }

    if (/^PMEVCNTR/) {
        #print;
        &do_pmevcntr();
        next;
    }

    if (/^PMEVTYPER/) {
        #print;
        &do_pmevtyper();
        next;
    }

    if (/^(\w+(\[\d+\]))/ or /^(\w+(\[63\:0\])*)/) {
        #print;
        my $sname = $1;
        my $tbuf = $';
        if ($tbuf =~ /\=/) {
            $tbuf = $`;
        }
        my @ta = ( $tbuf =~ /\s+(\d+)/g );
        #print "$sname>>> " . join(",",@ta) . "\n";
	&stuff_sreg($sname,@ta);
        next;
    }

}

&print_sreg_decodes($sregs_decode_file);
&print_sreg_map_entries($sregs_map_file);


sub print_sreg_decodes {
    my ($sregs_decode_file) = @_;

    open(SREGSFILE,">$sregs_decode_file") or die;

    foreach my $sreg (@all_regs) {
      #print "$sreg   " . $sys_regs{$sreg} . "  " . $sys_regs_info{$sreg} . "\n";

      if ($sreg eq 'DBGDTRRX_EL0') {
         print SREGSFILE "  case $sys_regs{$sreg}: $sys_regs_info{$sreg}\n";
         print SREGSFILE "     if (is_read) rname = \"DBGDTRRX_EL0\";\n";
         print SREGSFILE "     else rname = \"DBGDTRTX_EL0\";\n";
         print SREGSFILE"     break;\n";
      } elsif ($sreg eq 'DBGDTRRX_EL0' or $sreg eq 'DBGDTRTX_EL0') {
         # already handled...
      } else {
         print SREGSFILE "  case $sys_regs{$sreg}: rname = \"$sreg\"; break;  $sys_regs_info{$sreg}\n";
      }
    }

    close SREGSFILE;
}

sub print_sreg_map_entries {
    my ($sregs_map_file) = @_;

    open(SREGSFILE,">$sregs_map_file") or die;

    foreach my $sreg (@all_regs) {
      print SREGSFILE "  sreg_names[\"$sreg\"] = $sys_regs{$sreg}; $sys_regs_info{$sreg}\n";
    }

    close SREGSFILE;
}


sub stuff_sreg {
    my ($sname_in,@ops) = @_;

    my $sname = $sname_in;

    if ($sname_in =~ /(\w+(\[\d+\]))/) {
        # allow brackets for GP or V regs...
    }
    elsif ($sname_in =~ /\[/) {
        $sname = $`;
    }
    
    if ($order == 1) {
        ($op1,$crn,$crm,$op2) = @ops if $#ops == 3;
        (     $crn,$crm,$op2) = @ops if $#ops == 2;
        (          $crm,$op2) = @ops if $#ops == 1;
        (               $op2) = @ops if $#ops == 0;
    } 
    elsif ($order == 2) {
        ($crn,$op1,$crm,$op2) = @ops if $#ops == 3;
        (     $op1,$crm,$op2) = @ops if $#ops == 2;
        (          $crm,$op2) = @ops if $#ops == 1;
        (               $op2) = @ops if $#ops == 0;
    } 
    elsif ($order == 3) {
        (     $op1,$crm,$op2) = @ops if $#ops == 2;
        (          $crm,$op2) = @ops if $#ops == 1;
        (               $op2) = @ops if $#ops == 0;
    }

    my $sreg_index = sprintf("0x%x%x%x%x%x",$op0,$op1,$crn,$crm,$op2);
    $sys_regs{$sname} = $sreg_index;
    my $sreg_decode = sprintf("// op0=%d, op1=%d, CRn=%d, CRm=%d, op2=%d",$op0,$op1,$crn,$crm,$op2);
    $sys_regs_info{$sname} = $sreg_decode;
    push(@all_regs,$sname);
    &check_id($sreg_index,$sname);
    #print "$sreg  $sreg_index\n";
}

sub check_id {
    my ($id,$sreg) = @_;

    if ($sreg eq 'DBGDTRRX_EL0' or $sreg eq 'DBGDTRTX_EL0') {
        # these two are the same register, and named based on access type (read vs write)...
    } elsif (defined($sreg_ids{$id})) {
        print "!!!!OOPS! $sreg ID WAS USED FOR '" . $sreg_ids{$id} . " ???\n";
    } else {
        $sreg_ids{$id} = $sreg;
    }
}

sub do_pmevcntr {
    $op1 = 14;
    $crn = 3;
    for ($crm = 8; $crm <= 10; $crm++) {
        for ($op2 = 0; $op2 <= 7; $op2++) {
	    my $pmid = ($crm<<3|$op2) & 0x3f;
            my $sname = "PMEVCNTR${pmid}_EL0";
            my $sreg_index = sprintf("0x%x%x%x%x%x",$op0,$op1,$crn,$crm,$op2);
            $sys_regs{$sname} = $sreg_index;
            my $sreg_decode = sprintf("// op0=%d, op1=%d, CRn=%d, CRm=%d, op2=%d",$op0,$op1,$crn,$crm,$op2);
            $sys_regs_info{$sname} = $sreg_decode;
            push(@all_regs,$sname);
            &check_id($sreg_index,$sname);
            #print "$sname  $sreg_index\n";
        }
    }
    $crm = 11;
    for ($op2 = 0; $op2 <= 6; $op2++) {
	 my $pmid = ($crm<<3|$op2) & 0x3f;
         my $sname = "PMEVCNTR${pmid}_EL0";
         my $sreg_index = sprintf("0x%x%x%x%x%x",$op0,$op1,$crn,$crm,$op2);
         $sys_regs{$sname} = $sreg_index;
         my $sreg_decode = sprintf("// op0=%d, op1=%d, CRn=%d, CRm=%d, op2=%d",$op0,$op1,$crn,$crm,$op2);
         $sys_regs_info{$sname} = $sreg_decode;
         push(@all_regs,$sname);
         &check_id($sreg_index,$sname);
         #print "$sname  $sreg_index\n";
    }
}

sub do_pmevtyper {
    for ($crm = 12; $crm <= 14; $crm++) {
        for ($op2 = 0; $op2 <= 7; $op2++) {
	    my $pmid = ($crm<<3|$op2) & 0x1f;
            my $sname = "PMEVTYPER${pmid}_EL0";
            my $sreg_index = sprintf("0x%x%x%x%x%x",$op0,$op1,$crn,$crm,$op2);
            $sys_regs{$sname} = $sreg_index;
            my $sreg_decode = sprintf("// op0=%d, op1=%d, CRn=%d, CRm=%d, op2=%d",$op0,$op1,$crn,$crm,$op2);
            $sys_regs_info{$sname} = $sreg_decode;
            push(@all_regs,$sname);
            &check_id($sreg_index,$sname);
            #print "$sname  $sreg_index\n";
        }
    }
    $crm = 15;
    for ($op2 = 0; $op2 <= 6; $op2++) {
	 my $pmid = ($crm<<3|$op2) & 0x1f;
         my $sname = "PMEVTYPER${pmid}_EL0";
         my $sreg_index = sprintf("0x%x%x%x%x%x",$op0,$op1,$crn,$crm,$op2);
         $sys_regs{$sname} = $sreg_index;
         my $sreg_decode = sprintf("// op0=%d, op1=%d, CRn=%d, CRm=%d, op2=%d",$op0,$op1,$crn,$crm,$op2);
         $sys_regs_info{$sname} = $sreg_decode;
         push(@all_regs,$sname);
         &check_id($sreg_index,$sname);
         #print "$sname  $sreg_index\n";
    }
}
