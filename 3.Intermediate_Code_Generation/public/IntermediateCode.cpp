#include "IntermediateCode.hpp"

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

bool isValidArithmeticOperation(Expr* e1, Expr* e2) {
    if ((e1->type == NUMBER_EXPR ||
        e1->type == CONST_NUMBER_EXPR ||
        e1->type == VAR_EXPR) &&
        (e2->type == NUMBER_EXPR ||
            e2->type == CONST_NUMBER_EXPR ||
            e2->type == VAR_EXPR)) return true;
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

    switch(symbol->getType()) {
        case USERFUNC: {
            newExpr->type = USERFUNCTION_EXPR;
            newExpr->symbol = symbol;
            newExpr->value = symbol->getId();
        };
        default: break;
    }

    return newExpr;
}

Expr* newNilExpr() {
    Expr* newExpr = new Expr;

    newExpr->type = NIL_EXPR;

    return newExpr;
}

Expr* newBoolExpr(std::string value) {
    Expr* newExpr = new Expr;

    newExpr->type = BOOLEAN_EXPR;
    newExpr->value = value == "true";

    return newExpr;
}

Expr* newStringExpr(std::string value) {
    Expr* newExpr = new Expr;

    newExpr->type = CONST_STRING_EXPR;
    newExpr->value = value;

    return newExpr;
}

Expr* newIntegerExpr(int value) {
    Expr* newExpr = new Expr;

    newExpr->type = CONST_NUMBER_EXPR;
    newExpr->value = value;

    return newExpr;
}

Expr* newDoubleExpr(double value) {
    Expr* newExpr = new Expr;

    newExpr->type = CONST_NUMBER_EXPR;
    newExpr->value = value;

    return newExpr;
}

bool isFunctionExpr(Expr* expr) {
    return expr->type == USERFUNCTION_EXPR || expr->type == LIBRARYFUNCTION_EXPR;
}

unsigned int nextQuadLabel() {
    return Quads.size();
}

std::string exprValueToString(Expr* expr) {
    switch(expr->type) {
        case CONST_NUMBER_EXPR:
        case NUMBER_EXPR:
            return std::to_string(std::get<int>(expr->value));
        case CONST_BOOLEAN_EXPR:
        case BOOLEAN_EXPR:
            return std::to_string(std::get<bool>(expr->value));
        case CONST_STRING_EXPR:
        case STRING_EXPR:
            return std::get<std::string>(expr->value);
        case NIL_EXPR:
            return "NIL";
        case USERFUNCTION_EXPR:
        case LIBRARYFUNCTION_EXPR:
        case VAR_EXPR:
            return "TEST";
        default:
            return "UKNOWN";
    }
}

void printQuads() {
    std::cout << std::endl;
    std::cout << "quad#\topcode\t\tresult\t\targ1\t\targ2\t\tlabel" << std::endl;
    std::cout << "=============================================================================" << std::endl;

    for (auto it = Quads.begin(); it != Quads.end(); ++it) {
        Quad* quad = *it;
        std::cout << quad->label << ':';
        std::cout << '\t' << opcodeToString(quad->opcode);

        // if (quad->result != NULL) std::cout << '\t' << exprValueToString(quad->result);
        if (quad->arg1 != NULL) std::cout << '\t' << exprValueToString(quad->arg1);
        if (quad->arg2 != NULL) std::cout << '\t' << exprValueToString(quad->arg2);
        // Extend code for other fields

        std::cout << std::endl;
    }

    std::cout << std::endl;
}