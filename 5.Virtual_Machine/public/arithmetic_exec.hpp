#ifndef ARITHMETIC_EXEC
#define ARITHMETIC_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"
#include <string.h>

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl (double x, double y) { return x+y; }
double sub_impl (double x, double y) { return x-y; }
double mul_impl (double x, double y) { return x*y; }
double div_impl (double x, double y) { return x/y; }
double mod_impl (double x, double y) { return ((unsigned int) x % (unsigned int) y); }

arithmetic_func_t arithmeticFuncs[] = {
    add_impl, sub_impl, mul_impl, div_impl, mod_impl
};

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

extern void execute_assign(Instruction*);
extern void execute_add(Instruction*);
extern void execute_sub(Instruction*);
extern void execute_mul(Instruction*);
extern void execute_div(Instruction*);
extern void execute_mod(Instruction*);
extern void execute_and(Instruction*);
extern void execute_or(Instruction*);
extern void execute_not(Instruction*);

extern void avm_assign(avm_memcell* lv, avm_memcell* rv);

void execute_arithmetic (Instruction * instr) {
    avm_memcell* lv = avm.avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    assert(&stack[AMV_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval);
    assert(rv1 && rv2);

    if (rv1->type != NUMBER_M || rv2->type != NUMBER_M) {
        std::cout << "Not a number in arithmetic." << std::endl;  //avm_error
        executionFinished = 1;
    } else {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - ADD_OP];
        //avm_memcellclear(lv);
        lv->type = NUMBER_M;
        //lv->data = (*op) (rv1->data, rv2->data);
    }
}

void execute_and(Instruction * instr) {

}

void execute_or(Instruction * instr) {

}

void execute_not(Instruction * instr) {

}

void execute_assign(Instruction * instr) {
    avm_memcell* lv = avm.avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* rv = avm.avm_translate_operand(&instr->arg1, &ax);

    assert(&stack[AMV_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval);
    assert(&stack[AMV_STACKSIZE-1] >= rv && rv > &stack[top] || rv == &retval);
    avm_assign(lv, rv);
}

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
    if (lv == rv) //Same cells? destructive to assign!
        return;

    if (lv->type == TABLE_M && rv->type == TABLE_M && lv->data.index() == rv->data.index()) //Same tables? no need to assign.
        return;

    if (rv->type == UNDEFINED_M) // From undefined r-value? warn!
        std::cout << "Assigning from 'Undefined' content." << std::endl; //avm_warning

    //avm_memcellclear(lv); //Clear old cell contents.

    memcpy(lv, rv, sizeof(avm_memcell));

    //Now take care of copied values or reference counting
    if (lv->type == STRING_M)
        lv->data = rv->data;
    else if (lv->type == TABLE_M) {
        //lv->data->++;
    }

    std::cout << lv->type<< " "<< rv->type << std::endl;
}

#endif