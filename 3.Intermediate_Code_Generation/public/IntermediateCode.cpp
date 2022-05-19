#include "IntermediateCode.hpp"
#include <iomanip>
#include <algorithm>

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

    tempNameCounter = 0;
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
    Expr* newExpr = new Expr();

    
    switch(symbol->getType()) {
        case USERFUNC: {
            newExpr->symbol = symbol;
            newExpr->value = symbol->getId();
            newExpr->type = USERFUNCTION_EXPR;
            break;
        };
        case LIBRARYFUNC: {
            newExpr->symbol = symbol;
            newExpr->value = symbol->getId();
            newExpr->type = LIBRARYFUNCTION_EXPR;
        };
        case GLOBALVAR: {
            newExpr->symbol = symbol;
            newExpr->value = symbol->getId();
            newExpr->type = VAR_EXPR;
        };
        case LOCALVAR: {
            newExpr->symbol = symbol;
            newExpr->value = symbol->getId();
            newExpr->type = VAR_EXPR;
        };
    }

    return newExpr;
}

Expr* changeType(Expr* expr, Expr_T type) {
    expr->type = type;
    return expr;
}

Expr* changeValue(Expr* expr, std::variant<std::string, int, double, bool> value) {
    expr->value = value;
    return expr;
}

Expr* newNilExpr() {
    Expr* newExpr = new Expr();

    newExpr->type = NIL_EXPR;

    return newExpr;
}

Expr* newBoolExpr(std::string value) {
    Expr* newExpr = new Expr();

    newExpr->type = CONST_BOOLEAN_EXPR;
    newExpr->value = (value == "true");

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

bool areExprTypesEq(Expr* expr1, Expr* expr2) {
    return expr1->type == expr2->type;
}

bool areExprBoolTypes(Expr* expr1, Expr* expr2) {
    return (expr1->type == BOOLEAN_EXPR || expr1-> type == CONST_BOOLEAN_EXPR ) &&
            (expr2->type == BOOLEAN_EXPR || expr2-> type == CONST_BOOLEAN_EXPR );
}

void patchlabel (unsigned int quadNo, unsigned int label) {
    Quads[quadNo]->label = label;
}

unsigned int nextQuadLabel() {
    return Quads.size();
}

std::string fixPrecision(std::string num) {
    std::string fixedNum = "";
    int size = num.length() - 1;
    bool flag = false;

    for(int i = 0; i <= size; i++) {
        if(num[size - i] != '0') flag = true;
        if(!flag) continue;
        fixedNum += num[size - i];
    }

    std::reverse(fixedNum.begin(), fixedNum.end());
    return fixedNum;
}

std::string exprValueToString(Expr* expr) {
    switch(expr->type) {
        case CONST_NUMBER_EXPR:
            if(expr->value.index() == 1)
                return std::to_string(std::get<int>(expr->value));
            if(expr->value.index() == 2)
                return fixPrecision(std::to_string(std::get<double>(expr->value)));
        case NUMBER_EXPR:
            return std::to_string(std::get<int>(expr->value));
        case CONST_BOOLEAN_EXPR:
            return std::get<bool>(expr->value) == true ? "true" : "false";
        case BOOLEAN_EXPR:
            return std::to_string(std::get<bool>(expr->value));
        case CONST_STRING_EXPR:
            return std::get<std::string>(expr->value);
        case STRING_EXPR:
            return std::get<std::string>(expr->value);
        case NIL_EXPR:
            return "NIL";
        case USERFUNCTION_EXPR:
            return "USERFUNC";
        case LIBRARYFUNCTION_EXPR:
            return "LIBRARYFUNC";
        case VAR_EXPR:
            return "TEST";
        default:
            return "UKNOWN";
    }
}

std::string fixTabs(Opcode op) {
    switch (op) {
        case OP_FUNCSTART:
            return "\b\b\b\b\b\b\b\b";
        case OP_IF_GREATER:
            return "\b\b\b\b\b\b\b\b";
        case OP_IF_LESS:
            return "\b\b\b\b\b\b\b\b";
        case OP_IF_GREATEQ:
            return "\b\b\b\b\b\b\b\b";
        case OP_IF_NOTEQ:
            return "\b\b\b\b\b\b\b\b";
        case OP_GETRETVAL:
            return "\b\b\b\b\b\b\b\b";
        case OP_TABLECREATE:
            return "\b\b\b\b\b\b\b\b";
        case OP_IF_LESSEQ:
            return "\b\b\b\b\b\b\b\b";
        default:
            return "";
    }
}

void printQuads() {
    std::cout << std::endl;
    std::cout << "quad#\topcode\t\tresult\t\targ1\t\targ2\t\tlabel" << std::endl;
    std::cout << "=============================================================================" << std::endl;
    int counter = 0;
    for (auto it = Quads.begin(); it != Quads.end(); ++it) {
        Quad* quad = *it;
        std::cout << counter++ << ':' << '\t';
        std::cout << opcodeToString(quad->opcode) << "\t\t" << fixTabs(quad->opcode);

        if (quad->result != NULL) {
            std::cout << quad->result->symbol->getId() << "\t\t";       
        } else std::cout << "" << "\t\t";
        if (quad->arg1 != NULL) {
            if(quad->arg1->type == CONST_NUMBER_EXPR || quad->arg1->type == CONST_BOOLEAN_EXPR || quad->arg1->type == CONST_STRING_EXPR) {
                std::cout << exprValueToString(quad->arg1) << "\t\t";
            }
            else{
                std::cout << quad->arg1->symbol->getId() << "\t\t";
            }
        } else std::cout << "" << "\t\t";
        if (quad->arg2 != NULL) {
            if(quad->arg2->type == CONST_NUMBER_EXPR || quad->arg2->type == CONST_BOOLEAN_EXPR || quad->arg2->type == CONST_STRING_EXPR) 
                std::cout << exprValueToString(quad->arg2) << "\t\t";
            else 
                std::cout << quad->arg2->symbol->getId() << "\t\t";
        } else std::cout << "" << "\t\t";
        if (quad->label != 0) {
            std::cout << quad->label;
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}