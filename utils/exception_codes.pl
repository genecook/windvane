#!/usr/bin/perl

my $ec        = 0;
my $a32       = 0;
my $a64       = 1;
my $el1_valid = 0;
my $el2_valid = 0;
my $el3_valid = 0;

my $ec_txt       = '';
my $iss_enc_txt  = '';
my $iss_enc_page = '';

my $in_ec = 0;
my $next_ec = 0;

while(<>) {
    $in_ec = 1 if /D7\.2\.27   ESR_ELx\, Exception Syndrome Register/;

    $in_ec = 0 if /IL\, bit \[25\]/;

    next if not $in_ec;

    
    if (/EC \=\= ([01]+)/) {
        if ($ec_txt ne '') {
            $ec_txt .= $` if $` ne '';
            if (/from AArch32/ or /in AArch32/) {
               $a32 = 1;
               $a64 = 0;
            } elsif (/from either AArch32/ or /AArch32 or AArch64/) {
               $a32 = 1;
	    }
	    print "\nEC: $ec\n";
            print "AArch32: $a32\n";
            print "AArch64: $a64\n";
            print "EL1: $el1_valid\n";
            print "EL2: $el2_valid\n";
            print "EL3: $el3_valid\n";
            if ($ec_txt =~ /See ISS/) {
               $ec_txt = $`;
               $iss_enc_txt = 'See ISS' . $';
	    }
            if ($iss_enc_txt =~ / on page (D7\-\d+)/) {
              $iss_enc_page = $1;
              $iss_enc_txt =~ s/( on page D7\-\d+)//;
            }
            $iss_enc_txt =~ s/ARM DDI 0487A\.b Copyright \© 2013 ARM Limited\.//s;
            $iss_enc_txt =~ s/All rights reserved\. //;
            $iss_enc_txt =~ s/D7\-1833ID122413 Non\-Confidential \- BetaD7 AArch64//;
            $iss_enc_txt =~ s/System Register Descriptions D7\.2 General system control registers//;
            $iss_enc_txt =~ s/EC31 26IL25ISS24 0D7\-1832 Copyright \© 2013 ARM Limited\.//;
            $iss_enc_txt =~ s/ARM DDI 0487A\.bNon\-Confidential \- Beta ID122413D7 AArch64//;
            print "description: $ec_txt\n";
            print "encoding: $iss_enc_txt\n"; 
            print "page: $iss_enc_page\n";
	}

	$ec = $1;
        $ec_txt = '';
        $iss_enc_txt = '';
        $el1_valid = 0;
        $el2_valid = 0;
        $el3_valid = 0;
        $a32 = 0;
        $a64 = 1;
        $next_ec = 1;
        next;
    }

    if ($next_ec and /\(This value is valid for/) {
        $el1_valid = 1 if /ESR_EL1/ or /all described registers/;
        $el2_valid = 1 if /ESR_EL2/ or /all described registers/;
        $el3_valid = 1 if /ESR_EL3/ or /all described registers/;
        next;
    }

    if ($next_ec) {
	chomp;
        $ec_txt .= $_;
        if (/from AArch32/ or /in AArch32/) {
           $a32 = 1;
           $a64 = 0;
        } elsif (/from either AArch32/ or /AArch32 or AArch64/) {
           $a32 = 1;
	}
    }
}

if ($ec_txt ne '') {
    print "\nEC: $ec\n";
    print "AArch32: $a32\n";
    print "AArch64: $a64\n";
    print "EL1: $el1_valid\n";
    print "EL2: $el2_valid\n";
    print "EL3: $el3_valid\n";
    if ($ec_txt =~ /See ISS/) {
       $ec_txt = $`;
       $iss_enc_txt = 'See ISS' . $';
    }
            if ($iss_enc_txt =~ / on page (D7\-\d+)/) {
              $iss_enc_page = $1;
              $iss_enc_txt =~ s/( on page D7\-\d+)//;
            }
    $iss_enc_txt =~ s/ARM DDI 0487A\.b Copyright \© 2013 ARM Limited\.//s;
    $iss_enc_txt =~ s/All rights reserved\. //;
    $iss_enc_txt =~ s/D7\-1833ID122413 Non\-Confidential \- BetaD7 AArch64//;
    $iss_enc_txt =~ s/System Register Descriptions D7\.2 General system control registers//;
    $iss_enc_txt =~ s/EC31 26IL25ISS24 0D7\-1832 Copyright \© 2013 ARM Limited\.//;
    $iss_enc_txt =~ s/ARM DDI 0487A\.bNon\-Confidential \- Beta ID122413D7 AArch64//;

    print "description: $ec_txt\n";
    print "encoding: $iss_enc_txt\n"; 
    print "page: $iss_enc_page\n";
}
