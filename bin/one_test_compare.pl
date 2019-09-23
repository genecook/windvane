#!/usr/bin/perl -w

my $num_instrs   = 10000;

my $projectdir   = $ENV{'HOME'} . '/Desktop/windvane';

my $bindir       = "$projectdir/bin";
my $root_testdir = "$projectdir/test";
my $bcdir        = "$projectdir/boot_code";

my $seed         = defined($ARGV[0]) ? ('--seed ' . $ARGV[0]) : '';

# generate...

if (system("$bindir/x64sim -n $num_instrs -L $bcdir/bootel1toel0.obj -S test.elf -F -T trace $seed 1>gen.log 2>&1")) {
    die("Generation fail!\n");
}

if (!(-f 'test.elf')) {
    die("Generation failed to produce elf!\n");
}

if (!(-f 'trace.0')) {
    die("Generation failed to produce trace!\n");
}

# translate trace into ascii...

if (system("$bindir/show_simtrace trace.0 1>trace.ascii 2>&1")) {
    die("Simtrace failed on generated trace!\n");
}

if (!(-f 'trace.ascii')) {
    die("Simtrace on generated trace failed to produce ascii trace!\n");
}

# extract disassembly from ascii trace...

if (&extract_disasm('test.asm','trace.ascii',0)) {
    die("Disassembly (gen) fail!\n");
}

if (!(-f 'test.asm')) {
    die("No (gen) disassembly!\n");
}

# extract disassembly listing from ascii trace...

if (&extract_disasm_lst('test.lst','trace.ascii',0)) {
    die("Disassembly listing (gen) fail!\n");
}

if (!(-f 'test.lst')) {
    die("No (gen) disassembly listing!\n");
}

# compress (filter) ascii trace for use with tkdiff...

if (&compress_trace('trace.ascii.tkdiff','trace.ascii',0)) {
    die("Compress of trace.ascii fail!\n");
}

if (!(-f 'trace.ascii.tkdiff')) {
    die("Failed to 'compress' (gen) ascii trace!\n");
}

# resimulate test...

my $resim_count = $num_instrs + 10; # should halt when wfi hit but lets see???

if (system("$bindir/x64sim -n $resim_count -L test.elf -S resim_test.elf -T resim_trace 1>resim.log 2>&1")) {
    die("Resimulation fail!\n");
}

if (!(-f 'resim_test.elf')) {
    die("Resimulation failed to produce elf!\n");
}

if (!(-f 'resim_trace.0')) {
    die("Resimulation failed to produce trace!\n");
}

# translate (resim) trace into ascii...

if (system("$bindir/show_simtrace resim_trace.0 1>resim_trace.ascii 2>&1")) {
    die("Simtrace (resim) fail!\n");
}

if (!(-f 'resim_trace.ascii')) {
    die("Simtrace on resim trace failed to produce ascii trace!\n");
}

# extract (resim) disassembly from ascii (resim) trace...

if (&extract_disasm('resim_test.asm','resim_trace.ascii',1)) {
    die("Disassembly (resim) fail!\n");
}

if (!(-f 'resim_test.asm')) {
    die("No (resim) disassembly!\n");
}

# compress (filter) ascii trace for use with tkdiff...

if (&compress_trace('resim_trace.ascii.tkdiff','resim_trace.ascii',0)) {
    die("Compress of trace.ascii fail!\n");
}

# compare disassemblys...

if (system("/usr/bin/diff test.asm resim_test.asm 1>disasm_diff.log 2>&1")) { 
    die("Disassembly mismatch!\n");  
}

# compare traces...

if (!(-f 'trace.ascii.tkdiff') or !(-f 'resim_trace.ascii.tkdiff')) {
    die("Trace compare fails! - One or both (tkdiff) trace files is missing!\n");
}

if (system("/usr/bin/diff trace.ascii.tkdiff resim_trace.ascii.tkdiff 1>trace_diff.log 2>&1")) {
    die("Trace mismatch! - see trace_diff.log\n");
}

print "Success!\n";

exit 0;


sub extract_disasm {
    my ($asm_file,$ascii_trace_file,$resim) = @_;

    if (!open(TRACE,$ascii_trace_file)) {
       #"Unable to open '$ascii_trace_file'?\n");
       return 1;
    }

    if (!open(ASM,">$asm_file")) {
       # or die("Unable to open '$asm_file'?\n");
	return 1;
    }

    while(<TRACE>) {
	print ASM "$1\n" if /^\s+disassembly\: \"([^\\]+)\\/;
    }

    close ASM;
    close TRACE;

    return 0;
}

sub extract_disasm_lst {
    my ($lst_file,$ascii_trace_file,$resim) = @_;

    if (!open(TRACE,$ascii_trace_file)) {
        #or die("Unable to open '$ascii_trace_file'?\n");
	return 1;
    }

    if (!open(LST,">$lst_file")) {
        # or die("Unable to open '$lst_file'?\n");
	return 1;
    }

    my $pc = 0;
    my $opcode = 0;
    my $disasm = '';

    while(<TRACE>) {
        $pc     = 0 + $1 if /^\s+PC\: (\d+)/;
        $opcode = 0 + $1 if /^\s+Opcode\: (\d+)/;

	if (/^\s+disassembly\: \"([^\\]+)\\/) {
	    $disasm = $1;
            $opc_le = &le($opcode);
            printf(LST "0x%08x\:  db 0x%08x  # 0x%08x  --  %s\n",$pc,$opc_le,$opcode,$disasm);
	}
    }

    close LST;
    close TRACE;

    return 0;
}

sub le {
    my ($opcode) = @_;

    my $byte0 = ($opcode>>24) & 0xff;  # msb bits 31:24
    my $byte1 = ($opcode>>16) & 0xff;  #          23:16
    my $byte2 = ($opcode>>8)  & 0xff;  #          15:8
    my $byte3 = $opcode       & 0xff;  #          7:0

    my $opc_le = ($byte3<<24) | ($byte2<<16) | ($byte1<<8) | $byte0;

    return $opc_le;
}

sub compress_trace {
    my ($ascii_trace_dest,$ascii_trace_src) = @_;

    if (!open(TRACE_IN,$ascii_trace_src)) {
        # or die("Unable to open '$ascii_trace_src'?\n");
	return 1;
    }

    if (!open(TRACE_OUT,">$ascii_trace_dest")) {
        # or die("Unable to open '$ascii_trace_dest'?\n");
	return 1;
    }

    while(<TRACE_IN>) {
        next if /^Test a64sim sim trace\,/;
	next if /^\s+instr_group\:/;
        next if /^\s+Goal\: [01]/;
        print TRACE_OUT;
    }

    close TRACE_OUT;
    close TRACE_IN;

    return 0;
}



