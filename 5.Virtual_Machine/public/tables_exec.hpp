#ifndef TABLES_EXEC
#define TABLES_EXEC

#include "global_def.hpp"

void execute_newtable(Instruction* instr) {
    avm_memcell* lv = avm.avm_translate_operand(&instr->arg1, NULL);
    // assert(lv && (stack[AVM_STACKSIZE - 1] >= lv && lv > stack[top] || lv == &retval));

    lv->avm_memcellclear();

    lv->type = TABLE_M;
    lv->data = new avm_table();
    std::get<avm_table*>(lv->data)++;
}

void execute_tablegetelem(Instruction* instr) {

    avm_memcell* lv = avm.avm_translate_operand(&instr->result, NULL);
    avm_memcell* t = avm.avm_translate_operand(&instr->arg1, NULL);
    avm_memcell* i = avm.avm_translate_operand(&instr->arg2, &ax);

    // 
    // Asserts
    // 

    lv->avm_memcellclear();
    lv->type = NIL_M;

    if (t->type != TABLE_M) {
        std::cout << "Illegal use of type " << avm_memcell_t_to_string[t->type] << " as table!" << std::endl;
    }
    else {
        avm_memcell* content = std::get<TABLE_M>(t->data)->get(i);
        if (content)
            avm_assign(lv, content);
        else {
            std::cout << t->to_string() << "[" << i->to_string() << "]" << " not found!" << std::endl;
        }
    }
}

void execute_tablesetelem(Instruction* instr) {
    avm_memcell* t = avm.avm_translate_operand(&instr->result, NULL);
    avm_memcell* i = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* c = avm.avm_translate_operand(&instr->arg2, &bx);

    // assert

    if (t->type != TABLE_M)
        std::cout << "Illegal use of type " << avm_memcell_t_to_string[t->type] << " as table!" << std::endl;
    else
        std::get<TABLE_M>(t->data)->set(i, c);
}

void execute_nop(Instruction* instr) {

}

#endif