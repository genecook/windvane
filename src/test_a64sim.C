#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boost/program_options.hpp"

#include <iostream>

#include "a64sim.h"
#include "SimTrace.h"
#include "a64Scaffold.h"

#define CPUID 0

namespace 
{
  const size_t COMMAND_LINE_ERROR = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}

// ---------------------------------------------------------------------------------------------------------------------
// program parameters - keep it simple...
// ---------------------------------------------------------------------------------------------------------------------

std::string  sim_init_file     = "./setup/a64sim.ini";
std::string  exc_enables_file  = "./setup/a64sim_exceptions.ini";

std::string  rlog_file         = "";
FILE        *RUNLOG            = stdout;

std::string  errlog_file       = "";
FILE        *ERRLOG            = stderr;

std::string  tracelog_file     = "";
FILE        *TRACELOG          = stdout;

std::string  debuglog_file     = "";
FILE        *DEBUGLOG          = stderr;

std::string  elf_src_file      = "";
std::string  elf_dest_file     = "";

std::string  simtrace_file     = "";

unsigned int seed              = time(NULL);
int          number_of_instrs  = 1000;

unsigned int cpu_index         = CPUID;

bool         do_help           = false;

int          verbose_level     = 0;

// ---------------------------------------------------------------------------------------------------------------------
// succinct help...
// ---------------------------------------------------------------------------------------------------------------------

void show_help() {
  printf("\n");
  printf("    cmdline options:\n");
  printf("        --sim_init_file (or -i) <file path>     -- path to (input) simulation init file (default is './a64sim.ini')\n");
  printf("        --exc_enables_file (or -x) <file path>  -- path to (input) simulation exception enables file (default is './a64sim_exceptions.ini')\n");
  printf("        --run_log (or -r) <file path>           -- path to simulation run log output (default is stdout)\n");
  printf("        --err_log (or -e) <file path>           -- path to simulation error log output (default is stderr)\n");
  printf("        --trace_log (or -t) <file path>         -- path to simulation trace output (default is stdout)\n");
  printf("        --debug_log (or -d) <file path>         -- path to simulation debug output (default is stderr)\n");
  printf("        --sim_load_file (or -L) <file path>     -- path to simulation source file\n");
  printf("        --sim_save_file (or -S) <file path>     -- path to simulation output file\n");  
  printf("        --sim_trace_file (or -T) <file path>    -- path to simulation trace file (default is none)\n");  
  printf("        --seed <unsigned int>                   -- initial seed (default is random value\n");
  printf("        --num_instrs (or -n) <count>            -- number of instructions to simulate (default is 1000)\n");
  printf("        --verbose_level (or -V) <level>         -- debug verbage level\n");
}

// ---------------------------------------------------------------------------------------------------------------------
// parse command line options...
// ---------------------------------------------------------------------------------------------------------------------

int parse_cmdline_options(int argc,char **argv) {
  try {
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
      ("help,h", "Print help messages")
      ("sim_init_file,i", po::value<string>(),"Simulator initialization file")
      ("exc_enables_file,x", po::value<string>(),"Simulator exception enables file")
      ("run_log,r",po::value<string>(),"Run log file")
      ("err_log,e",po::value<string>(),"Error log file")
      ("trace_log,t",po::value<string>(),"Trace file")
      ("debug_log,t",po::value<string>(),"Debug log file")
      ("sim_load_file,L",po::value<string>(),"Simulation Load file")
      ("sim_save_file,S",po::value<string>(),"Simulation Save file")
      ("sim_trace_file,T",po::value<string>(),"Simulator trace file")
      ("seed",po::value<unsigned int>(),"Initial seed")
      ("num_instrs,n",po::value<int>(),"Number of 'freerun' instructions")

      ("verbose_level,V",po::value<int>(),"Debug verbage level");

    po::variables_map vm;
    try {
      po::store(po::parse_command_line(argc,argv,desc),vm);
      if (vm.count("help")) {
	show_help();
        do_help = true;
        return SUCCESS;
      }
      if (vm.count("sim_init_file"))    { sim_init_file    = vm["sim_init_file"].as<string>(); }
      if (vm.count("exc_enables_file")) { exc_enables_file = vm["exc_enables_file"].as<string>(); }

      if (vm.count("run_log")) {
	 rlog_file = vm["run_log"].as<string>();
         RUNLOG = fopen(rlog_file.c_str(),"w");
         if (RUNLOG == NULL) {
	   fprintf(stderr,"ERROR: problems opening run-log file '%s'\n",rlog_file.c_str());
           throw(COMMAND_LINE_ERROR);
	 }
      }
      if (vm.count("err_log")) {
	 errlog_file = vm["err_log"].as<string>();
         ERRLOG = fopen(errlog_file.c_str(),"w");
         if (ERRLOG == NULL) {
	   fprintf(stderr,"ERROR: problems opening error-log file '%s'\n",errlog_file.c_str());
           throw(COMMAND_LINE_ERROR);
	 }
      }
      if (vm.count("trace_log")) {
	 tracelog_file = vm["trace_log"].as<string>();
         TRACELOG = fopen(tracelog_file.c_str(),"w");
         if (TRACELOG == NULL) {
	   fprintf(stderr,"ERROR: problems opening trace-log file '%s'\n",tracelog_file.c_str());
           throw(COMMAND_LINE_ERROR);
	 }
      }
      if (vm.count("debug_log")) {
	 debuglog_file = vm["debug_log"].as<string>();
         DEBUGLOG = fopen(debuglog_file.c_str(),"w");
         if (DEBUGLOG == NULL) {
	   fprintf(stderr,"ERROR: problems opening debug-log file '%s'\n",debuglog_file.c_str());
           throw(COMMAND_LINE_ERROR);
	 }
      }
      if (vm.count("sim_load_file")) {
	 elf_src_file = vm["sim_load_file"].as<string>();
      }
      if (vm.count("sim_save_file")) {
	 elf_dest_file = vm["sim_save_file"].as<string>();
      }

      if (vm.count("sim_trace_file")) { 
         simtrace_file = vm["sim_trace_file"].as<string>(); 
      }

      if (vm.count("seed")) { seed = vm["seed"].as<unsigned int>(); }
      if (vm.count("num_instrs")) { number_of_instrs = vm["num_instrs"].as<int>(); }

      if (vm.count("verbose_level")) { verbose_level = vm["verbose_level"].as<int>(); }

      po::notify(vm);
    }
    catch(po::error& e) {
      printf("ERROR: %s\n",e.what());
      return COMMAND_LINE_ERROR;
    }
  }
  catch(std::exception& e) {
      printf("Unhandled exception?\n");
      return ERROR_UNHANDLED_EXCEPTION;
  }

  return SUCCESS;
}

// ---------------------------------------------------------------------------------------------------------------------
// main always writes some messages to stdout (or stderr for errors). all output from simulator controlled via
// command line options...
// ---------------------------------------------------------------------------------------------------------------------

int main(int argc,char **argv) {
  printf("A64simulatorX/single-core - Tuleta Software Co. All rights reserved.\n\n");

  int rcode = parse_cmdline_options(argc,argv);

  if (rcode != SUCCESS || do_help)
    exit(rcode);

  // use scoping with static instance of simulator to control when simulator destructer is invoked...
  {
    Scaffold scaffold(sim_init_file.c_str(),exc_enables_file.c_str(),RUNLOG,ERRLOG,TRACELOG,DEBUGLOG);

    scaffold.SetSimTraceFile(simtrace_file);

    if (elf_src_file != "") {
      // simulate from an existing test... 
      rcode = scaffold.Simulate(elf_src_file,cpu_index,number_of_instrs,verbose_level);
    } else {
      // let the simulator 'freerun' to produce a test...
      rcode = scaffold.FreeRun(cpu_index,number_of_instrs,seed,false,verbose_level);
    }

    if (!rcode && elf_dest_file != "") {
      scaffold.Save(elf_dest_file);
    }
  }

  if (rlog_file != "")     fclose(RUNLOG);
  if (errlog_file != "")   fclose(ERRLOG);
  if (tracelog_file != "") fclose(TRACELOG);
  if (tracelog_file != "") fclose(DEBUGLOG);

  exit(rcode);
}
