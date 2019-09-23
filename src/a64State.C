#include <stdexcept>
#include <ctype.h>
#include "a64sim.h"

#include <A64SIMREG_ENUMS.h>

void State::Init() {
#include <A64SIMREG_INITS.C>
}

int State::RegNameIndex(std::string _register_name) {
  // use 'unadorned' reg-name...
  
  if (all_supported_registers.find(_register_name) != all_supported_registers.end()) {
    return all_supported_registers[_register_name];
  }

  // hmmm. convert to upper case and try again...
  
  char tbuf[_register_name.size() + 1];
  strcpy(tbuf,_register_name.c_str());
  for (unsigned int i = 0; i < _register_name.size(); i++) {
    tbuf[i] = toupper(tbuf[i]);
  }
  std::string register_name = tbuf;

  if (all_supported_registers.find(register_name) != all_supported_registers.end()) {
    return all_supported_registers[register_name];
  }

  // oops...
  
  throw std::runtime_error("Unrecognized register name: '" + register_name + "'");
  return -1;
}

void State::InitializeRegister(std::string &rname,unsigned long long rval, unsigned long long rval_hi) {
  int reg_id = RegNameIndex(rname);

  switch(reg_id) {
#include <A64SIMREG_CASES.C>
    default: break;
  } 
}

void State::ReserveAppRegister(std::string &rname) {
  int reg_id = RegNameIndex(rname);

  switch(reg_id) {
#include <A64SIMREG_RESERVE_CASES.C>
    default: break;
  } 
}

int State::WriteResource(std::string &rname,unsigned long long rval, unsigned long long rval_hi) {
  int rcode = 0;
  
  try {
    InitializeRegister(rname,rval,rval_hi);
  } catch(...) {
    // unrecognized resource...
    rcode = -1;
  }
  
  return rcode;
}

int State::ReadResource(std::string &rname,unsigned long long &rval, unsigned long long &rval_hi) {
  int rcode = 0;

  try {
    int reg_id = RegNameIndex(rname);
    
    switch(reg_id) {
#include <A64SIMREG_ACCESS_CASES.C>
      default: break;
    }
  } catch(...) {
    // unrecognized resource...
    rcode = -1;
  }
  
  return rcode;
}


