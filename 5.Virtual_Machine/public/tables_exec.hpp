#ifndef TABLES_EXEC
#define TABLES_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"

extern void execute_newtable(Instruction*);
extern void execute_tablegetelem(Instruction*);
extern void execute_tablesetelem(Instruction*);
extern void execute_nop(Instruction*);

void execute_newtable(Instruction * instr) {

}

void execute_tablegetelem(Instruction * instr) {

}

void execute_tablesetelem(Instruction * instr) {

}

void execute_nop(Instruction * instr) {

}

#endif