#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

#include "boost/program_options.hpp"

using namespace std;

namespace
{
  const size_t COMMAND_LINE_ERROR = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}

#define NCORES 8

int main(int argc,char **argv) {
  printf("MP test harness - Tuleta Software Co. All rights reserved.\n\n");

  string tester = "";

  try {
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
      ("help,h","Print help messages")
      ("tester,T",po::value<string>(),"Test program");

    po::variables_map vm;

    try {
      po::store(po::parse_command_line(argc,argv,desc),vm);
      if (vm.count("help")) {
         printf("\n");
         printf("    cmdline options:\n");
         printf("       --tester (or -T) <file path>  -- path to tester binary or script\n");
         return SUCCESS;
      }

      if (vm.count("tester")) 
        tester = vm["tester"].as<string>();
      po::notify(vm);
    } 
    catch(po::error& e) {
      printf("ERROR: %s\n",e.what());
      return COMMAND_LINE_ERROR;
    }
  }
  catch(std::exception& e) {
      printf("Error(s) occurred when processing command line options\n");
      return ERROR_UNHANDLED_EXCEPTION;
  }

  if (tester == "") {
    printf("OOPS! no tester specified.\n");
    return COMMAND_LINE_ERROR;   
  }

  printf("tester: '%s'\n",tester.c_str());

  char tbuf[1024];

  #pragma omp parallel private(tbuf)
  {
    #pragma omp for
    for (int i = 0; i < NCORES; i++) {
       sprintf(tbuf,"%s %d",tester.c_str(),i);
       system(tbuf);
    }
  }

  exit(0);
}

