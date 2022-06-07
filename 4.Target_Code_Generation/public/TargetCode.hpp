#include <string.h>
#include <string>
#include <stack>
#include <algorithm>

#include "Symbol.hpp"
#include "IntermediateCode.hpp"

extern std::vector<Quad*> Quads;
unsigned int currProcessedQuad;

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
        return "size";
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
    IF_EQ_OP,
    IF_NOTEQ_OP,
    IF_LESSEQ_OP,
    IF_GREATEREQ_OP,
    IF_LESS_OP,
    IF_GREATER_OP,
    AND_OP,
    NOT_OP,
    OR_OP,
    JUMP_OP,
    CALLFUNC_OP,
    PUSHARG_OP,
    ENTERFUNC_OP,
    FUNCEND_OP,
    TABLECREATE_OP,
    TABLEGETELEM_OP,
    TABLESETELEM_OP,
    NOP_OP
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

std::vector<Instruction> instructions{};
std::vector<double> const_numbers{};
std::vector<std::string> const_strings{};
std::vector<Symbol*> userfunctions{};
std::vector<std::string> libfuncs_used{};

typedef void (*generator_func_t)(Quad* q);

extern unsigned int programVarOffset;
extern unsigned int functionLocalOffset;
extern unsigned int formalArgOffset;
extern unsigned int scopeSpaceCounter;



unsigned int consts_newstring(std::string s) { //TODO rename function
    auto it = std::find(const_strings.begin(), const_strings.end(), s);
    if (it == const_strings.end()) {
        const_strings.push_back(s);
        return const_strings.size() - 1;
    }
    else {
        return it - const_strings.begin();
    }
}

unsigned int consts_newnumber(double n) { //TODO: RENAME
    auto it = std::find(const_numbers.begin(), const_numbers.end(), n);
    if (it == const_numbers.end()) {
        const_numbers.push_back(n);
        return const_numbers.size() - 1;
    }
    else {
        return it - const_numbers.begin();
    }
}


unsigned int libfuncs_newused(std::string s) {
    auto it = std::find(libfuncs_used.begin(), libfuncs_used.end(), s);
    if (it == libfuncs_used.end()) {
        libfuncs_used.push_back(s);
        return libfuncs_used.size() - 1;
    }
    else {
        return it - libfuncs_used.begin();
    }
}

unsigned int userfuncs_newfunc(Symbol* sym) {
    for (auto it = userfunctions.begin(); it != userfunctions.end(); it++) {
        if ((*it)->getId() == sym->getId() && (*it)->get_taddress() == sym->get_taddress())
            return it - userfunctions.begin();
    }
    userfunctions.push_back(sym);
    return userfunctions.size() - 1;
}

VMarg make_operand(Expr* e) {
    VMarg vmarg{};

    if (!e) {
        vmarg.type = UNDEFINED_T;
        vmarg.val = 0;
        return vmarg;
    }

    switch (e->type) {
    case ASSIGN_EXPR:
    case VAR_EXPR:
    case TABLE_ITEM_EXPR:
    case ARITHMETIC_EXPR:
    case BOOLEAN_EXPR:
    case NEW_TABLE_EXPR:
        assert(e->symbol);

        vmarg.val = e->symbol->getOffset();

        switch (e->symbol->getScopespace()) {
        case PROGRAM_VAR:
            vmarg.type = GLOBAL_T;
            break;
        case FUNCTION_LOCAL:
            vmarg.type = LOCAL_T;
            break;
        case FORMAL_ARG:
            vmarg.type = FORMAL_T;
            break;
        default:
            assert(0);
        }
        break;
    case CONST_BOOLEAN_EXPR:
        vmarg.val = std::get<bool>(e->value);
        vmarg.type = BOOL_T;
        break;
    case CONST_STRING_EXPR:
        vmarg.val = consts_newstring(std::get<std::string>(e->value));
        vmarg.type = STRING_T;
        break;
    case CONST_REAL_EXPR:
        vmarg.val = consts_newnumber(std::get<double>(e->value));
        vmarg.type = NUMBER_T;
        break;
    case NIL_EXPR:
        vmarg.type = NIL_T;
        break;
    case USERFUNCTION_EXPR:
        vmarg.type = USERFUNC_T;
        vmarg.val = userfuncs_newfunc(e->symbol);
        break;
    case LIBRARYFUNCTION_EXPR:
        vmarg.type = LIBFUNC_T;
        vmarg.val = libfuncs_newused(e->symbol->getId());
        break;
    default:
        assert(0);
    }

    return vmarg;
}

VMarg make_retvaloperand() {
    VMarg arg;
    arg.type = RETVAL_T;
    arg.val = 0;

    return arg;
}

void  emit_t(Instruction instr) {
    instructions.push_back(instr);
}

void generate(VMopcode op, Quad* quad) {
    Instruction t{};
    t.srcLine = quad->line;
    t.opcode = op;
    t.arg1 = make_operand(quad->arg1);
    t.arg2 = make_operand(quad->arg2);
    if (op >= IF_EQ_OP && op <= IF_GREATER_OP) {
        t.result.type = LABEL_T;
        t.result.val = quad->label;
    }
    else
        t.result = make_operand(quad->result);

    emit_t(t);
}

// void generate_relational(VMopcode op, Quad* quad) {
//     Instruction t{};
//     t.srcLine = quad->line;
//     t.opcode = op;
//     t.arg1 = make_operand(quad->arg1);
//     t.arg2 = make_operand(quad->arg2);
//     t.result.type = LABEL_T;
//     if (quad->label < currProcessedQuad)
//         t.result.val = Quads[quad->label].taddress;
//     else
// }

void generate_ADD(Quad* q) { generate(ADD_OP, q); }

void generate_SUB(Quad* q) { generate(SUB_OP, q); }

void generate_MUL(Quad* q) { generate(MUL_OP, q); }

void generate_DIV(Quad* q) { generate(DIV_OP, q); }

void generate_UMINUS(Quad* q) {
    q->arg2 = newDoubleExpr(-1);
    generate(MUL_OP, q);
    q->arg2 = NULL;
}

void generate_MOD(Quad* q) { generate(MOD_OP, q); }

void generate_NEWTABLE(Quad* q) { generate(TABLECREATE_OP, q); }

void generate_TABLEGETELEM(Quad* q) { generate(TABLEGETELEM_OP, q); }

void generate_TABLESETELEM(Quad* q) { generate(TABLESETELEM_OP, q); }

void generate_ASSIGN(Quad* q) { generate(ASSIGN_OP, q); }

void generate_NOP(Quad* q) {
    Instruction t{};
    t.opcode = NOP_OP;
    emit_t(t);
}

void generate_JUMP(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = JUMP_OP;
    t.result.type = LABEL_T;
    t.result.val = q->label;
    emit_t(t);
}

void generate_IF_EQ(Quad* q) { generate(IF_EQ_OP, q); }

void generate_NOTEQ(Quad* q) { generate(IF_NOTEQ_OP, q); }

void generate_GREATER(Quad* q) { generate(IF_GREATER_OP, q); }

void generate_GREATEREQ(Quad* q) { generate(IF_GREATEREQ_OP, q); }

void generate_LESS(Quad* q) { generate(IF_LESS_OP, q); }

void generate_LESSEQ(Quad* q) { generate(IF_LESSEQ_OP, q); }

void generate_NOT(Quad* q) { generate(NOT_OP, q); }

void generate_OR(Quad* q) { generate(OR_OP, q); }

void generate_AND(Quad* q) { generate(AND_OP, q); }

void generate_PARAM(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = PUSHARG_OP;
    t.arg1 = make_operand(q->arg1);
    emit_t(t);
}

void generate_CALL(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = CALLFUNC_OP;
    t.arg1 = make_operand(q->arg1);
    emit_t(t);
}

void generate_GETRETVAL(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = ASSIGN_OP;
    t.result = make_operand(q->result);
    t.arg1 = make_retvaloperand();
    emit_t(t);
}

void generate_FUNCSTART(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = ENTERFUNC_OP;
    t.result = make_operand(q->arg1);
    emit_t(t);
}

void generate_RETURN(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = ASSIGN_OP;
    t.result = make_retvaloperand();
    t.arg1 = make_operand(q->arg1);
    emit_t(t);
}

void reset_operand(VMarg* arg) {
    arg->val = 0;
    arg->type = UNDEFINED_T;
}

void generate_FUNCEND(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = FUNCEND_OP;
    t.result = make_operand(q->arg1);
    emit_t(t);
}

generator_func_t generators[] = {
        generate_ASSIGN, generate_ADD, generate_SUB,
        generate_MUL, generate_DIV, generate_MOD,
        generate_UMINUS, generate_AND, generate_OR,
        generate_NOT, generate_IF_EQ, generate_NOTEQ,
        generate_LESSEQ, generate_GREATEREQ, generate_LESS,
        generate_GREATER, generate_JUMP, generate_CALL,
        generate_PARAM, generate_RETURN, generate_GETRETVAL,
        generate_FUNCSTART, generate_FUNCEND, generate_NEWTABLE,
        generate_TABLEGETELEM, generate_TABLESETELEM, generate_NOP };

void generate_final_instructions(void) {
    for (currProcessedQuad = 1; currProcessedQuad < Quads.size(); currProcessedQuad++) {
        (*generators[Quads[currProcessedQuad]->opcode]) (Quads[currProcessedQuad]);
    }
}

unsigned int next_instruction_label(void) {
    return instructions.size();
}



void printTargetCode(std::string filename) {
    FILE* file;
    if (filename == "") file = stdout;
    else file = fopen(std::string(filename + ".tc").c_str(), "wb");

    if (!file) {
        printf("File cannot open.\n");
        return;
    }
    fprintf(file, "Instruction#\t\tOpcode\t\tResult\t\tArg1\t\tArg2\n");
    fprintf(file, "===================================================================================\n");

    for (int i = 0; i < instructions.size(); i++) {

        Instruction curr = instructions[i];

        fprintf(file, "%d:\t\t\t%s\t\t%s\t%s\t%s\n", i + 1,
            VMopToString(curr.opcode),
            curr.result.to_string().c_str(),
            curr.arg1.to_string().c_str(),
            curr.arg2.to_string().c_str());
    }
    fprintf(file, "===================================================================================\n");

    if (!const_numbers.empty()) {
        fprintf(file, "\nConst Numbers:\n");
        fprintf(file, "===================================================================================\n");
        for (int i = 0; i < const_numbers.size(); ++i)
            fprintf(file, "%d:\t%s\n", i, remove_extra_zero(modify_number(const_numbers[i])).c_str());
        fprintf(file, "===================================================================================\n");
    }

    if (!const_strings.empty()) {
        fprintf(file, "\nConst Strings:\n");
        fprintf(file, "===================================================================================\n");
        for (int i = 0; i < const_strings.size(); ++i)
            fprintf(file, "%d:\t%s\n", i, const_strings[i].c_str());
        fprintf(file, "===================================================================================\n");
    }

    if (!userfunctions.empty()) {
        fprintf(file, "\nUser Functions:\n");
        fprintf(file, "===================================================================================\n");
        for (int i = 0; i < userfunctions.size(); ++i)
            fprintf(file, "%d:\t%s\n", i, userfunctions[i]->getId().c_str());
        fprintf(file, "===================================================================================\n");
    }

    if (!libfuncs_used.empty()) {
        fprintf(file, "\nLibrary Functions:\n");
        fprintf(file, "===================================================================================\n");
        for (int i = 0; i < libfuncs_used.size(); ++i)
            fprintf(file, "%d:\t%s\n", i, libfuncs_used[i].c_str());
        fprintf(file, "===================================================================================\n");
    }
}




void printTargetInBinary(std::string filename) {
    FILE* file;
    if (filename == "") file = stdout;
    else file = fopen(std::string(filename + ".ab").c_str(), "wb");

    unsigned int magicNumber = 340200501;
    fwrite(&magicNumber, sizeof(magicNumber), 1, file);

    if (!const_strings.empty()) {
        unsigned int size = const_strings.size();
        fwrite(&size, sizeof(size), 1, file);
        for (int i = 0; i < size; ++i) {
            const char* string = const_strings[i].c_str();
            fwrite(string, sizeof(char), strlen(string) + 1, file);
        }
    }
    else {
        unsigned int size = 0;
        fwrite(&size, sizeof(size), 1, file);
    }

    if (!const_numbers.empty()) {
        unsigned int size = const_numbers.size();
        fwrite(&size, sizeof(size), 1, file);
        for (int i = 0; i < size; ++i) {
            double num = const_numbers[i];
            fwrite(&num, sizeof(double), 1, file);
        }
    }
    else {
        unsigned int size = 0;
        fwrite(&size, sizeof(size), 1, file);
    }

    if (!userfunctions.empty()) {
        unsigned int size = userfunctions.size();
        fwrite(&size, sizeof(size), 1, file);
        for (int i = 0; i < size; ++i) {
            unsigned int address = userfunctions[i]->get_taddress();
            unsigned int localsize = userfunctions[i]->getOffset();
            const char* id = userfunctions[i]->getId().c_str();
            fwrite(&address, sizeof(unsigned int), 1, file);
            fwrite(&localsize, sizeof(unsigned int), 1, file);
            fwrite(id, sizeof(char), strlen(id) + 1, file);
        }
    }
    else {
        unsigned int size = 0;
        fwrite(&size, sizeof(size), 1, file);
    }

    if (!libfuncs_used.empty()) {
        unsigned int size = libfuncs_used.size();
        fwrite(&size, sizeof(size), 1, file);
        for (int i = 0; i < size; ++i) {
            const char* id = libfuncs_used[i].c_str();
            fwrite(id, sizeof(char), strlen(id) + 1, file);
        }
    }
    else {
        unsigned int size = 0;
        fwrite(&size, sizeof(size), 1, file);
    }

    if (!instructions.empty()) {
        unsigned int size = instructions.size();
        fwrite(&size, sizeof(size), 1, file);
        for (int i = 0; i < size; ++i) {
            const char* opcode = VMopToString(instructions[i].opcode);
            const char* result_type = VMtypeToString(instructions[i].result.type).c_str();
            unsigned int result_val = instructions[i].result.val;
            const char* arg1_type = VMtypeToString(instructions[i].arg1.type).c_str();
            unsigned int arg1_val = instructions[i].arg1.val;
            const char* arg2_type = VMtypeToString(instructions[i].arg2.type).c_str();
            unsigned int arg2_val = instructions[i].arg2.val;
            unsigned int srcLine = instructions[i].srcLine;
            fwrite(opcode, sizeof(char), 1, file);
            fwrite(result_type, sizeof(char), 1, file);
            fwrite(&result_val, sizeof(unsigned int), 1, file);
            fwrite(arg1_type, sizeof(char), 1, file);
            fwrite(&arg1_val, sizeof(unsigned int), 1, file);
            fwrite(arg2_type, sizeof(char), 1, file);
            fwrite(&arg2_val, sizeof(unsigned int), 1, file);
            fwrite(&srcLine, sizeof(int), 1, file);
        }
    }
    else {
        unsigned int size = 0;
        fwrite(&size, sizeof(size), 1, file);
    }
    return;
}
