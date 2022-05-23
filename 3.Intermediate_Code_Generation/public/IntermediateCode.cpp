#include "IntermediateCode.hpp"

Quads::Quads() {
    quadVector = std::vector<Quad*>();

    programVarOffset = 0;
    functionLocalOffset = 0;
    formalArgOffset = 0;
    scopeSpaceCounter = 1;
}

void Quads::emit(Opcode op, Expr* arg1, Expr* arg2, Expr* result, unsigned int line, unsigned int label) {
    Quad* newQuad = new Quad();
    newQuad->arg1 = arg1;
    newQuad->arg2 = arg2;
    newQuad->result = result;
    newQuad->line = line;
    newQuad->label = label;
    newQuad->opcode = op;

    quadVector.push_back(newQuad);
}

Scopespace_T Quads::getCurrentScopespace() {
    if (scopeSpaceCounter == 1)
        return PROGRAM_VAR;
    else if (scopeSpaceCounter % 2 == 0)
        return FORMAL_ARG;
    else
        return FUNCTION_LOCAL;
}

unsigned int Quads::getCurrentScopeOffset() {
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

void Quads::incCurrentScopeOffset() {
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

void Quads::enterScopespace() {
    ++scopeSpaceCounter;
}

void Quads::exitScopepace() {
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

Expr* Symbol::toExpr() {
    Expr* newExpr = new Expr();

    switch (m_type) {
    case GLOBALVAR: {
        newExpr->symbol = this;
        newExpr->type = VAR_EXPR;
        newExpr->value = m_id;
        break;
    };
    case LOCALVAR: {
        newExpr->symbol = this;
        newExpr->type = VAR_EXPR;
        newExpr->value = m_id;
        break;
    };
    case FORMAL_ARG: {
        newExpr->symbol = this;
        newExpr->type = VAR_EXPR;
        newExpr->value = m_id;
        break;
    };
    case LIBRARYFUNC: {
        newExpr->symbol = this;
        newExpr->type = LIBRARYFUNCTION_EXPR;
        newExpr->value = m_id;
        break;
    };
    case USERFUNC: {
        newExpr->symbol = this;
        newExpr->type = USERFUNCTION_EXPR;
        newExpr->value = m_id;
        break;
    }
    }

    return newExpr;
}

