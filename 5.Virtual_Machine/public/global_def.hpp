#ifndef GLOBAL_DEF_HPP
#define GLOBAL_DEF_HPP

#define AVM_STACKSIZE 4096  // memory_cell
#define AVM_STACKENV_SIZE 4 // avm

#define AVM_NUMACTUALS_OFFSET +4    // funcs_exec
#define AVM_SAVEDPC_OFFSET +3       // funcs_exec
#define AVM_SAVEDTOP_OFFSET +2      // funcs_exec
#define AVM_SAVEDTOPSP_OFFSET +1    // funcs_exec

#include "helper.hpp"
#include "Instruction.hpp"
#include "Memory_Cell.hpp"
#include "AVM.hpp"
#include "arithmetic_exec.hpp"
#include "funcs_exec.hpp"
#include "jumps_exec.hpp"
#include "tables_exec.hpp"
#include "libfuncs_Impl.hpp"

extern std::vector<avm_memcell> stack;

extern avm_memcell ax, bx, cx, retval;
extern unsigned int top, topsp;
extern unsigned char executionFinished;
extern unsigned int pc;
extern unsigned int currLine;
extern unsigned int codeSize;
unsigned int totalActuals = 0;
extern Instruction* code;
extern AVM avm;



#endif