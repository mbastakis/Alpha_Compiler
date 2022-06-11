#ifndef FUNCS_EXEC
#define FUNCS_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"

extern void execute_call(Instruction*);
extern void execute_pusharg(Instruction*);
extern void execute_funcenter(Instruction*);
extern void execute_funcexit(Instruction*);

extern char* avm_tostring(avm_memcell*);
extern void avm_calllibfunc(char* funName);
extern void avm_callsaveEnvironment();
//extern userFunc* avm_getfuncinfo (unsigned address);

unsigned totalActuals = 0;

void avm_dec_top() {
    if (!top) { //Stack overflow
        //avm_error("stack overflow");
        executionFinished = 1;
    } else --top;
}

void avm_push_envValue (unsigned int val) {
    stack[top].type = NUMBER_M;
    stack[top].data = val;
    avm_dec_top();
}

void avm_callsaveEnvironment() {
    avm_push_envValue(totalActuals);
    avm_push_envValue(pc + 1);
    avm_push_envValue(top + totalActuals +2);
    avm_push_envValue(topsp);
}

void execute_call(Instruction * instr) {
    avm_memcell* func = avm.avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveEnvironment();

    switch (func->type) {
        case USERFUNC_M: {
            //pc = func->data;
            assert(pc < codeSize); 
            assert(code[pc].opcode == ENTERFUNC_OP);
            break;
        } case STRING_M: {
            //avm_calllibfunc(func->data);
            break;
        } case LIBFUNC_M: {
            //avm_calllibfunc(func->data);
            break;
        }
        default: {
            //char* s = avm_tostring(func);
            std::cout << "Call: cannot bind the argument to a function." << std::endl;  //avm_error
            //free(s);
            executionFinished = 1;
            break;
        }

        
    }
}

void execute_pusharg(Instruction * instr) {

}

void execute_funcenter(Instruction * instr) {
    avm_memcell* func = avm.avm_translate_operand(&instr->result, &ax);
    assert(func);
    //assert(pc == func->data); //Func address should match PC.

    //Callee actions here.
    totalActuals = 0;
    /*userFunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;*/
}

void execute_funcexit(Instruction * instr) {

}

#endif