#!/usr/bin/perl

# *************************************************************************************
# parse derived exceptions code text to create Java cases...
#
#    cat ../derived/exception_codes.txt | ./exccodes.pl >exccodes.java
# *************************************************************************************

my $ec = '';
my $a64 = 0;
my $el1 = 0;
my $el2 = 0;
my $el3 = 0;
my $desc = '';

my $do_el1 = 1;
my $do_el2 = 0;
my $do_el3 = 0;

while(<>) {
    if (/^EC\: ([01]+)$/) {
        $ec = $1;
        $a64 = 0;
        $el1 = 0;
        $el2 = 0;
        $el3 = 0;
        $desc = '';
	next;
    }
    if (/^AArch64$/) {
	$a64 = 1;
	next;
    }
    if (/^EL1\: 1$/) {
	$el1 = 1;
	next;
    }
    if (/^EL2\: 1$/) {
	$el2 = 1;
	next;
    }
    if (/^EL3\: 1$/) {
	$el3 = 1;
	next;
    }

    if (/^description\: /) {
	$desc = $';
	chomp $desc;
    
        my $doit = 1;  #just do it ($do_el1 and $el1) or ($do_el2 and $el2) or ($do_el3 and $el3);

        if ($doit) {
           my $caseno = oct("0b".$ec);
           print("        case $caseno\: // EC = $ec\n");
           print("             ec_brief = \"$desc\"\n");
           print("             ec_descr = \"$desc\"\n");
           print("             break;\n");
        }
    }
    
}
