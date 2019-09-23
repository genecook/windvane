#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <string>

#include "a64sim.h"

#include "a64simUserSpace.h"

namespace UserSpace {

struct plugin {
  plugin() { user_space_handle = NULL; my_runner = NULL; };

  std::string dll_name;
  void * user_space_handle;  
  a64simUserSpace::FreeRun *my_runner;
  void (*free_handle)(void *);
};
  
std::vector<struct plugin> user_plugins;


void Load(std::string dll_file) {
     //std::cout << "[userSpace::Load] dll: '" << dll_file << "'" << std::endl;

     if (dll_file.size() == 0) {
       throw std::runtime_error("User plugin file-path not specified?");
     }
  
     struct plugin next_dll;

     next_dll.dll_name = dll_file;

     // load the plugin...
     
     next_dll.user_space_handle = dlopen(dll_file.c_str(),RTLD_LAZY);
     if (next_dll.user_space_handle) {
       std::cout << "User-space shared library '" << dll_file << "' loaded..." << std::endl;
     } else {
       char tbuf[1024];
       sprintf(tbuf,"Unable to open user plugin '%s'",dll_file.c_str());
       throw std::runtime_error(tbuf);
     }

     
     // get address of routine that returns plugin 'FreeRun' object...
     
     dlerror();

     a64simUserSpace::FreeRun * (*get_handle)();
     
     get_handle = (a64simUserSpace::FreeRun * (*)()) dlsym(next_dll.user_space_handle,"get_freerun_handle");

     const char *dlsym_error = dlerror();

     if (dlsym_error != NULL) {
       char tbuf[1024];
       sprintf(tbuf, "User-space plugin 'get_freerun_handle' routine did not load: %s\n",dlsym_error);
       throw std::runtime_error(tbuf);
     }
     if (!get_handle) {
       char tbuf[1024];
       sprintf(tbuf, "User-space 'get_freerun_handle' routine not found\n");
       throw std::runtime_error(tbuf);
     }

     
     // go ahead and call the routine that returns plugin 'FreeRun' object...
     
     next_dll.my_runner = (a64simUserSpace::FreeRun *) (*get_handle)();

     
     // get factory discard symbol...
     
     void (*free_handle)(void *);

     free_handle = (void (*)(void *)) dlsym(next_dll.user_space_handle,"discard_freerun_handle");

     dlsym_error = dlerror();
     
     if (dlsym_error != NULL) {
       char tbuf[1024];
       sprintf(tbuf, "User-space plugin 'discard_freerun_handle' routine did not load: %s\n",dlsym_error);
       throw std::runtime_error(tbuf);
     }
     if (!get_handle) {
       char tbuf[1024];
       sprintf(tbuf, "User-space plugin 'get_freerun_handle' routine not found: %s\n",dlsym_error);
       throw std::runtime_error(tbuf);
     }
     
     next_dll.free_handle = free_handle;

     
     // this plugin seems okay...
     
     user_plugins.push_back(next_dll);
}


void Unload() {
  for (std::vector<struct plugin>::iterator i = user_plugins.begin(); i != user_plugins.end(); i++) {
     (*i).free_handle((*i).my_runner);
     dlclose((*i).user_space_handle);
     std::cout << "User-space shared library '" << (*i).dll_name << "' closed." << std::endl;
  }

  user_plugins.erase(user_plugins.begin(),user_plugins.end());
}

  
int Init(State *cpus, int num_cores, std::string cmdline_options) {
  int rcode = 1;
  
  for (std::vector<struct plugin>::iterator i = user_plugins.begin(); i != user_plugins.end(); i++) {
    if ((*i).my_runner->Init(cpus,num_cores,cmdline_options)) {
       // each plugin Init methos that fails, causes plugin 'traverse' to end...
       rcode = 0;
       break;
    }
  }

  return rcode;
}

  
int FreerunStep(State *cpu,Memory *memory,Packet *ipacket,bool first_time, bool last_time) {
  UserSpace::outcome my_outcome = FREERUNSTEP;

  for (std::vector<struct plugin>::iterator i = user_plugins.begin(); i != user_plugins.end(); i++) {
    my_outcome = (UserSpace::outcome) (*i).my_runner->PreStep(cpu,memory,ipacket,first_time,last_time);
     // each plugin can cause plugin 'traverse' to end, or allow same to continue...
     // in effect, 1st plugin that doesn't return CONTINUE takes ownership
     if (my_outcome != CONTINUE)
       break;
  }

  if (my_outcome == CONTINUE)
    my_outcome = FREERUNSTEP;
  
  return my_outcome;
}

  
int PostStep(State *cpu, Memory *memory, Packet *ipacket, int step_result) {
  UserSpace::outcome my_outcome = SUCCESS;
  
  for (std::vector<struct plugin>::iterator i = user_plugins.begin(); i != user_plugins.end(); i++) {
    my_outcome = (UserSpace::outcome) (*i).my_runner->PostStep(cpu, memory, ipacket, (a64simUserSpace::FreeRun::STEP_RESULT) step_result);
     // each plugin can cause plugin 'traverse' to end, or allow same to continue...
     // in effect, 1st plugin that doesn't return CONTINUE takes ownership
     if (my_outcome != CONTINUE)
       break;
  }
  
  if (my_outcome == CONTINUE)
    my_outcome = SUCCESS;
  
  return my_outcome;
}


int MapAddress(State *cpu,Packet *packet,Memory *memory,unsigned long long LA,
		  bool is_data,bool is_privileged,bool is_write,int number_of_bytes) {
  int rcode = 1;
  
  for (std::vector<struct plugin>::iterator i = user_plugins.begin(); i != user_plugins.end(); i++) {
     rcode = (*i).my_runner->MapAddress(cpu,packet,memory,LA,is_data,is_privileged,is_write,number_of_bytes);
     // each plugin can cause plugin 'traverse' to end, or allow same to continue...
     if (rcode != 1)
       break;
  }

  return rcode;
}


}
