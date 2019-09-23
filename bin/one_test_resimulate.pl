#!/usr/bin/perl -w

my $num_instrs   = 10;

my $projectdir   = $ENV{'HOME'} . '/Desktop/windvane';

my $bindir       = "$projectdir/bin";
my $root_testdir = "$projectdir/test";
my $bcdir        = "$projectdir/boot_code";

my $seed         = defined($ARGV[0]) ? ('--seed ' . $ARGV[0]) : '';

my $resim_binary = $ENV{'HOME'} . '/Downloads/test_unicorn/resim_trace_arm64';

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

# resimulate test...

if (system("$resim_binary trace.0 1>resim.log 2>&1")) {
    die("Resimulation fail!\n");
}

my $see_pass = 0;
open(RESIM_LOG,'resim.log') or die("no resimulation log (trace.0)?\n");
while(<RESIM_LOG>) {
    $see_pass = 1 if /^PASS\!$/;
}
close RESIM_LOG;
if (!$see_pass) {
    die("Resimulation did not indicate test passed!\n");
}

print "PASS!\n";

exit(0);


