#ifndef JUMPS_EXEC
#define JUMPS_EXEC

#include "Instruction.hpp"
#include "AVM.hpp"

typedef unsigned char (*tobool_func_t)(avm_memcell*); //unsigned int?

unsigned char number_tobool (avm_memcell* m) { return 0;}//return m->data != 0;}
unsigned char string_tobool (avm_memcell* m) { return 0;}//return m->data[0] != 0; }
unsigned char bool_tobool (avm_memcell* m) { return 0;}//return m->data; }
unsigned char table_tobool (avm_memcell* m) { return 1; }
unsigned char userfunc_tobool (avm_memcell* m) { return 1; }
unsigned char libfunc_tobool (avm_memcell* m) { return 1; }
unsigned char nill_tobool (avm_memcell* m) { return 0; }
unsigned char undef_tobool (avm_memcell* m) { assert(0); return 0; }

tobool_func_t toboolFuncs[] = {
    number_tobool, string_tobool, bool_tobool, 
    table_tobool, userfunc_tobool, libfunc_tobool,
    nill_tobool, undef_tobool
};

unsigned char avm_tobool (avm_memcell* m) {
    assert(m->type >= 0 && m->type < UNDEFINED_M);
    return (*toboolFuncs[m->type]) (m);
}

std::string typeStrings[] = { "number", "string", "bool", "table",
                             "userfunc", "ibfunc", "nill", "undef"};

extern void execute_jeq(Instruction*);
extern void execute_jne(Instruction*);
extern void execute_jle(Instruction*);
extern void execute_jge(Instruction*);
extern void execute_jlt(Instruction*);
extern void execute_jgt(Instruction*);

void execute_jeq(Instruction * instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    } else if(rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    } else if(rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: "+ typeStrings[rv2->type] +")." << std::endl; //avm_error
    } else {
        /*if (rv1->type == NUMBER_M) {
        } else if (rv1->type == STRING_M) {
        } else if (rv1->type == TABLE_M) {
        } else if (rv1->type == USERFUNC_M) {
        } else if (rv1->type == LIBFUNC_M) {
        }*/
        /*Equality check with dispatching*/
        result = (avm_tobool(rv1) == avm_tobool(rv2)); 
    }

    if(!executionFinished && result)
        pc = instr->result.val;
}

void execute_jne(Instruction * instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    } else if(rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    } else if(rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: "+ typeStrings[rv2->type] +")." << std::endl; //avm_error
    } else {
        /*if (rv1->type == NUMBER_M) {
        } else if (rv1->type == STRING_M) {
        } else if (rv1->type == TABLE_M) {
        } else if (rv1->type == USERFUNC_M) {
        } else if (rv1->type == LIBFUNC_M) {
        }*/
        /*Equality check with dispatching*/
        result = (avm_tobool(rv1) != avm_tobool(rv2)); 
    }

    if(!executionFinished && result)
        pc = instr->result.val;
}

void execute_jle(Instruction * instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    } else if(rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    } else if(rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) <= avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: "+ typeStrings[rv2->type] +")." << std::endl; //avm_error
    } else {
        /*if (rv1->type == NUMBER_M) {
        } else if (rv1->type == STRING_M) {
        } else if (rv1->type == TABLE_M) {
        } else if (rv1->type == USERFUNC_M) {
        } else if (rv1->type == LIBFUNC_M) {
        }*/
        /*Equality check with dispatching*/
        result = (avm_tobool(rv1) <= avm_tobool(rv2)); 
    }

    if(!executionFinished && result)
        pc = instr->result.val;
}

void execute_jge(Instruction * instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    } else if(rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    } else if(rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) >= avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: "+ typeStrings[rv2->type] +")." << std::endl; //avm_error
    } else {
        /*if (rv1->type == NUMBER_M) {
        } else if (rv1->type == STRING_M) {
        } else if (rv1->type == TABLE_M) {
        } else if (rv1->type == USERFUNC_M) {
        } else if (rv1->type == LIBFUNC_M) {
        }*/
        /*Equality check with dispatching*/
        result = (avm_tobool(rv1) >= avm_tobool(rv2)); 
    }

    if(!executionFinished && result)
        pc = instr->result.val;
}

void execute_jlt(Instruction * instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    } else if(rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    } else if(rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) < avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: "+ typeStrings[rv2->type] +")." << std::endl; //avm_error
    } else {
        /*if (rv1->type == NUMBER_M) {
        } else if (rv1->type == STRING_M) {
        } else if (rv1->type == TABLE_M) {
        } else if (rv1->type == USERFUNC_M) {
        } else if (rv1->type == LIBFUNC_M) {
        }*/
        /*Equality check with dispatching*/
        result = (avm_tobool(rv1) < avm_tobool(rv2)); 
    }

    if(!executionFinished && result)
        pc = instr->result.val;
}

void execute_jgt(Instruction * instr) {
    assert(instr->result.type == LABEL_T);

    avm_memcell* rv1 = avm.avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm.avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == UNDEFINED_M || rv2->type == UNDEFINED_M) {
        std::cout << "Undefined involved in equality." << std::endl;  //avm_error
    } else if(rv1->type == NIL_M || rv2->type == NIL_M) {
        result = rv1->type == NIL_M && rv2->type == NIL_M;
    } else if(rv1->type == BOOL_M || rv2->type == BOOL_M) {
        result = (avm_tobool(rv1) > avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        std::cout << "The compare can not be done because the types are diffirent (arg1: " + typeStrings[rv1->type] + " and arg2: "+ typeStrings[rv2->type] +")." << std::endl; //avm_error
    } else {
        /*if (rv1->type == NUMBER_M) {
        } else if (rv1->type == STRING_M) {
        } else if (rv1->type == TABLE_M) {
        } else if (rv1->type == USERFUNC_M) {
        } else if (rv1->type == LIBFUNC_M) {
        }*/
        /*Equality check with dispatching*/
        result = (avm_tobool(rv1) > avm_tobool(rv2)); 
    }

    if(!executionFinished && result)
        pc = instr->result.val;
}

#endif