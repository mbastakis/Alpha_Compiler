#ifndef FUNCS_EXEC
#define FUNCS_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"

extern void execute_call(Instruction*);
extern void execute_pusharg(Instruction*);
extern void execute_funcenter(Instruction*);
extern void execute_funcexit(Instruction*);

void execute_call(Instruction * instr) {

}

void execute_pusharg(Instruction * instr) {

}

void execute_funcenter(Instruction * instr) {

}

void execute_funcexit(Instruction * instr) {

}

#endif