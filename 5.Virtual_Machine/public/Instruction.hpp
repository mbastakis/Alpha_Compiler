#ifndef INSTRUCTION
#define INSTRUCTION

#include <cassert>
#include <string>

typedef enum {
    LABEL_T = 0,
    GLOBAL_T,
    FORMAL_T,
    LOCAL_T,
    NUMBER_T,
    STRING_T,
    BOOL_T,
    NIL_T,
    USERFUNC_T,
    LIBFUNC_T,
    RETVAL_T,
    UNDEFINED_T
} VMarg_T;

std::string VMtypeToString(VMarg_T type) {
    switch (type) {
    case LABEL_T:
        return "label";
    case GLOBAL_T:
        return "global";
    case FORMAL_T:
        return "formal";
    case LOCAL_T:
        return "local";
    case NUMBER_T:
        return "number";
    case STRING_T:
        return "string";
    case BOOL_T:
        return "bool";
    case NIL_T:
        return "nil";
    case USERFUNC_T:
        return "userfunc";
    case LIBFUNC_T:
        return "libfunc";
    case RETVAL_T:
        return "retval";
    case UNDEFINED_T:
        return "undefined";
    default:
        assert(0);
    }
}

typedef enum {
    ASSIGN_OP = 0,
    ADD_OP,
    SUB_OP,
    MUL_OP,
    DIV_OP,
    MOD_OP,
    UMINUS_OP,
    AND_OP,
    OR_OP,
    NOT_OP,
    IF_EQ_OP,
    IF_NOTEQ_OP,
    IF_LESSEQ_OP,
    IF_GREATEREQ_OP,
    IF_LESS_OP,
    IF_GREATER_OP,
    CALLFUNC_OP,
    PUSHARG_OP,
    ENTERFUNC_OP,
    FUNCEND_OP,
    TABLECREATE_OP,
    TABLEGETELEM_OP,
    TABLESETELEM_OP,
    NOP_OP,
    JUMP_OP
} VMopcode;

const char* VMopToString(VMopcode op) {
    switch (op) {
    case ASSIGN_OP:
        return "assign";
    case ADD_OP:
        return "add";
    case SUB_OP:
        return "sub";
    case MUL_OP:
        return "mul";
    case DIV_OP:
        return "div";
    case MOD_OP:
        return "mod";
    case UMINUS_OP:
        return "uminus";
    case AND_OP:
        return "and";
    case OR_OP:
        return "or";
    case NOT_OP:
        return "not";
    case IF_EQ_OP:
        return "if_eq";
    case IF_NOTEQ_OP:
        return "if_noteq";
    case IF_LESSEQ_OP:
        return "if_lesseq";
    case IF_GREATEREQ_OP:
        return "if_greatereq";
    case IF_LESS_OP:
        return "if_less";
    case IF_GREATER_OP:
        return "if_greater";
    case CALLFUNC_OP:
        return "call";
    case PUSHARG_OP:
        return "pusharg";
    case ENTERFUNC_OP:
        return "enterfunc";
    case FUNCEND_OP:
        return "exitfunc";
    case TABLECREATE_OP:
        return "tablecreate";
    case TABLEGETELEM_OP:
        return "tablegetelem";
    case TABLESETELEM_OP:
        return "tablesetelem";
    case NOP_OP:
        return "nop";
    case JUMP_OP:
        return "jump";
    default:
        assert(0);
    }
}


typedef struct {
    VMarg_T type;
    unsigned int val;

    std::string to_string() {
        if (this->type == UNDEFINED_T)
            return "";
        if (this->type == RETVAL_T)
            return std::to_string(this->type) + "(" + VMtypeToString(this->type) + ")";
        else
            return std::to_string(this->type) + "(" + VMtypeToString(this->type) + ")," + std::to_string(this->val);
    }
} VMarg;

class Instruction {
public:
    VMopcode opcode;
    VMarg result;
    VMarg arg1;
    VMarg arg2;
    int srcLine;

    Instruction() {
        opcode = NOP_OP;
        result.type = UNDEFINED_T;
        result.val = 0;
        arg1.type = UNDEFINED_T;
        arg1.val = 0;
        arg2.type = UNDEFINED_T;
        arg2.val = 0;
    }
};

#endif