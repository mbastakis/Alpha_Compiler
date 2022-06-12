#ifndef LIBFUNCS_IMPL
#define LIBFUNCS_IMPL

#define AVM_NUMACTUALS_OFFSET_V2 + 4    // funcs_exec
#define AVM_SAVEDTOP_OFFSET_V2 + 2      // funcs_exec
#define AVM_SAVEDTOPSP_OFFSET_V2 + 1    // funcs_exec

#include <functional>
#include <iostream>
#include <cmath>
#include <string>
#include "AVM.hpp"

extern unsigned int avm_get_envvalue(unsigned int);

// 15 diale3i: 30, 23, 35, 36 | front : ta idia~

unsigned int avm_totalactuals() {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET_V2);
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
    std::cout << std::endl;
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
    unsigned int p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET_V2);
    (&retval)->avm_memcellclear();

    if (!p_topsp) {
        std::cout << "'totalarguments' called outside of a function" << std::endl;
        retval.type = NIL_M;
    }
    else {
        retval.type = NUMBER_M;
        retval.data = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET_V2);
    }
}

void argument(void) {
    unsigned int p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET_V2);
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

    if (std::get<double>(arg->data) < avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET_V2)) {
        retval = stack[p_topsp + AVM_STACKENV_SIZE + n + 1];
    }
    else {
        retval.type = NIL_M;
    }

}

void a_cos(void) {
    unsigned int n = avm_totalactuals();
    if (n != 1) {
        std::cout << "One argument (not" << n << ") expected in 'argument'!" << std::endl;
        retval.type = NIL_M;
        return;
    }
    else {
        avm_memcell* arg = avm_getactual(0);
        (&retval)->avm_memcellclear();
        if (arg->type != NUMBER_M)
            std::cout << "Cos expected argument of type NUMBER!" << std::endl;
        else {
            double argVal = std::get<double>(arg->data);
            retval.type = NUMBER_M;
            retval.data = std::cos(argVal * 3.14159 / 180);
        }
    }
}

void a_sin(void) {
    unsigned int n = avm_totalactuals();
    if (n != 1) {
        std::cout << "One argument (not" << n << ") expected in 'argument'!" << std::endl;
        retval.type = NIL_M;
        return;
    }
    else {
        avm_memcell* arg = avm_getactual(0);
        (&retval)->avm_memcellclear();
        if (arg->type != NUMBER_M)
            std::cout << "Sin expected argument of type NUMBER!" << std::endl;
        else {
            double argVal = std::get<double>(arg->data);
            retval.type = NUMBER_M;
            retval.data = std::sin(argVal * 3.14159 / 180);
        }
    }
}

void a_sqrt(void) {
    unsigned int n = avm_totalactuals();
    if (n != 1) {
        std::cout << "One argument (not" << n << ") expected in 'argument'!" << std::endl;
        retval.type = NIL_M;
        return;
    }
    else {
        avm_memcell* arg = avm_getactual(0);
        (&retval)->avm_memcellclear();
        if (arg->type != NUMBER_M)
            std::cout << "Sqrt expected argument of type NUMBER!" << std::endl;
        else {
            double argVal = std::get<double>(arg->data);

            if (argVal < 0) {
                retval.type = NIL_M;
                return;
            }

            retval.type = NUMBER_M;
            retval.data = std::sqrt(argVal);
        }
    }
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || (*it) == '.')) ++it;
    return !s.empty() && it == s.end();
}

void strtonum() {
    unsigned int n = avm_totalactuals();
    if (n != 1) {
        std::cout << "One argument (not" << n << ") expected in 'argument'!" << std::endl;
        retval.type = NIL_M;
        return;
    }
    else {
        avm_memcell* arg = avm_getactual(0);
        (&retval)->avm_memcellclear();
        if (arg->type != NUMBER_M)
            std::cout << "Cos expected argument of type NUMBER!" << std::endl;
        else {
            std::string argVal = std::get<std::string>(arg->data);
            try {
                std::size_t offset = 0;
                double d = std::stod(argVal, &offset);
                retval.type = NUMBER_M;
                retval.data = d;
            }
            catch (...) {
                retval.type = NIL_M;
                return;
            };
        }
    }
}

#endif