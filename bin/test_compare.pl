#!/usr/bin/perl

use File::Temp qw/ tempfile tempdir/;

my $projectdir   = $ENV{'HOME'} . '/Desktop/windvane';

my $bindir       = "$projectdir/bin";
#my $root_testdir = "$projectdir/test";
my $root_testdir = "$projectdir/random_test";

my $num_of_tests = 10000;

my $id           = '.';
my $err_file     = "$root_testdir/ERRORS";

if (defined($ARGV[0])) {
   $id = $ARGV[0];
   $err_file .= ".$id";
}

#my $test_compare_bin = "$bindir/one_test_compare.pl";
my $test_compare_bin = "$bindir/one_test_resimulate.pl";

system "mkdir -p $root_testdir" if not -d $root_testdir;

my $pass_cnt = 0;

#print 'working...';

for (my $i = 0; $i < $num_of_tests; $i++) {
  my $testdir = tempdir('XXXXXX', DIR => $root_testdir);

  chdir $testdir;

  if (system("$test_compare_bin 1>test_compare.log 2>&1")) {
      #system("touch $err_file");
      #print "TEST COMPARE FAIL! SEE: $testdir/test_compare.log\n";
  } else {
      system("rm -rf $testdir"); 
      $pass_cnt += 1;
  }

  chdir $root_testdir;
}

print "done.\n";
print "# passed: $pass_cnt\n";

exit(0);



   

   
