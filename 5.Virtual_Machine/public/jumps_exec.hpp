#ifndef JUMPS_EXEC
#define JUMPS_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"

typedef unsigned char (*tobool_func_t)(avm_memcell*); //unsign int?

unsigned char number_tobool (avm_memcell* m) { return m->data != 0; }
unsigned char string_tobool (avm_memcell* m) { return m->data[0] != 0; }
unsigned char bool_tobool (avm_memcell* m) { return m->data; }
unsigned char table_tobool (avm_memcell* m) { return 1; }
unsigned char userfunc_tobool (avm_memcell* m) { return 1; }
unsigned char libfunc_tobool (avm_memcell* m) { return 1; }
unsigned char nill_tobool (avm_memcell* m) { return 0; }
unsigned char undef_tobool (avm_memcell* m) { assert(0); return 0; }

tobool_func_t toboolFuncs[] = {
    number_tobool, string_tobool, bool_tobool, 
    table_tobool, userfunc_tobool, libfunc_tobool,
    nill_tobool, undef_tobool
}

unsigned char avm_tobool (avm_memcell* m) {
    assert(m->type >= 0 && m->type < UNDEFINED_M);
    return (*tobool_funcs[m->type]) (m);
}

extern void execute_jeq(Instruction*);
extern void execute_jne(Instruction*);
extern void execute_jle(Instruction*);
extern void execute_jge(Instruction*);
extern void execute_jlt(Instruction*);
extern void execute_jgt(Instruction*);

void execute_jeq(Instruction * instr) {

}

void execute_jne(Instruction * instr) {

}

void execute_jle(Instruction * instr) {

}

void execute_jge(Instruction * instr) {

}

void execute_jlt(Instruction * instr) {

}

void execute_jgt(Instruction * instr) {

}

#endif