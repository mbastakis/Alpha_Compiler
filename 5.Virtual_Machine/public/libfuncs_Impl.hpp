#ifndef LIBFUNCS_IMPL
#define LIBFUNCS_IMPL

#define AVM_NUMACTUALS_OFFSET +4    // funcs_exec
#define AVM_SAVEDTOP_OFFSET +2      // funcs_exec
#define AVM_SAVEDTOPSP_OFFSET +1    // funcs_exec

#include <functional>
#include "AVM.hpp"

extern unsigned int avm_get_envvalue(unsigned int);

// 15 diale3i: 30, 23, 35, 36 | front : ta idia~

unsigned int avm_totalactuals() {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned int i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void print(void) {
    unsigned int n = avm_totalactuals();
    for (int i = 0; i < n; ++i) {
        std::cout << avm_getactual(i)->to_string();
    }
}

void typeof(void) {
    unsigned int n = avm_totalactuals();

    if (n != 1)
        std::cout << "One argument (not" << n << ") expected in 'typeof'!" << std::endl;
    else {
        (&retval)->avm_memcellclear();
        retval.type = STRING_M;
        retval.data = avm_memcell_t_to_string[avm_getactual(0)->type];
    }
}

void totalarguments(void) {
    unsigned int p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    (&retval)->avm_memcellclear();

    if (!p_topsp) {
        std::cout << "'totalarguments' called outside of a function" << std::endl;
        retval.type = NIL_M;
    }
    else {
        retval.type = NUMBER_M;
        retval.data = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void argument(void) {
    unsigned int p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    unsigned int n = avm_totalactuals();
    if (n != 1) {
        std::cout << "One argument (not" << n << ") expected in 'argument'!" << std::endl;
        retval.type = NIL_M;
        return;
    }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != NUMBER_M) {
        std::cout << "Expected to be called with number as argument!" << std::endl;
        retval.type = NIL_M;
        return;
    }

    (&retval)->avm_memcellclear();

    if (!p_topsp) {
        std::cout << "'argument' called outside of a function" << std::endl;
        retval.type = NIL_M;
        return;
    }

    if (std::get<double>(arg->data) < avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET)) {
        retval = stack[p_topsp + AVM_STACKENV_SIZE + n + 1];
    }
    else {
        retval.type = NIL_M;
    }

}

#endif