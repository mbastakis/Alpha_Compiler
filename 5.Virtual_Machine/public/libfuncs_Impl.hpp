#ifndef LIBFUNCS_IMPL
#define LIBFUNCS_IMPL

#include <functional>

#include "Instruction.hpp"
#include "AVM.hpp"

extern unsigned int topsp, top;

std::function<void(void)> libfunc_print;
std::function<void(void)> libfunc_input;
std::function<void(void)> libfunc_objectmemberkeys;
std::function<void(void)> libfunc_objecttotalmembers;
std::function<void(void)> libfunc_objectcopy;
std::function<void(void)> libfunc_totalarguments;
std::function<void(void)> libfunc_argument;
std::function<void(void)> libfunc_typeof;
std::function<void(void)> libfunc_strtonum;
std::function<void(void)> libfunc_sqrt;
std::function<void(void)> libfunc_cos;
std::function<void(void)> libfunc_sin;

// 15 diale3i: 30, 23, 35, 36 | front : ta idia~

unsigned int avm_totalactuals() {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned int i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print() {
    unsigned int n = avm_totalactuals();
    for (int i = 0; i < n; ++i) {
        cout << avm_getactual(i)->to_string();
    }
}

void libfunc_typeof(void) {
    unsigned int n = avm_totalactuals();

    if (n != 1)
        std::cout << "One argument (not" << n << ") expected in 'typeof'!" << std::endl;
    else {
        (&retval)->avm_memcellclear();
        retval.type = STRING_M;
        retval.data = avm_memcell_t_to_string[avm_getactual(0)->type];
    }
}

void libfunc_totalargument() {
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

#endif