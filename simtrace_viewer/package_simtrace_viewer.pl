#!/usr/bin/perl -w

#******************************************************************************************************************
# package_simtrace_viewer.pl - script to package up simtrace viewer jar files into a single jar file
#
#   Script will combine protocol buffer jar file, scaffold jar file, and simtrace viewer jar file into a
#   single jar file, copy that final jar file into windvane bin directory along with a shell script used to
#   start the sim-trace viewer.
#
#   NOTE: the script does not remove artifacts from the previous invocation of the tool. Thus to use:
#
#      cd $Desktop/windvane                  ### EDIT 'WVHOME' TO REFLECT WHERE YOU HAVE WINDVANE CHECKED OUT TO
#      rm -rf jartmp *jar packages
#      ./simtrace_viewer/package_simtrace_viewer.pl
#
#   After the script runs, the top-level shell script and jar file will be in the windvane bin directory.
#******************************************************************************************************************

use Cwd;


my $JAVA_HOME               = $ENV{HOME} . '/Downloads/jdk1.8.0_112';
my $PROTOBUF_JAR            = "/usr/share/java/protobuf-2.6.1.jar";
my $JAR_EXEC                = "$JAVA_HOME/bin/jar";
my $PACKAGER_EXEC           = "$JAVA_HOME/bin/javapackager";

my $WVHOME                  = $ENV{HOME} . '/Desktop/windvane';

my $WVHOME                  = `/bin/pwd`;

my $SCAFFOLD_HOME           = "$WVHOME/scaffold_SAPI";
my $SIMTRACE_VIEWER_JARFILE = 'simtrace_viewer.jar';

my $JARTMP_DIR              = 'jartmp';


my $STV_JAR                 = 'stv.jar';


my $STHOME                  = 'simtrace_viewer';

my $STVIEWER_MANIFEST       = "$STHOME/SimTraceViewer.mf";
my $SIMVIEWER_SCRIPTNAME    = 'simtrace_viewer.sh';
my $SIMVIEWER_SCRIPT        = "$STHOME/$SIMVIEWER_SCRIPTNAME";


print "Java home: $JAVA_HOME\n"; 
print "windvane home: $WVHOME\n";
print "scaffold dev dir: $SCAFFOLD_HOME\n";


die("Java home dir '$JAVA_HOME' does not exist?\n") if not -d $JAVA_HOME;
die("Protocol buffer java jarfile '$PROTOBUF_JAR' not found?\n") if not -f $PROTOBUF_JAR;

my $pwd = `/bin/pwd`;
chomp $pwd;

die("This script must be run in directory '$WVHOME'\n") if $pwd ne $WVHOME;


if (-l 'scaffold_SAPI') {
    print "Link to 'scaffold_SAPI' directory is in place...\n";
} else {
    system("ln -s $SCAFFOLD_HOME");
} 


die("Jar file '$SIMTRACE_VIEWER_JARFILE' exists. Remove or rename.\n") if -f $SIMTRACE_VIEWER_JARFILE;
die("Jar tmp dir '$JARTMP_DIR' exists. Remove or rename.\n") if -d $JARTMP_DIR;
die("Final simviewer jar file '$STV_JAR' exists. Remove or rename.\n") if -f $STV_JAR;
die("Simviewer startup script '$SIMVIEWER_SCRIPT' not found?\n") if not -e $SIMVIEWER_SCRIPT;

die("packages dir './packages' exists. Remove or rename.\n") if -d 'packages';
die("Java packaging tool '$PACKAGER_EXEC' not found?\n") if not -e $PACKAGER_EXEC;


print "Building $SIMTRACE_VIEWER_JARFILE...\n";

die ("Problems building $SIMTRACE_VIEWER_JARFILE ?\n") if system("make -f simtrace_viewer/Makefile $SIMTRACE_VIEWER_JARFILE");

die("$SIMTRACE_VIEWER_JARFILE just built doesn't seem to be there?\n") if not -f $SIMTRACE_VIEWER_JARFILE;


system("mkdir $JARTMP_DIR");


die("Problems extracting classes from ../$SIMTRACE_VIEWER_JARFILE ?\n") if system("cd $JARTMP_DIR;$JAR_EXEC -xf ../$SIMTRACE_VIEWER_JARFILE");
die("Problems extracting classes from ../$PROTOBUF_JAR ?\n") if system("cd $JARTMP_DIR;$JAR_EXEC -xf $PROTOBUF_JAR");

print "jar files cracked...\n";

die("Problems building final jar file '$STV_JAR' ?\n") if system("$JAR_EXEC -cvfm $STV_JAR $STVIEWER_MANIFEST -C $JARTMP_DIR .");

print "top level jar file created...\n";

die("Problems copying simtrace viewer startup script '$SIMVIEWER_SCRIPT' to ./bin?") if system("cp $SIMVIEWER_SCRIPT bin");
die("Problems copying final jar file '$STV_JAR' to ./bin?") if system("cp $STV_JAR ./bin");

print "To run simtrace viewer, type: $WVHOME/bin/$SIMVIEWER_SCRIPTNAME\n";


print "packing up stand-alone app...\n";

die("Problems packaging the app?\n") if system("export JAVA_HOME=$JAVA_HOME;$PACKAGER_EXEC -deploy -native -outdir packages -outfile stv -srcdir . -srcfiles stv.jar -appclass simtrace_viewer.Main -name 'a64_simtrace_viewer' -title 'A64sim Sim-Trace Viewer'");



