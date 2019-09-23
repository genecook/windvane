#!/usr/bin/perl

while(<>) {
    if (/address\: (\d+)/) {
        my $addr = $1;
	my $hex_addr = sprintf("0x%x", 0 + $addr);
        s/$addr/$addr \($hex_addr\)/;
    }
    print;
}
