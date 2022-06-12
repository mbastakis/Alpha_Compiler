#ifndef JUMPS_EXEC
#define JUMPS_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"

typedef bool (*tobool_func_t)(avm_memcell*);

bool number_tobool(avm_memcell* m) { return std::get<double>(m->data) != 0; }
bool string_tobool(avm_memcell* m) { return std::get<std::string>(m->data).empty(); }
bool bool_tobool(avm_memcell* m) { return std::get<bool>(m->data); }
bool table_tobool(avm_memcell* m) { return 1; }
bool userfunc_tobool(avm_memcell* m) { return 1; }
bool libfunc_tobool(avm_memcell* m) { return 1; }
bool nill_tobool(avm_memcell* m) { return 0; }
bool undef_tobool(avm_memcell* m) { assert(0); return 0; }

tobool_func_t toboolFuncs[] = {
    number_tobool, string_tobool, bool_tobool,
    table_tobool, userfunc_tobool, libfunc_tobool,
    nill_tobool, undef_tobool
};

bool avm_tobool(avm_memcell* m) {
    assert(m->type >= 0 && m->type < UNDEFINED_M);
    return (*toboolFuncs[m->type]) (m);
}

std::string typeStrings[] = { "number", "string", "bool", "table",
                             "userfunc", "ibfunc", "nill", "undef" };

extern void execute_jeq(Instruction*);
extern void execute_jne(Instruction*);
extern void execute_jle(Instruction*);
extern void execute_jge(Instruction*);
extern void execute_jlt(Instruction*);
extern void execute_jgt(Instruction*);

void execute_jeq(Instruction* instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    bool result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    }
    else if (rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    }
    else if (rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: " + typeStrings[rv2->type] + ")." << std::endl; //avm_error
    }
    else {
        if (rv1->type == NUMBER_M) {
            result = std::get<double>(rv1->data) == std::get<double>(rv2->data);
        }
        else if (rv1->type == STRING_M) {
            result = std::get<std::string>(rv1->data) == (std::get<std::string>(rv2->data));
        }
        else if (rv1->type == TABLE_M) {
            result = std::get<avm_table*>(rv1->data) == (std::get<avm_table*>(rv2->data));
        }
        else if (rv1->type == USERFUNC_M) {
            result = std::get<unsigned int>(rv1->data) == (std::get<unsigned int>(rv2->data));
        }
        else if (rv1->type == LIBFUNC_M) {
            result = std::get<std::string>(rv1->data) == (std::get<std::string>(rv2->data));
        }
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jne(Instruction* instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    bool result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    }
    else if (rv1->type == NIL_M || rv2->type == NIL_M) {
        result = !(rv1->type == NIL_M && rv2->type == NIL_M);
    }
    else if (rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: " + typeStrings[rv2->type] + ")." << std::endl; //avm_error
    }
    else {
        if (rv1->type == NUMBER_M) {
            result = std::get<double>(rv1->data) != std::get<double>(rv2->data);
        }
        else if (rv1->type == STRING_M) {
            result = std::get<std::string>(rv1->data) != (std::get<std::string>(rv2->data));
        }
        else if (rv1->type == TABLE_M) {
            result = std::get<avm_table*>(rv1->data) != (std::get<avm_table*>(rv2->data));
        }
        else if (rv1->type == USERFUNC_M) {
            result = std::get<unsigned int>(rv1->data) != (std::get<unsigned int>(rv2->data));
        }
        else if (rv1->type == LIBFUNC_M) {
            result = std::get<std::string>(rv1->data) != (std::get<std::string>(rv2->data));
        }
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jle(Instruction* instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    bool result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    }
    else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: " + typeStrings[rv2->type] + ")." << std::endl; //avm_error
    }
    else {
        if (rv1->type == NUMBER_M) {
            result = std::get<double>(rv1->data) <= std::get<double>(rv2->data);
        }
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jge(Instruction* instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    bool result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    }
    else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: " + typeStrings[rv2->type] + ")." << std::endl; //avm_error
    }
    else {
        if (rv1->type == NUMBER_M) {
            result = std::get<double>(rv1->data) >= std::get<double>(rv2->data);
        }
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jlt(Instruction* instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    bool result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    }
    else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: " + typeStrings[rv2->type] + ")." << std::endl; //avm_error
    }
    else {
        if (rv1->type == NUMBER_M) {
            result = std::get<double>(rv1->data) < std::get<double>(rv2->data);
        }
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jgt(Instruction* instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    bool result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    }
    else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: " + typeStrings[rv2->type] + ")." << std::endl; //avm_error
    }
    else {
        if (rv1->type == NUMBER_M) {
            result = std::get<double>(rv1->data) > std::get<double>(rv2->data);
        }
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}




#endif