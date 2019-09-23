#!/usr/bin/perl -w

my %opcodes = ();
my %notes = ();

open(OCFILE,'./derived/a64_instr_decode.C');
while(<OCFILE>) {
    if (/^\s+\/\/\ (0x[0-9a-f]+)\, (\w+)\: \'[^\']+\' \- \'([^\']+)\'/) {
	my $opcode = $1;
        my $enum = $2;
        my $description = $3;
        #print "$opcode $enum '$description'\n"; 
        $opcodes{$enum} = $opcode;
        $notes{$enum} = $description; 
        next;
    }
}
close OCFILE;

my $print_hdr = 1;

while(<>) {
    if ($print_hdr) {
	&do_hdr;
        $print_hdr = 0;
    }

    if (/^(\w+)/) {
        my $enum = $1;
        my $opcode = $opcodes{$enum};
        my $notes = $notes{$enum};
        my $ld_or_str = ($enum =~ /^LD/) ? 'LOAD' : 'STORE';
        my $access_type = &access_type($enum);
        my $data_size = &data_size($enum);
        my $word_size = &word_size($enum);
        my $sign_extend = &sign_extend($enum);
        my $base_address = &base_address($enum);
        my $offset = &offset($enum);
        my $wback = &wback($enum);
        my $post_index = &post_index($enum);
        my $scale = &scale($enum);
        my $shift = &shift($enum);
        my $unpred_writeback = &unpred_writeback($enum);
        my ($src_reg1,$src_reg2) = &src_regs($enum);
        my ($dest_reg1,$dest_reg2) = &dest_regs($enum);

        print "$enum,$opcode,$notes,$ld_or_str,$access_type,$data_size,$word_size,$sign_extend,$base_address,$offset,$wback,$post_index,$scale,$shift,$unpred_writeback,$src_reg1,$src_reg2,$dest_reg1,$dest_reg2\n";
	next;
    }
    $print_hdr = 1 if /^\s*$/; 
}

sub do_hdr {
    print ",,,,,,,,,,,,,,,,,,\n";
    print "mnemonic,opcode,description,ld or st,access type,data size,word size,sign extend,base address,offset ,wback,Post-index,scale,shift,Unpred-writeback,src register1,src register2,dest register1,dest register2\n";
}

sub access_type {
    my($enum) = @_;

    my $type = '?';

    if ($enum =~ /X/ or $enum =~ /LDA/ or $enum =~ /STLR/) {
       $type = 'EXCLUSIVE';
    } elsif ($enum =~ /PRFM/) {
       $type = 'PREFETCH';
    } elsif ($enum =~ /LDN/) {
	$type = 'STREAM';
    } elsif ($enum =~ /LDUR/ or $enum =~ /STUR/) {
        $type = 'UNPRIVILEGED';
    } else {
        $type = 'NORMAL';
    }

    return $type;    
}

sub data_size {
    my($enum) = @_;

    my $dsize = '4';

    $dsize = 1 if $enum =~ /RB/ or $enum =~ /SB/;
    $dsize = 2 if $enum =~ /RH/ or $enum =~ /SH/;

    return $dsize
}

sub word_size {
    my($enum) = @_;

    my $wsize = 4;

    $wsize = 8 if $enum =~ /_64/;

    $wsize = 1 if $enum =~ /RB/ or $enum =~ /SB/;
    $wsize = 2 if $enum =~ /RH/ or $enum =~ /SH/;

    return $wsize;
}

sub sign_extend {
    my($enum) = @_;

    my $extend = '';

    $extend = 64 if $enum =~ /SW/;
    $extend = 32 if ($enum =~ /SB/ or $enum =~ /SH/) and $enum =~ /_32/;
    $extend = 64 if ($enum =~ /SB/ or $enum =~ /SH/) and $enum =~ /_64/;

    return $extend;
}

sub base_address {
    my($enum) = @_;

    my $base_addr = 'NREG';

    $base_addr = 'PC' if $enum =~ /LDR_REG_(32|64)/;

    return $base_addr;
}

sub wback {
    my($enum) = @_;

    my $wrback = 'false';

    $wrback = 'true' if $enum =~ /_POST/ or $enum =~ /_PRE/;

    return $wrback; 
}

sub post_index {
    my($enum) = @_;

    my $pindex = 'false';

    $pindex = 'true' if $enum =~ /_POST/;

    return $pindex;
}

sub scale {
    my($enum) = @_;

    my $sc = 0;

    $sc = 'packet->size.Value()' if $enum =~ /_IMM_/ or $enum =~ /_REG_OFF_/ or $enum =~ /LDR_REG_(32|64)/ or $enum =~ /LDTR_REG_(32|64)/ or $enum =~ /LDRSW_REG/;

    return $sc;
}

sub offset {
    my($enum) = @_;

    my $offset = '';

    $offset = '"SignExtend(packet->imm9.Value(),9)"' if $enum =~ /_IMM_REG_(PRE|POST)/;

    $offset = '"LSL(packet->imm12.Value(),scale)"' if $enum =~ /_IMM_REG_(32|64|OFF)/;

    $offset = '"SignExtend(packet->imm19.Value()<<2,21)"' if $enum =~ /LDR_REG_32|LDR_REG_64|LDRSW_REG/;

    $offset = '"SignExtend(packet->imm9.Value(),9)"' if ($enum =~ /_IMM_REG_(32|64)/ and $enum =~ /(SB|SH|SW)/) or $enum =~ /LDTRSW_REG/ or $enum =~ /LDTR_REG_(32|64)/;

    $offset = '"ExtendReg(packet->Rm.Value(),DecodeRegExtend(packet->option.Value(),packet->S.Value()==1 ? scale : 0,packet->size.Value()==1 ? 64 : 32)"' 
	if $enum =~ /_REG_OFF/ and not $enum =~ /_IMM_/;

    return $offset;
}

sub shift {
    my($enum) = @_;

    my $sh = '';

    return $sh;
}

sub unpred_writeback {
    my($enum) = @_;

    my $unpred = '';

    return $unpred;
}


sub src_regs {
    my($enum) = @_;

    my $is_str = ($enum =~ /^LD/) ? 0 : 1;

    my $sreg1 = $is_str ? 'TREG' : '';
    my $sreg2 = '';

    return ($sreg1,$sreg2);
}

sub dest_regs {
    my($enum) = @_;

    my $is_ld = ($enum =~ /^LD/) ? 1 : 0;

    my $dreg1 = $is_ld ? 'XT' : '';
    my $dreg2 = '';

    return ($dreg1,$dreg2);
}

