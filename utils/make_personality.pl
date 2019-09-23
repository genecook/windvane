#!/usr/bin/perl -w

my $sim_ini_file = $ARGV[0];

print "  //'$sim_ini_file'\n";

my $section = '';

my $do_exceptions = ($sim_ini_file =~ /exceptions/) ? 1 : 0;

open(INIFILE,$sim_ini_file) or die;

while(<INIFILE>) {
    next if /^\s*$/ or /^\s*\;/;

    if (/\;/) {
    #  $comment = $'; 
      $_ = $`;
    }

    if (/^\s*\[([^\]]+)\]/) {
       my $next_section = $1;
       $next_section = 'Pstate' if $next_section eq 'PSTATE';
       if ( ($section ne '') and !$do_exceptions) {
           if ( ($section eq 'MPIDR_EL1') or ($section eq 'VMPIDR_EL2') ) {
               print "   my_cpu->SetID(i);\n";
           }
	   print "   TraceLogEntry(\"    # $section\: 0x\%x\\n\",my_cpu->$section.Value());\n";
       }
       $section = $next_section;
       next;
    }

    if (/^\s*(\w+)\s*\=\s*([0-9abcdefx\.\-]+)/) {
       my $field = $1;
       my $value = $2;
       if ($do_exceptions and ($section eq 'Testbed') ) {
           my $ename = uc($field);
	   print "   exception_enables.Add($value,GENERATION_ERROR,$ename);\n";
           my $onoff = ($value == 1) ? 'Enabled' : 'Disabled';
           print "   TraceLogEntry(\"  # $section\.$field\: $onoff\\n\");\n";
       } elsif ($do_exceptions and ($section eq 'Exception Enables') ) {
           my $ename = uc($field);
	   print "   exception_enables.Add($value,ARCH_EXCEPTION,$ename);\n";
           my $onoff = ($value == 1) ? 'Enabled' : 'Disabled';
           print "   TraceLogEntry(\"  # $section\.$field\: $onoff\\n\");\n";
       } elsif ( ($field eq 'IT') or ($field eq 'PMUVer') or ($field eq 'TraceVer') ) {
         print "   TraceLogEntry(\"# WARNING: $section\.$field NOT supported or is READ-ONLY...\\n\");\n";
       } elsif ($field =~ /Value/i) {
         print "   my_cpu->$section.Value($value);\n";
       } else {
         print "   my_cpu->$section\.$field($value);\n";
       }
       next;
    }

    die "OOPS!: " . $_;
}

if ( ($section ne '') and !$do_exceptions) {
    print "  TraceLogEntry(\"    # $section\: 0x\%x\\n\",my_cpu->$section.Value());\n";
}

close INIFILE;

