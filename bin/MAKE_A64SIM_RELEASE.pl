#!/usr/bin/perl -w

#**********************************************************************************************************************
# MAKE_A64SIM_RELEASE.pl
#
# rm -rf test a64sim_1.0.4-alpha.tar.gz a64sim ~/Downloads/newlib/aarch64-unknown-none.tar.gz
#**********************************************************************************************************************

my $next_release_no = $ARGV[0];

die "No release# specified.\n" if not defined($next_release_no);

print "Next release#: $next_release_no\n";

my $thisdir = `/bin/pwd`;
chomp $thisdir;

my $releases_dir = 'a64sim';

my $releases_build_dir = $ENV{HOME} . "/Desktop/$releases_dir";

if (-d $releases_build_dir) {
    die("Release build directory '$releases_build_dir' already exists. Rename or remove before proceeding...\n");
}


my $release_tarball = "a64sim_${next_release_no}.tar.gz";

if (-f $release_tarball) {
    die("Release tar-file '$release_tarball' already exists. Rename or remove before proceeding...\n");
}


print "Release build directory: '$releases_build_dir'\n";

die("Problems creating release build dir?\n") if system("mkdir -v $releases_build_dir");

chdir $releases_build_dir;

print "here i am: " . `/bin/pwd` . "\n";

my @rel_dirs = qw( bin docs examples test third_party/newlib third_party/newlib/newlib-aarch64 );

foreach my $dir (@rel_dirs) {
    die("Can't make release sub-dir '$dir'?\n") if system("/bin/mkdir -p -v $dir");
}

my $a64sim_src_dir = $ENV{HOME} . '/Desktop/windvane';

my $newlib_source_dir  = $ENV{HOME} . '/Downloads/newlib-2.5.0/newlib';

my %files_to_copy = (
    "$a64sim_src_dir/bin/a64sim"                      => 'bin',
    "$a64sim_src_dir/tarmac/a64sim2tarmac"            => 'bin',
    "$a64sim_src_dir/tarmac2simtrace/tarmac2simtrace" => 'bin',
    "$a64sim_src_dir/bin/a64sim_trace_viewer"         => 'bin',
    
    "$a64sim_src_dir/bin/stv.jar"                     => 'bin',
    
    "$a64sim_src_dir/docs/README"                     => '.',
    "$a64sim_src_dir/docs/LICENSE"                    => '.',

    "$a64sim_src_dir/docs/a64sim_command_line.html"   => 'docs',
    "$a64sim_src_dir/docs/a64sim_configuration.html"  => 'docs',
    "$a64sim_src_dir/docs/a64sim_features.html"       => 'docs',
    "$a64sim_src_dir/docs/a64sim_license.html"        => 'docs',
    "$a64sim_src_dir/docs/a64sim_links.html"          => 'docs',
    "$a64sim_src_dir/docs/index.html"                 => 'docs',
    
    "$a64sim_src_dir/docs/a64sim_users_guide.html"    => 'docs',
    "$a64sim_src_dir/docs/a64sim_quick_start.html"    => 'docs',

    "$a64sim_src_dir/docs/logo.png"                   => 'docs',
    "$a64sim_src_dir/docs/simtrace_viewer_main.png"   => 'docs',

    "$a64sim_src_dir/boot_code/boot2el0.obj"          => 'test',
    
    "$newlib_source_dir/README"                       => 'third_party/newlib'
);

for my $key (keys %files_to_copy) {
    die("Problems copying file '$key' into release directory?\n") if system("cp $key $files_to_copy{$key}");
    print "$key copied to " . $files_to_copy{$key} . "\n";
} 


#--------------------------------------------------------------------------------------------------------------
# copy examples...
#--------------------------------------------------------------------------------------------------------------

my @examples = qw( lib Makefile.inc NOTES example1 example2 example3 example4 example5 example6 example7 example8 );

my $examples_dir = "$a64sim_src_dir/tutorial";

foreach my $example (@examples) {
    my $exdir = "$examples_dir/$example";
    die("Problems copying example '$example' into release examples directory?\n") if system("cp -R $exdir examples");
}

my $examples_notes = "$examples_dir/NOTES";

die("Problems copying example notes ($examples_notes) into release examples directory?\n") if system("cp $examples_notes examples");


#--------------------------------------------------------------------------------------------------------------
# install newlib build, along with notes and newlib licensing file...
#--------------------------------------------------------------------------------------------------------------

my $downloads_dir = $ENV{HOME} . '/Downloads';

my $newlib_rel_dir = "$releases_build_dir/third_party/newlib";


# copy build directory notes, scripts, etc...

my $newlib_bld_dir = "$downloads_dir/newlib-aarch64";

my @newlib_bld_files = qw( NOTES.txt MAKE_LINKS.sh RUN_CONFIGURE.sh RUN_MAKE.sh RUN_MAKE_INSTALL.sh ); 

my $dest_dir = "$newlib_rel_dir/newlib-aarch64";

for my $file (@newlib_bld_files) {
    system("cp $newlib_bld_dir/$file $dest_dir");
}

system("cp $newlib_bld_dir/README_TOO $newlib_rel_dir");


# copy installed newlib files...

my $newlib_install_dir = "$downloads_dir/newlib";

chdir $newlib_install_dir;

my $newlib_install_tar = 'aarch64-unknown-none.tar.gz';

die("newlib install dir tar-ball '$newlib_install_dir/$newlib_install_tar' already exists. Rename or remove before proceeding.\n") if -f $newlib_install_tar;
die("Problems tar'ing up newlib install dir?\n") if system("tar czfv $newlib_install_tar aarch64-unknown-none");
die("Problems copying newlib install tar file into release dir?\n") if system("cp $newlib_install_tar $newlib_rel_dir");

chdir $newlib_rel_dir;

die("Problems unpacking newlib install tar in $newlib_rel_dir ?\n") if system("tar xzfv $newlib_install_tar");
system("rm $newlib_install_tar");


chdir $thisdir;

print "this dir: '$thisdir'\n";

die("Problems tar'ing release?\n") if system("tar czfv $release_tarball $releases_dir");


#--------------------------------------------------------------------------------------------------------------
# now to create stand-alone GUI build...
#
# process:
#    1. unpack .deb file from 'windvane/packages' dir into ./test
#    2. mkdir ./test/a64sim
#    3. mv ./test/opt ./test/a64sim
#    4. cd ./test/opt
#    5. tar xzfv $release_tarball
#    6. mv tuleta_software a64sim
#    7. mkdir DEBIAN
#    8. cp $a64sim_src_dir/docs/DEBIAN/control DEBIAN 
#    7. cd ..
#    8. dpkg-deb --build a64sim
#--------------------------------------------------------------------------------------------------------------

### $thisdir
    
my $DEBIAN_PACKAGE_UTIL = '/usr/bin/dpkg';

my $DEBIAN_BUILD_DIR = "$thisdir/test";

my $GUI_BUNDLES_DEB = "$a64sim_src_dir/packages/bundles/a64-simtrace-viewer-1.0.deb";


print "packing up...\n";


# check files...

die("Release tar-ball '$thisdir/$release_tarball' not found?\n") if not -f "$thisdir/$release_tarball";

die("'debian' build directory '$DEBIAN_BUILD_DIR' already exists. Rename or remove before proceeding...\n") if -d $DEBIAN_BUILD_DIR;

die("GUI bundle/.deb file '$GUI_BUNDLES_DEB' not found?\n") if not -f $GUI_BUNDLES_DEB;

die("debian control file '$a64sim_src_dir/docs/DEBIAN/control' not found?\n") if not -f "$a64sim_src_dir/docs/DEBIAN/control";
die("debian 'post-install' file '$a64sim_src_dir/docs/DEBIAN/postinst' not found?\n") if not -f "$a64sim_src_dir/docs/DEBIAN/postinst";


# Unpack .deb file from 'windvane/packages' dir:

die("Unpack of stand-alone GUI failed?\n") if system("$DEBIAN_PACKAGE_UTIL -x $GUI_BUNDLES_DEB $DEBIAN_BUILD_DIR");

die("After unpack, no '$DEBIAN_BUILD_DIR/opt' dir?\n") if not -d "$DEBIAN_BUILD_DIR/opt";


# mov opt/GUI dir into a64sim sub-dir...

system("mkdir $DEBIAN_BUILD_DIR/a64sim");
system("mv $DEBIAN_BUILD_DIR/opt $DEBIAN_BUILD_DIR/a64sim");


# copy in debian control file, post-install script...

system("mkdir $DEBIAN_BUILD_DIR/a64sim/DEBIAN");
system("cp $a64sim_src_dir/docs/DEBIAN/control $DEBIAN_BUILD_DIR/a64sim/DEBIAN");
system("cp $a64sim_src_dir/docs/DEBIAN/copyright $DEBIAN_BUILD_DIR/a64sim/DEBIAN");
#system("cp $a64sim_src_dir/docs/DEBIAN/postinst $DEBIAN_BUILD_DIR/a64sim/DEBIAN"); <---doesn't seem to work


# untar a64sim in a64sim/opt dir...

chdir "$DEBIAN_BUILD_DIR/a64sim/opt";
system("tar xzfv $thisdir/$release_tarball");


chdir $DEBIAN_BUILD_DIR;

die if system("mkdir -p -v a64sim/opt/tuleta_software");
die if system("mv a64sim/opt/a64sim a64sim/opt/tuleta_software");
die if system("mv a64sim/opt/a64_simtrace_viewer a64sim/opt/tuleta_software");

die if system("$DEBIAN_PACKAGE_UTIL --build a64sim");

chdir $thisdir;

die("Final debian package file '$DEBIAN_BUILD_DIR/a64sim.deb' not found?\n") if not -f "$DEBIAN_BUILD_DIR/a64sim.deb";

print("Final debian package: $DEBIAN_BUILD_DIR/a64sim.deb\n");




