#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a64sim.h"
#include "a64_instr_enums.h"
#include "disasm_utils.h"

//==========================================================================================
// disassembly can be done after instruction has been decoded...
//==========================================================================================

void Control::Disassemble(char *tbuf) { 
   unsigned long long tmask;

   strcpy(tbuf,"?");

   if (packet->sf.IsDefined()) {
      // packet/dsize is used by execute method, but is also needed for disassembly
      packet->setDsize( packet->sf.Value()==1 ? 64 : 32 );
   }

   // most assembly is auto-generated, but there are hand-crafted cases too. check these first...

   bool have_hc_case = false;

   switch(packet->A64InstrIndex)  {
#include "disasm_include_code_hc.C"
      default: break;
   }

   if (have_hc_case) {
      // hand-crafted assembly case exists for this instruction...
      return;
   }

   // look thru auto-generated assembly...

   switch(packet->A64InstrIndex)  {
#include "disasm_include_code.C"
      default: strcpy(tbuf,"INVALID DISASSEMBLY CASE\n");
               throw INTERNAL_ERROR;
               break;
  }
}
