#ifndef INTERMEDIATECODE_HPP
#define INTERMEDIATECODE_HPP

#include "Symbol.hpp"
#include "SymbolTable.hpp"
#include <variant>
#include <cassert>
#include <vector>

typedef enum {
    OP_ASSIGN,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_UMINUS,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_IF_EQ,
    OP_IF_NOTEQ,
    OP_IF_LESSEQ,
    OP_IF_GREATEQ,
    OP_IF_LESS,
    OP_IF_GREATER,
    OP_JUMP,
    OP_CALL,
    OP_PARAM,
    OP_RET,
    OP_GETRETVAL,
    OP_FUNCSTART,
    OP_FUNCEND,
    OP_TABLECREATE,
    OP_TABLEGETELEM,
    OP_TABLESETELEM
} Opcode;

typedef enum {   //expression type
    CONST_NUMBER_EXPR,
    NUMBER_EXPR,
    CONST_BOOLEAN_EXPR,
    BOOLEAN_EXPR,
    CONST_STRING_EXPR,
    STRING_EXPR,
    NIL_EXPR,
    USERFUNCTION_EXPR,
    LIBRARYFUNCTION_EXPR,
    VAR_EXPR
} Expr_T;

typedef struct {
    Expr_T type;
    Symbol* symbol;
    //Expr* next;
    std::variant<std::string, double, bool> value;
} Expr;

typedef struct {
    Opcode opcode;
    Expr* result;
    Expr* arg1;
    Expr* arg2;
    unsigned int label;
    unsigned int line;
} Quad;

/* Global Variables */
extern std::vector<Quad*> Quads;
extern SymbolTable symtable;
extern unsigned int currentScope; //we never initialize this
extern int yylineno;

extern unsigned int programVarOffset;
extern unsigned int functionLocalOffset;
extern unsigned int formalArgOffset;
extern unsigned int scopeSpaceCounter;
unsigned int tempNameCounter = 1;

void emit(Opcode op, Expr* arg1, Expr* arg2, Expr* result, unsigned int line,
    unsigned int label) {

    Quad* newQuad = new Quad();
    newQuad->arg1 = arg1;
    newQuad->arg2 = arg2;
    newQuad->result = result;
    newQuad->line = line;
    newQuad->label = label;
    newQuad->opcode = op;

    Quads.push_back(newQuad);
}

std::string newTempName() {
    return std::string("$") + std::to_string(tempNameCounter++);
}

void resetTemp() {

    auto symList = symtable.getSymbols(currentScope);
    for (auto it = symList.begin(); it != symList.end(); it++) {  //delete all the temporary symbols from current scope
        std::string id = (*it)->getId();
        if (id[0] == '$') symtable.removeSymbol(id, currentScope);
    }

    tempNameCounter = 1;
}

//for creating a new temporary variable
Symbol* newTempSymbol() {
    std::string name = newTempName();
    Symbol* symbol = symtable.scopeLookup(name, currentScope);
    if (symbol == NULL)
        return new Symbol(name, LOCALVAR, yylineno, currentScope, true);
    else
        return symbol;
}

Scopespace_T getCurrentScopespace() {
    if (scopeSpaceCounter == 1)
        return PROGRAM_VAR;
    else if (scopeSpaceCounter % 2 == 0)
        return FORMAL_ARG;
    else
        return FUNCTION_LOCAL;
}

unsigned int getCurrentScopeOffset() {
    switch (getCurrentScopespace()) {
    case PROGRAM_VAR:
        return programVarOffset;
    case FORMAL_ARG:
        return formalArgOffset;
    case FUNCTION_LOCAL:
        return functionLocalOffset;
    default:
        assert(0);
    }
}

void incCurrentScopeOffset() {
    switch (getCurrentScopespace()) {
    case PROGRAM_VAR:
        ++programVarOffset;
        break;
    case FORMAL_ARG:
        ++formalArgOffset;
        break;
    case FUNCTION_LOCAL:
        ++functionLocalOffset;
        break;
    default:
        assert(0);
    }
}

void enterScopespace() {
    ++scopeSpaceCounter;
}

void exitScopepace() {
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

bool isValidArithmeticOperation(unsigned int e1, unsigned int e2) {
    if ((e1 == NUMBER_EXPR ||
        e1 == CONST_NUMBER_EXPR ||
        e1 == VAR_EXPR) &&
        (e2 == NUMBER_EXPR ||
            e2 == CONST_NUMBER_EXPR ||
            e2 == VAR_EXPR)) return true;
    return false;
}

// EVA
void resetFormalArgsOffset() {
    formalArgOffset = 0;
}

void resetFunctionLocalOffset() {
    functionLocalOffset = 0;
}

void restoreCurrentScopeOffset(unsigned int offset) {
    switch (getCurrentScopespace()) {
        case PROGRAM_VAR:
            programVarOffset = offset;
            break;
        case FORMAL_ARG:
            formalArgOffset = offset;
            break;
        case FUNCTION_LOCAL:
            functionLocalOffset = offset;
            break;
        default: assert(0);
    }
}

std::string opcodeToString(Opcode opcode) {
    switch (opcode) {
        case OP_ASSIGN: return "assign";
        case OP_ADD: return "add";
        case OP_SUB: return "sub";
        case OP_MUL: return "mul";
        case OP_DIV: return "div";
        case OP_MOD: return "mod";
        case OP_UMINUS: return "uminus";
        case OP_AND: return "and";
        case OP_OR: return "or";
        case OP_NOT: return "not";
        case OP_IF_EQ: return "if_eq";
        case OP_IF_NOTEQ: return "if_noteq";
        case OP_IF_LESSEQ: return "if_lesseq";
        case OP_IF_GREATEQ: return "if_greatereq";
        case OP_IF_LESS: return "if_less";
        case OP_IF_GREATER: return "if_greater";
        case OP_JUMP: return "jump";
        case OP_CALL: return "call";
        case OP_PARAM: return "param";
        case OP_RET: return "return";
        case OP_GETRETVAL: return "getretval";
        case OP_FUNCSTART: return "funcstart";
        case OP_FUNCEND: return "funcend";
        case OP_TABLECREATE: return "tablecreate";
        case OP_TABLEGETELEM: return "tablegetelem";
        case OP_TABLESETELEM: return "tablesetelem";
        default: return "UNKNOWN";
    }
}

// Extend for other cases
Expr* symbolToExpr(Symbol* symbol) {
    Expr* newExpr = new Expr;

    newExpr->symbol = symbol;
    newExpr->value = symbol->getId();
    switch(symbol->getType()) {
        case USERFUNC: newExpr->type = USERFUNCTION_EXPR;
        case LIBRARYFUNC: newExpr->type = LIBRARYFUNCTION_EXPR;
        
        default: break;
    }

    return newExpr;
}


//function patchlabel sel.10 II

//function lvalue_exp sel.18 II


unsigned int nextQuadLabel() {
    return Quads.size();
}

void printQuads() {
    std::cout << std::endl;
    std::cout << "quad#\topcode\t\tresult\t\targ1\t\targ2\t\tlabel" << std::endl;
    std::cout << "=============================================================================" << std::endl;

    for (auto it = Quads.begin(); it != Quads.end(); ++it) {
        Quad* quad = *it;
        std::cout << quad->label << ':';
        std::cout << '\t' << opcodeToString(quad->opcode);

        if (quad->result != NULL) std::cout << '\t' << std::get<std::string>(quad->result->value);
        // Extend code for other fields

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

#endif