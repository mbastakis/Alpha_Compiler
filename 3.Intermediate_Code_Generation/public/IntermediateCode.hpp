#ifndef INTERMEDIATECODE_HPP
#define INTERMEDIATECODE_HPP

#include "Symbol.hpp"
#include "SymbolTable.hpp"

#include <variant>
#include <vector>
#include <cassert>

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
    VAR_EXPR,
    TABLE_ITEM_EXPR,

    CONST_INTEGER_EXPR,
    INTEGER_EXPR,

    CONST_REAL_EXPR,
    REAL_EXPR,

    CONST_BOOLEAN_EXPR,
    BOOLEAN_EXPR,

    CONST_STRING_EXPR,
    STRING_EXPR,

    NIL_EXPR,

    USERFUNCTION_EXPR,
    LIBRARYFUNCTION_EXPR,

    ARITHMETIC_EXPR,
    ASSIGN_EXPR,
    BOOL_EXPR,
    NEW_TABLE_EXPR,
} Expr_T;

typedef struct Expr {
    Expr_T type;
    Symbol* symbol;
    std::variant<std::string, int, double, bool> value;
    struct Expr* index;
    struct Expr* next;
} Expr;

typedef struct {
    Opcode opcode;
    Expr* result;
    Expr* arg1;
    Expr* arg2;
    unsigned int label;
    unsigned int line;
} Quad;

class Quads {
private:
    std::vector<Quad*> quadVector;
    unsigned int programVarOffset;
    unsigned int functionLocalOffset;
    unsigned int formalArgOffset;
    unsigned int scopeSpaceCounter;
    unsigned int tempNameCounter;

public:
    Quads();
    void emit(Opcode op, Expr* arg1, Expr* arg2, Expr* result, unsigned int line, unsigned int label);
    Scopespace_T getCurrentScopespace();
    unsigned int getCurrentScopeOffset();
    void incCurrentScopeOffset();
    void enterScopespace();
    void exitScopepace();

};

#endif