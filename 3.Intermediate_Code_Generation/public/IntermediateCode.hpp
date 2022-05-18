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
    std::variant<std::string, int, double, bool> value;
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
extern unsigned int tempNameCounter;

Scopespace_T getCurrentScopespace();

unsigned int getCurrentScopeOffset();

void enterScopespace();

void exitScopepace();

void incCurrentScopeOffset();

void emit(Opcode op, Expr* arg1, Expr* arg2, Expr* result, unsigned int line,
    unsigned int label);

std::string newTempName();

void resetTemp();

Symbol* newTempSymbol();

bool isValidArithmeticOperation(Expr* e1, Expr* e2);

// EVA
void resetFormalArgsOffset();

void resetFunctionLocalOffset();

void restoreCurrentScopeOffset(unsigned int offset);

std::string opcodeToString(Opcode opcode);

// Extend for other cases
Expr* symbolToExpr(Symbol* symbol);

Expr* newNilExpr();

Expr* newBoolExpr(std::string value);

Expr* newStringExpr(std::string value);

Expr* newIntegerExpr(int value);

Expr* newDoubleExpr(double value);

bool isFunctionExpr(Expr* expr);

unsigned int nextQuadLabel();

std::string exprValueToString(Expr* expr);

void printQuads();

#endif