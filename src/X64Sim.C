#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string>

#include "boost/program_options.hpp"

#include "X64Simulator.h"


namespace 
{
  const size_t COMMAND_LINE_ERROR = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}


int main(int argc,char **argv) {
  printf("A64simulator - Tuleta Software Co. Copyright 2018. All rights reserved.\n\n");

  X64Simulator my_simulator;

  bool save_test = false;

  semihostParams app_sh_parms;

  unsigned long long reset_address = 0;

  unsigned long long uart_base_address = 0;
  unsigned long long counter_base_address = 0;
  
  try {
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
      ("help,h","Print help messages")
      ("version,V","Print tool version")
      
      ("sim_load_file,L",po::value< vector<string> >(),"Simulation Load file")
      ("sim_save_file,S",po::value<string>(),"Simulation Save file")
      ("sim_trace_file,T",po::value<string>(),"Simulator trace file")
      ("num_cores,N",po::value<unsigned int>(),"Number of cores to enable")
      ("max_instrs,n",po::value<unsigned int>(),"Maximum number of instructions per core to simulate")
      
      ("freerun,F","Allow simulator to 'freerun'")
      ("seed,s",po::value<unsigned int>(),"Initial seed to use when freerun enabled")
      ("end_test_file",po::value<string>(),"Simulation file to load at 'freerun' end-of-test.")

      ("userspace_dll,U",po::value< vector<string> >(),"User space dynamic library")
      ("userspace_options,O",po::value< vector<string> >(),"User space cmdline options")
      
//      ("threaded,M","Enable threaded execution. Number of threads specified via 'OMP_NUM_THREADS' environment variable")

      ("show_disassembly,D","Print address/disassembly for each instruction during simulation")

      ("EL1","Starting privilege level is EL1")
      ("reset_address",po::value<string>(),"Reset address")
      ("dram_range",po::value<string>(),"DRAM address range")
      ("uart",po::value<string>(),"Instantiate uart, specify (physical) base address for memory mapped registers")      
      ("counter",po::value<string>(),"Instantiate system counter module, specify (physical) base address for memory mapped registers")   
      ("reserve_register",po::value< vector<string> >(),"Reserve application register")
      
      ("port,P",po::value<string>(),"Port simulation debug server will listen on")
      ("core,C",po::value<string>(),"ID of processor element simulation debug server will attach to")

      ("heap_base",po::value<string>(),"Heap base address")
      ("heap_limit",po::value<string>(),"Heap limit")
      ("stack_base",po::value<string>(),"Stack base address")
      ("stack_limit",po::value<string>(),"Stack limit")
      ("env_ptr",po::value<string>(),"Env buffer address")
      ("cmdline_ptr",po::value<string>(),"Cmdline buffer address")

      ("app_cmdline",po::value<string>(),"Application cmdline")
      ("app_env",po::value<string>(),"Application environment");
    
    po::variables_map vm;
  
    try {
      po::store(po::parse_command_line(argc,argv,desc),vm);

      if (vm.count("version")) {
	 printf("a64sim 1.0.4 Alpha\n");
         return SUCCESS;
      }
      
      if (vm.count("help")) {
         printf("\n");
         printf("    command line options:\n");
	 
         printf("        --help (or -h)                          -- print this help message.\n");
         printf("        --version (or -V)                       -- print tool version information.\n");
	 printf("\n");	 
         printf("        --sim_load_file (or -L) <file path>     -- path to simulation source (ELF) file - (default is none)\n");
         printf("        --sim_save_file (or -S) <file path>     -- path to simulation output (ELF) file (default is none)\n");
	 printf("\n");
         printf("        --sim_trace_file (or -T) <file path>    -- path to simulation trace file (default is none)\n");
	 printf("\n");
         printf("        --num_cores (or -N) <count>             -- number of cores to enable (default is 1)\n");
         printf("        --max_instrs (or -n) <count>            -- Maximum number of instructions per core to simulate (default is 1000)\n");
	 printf("\n");
         printf("        --port (or -P) <port>                   -- (TCP) port simulation debug server will listen on\n");
         printf("        --core (or -C) <core>                   -- ID of processor element simulation debug server will attach to\n");
	 printf("\n");
         printf("        --freerun (or -F)                       -- Allow simulator to 'freerun' when uninitialized instruction memory encountered\n");
         printf("        --seed (or -S) <unsigned int>           -- initial seed to use when freerun enabled (default is random value)\n");
         printf("        --end_test_file<file path>              -- path to simulation source (ELF) file to load at freerun 'end-of-test' (default is none)\n");
	 
//	 printf("        --threaded (or -M)                      -- Enable threaded execution. Number of threads specified via 'OMP_NUM_THREADS' environment variable\n");
	 printf("\n");
         printf("        --show_disassembly (or -D)              -- Print address/disassembly for each instruction during simulation\n");
	 printf("\n");
	 printf("        --userspace_dll (or -U) <file path>     -- path to 'user space' dynamic library (default is none)\n");
	 printf("        --userspace_options (or -O) <file path> -- 'user space' cmdline options (default is none)\n");
	 printf("\n");	 
	 printf("        --EL1                                   -- Start simulation at privilege level 1\n");
	 printf("        --reset_address                         -- Start simulation at this address\n");
	 printf("        --dram_range <addressLo..addressHi>     -- Constrain simulation to this physical address range\n");
	 printf("        --uart <baseAddress>                    -- Instantiate uart, specify (physical) base address for memory mapped registers\n");
	 printf("        --counter <baseAddress>                 -- Instantiate system counter module, specify (physical) base address for memory mapped registers\n");
	 printf("        --reserve_register <register>           -- Reserve application register\n");	 
	 printf("\n");	 
         printf("        --app_cmdline                           -- application cmdline + arguments. May be used by stand-alone C app.\n");
         printf("        --app_env                               -- application environment. May be used by stand-alone C app.\n");
	 printf("        --heap_base                             -- heap base address      - standalone C apps - semihosting\n");
	 printf("        --heap_limit                            -- heap limit             -                \"\n");
	 printf("        --stack_base                            -- stack base address     -                \"\n");
	 printf("        --stack_limit                           -- stack limit            -                \"\n");
	 printf("        --env_ptr                               -- env buffer address     -                \"\n");
	 printf("        --cmdline_ptr                           -- cmdline buffer address -                \"\n");
         return SUCCESS;
      }
    
      if (vm.count("sim_load_file")) {
	 vector<string> obj_files = vm["sim_load_file"].as< vector<string> >();
         for (vector<string>::iterator i = obj_files.begin(); i != obj_files.end(); i++) {
	    my_simulator.AddSrcFile(*i);
	 } 
      }

      if (vm.count("sim_save_file"))      { my_simulator.SetDestFile(vm["sim_save_file"].as<string>()); save_test= true; }
      if (vm.count("sim_trace_file"))     { my_simulator.SetSimTraceFile(vm["sim_trace_file"].as<string>());             }
      if (vm.count("num_cores"))          { my_simulator.SetCoreCount(vm["num_cores"].as<unsigned int>());               }
      
      if (vm.count("freerun"))            { my_simulator.EnableFreerun();                                                }
      if (vm.count("seed"))               { my_simulator.SetSeed(vm["seed"].as<unsigned int>());                         } 
      if (vm.count("end_test_file"))      { my_simulator.SetEndTestFile(vm["end_test_file"].as<string>());               }

      if (vm.count("userspace_dll")) {
	 vector<string> userspace_options;
	 if (vm.count("userspace_options"))
	   userspace_options = vm["userspace_options"].as< vector<string> >();
	 vector<string> dll_files = vm["userspace_dll"].as< vector<string> >();
	 for (unsigned int i = 0; i < dll_files.size(); i++) {
	    string options = (userspace_options.size() >= i) ? userspace_options[i] : ""; 
	    my_simulator.AddUserSpaceDLL(dll_files[i],options);
	 }
      }
      
      if (vm.count("EL1")) {
	printf("  Will start simulation at EL1...\n");
	my_simulator.SetStartPrivilegeLevel(1);
      }
      
      if (vm.count("reset_address")) {
	string rs = vm["reset_address"].as<string>();
	if (sscanf(rs.c_str(),"0x%llx",&reset_address) != 1) {
	    fprintf(stderr,"Invalid reset address specified (value must be specified in hexadecimal format). Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
	printf("  Reset address specified: 0x%llx\n",reset_address);
      }

      if (vm.count("dram_range")) {
	string rs = vm["dram_range"].as<string>();
        std::size_t pos = rs.find("..");
        if (pos == std::string::npos) {
	    fprintf(stderr,"Invalid 'dram' address range specified. Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
        string addrLo_str = rs.substr(0,pos);
	string addrHi_str = rs.substr(pos + 2);
	unsigned long long address_lo = 0, address_hi = 0;
	if (sscanf(addrLo_str.c_str(),"0x%llx",&address_lo) != 1) {
	    fprintf(stderr,"Invalid 'dram' address range (low address) specified. Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
	if (sscanf(addrHi_str.c_str(),"0x%llx",&address_hi) != 1) {
	    fprintf(stderr,"Invalid 'dram' address range (high address) specified. Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}

	printf("  dram (simulator memory) address range specified: 0x%llx..0x%llx\n",address_lo,address_hi);
	
	my_simulator.SetAddressRange(address_lo,address_hi);
      }

      if (vm.count("uart")) {
	string rs = vm["uart"].as<string>();
	if (sscanf(rs.c_str(),"0x%llx",&uart_base_address) != 1) {
	    fprintf(stderr,"Invalid uart base address specified (value must be specified in hexadecimal format). Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
	printf("  Uart memory-mapped registers base address specified: 0x%llx\n",uart_base_address);
	if (!my_simulator.MapDevice("UART_PL011",uart_base_address)) {
          fprintf(stderr,"Problems adding in uart. Program aborted.\n");
          return COMMAND_LINE_ERROR;      
	}
      }
      
      if (vm.count("counter")) {
	string rs = vm["counter"].as<string>();
	if (sscanf(rs.c_str(),"0x%llx",&counter_base_address) != 1) {
	    fprintf(stderr,"Invalid system counter module base address specified (value must be specified in hexadecimal format). Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
	printf("  System counter module memory-mapped registers base address specified: 0x%llx\n",uart_base_address);
	if (!my_simulator.MapDevice("SYSTEM_COUNTER",counter_base_address)) {
          fprintf(stderr,"Problems adding in system counter module. Program aborted.\n");
          return COMMAND_LINE_ERROR;      
	}
      }
      
      if (vm.count("reserve_register")) {
	 vector<string> rnames = vm["reserve_register"].as< vector<string> >();
         for (vector<string>::iterator i = rnames.begin(); i != rnames.end(); i++) {
	    my_simulator.AddRegisterReservation(*i);
	 } 
      }
      
      if (vm.count("show_disassembly"))   { my_simulator.setShowProgress(true); }

      if (vm.count("max_instrs")) {
	int max_count = vm["max_instrs"].as<unsigned int>();
	if (max_count < 0) {
          printf("Note: max_instrs arguments is negative, thus maximum instructions count will NOT be enforced...\n");   
	} else if (max_count == 0) {
          printf("Note: zero specified for max_instrs (maximum # of instructions) argument?\n");
	}
	my_simulator.SetMaxInstrs(max_count);
      }

      if (vm.count("threaded")) {
	// pick off OMP_NUM_THREADS shell var here, pass onto simulator...
	// do all error processing on the shell variable here, rather than waiting 'til simulate time...
	char *ncore_str = getenv("OMP_NUM_THREADS");
        if (ncore_str == NULL) {
	    fprintf(stderr,"Environment variable 'OMP_NUM_THREADS' not set. Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
	int ncores = 0;
        if (sscanf(ncore_str,"%u",&ncores) != 1) {
	    fprintf(stderr,"Environment variable 'OMP_NUM_THREADS' does not parse into a valid unsigned integer. Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
        if (ncores == 0) {
	    fprintf(stderr,"Thread count, as gleaned from environment variable 'OMP_NUM_THREADS', is zero. Program aborted.\n");
            return COMMAND_LINE_ERROR;      
	}
        if (ncores > my_simulator.MaxCores()) { 
	    fprintf(stderr,"Thread count (%d), as gleaned from environment variable 'OMP_NUM_THREADS', exceeds the maximum # of implemented cores. Program aborted.\n",ncores);
            return COMMAND_LINE_ERROR;
	}      
        if (ncores != my_simulator.CoreCount()) {
	    fprintf(stderr,"NOTE: Thread count (%d), as gleaned from environment variable 'OMP_NUM_THREADS', does not match the cmdline specified core count (%d). Threading is disabled.\n",
                   ncores,my_simulator.CoreCount());
	} else {
            if (my_simulator.SetThreadedCoreCount(ncores)) {
	      fprintf(stderr,"Problems with (threaded) core count specified (%d). Threads not yet supported. Program aborted.\n",ncores);
              return COMMAND_LINE_ERROR;      
	    } else {
              printf("Threads are enabled.\n");
	    }
	}
      }

      int port = -1;
      unsigned int core_id = 0;
      
      if (vm.count("port"))  {
 	 std::string ts = vm["port"].as<string>();
         if (sscanf(ts.c_str(),"%d",&port) != 1) {
 	   fprintf(stderr,"ERROR: for 'port' cmdline arg, was expecting port#. Instead saw: '%s'\n",ts.c_str());
           return COMMAND_LINE_ERROR;
 	 } 
      }

      if (vm.count("core"))  {
 	 std::string ts = vm["core"].as<string>();
         if (sscanf(ts.c_str(),"%d",&core_id) != 1) {
 	   fprintf(stderr,"ERROR: for 'core' cmdline arg, was expecting core ID. Instead saw: '%s'\n",ts.c_str());
           return COMMAND_LINE_ERROR;
 	 }
	 if (((int) core_id) >= my_simulator.CoreCount()) {
 	   fprintf(stderr,"ERROR: for 'core' cmdline arg, core ID specified (%d) is invalid given the core count (%d).\n",
		  core_id,my_simulator.CoreCount());
           return COMMAND_LINE_ERROR;
	 }
      }

      my_simulator.SetDebugServerParms(port,core_id);

      if (my_simulator.DebugServerEnabled() && my_simulator.FreerunEnabled()) {
	fprintf(stderr,"ERROR: 'port' and 'freerun' command line arguments are mutually exclusive.\n");
        return COMMAND_LINE_ERROR;	
      }
      
      if (vm.count("heap_base"))   {
 	 std::string ts = vm["heap_base"].as<string>();
         if (sscanf(ts.c_str(),"0x%llx",&app_sh_parms.heap_base) != 1) {
	    fprintf(stderr,"ERROR: for 'heap_base' cmdline arg, was expecting hex value. Instead saw: '%s'\n",ts.c_str());
            return COMMAND_LINE_ERROR;
 	 }
	 app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      if (vm.count("heap_limit"))  {
 	 std::string ts = vm["heap_limit"].as<string>();
         if (sscanf(ts.c_str(),"0x%llx",&app_sh_parms.heap_limit) != 1) {
	    fprintf(stderr,"ERROR: for 'heap_limit' cmdline arg, was expecting hex value. Instead saw: '%s'\n",ts.c_str());
            return COMMAND_LINE_ERROR;
 	 }
	 app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      if (vm.count("stack_base"))  {
 	 std::string ts = vm["stack_base"].as<string>();
         if (sscanf(ts.c_str(),"0x%llx",&app_sh_parms.stack_base) != 1) {
	    fprintf(stderr,"ERROR: for 'stack_base' cmdline arg, was expecting hex value. Instead saw: '%s'\n",ts.c_str());
            return COMMAND_LINE_ERROR;
 	 }
	 app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      if (vm.count("stack_limit")) {
 	 std::string ts = vm["stack_limit"].as<string>();
         if (sscanf(ts.c_str(),"0x%llx",&app_sh_parms.stack_limit) != 1) {
	    fprintf(stderr,"ERROR: for 'stack_limit' cmdline arg, was expecting hex value. Instead saw: '%s'\n",ts.c_str());
            return COMMAND_LINE_ERROR;
 	 }
	 app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      if (vm.count("env_ptr")) {
 	 std::string ts = vm["env_ptr"].as<string>();
         if (sscanf(ts.c_str(),"0x%llx",&app_sh_parms.env_ptr) != 1) {
	    fprintf(stderr,"ERROR: for 'env_ptr' cmdline arg, was expecting hex value. Instead saw: '%s'\n",ts.c_str());
            return COMMAND_LINE_ERROR;
 	 }
	 app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      if (vm.count("cmdline_ptr")) {
 	 std::string ts = vm["cmdline_ptr"].as<string>();
         if (sscanf(ts.c_str(),"0x%llx",&app_sh_parms.cmdline_ptr) != 1) {
	    fprintf(stderr,"ERROR: for 'cmdline_ptr' cmdline arg, was expecting hex value. Instead saw: '%s'\n",ts.c_str());
            return COMMAND_LINE_ERROR;
 	 }
	 app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      
      if (vm.count("app_cmdline")) {
	strcpy(app_sh_parms.cmdline, vm["app_cmdline"].as<string>().c_str());
        app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }
      
      if (vm.count("app_app_env")) {
	strcpy(app_sh_parms.env, vm["app_env"].as<string>().c_str());
        app_sh_parms.MarkAsSet(); // mark semihost options as set if any are set. check before commiting same...
      }

      po::notify(vm);
    }
    catch(po::error& e) {
      fprintf(stderr,"ERROR: %s\n",e.what());
      return COMMAND_LINE_ERROR;
    }
  }
  catch(std::exception& e) {
      fprintf(stderr,"Error(s) occurred when processing command line options\n");
      return ERROR_UNHANDLED_EXCEPTION;
  }

  struct timeval t1,t2;
  gettimeofday(&t1,NULL);


  int rcode = my_simulator.ValidateOptions();

  if (rcode) {
    fprintf(stderr,"\n  One or more program options are invalid. Simulation aborted. Options:\n");
    my_simulator.ShowOptions();
    return rcode;
  }

  // record command line invocation...

  char cmdline[CMDLINE_MAX_LEN];
  strcpy(cmdline,argv[0]);

  for (int i = 1; i < argc; i++) {
    if (strlen(cmdline) + strlen(argv[i]) >= CMDLINE_MAX_LEN) {
      fprintf(stderr,"Oops! Command line used to invoke this program is excessively long? Aborting...\n");
      return -1;
    }
    strcat(cmdline," ");
    strcat(cmdline,argv[i]);
  }

  my_simulator.RecordCommandLine(cmdline);

  // if one or more semihosting parms have been set, then pass on to simulator.
  // semihosting is responsible for validating them...
  
  if (app_sh_parms.AreSet()) {
    printf("  C environment parameters have been specified...\n");
    my_simulator.InitSemihostingParms(app_sh_parms);
  }

  if (my_simulator.FreerunEnabled()) {
     printf("\nStarting simulation (freerun enabled, seed used: %u)...\n",my_simulator.Seed());
  } else {
     printf("\nStarting simulation...\n");
  }

  // name that tune...

  rcode = my_simulator.Go(reset_address);

  printf("Simulation ended.\n");

  if (!rcode && save_test)
    rcode = my_simulator.SaveTestImage();

  if (rcode) {
    printf("One or more errors occurred.\n");
    return rcode;
  }

  gettimeofday(&t2,NULL);

  double elapsed_time = ((t2.tv_sec - t1.tv_sec) * 1000.0)        // pick up milliseconds part 
                          + ((t2.tv_usec - t1.tv_usec) / 1000.0);   //  then microseconds...

  std::cout << "\nElapsed time: " << elapsed_time << " ms.\n";

  int total_instrs = my_simulator.SimulatedCount();

  if (total_instrs > 0) {
    long instrs_per_seconds = (long)((double) total_instrs * 1000.0 / elapsed_time);
    std::cout << "simulation rate: " << instrs_per_seconds << " instructions per second.\n";
  } 
  
  return 0;
}





