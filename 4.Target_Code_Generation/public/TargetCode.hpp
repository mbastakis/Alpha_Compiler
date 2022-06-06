#include <string.h>
#include <string>
#include <stack>
#include <algorithm>

#include "Symbol.hpp"
#include "IntermediateCode.hpp"

extern std::vector<Quad*> Quads;
unsigned int currProcessedQuad;

//--------------------------
typedef enum {
    label_a = 0,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a,
    undefined_a
} VMarg_T;

typedef enum {
    assign_op = 0,
    add_op,
    sub_op,
    mul_op,
    div__op,
    mod_op,
    if_eq_op,
    if_noteq_op,
    if_lesseq_op,
    if_greatereq_op,
    if_less_op,
    if_greater_op,
    and_op,
    not_op,
    or_op,
    jump_op,
    callfunc_op,
    pusharg_op,
    enterfunc_op,
    funcend_op,
    tablecreate_op,
    tablegetelem_op,
    tablesetelem_op,
    nop_op
} VMopcode;

std::string vmtype_to_string(VMarg_T);

typedef struct {
    VMarg_T type;
    unsigned int val;

    std::string to_string() {
        if (this->type == undefined_a)
            return "";
        if (this->type == retval_a)
            return std::to_string(this->type) + "(" + vmtype_to_string(this->type) + ")";
        else
            return std::to_string(this->type) + "(" + vmtype_to_string(this->type) + ")," + std::to_string(this->type == label_a ? this->val + 1 : this->val);
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
        opcode = nop_op;
        result.type = undefined_a;
        result.val = 0;
        arg1.type = undefined_a;
        arg1.val = 0;
        arg2.type = undefined_a;
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
        vmarg.type = undefined_a;
        vmarg.val = 0;
        return vmarg;
    }

    switch (e->type) {
        /* all those below use a var for storage */
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
            vmarg.type = global_a;
            break;
        case FUNCTION_LOCAL:
            vmarg.type = local_a;
            break;
        case FORMAL_ARG:
            vmarg.type = formal_a;
            break;
        default:
            assert(0);
        }
        break; /* from case new_table_e */
    case CONST_BOOLEAN_EXPR:
        vmarg.val = std::get<bool>(e->value);
        vmarg.type = bool_a;
        break;
    case CONST_STRING_EXPR:
        vmarg.val = consts_newstring(std::get<std::string>(e->value));
        vmarg.type = string_a;
        break;
    case CONST_REAL_EXPR: //was const_num_e before, check if it is ok with integers. 
        vmarg.val = consts_newnumber(std::get<double>(e->value));
        vmarg.type = number_a;
        break;
    case NIL_EXPR:
        vmarg.type = nil_a;
        break;
    case USERFUNCTION_EXPR:
        vmarg.type = userfunc_a;
        vmarg.val = userfuncs_newfunc(e->symbol);
        break;
    case LIBRARYFUNCTION_EXPR:
        vmarg.type = libfunc_a;
        vmarg.val = libfuncs_newused(e->symbol->getId());
        break;
    default:
        assert(0);
    }

    return vmarg;
}


void make_numberoperand(VMarg* arg, double val) {
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(VMarg* arg, unsigned int val) {
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(VMarg* arg) { arg->type = retval_a; }

void  emit_t(Instruction instr) {
    instructions.push_back(instr);
}

void generate(VMopcode op, Quad* quad) {
    Instruction t{};
    t.srcLine = quad->line;
    t.opcode = op;
    t.arg1 = make_operand(quad->arg1);
    t.arg2 = make_operand(quad->arg2);
    if (op >= if_eq_op && op <= if_greater_op) {
        t.result.type = label_a;
        t.result.val = quad->label;
    }
    else
        t.result = make_operand(quad->result);

    emit_t(t);
}

void generate_relational(VMopcode op, Quad* quad) {
    Instruction t{};
    t.srcLine = quad->line;
    t.opcode = op;
    t.arg1 = make_operand(quad->arg1);
    t.arg2 = make_operand(quad->arg2);
    t.result.type = label_a;
    if (quad->label < currProcessedQuad)
        t.result.val = Quads[quad->label].taddress;
    else
        

}

void generate_ADD(Quad* q) { generate(add_op, q); }

void generate_SUB(Quad* q) { generate(sub_op, q); }

void generate_MUL(Quad* q) { generate(mul_op, q); }

void generate_DIV(Quad* q) { generate(div__op, q); }

void generate_UMINUS(Quad* q) {
    q->arg2 = newDoubleExpr(-1); //TODO: check if it is ok with double (instead of int ->newExprConstNum)
    generate(mul_op, q);
    q->arg2 = NULL;
}

void generate_MOD(Quad* q) { generate(mod_op, q); }

void generate_NEWTABLE(Quad* q) { generate(tablecreate_op, q); }

void generate_TABLEGETELEM(Quad* q) { generate(tablegetelem_op, q); }

void generate_TABLESETELEM(Quad* q) { generate(tablesetelem_op, q); }

void generate_ASSIGN(Quad* q) { generate(assign_op, q); }

void generate_NOP(Quad* q) {
    Instruction t{};
    t.opcode = nop_op;
    emit_t(t);
}

void generate_JUMP(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = jump_op;
    t.result.type = label_a;
    t.result.val = q->label;
    emit_t(t);
}

void generate_IF_EQ(Quad* q) { generate(if_eq_op, q); }

void generate_NOTEQ(Quad* q) { generate(if_noteq_op, q); }

void generate_GREATER(Quad* q) { generate(if_greater_op, q); }

void generate_GREATEREQ(Quad* q) { generate(if_greatereq_op, q); }

void generate_LESS(Quad* q) { generate(if_less_op, q); }

void generate_LESSEQ(Quad* q) { generate(if_lesseq_op, q); }

void generate_NOT(Quad* q) { generate(not_op, q); }

void generate_OR(Quad* q) { generate(or_op, q); }

void generate_AND(Quad* q) { generate(and_op, q); }

void generate_PARAM(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = pusharg_op;
    t.arg1 = make_operand(q->arg1);
    emit_t(t);
}

void generate_CALL(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = callfunc_op;
    t.arg1 = make_operand(q->arg1);
    emit_t(t);
}

void generate_GETRETVAL(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = assign_op;
    t.result = make_operand(q->result);
    make_retvaloperand(&t.arg1);
    emit_t(t);
}

void generate_FUNCSTART(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = enterfunc_op;
    t.result = make_operand(q->arg1);
    emit_t(t);
}

void generate_RETURN(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = assign_op;
    make_retvaloperand(&t.result);
    t.arg1 = make_operand(q->result);
    emit_t(t);
}

void reset_operand(VMarg* arg) {
    arg->val = 0;
    arg->type = undefined_a;
}

void generate_FUNCEND(Quad* q) {
    Instruction t{};
    t.srcLine = q->line;
    t.opcode = funcend_op;
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

const char* vmopc_to_string(VMopcode op) {
    switch (op) {
    case assign_op:
        return "assign";
    case add_op:
        return "add";
    case sub_op:
        return "sub";
    case mul_op:
        return "mul";
    case div__op:
        return "div";
    case mod_op:
        return "mod";
    case if_eq_op:
        return "if_eq";
    case if_noteq_op:
        return "if_noteq";
    case if_lesseq_op:
        return "if_lesseq";
    case if_greatereq_op:
        return "if_greatereq";
    case if_less_op:
        return "if_less";
    case if_greater_op:
        return "if_greater";
    case callfunc_op:
        return "call";
    case pusharg_op:
        return "pusharg";
    case enterfunc_op:
        return "enterfunc";
    case funcend_op:
        return "exitfunc";
    case tablecreate_op:
        return "tablecreate";
    case tablegetelem_op:
        return "tablegetelem";
    case tablesetelem_op:
        return "tablesetelem";
    case jump_op:
        return "jump";
    default:
        assert(0);
    }
}

void print_tcode(FILE* fp) {
    unsigned int i;
    if (!fp) {
        printf("File could not be opened!\n");
        return;
    }
    fprintf(fp,
        "Instruction#"
        "          Opcode"
        "          Result"
        "            Arg1"
        "            Arg2\n");
    fprintf(fp,
        "================================================================="
        "===========\n");

    for (i = 0; i < instructions.size(); i++) {

        Instruction curr = instructions[i];
        fprintf(fp, "%d:%27s%16s%16s%16s\n", i + 1,
            vmopc_to_string(curr.opcode), curr.result.to_string().c_str(),
            curr.arg1.to_string().c_str(), curr.arg2.to_string().c_str());
    }

    if (!const_numbers.empty()) {
        fprintf(fp, "\nConst Numbers:\n");
        for (i = 0; i < const_numbers.size(); ++i)
            fprintf(fp, "%d:\t%s\n", i, remove_extra_zero(modify_number(const_numbers[i])).c_str());
        fprintf(
            fp,
            "================================================================="
            "===========\n");
    }

    if (!const_strings.empty()) {
        fprintf(fp, "\nConst Strings:\n");
        for (i = 0; i < const_strings.size(); ++i)
            fprintf(fp, "%d:\t%s\n", i, const_strings[i].c_str());
        fprintf(
            fp,
            "================================================================="
            "===========\n");
    }

    if (!userfunctions.empty()) {
        fprintf(fp, "\nUser Functions:\n");
        for (i = 0; i < userfunctions.size(); ++i)
            fprintf(fp, "%d:\t%s\n", i, userfunctions[i]->getId().c_str());
        fprintf(
            fp,
            "================================================================="
            "===========\n");
    }

    if (!libfuncs_used.empty()) {
        fprintf(fp, "\nLibrary Functions:\n");
        for (i = 0; i < libfuncs_used.size(); ++i)
            fprintf(fp, "%d:\t%s\n", i, libfuncs_used[i].c_str());
        fprintf(
            fp,
            "================================================================="
            "===========\n");
    }
}


std::string vmtype_to_string(VMarg_T type) {
    switch (type) {
    case label_a:
        return "label";
    case global_a:
        return "global";
    case formal_a:
        return "formal";
    case local_a:
        return "local";
    case number_a:
        return "number";
    case string_a:
        return "string";
    case bool_a:
        return "bool";
    case nil_a:
        return "nil";
    case userfunc_a:
        return "userfunc";
    case libfunc_a:
        return "libfunc";
    case retval_a:
        return "retval";
    case undefined_a:
        return "undefined";
    default:
        assert(0);
    }
}

void write_abc(
    FILE* abc_file) {
    unsigned int number, i;

    // Magic number
    unsigned int magic_number = 340200501;
    fwrite(&magic_number, sizeof(magic_number), 1, abc_file);

    // Const strings
    if (!const_strings.empty()) {
        number = const_strings.size();
        fwrite(&number, sizeof(number), 1, abc_file);
        for (i = 0; i < number; ++i) {
            const char* string = const_strings[i].c_str();
            fwrite(string, sizeof(char), strlen(string) + 1, abc_file);
        }
    }
    else {
        number = 0;
        fwrite(&number, sizeof(number), 1, abc_file);
    }

    // Const numbers
    if (!const_numbers.empty()) {
        number = const_numbers.size();
        fwrite(&number, sizeof(number), 1, abc_file);
        for (i = 0; i < number; ++i) {
            double num = const_numbers[i];
            fwrite(&num, sizeof(double), 1, abc_file);
        }
    }
    else {
        number = 0;
        fwrite(&number, sizeof(number), 1, abc_file);
    }

    // User functions
    if (!userfunctions.empty()) {
        number = userfunctions.size();
        fwrite(&number, sizeof(number), 1, abc_file);
        for (i = 0; i < number; ++i) {
            unsigned int address = userfunctions[i]->get_taddress();
            unsigned int localsize = userfunctions[i]->getOffset();
            const char* id = userfunctions[i]->getId().c_str();
            fwrite(&address, sizeof(unsigned int), 1, abc_file);
            fwrite(&localsize, sizeof(unsigned int), 1, abc_file);
            fwrite(id, sizeof(char), strlen(id) + 1, abc_file);
        }
    }
    else {
        number = 0;
        fwrite(&number, sizeof(number), 1, abc_file);
    }

    // Library functions
    if (!libfuncs_used.empty()) {
        number = libfuncs_used.size();
        fwrite(&number, sizeof(number), 1, abc_file);
        for (i = 0; i < number; ++i) {
            const char* id = libfuncs_used[i].c_str();
            fwrite(id, sizeof(char), strlen(id) + 1, abc_file);
        }
    }
    else {
        number = 0;
        fwrite(&number, sizeof(number), 1, abc_file);
    }

    // Instructions (first array of src lines, then actual instructions)
    if (!instructions.empty()) {
        number = instructions.size();
        fwrite(&number, sizeof(number), 1, abc_file);
        for (i = 0; i < number; ++i) {
            int line = instructions[i].srcLine;
            fwrite(&line, sizeof(int), 1, abc_file);
        }
        for (i = 0; i < number; ++i) {
            const char* opcode = vmopc_to_string(instructions[i].opcode);
            const char* result_type = vmtype_to_string(instructions[i].result.type).c_str();
            unsigned int result_val = instructions[i].result.val;
            const char* arg1_type = vmtype_to_string(instructions[i].arg1.type).c_str();
            unsigned int arg1_val = instructions[i].arg1.val;
            const char* arg2_type = vmtype_to_string(instructions[i].arg2.type).c_str();
            unsigned int arg2_val = instructions[i].arg2.val;
            fwrite(opcode, sizeof(char), 1, abc_file);
            fwrite(result_type, sizeof(char), 1, abc_file);
            fwrite(&result_val, sizeof(unsigned int), 1, abc_file);
            fwrite(arg1_type, sizeof(char), 1, abc_file);
            fwrite(&arg1_val, sizeof(unsigned int), 1, abc_file);
            fwrite(arg2_type, sizeof(char), 1, abc_file);
            fwrite(&arg2_val, sizeof(unsigned int), 1, abc_file);
        }
    }
    else {
        number = 0;
        fwrite(&number, sizeof(number), 1, abc_file);
    }
    return;
}
