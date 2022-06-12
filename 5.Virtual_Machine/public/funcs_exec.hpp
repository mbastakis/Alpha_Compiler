#ifndef FUNCS_EXEC
#define FUNCS_EXEC

#include "global_def.hpp"

extern unsigned int totalActuals;
extern unsigned int pc;
extern unsigned int codeSize;
extern avm_memcell ax;

extern char* avm_tostring(avm_memcell*);
extern void avm_callsaveEnvironment();
//extern userFunc* avm_getfuncinfo (unsigned address);
extern void avm_assign(avm_memcell*, avm_memcell*);

void avm_dec_top() {
    if (!top) { //Stack overflow
        //avm_error("stack overflow");
        std::cout << "Stack Overflow" << std::endl;
        executionFinished = 1;
    }
    else --top;
}

void avm_push_envValue(unsigned int val) {
    stack[top].type = NUMBER_M;
    stack[top].data = val;
    avm_dec_top();
}

void avm_callsaveEnvironment() {
    avm_push_envValue(totalActuals);
    avm_push_envValue(pc + 1);
    avm_push_envValue(top + totalActuals + 2);
    avm_push_envValue(topsp);
}

unsigned int avm_get_envvalue(unsigned int i) {
    assert(stack[i].type == NUMBER_M);
    unsigned int val = (unsigned int)std::get<double>(stack[i].data);
    assert(std::get<unsigned int>(stack[i].data) == val);
    return val;
}

void execute_call(Instruction* instr) {
    avm_memcell* func = avm.avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveEnvironment();

    switch (func->type) {
    case USERFUNC_M: {
        pc = std::get<unsigned int>(func->data);
        assert(pc < codeSize);
        assert(code[pc].opcode == ENTERFUNC_OP);
        break;
    }
    case STRING_M:
    case LIBFUNC_M: {
        avm.callLibFunc(std::get<std::string>(func->data));
        break;
    }
    default: {
        std::cout << "Call: cannot bind " << func->to_string() << " to a function." << std::endl;  //avm_error
        executionFinished = 1;
    }
    }
}

void execute_pusharg(Instruction* instr) {
    avm_memcell* arg1 = avm.avm_translate_operand(&instr->arg1, &ax);
    assert(arg1);

    avm_assign(&stack[top], arg1);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter(Instruction* instr) {
    avm_memcell* func = avm.avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == std::get<unsigned int>(func->data)); //Func address should match PC.

    //Callee actions here.
    totalActuals = 0;
    topsp = top;
    top = top - avm.getUserFunction(pc).localSize;
}

void execute_funcexit(Instruction* instr) {
    unsigned int oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while (++oldTop <= top)
        stack[oldTop].avm_memcellclear();
}

void AVM::callLibFunc(std::string libfuncName) {
    // func is the library function
    if (libfuncs_map.find(libfuncName) == libfuncs_map.end()) {
        std::cout << "Unsupported lib function: " << libfuncName << " called!";
        executionFinished = 1;
        return;
    }
    auto func = libfuncs_map[libfuncName];
    topsp = top;
    totalActuals = 0;
    func();
    if (!executionFinished)
        execute_funcexit(NULL);
}

#endif