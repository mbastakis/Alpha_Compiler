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

typedef enum {
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
extern unsigned int currentScope;
extern int yylineno;

extern unsigned int programVarOffset;
extern unsigned int functionLocalOffset;
extern unsigned int formalArgOffset;
extern unsigned int scopeSpaceCounter;
unsigned int tempNameCounter = 1;

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

void enterScopespace() {
    ++scopeSpaceCounter;
}

void exitScopepace() {
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

void incCurrentScopeOffset() {
    switch (getCurrentScopeOffset()) {
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
    for (auto it = symList.begin(); it != symList.end(); it++) {
        std::string id = (*it)->getId();
        if (id[0] == '$') symtable.removeSymbol(id, currentScope);
    }

    tempNameCounter = 1;
}

Symbol* newTempSymbol() {
    std::string name = newTempName();
    Symbol* symbol = symtable.scopeLookup(name, currentScope);
    if (symbol == NULL)
        return new Symbol(name, LOCALVAR, yylineno, currentScope, true);
    else
        return symbol;
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

#endif