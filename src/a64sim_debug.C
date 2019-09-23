#include "a64sim.h"
#include "a64sim_debug.h"


//****************************************************************************************************
// A64BreakPoint
//****************************************************************************************************

// match on PC, on any instruction phase...

bool A64BreakPoint::MatchOnASID(Packet *pkt) {
  if (!bkpt.has_asid())
    return true;
  for (unsigned int i = 0; i < pkt->translations.size(); i++) {
    if ( (pkt->translations[i])->ASID == (unsigned int) bkpt.asid())
      return true;
  }
  return false;
}

bool A64BreakPoint::MatchOnPC(Packet *pkt) {
  // match on pc logical address...
  bool address_match = bkpt.has_instr_addr_la() && ( (pkt->PC.Value() & bkpt.instr_addr_mask()) == (bkpt.instr_addr_la() & bkpt.instr_addr_mask()) );
  return address_match && MatchOnASID(pkt);
}

bool A64BreakPoint::MatchOnDataAddress(Packet *pkt) {
  // match on data logical address...
  if (!bkpt.has_data_addr_la())
    return false;

  bool address_match = false;

  for (unsigned int i = 0; (i < pkt->mOpsMemory.size()) && !address_match; i++) {
    if ( (pkt->mOpsMemory[i].address & bkpt.data_addr_mask()) == (bkpt.data_addr_la() & bkpt.data_addr_mask()) ) {
      // address match. see if r/w match as well...
      address_match = true;
      if (bkpt.has_read_access())
          address_match &= pkt->mOpsMemory[i].direction == 0;
      if (bkpt.has_write_access())
          address_match &= pkt->mOpsMemory[i].direction == 1;
    }
  }

  return address_match && MatchOnASID(pkt);
}

bool A64BreakPoint::MatchOnPhysicalAddress(Packet *pkt) {
  // match on (instruction or data) physical address...

  bool match_instr_pa = bkpt.has_instr_addr_pa();
  bool match_data_pa  = bkpt.has_data_addr_pa();
  
  if (!(match_instr_pa || match_data_pa))
    return false;

  bool address_match = false;

  for (unsigned int i = 0; (i < pkt->translations.size()) && !address_match; i++) {
    if (match_instr_pa && ((pkt->translations[i])->is_data == false) &&
	(((pkt->translations[i])->PA & bkpt.instr_addr_mask()) == (bkpt.instr_addr_pa() & bkpt.instr_addr_mask())) )
        address_match = true;

    if (match_data_pa && ((pkt->translations[i])->is_data == true) &&
	(((pkt->translations[i])->PA & bkpt.data_addr_mask()) == (bkpt.data_addr_pa() & bkpt.data_addr_mask())) ) {
        address_match = true;
        if (bkpt.has_read_access())
          address_match &= !(pkt->translations[i])->is_write;
        if (bkpt.has_write_access())
          address_match &= (pkt->translations[i])->is_write;
      }
  }

  return address_match;
}

// opcode match on instruction fetch state only...

bool A64BreakPoint::MatchOnOpcode(Packet *pkt) {
  return bkpt.has_opcode() && (pkt->State == FETCH_STATE) && 
         ( (pkt->Opcode & bkpt.opcode_mask()) == (bkpt.opcode() & bkpt.opcode_mask()) );
}

bool A64BreakPoint::MatchOnRegister(Packet *pkt) {
  // register group must be specified...
  if (!bkpt.has_reg_group()) return false;

  bool have_match = false;

  switch((int) bkpt.reg_group()) {
    case 0: // GP register...
    case 1: // SP register...
    case 2: // VFP register - lo order 64 bits only...
    case 3: // ASIMD register - 128 bits...
    case 4: // SPR...
            {
            int reg_type = RegDep::DEP_NONE();
            switch((int) bkpt.reg_group()) {
              case 0: reg_type = DEP_GP;     break; // GP register...
              case 1: reg_type = DEP_SP;     break; // SP (stack) register...
              case 2: reg_type = DEP_FP_DP;  break; // VFP (64 bits) register...
              case 3: reg_type = DEP_ASIMD;  break; // ASIMD register...
              case 4: reg_type = DEP_SPR;    break; // SPR...
              default: break;
            }
            bool check_reg_read  = bkpt.has_read_access() && bkpt.read_access();
            bool check_reg_write = bkpt.has_write_access() && bkpt.write_access();
            bool check_read_or_write = !(check_reg_read || check_reg_write); // if access direction not specified then either will do...
             // register index (as encoded by debug GUI) must match simulator encoded register dependency index...
            if (check_reg_read || check_read_or_write) {
              for (unsigned int i = 0; (i < pkt->srcRegDep.size()) && !have_match; i++) {
		 if (pkt->srcRegDep[i].TYPE()!=reg_type) continue; // type mismatch...
		 if (pkt->srcRegDep[i].ID()!=bkpt.reg_index()) continue; // index mismatch...
                 if (bkpt.has_reg_val() && ( (bkpt.reg_val() & bkpt.rval_mask()) != (pkt->srcRegDep[i].RVAL() & bkpt.rval_mask()) ) )
	           continue; // value mismatch...
                 have_match = true;
	      }
	    }
            if (!have_match && (check_reg_write || check_read_or_write)) {
              for (unsigned int i = 0; (i < pkt->destRegDep.size()) && !have_match; i++) {
	         if (pkt->destRegDep[i].TYPE()!=reg_type) continue;
                 if (pkt->destRegDep[i].ID()!=bkpt.reg_index()) continue;
                 if (bkpt.has_reg_val() && ( (bkpt.reg_val() & bkpt.rval_mask()) != (pkt->destRegDep[i].RVAL() & bkpt.rval_mask()) ) )
	           continue;
                 have_match = true;
	      }
	    }
            }
            break;

    case 5: // change to Pstate AND match on Pstate...
            if (pkt->NextPstate.Value() == pkt->Pstate.Value())
	      break; // Pstate was not updated. ASSUME then we don't care...
            if ( bkpt.has_reg_val() && ( (bkpt.reg_val() & bkpt.rval_mask()) != (pkt->NextPstate.Value() & bkpt.rval_mask()) ) )
              break; // updated Pstate value/mask does not match specified value/mask 
            have_match = true; 
            break;
 
    default: // OOPS!...
            break;
	    }

  return have_match;
}

bool A64BreakPoint::MatchOnException(Packet *pkt) {
  // exception class must be specified...
  if (!bkpt.has_excep_class()) 
    return false;
  // instruction must have caused the specified exception class...
  if (bkpt.excep_class() != pkt->exception_class)
    return false;

  bool have_match = false;

  switch((int) pkt->exception_class) {
    case NO_SIM_EXCEPTION: // no exception occurred...
         break;
    case ARCH_EXCEPTION:
         if (!bkpt.has_excep_type_arch())
	   break; 
         if (bkpt.excep_type_arch() != pkt->exception_type)
           break;
         if (bkpt.has_excep_imm() && (bkpt.excep_imm() != pkt->exception_imm))
           break; 
         have_match = true;
         break;
    case INTERNAL_ERROR:
         have_match = true; // should not get here, so always examine same...
         break;
    case GENERATION_ERROR: // caused by insertion/execution of random instruction...
                           // ASSUMED to be handled same as ARCH_EXCEPTION
         if (!bkpt.has_excep_type_int())
           break;
         if (bkpt.excep_type_int() != pkt->exception_type)
           break;
         if (bkpt.has_excep_imm() && (bkpt.excep_imm() != pkt->exception_imm))
           break; 
         have_match = true;
         break;
    default: break;
  }

  return have_match;
}

bool A64BreakPoint::Match(State *st, Packet *pkt, unsigned long long clock, const int cpuid) {
  if (MatchOnPC(pkt)) return true;
  if (MatchOnOpcode(pkt)) return true;
  if (MatchOnDataAddress(pkt)) return true;
  if (MatchOnPhysicalAddress(pkt)) return true;
  if (MatchOnRegister(pkt)) return true;
  if (MatchOnException(pkt)) return true;
    
  return false;
}

//****************************************************************************************************
// DebugSet
//****************************************************************************************************

void DebugSet::Update(scaffold_SAPI::Acknowledge &ack) {
  // if we got here then at least the cpu ID was specified in the acknowledge message...
  cpuid = ack.cpuid();              // matching cpu ID
  if (ack.step_count() > 0)               
    step_count = ack.step_count();  // NOTE: this is a 'step down' count, ie, gets decremented on each step
                                    //       and should trigger when it hits zero...
  instr_phase = ack.instr_phase();  // NOTE: used in conjunction with step_count

  report_step_updates   = ack.report_step_updates();
  report_memory_updates = ack.report_memory_updates();
  
  if (ack.reset_bkpts()) 
    bkpts.erase(bkpts.begin(),bkpts.end());

  for (int i = 0; i < ack.bkpts_size(); i++) {
     bkpts.push_back(A64BreakPoint(ack.bkpts(i)));
  }
}

bool DebugSet::Match(State *st, Packet *pkt, unsigned long long clock, const int cpuid) {
  // there are conditions for this cpu...

  if ( (instr_phase >= 0) && (pkt->State == instr_phase) ) {
    // match on instruction phase...
    return true;
  }

  if (step_count > 0) {
    // step is non-zero. decrement after each instruction is retired. break when count hits zero...
    if (pkt->State == RETIRE_STATE) {
      //printf("[DebugSet::Match] evaluating step count...\n");
      step_count -= 1;
    }
    if (step_count == 0) { // return true when count goes to zero...
      printf("[DebugSet::Match] breakpoint reached!\n");
      return true;
    }

    //printf("[DebugSet::Match] step count: %d\n",step_count);

    return false;
  }

  // return true if no defined breakpoints...

  if (bkpts.size() == 0)
    return true; // no step count and no breakpoints defined...

  // sequentially look for a matching breakpoint...

  for (unsigned int i = 0; i < bkpts.size(); i++) {
    if (bkpts[i].Match(st,pkt,clock,cpuid))
      return true;
  }

  // there are defined breakpoints but none match...

  return false;
}

//****************************************************************************************************
// DebugManager
//****************************************************************************************************

void DebugManager::UpdateConditions(scaffold_SAPI::Acknowledge &ack) {
  // if the cpu ID was specified in the acknowledge, then we ASSUME there are
  // one or more valid debug conditions...
  if (ack.cpuid() >= 0) {
    //printf("[DebugManager::UpdateConditions] conditions specified for cpu %d...\n",ack.cpuid());
    if (debug_sets.find(ack.cpuid()) == debug_sets.end())
      debug_sets[ack.cpuid()] = DebugSet();
    debug_sets[ack.cpuid()].Update(ack);
  }
}

bool DebugManager::HaveCpuBreakConditions(const int cpuid) {
  return debug_sets.find(cpuid) != debug_sets.end();
}

bool DebugManager::HaveAnyBreakConditions() {
  return debug_sets.size() > 0;
}

bool DebugManager::Report(State *st, Packet *pkt, unsigned long long clock, const int cpuid) {  
  // break (and report) if conditions are met for this cpu...

  if (HaveCpuBreakConditions(cpuid) && debug_sets[cpuid].Match(st,pkt,clock,cpuid))
    return true;

  // no report if there are any breakpoints set...

  return !HaveAnyBreakConditions();
}

// intermediate memory updates reported only if no breakpoints in place...

bool DebugManager::Report(scaffold_SAPI::MemoryAccessDebug &ma) {
  return !HaveAnyBreakConditions();
}
