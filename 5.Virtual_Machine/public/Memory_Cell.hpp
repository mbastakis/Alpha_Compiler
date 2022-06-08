#ifndef MEMORY_CELL
#define MEMORY_CELL

#include <string>
#include <stack>
#include <map>
#include <cassert>
#include <variant>

typedef enum {
    NUMBER_T = 0,
    STRING_T,
    BOOL_M,
    TABLE_M,
    USERFUNC_M,
    LIBFUNC_M,
    NIL_M,
    UNDEFINED_T
} avm_memcell_t;

class avm_table;

class avm_memcell {
public:
    avm_memcell_t type;
    // std::variant<
    //     double,
    //     std::string,
    //     bool,
    //     avm_table,
    //     unsigned int,
    //     std::string,
    // > data;

    avm_memcell() {
        this->type = UNDEFINED_T;
    }

    avm_memcell(avm_memcell_t type) {
        this->type = type;

    }

};


class avm_table {
public:
    unsigned int refCounter;
    std::map<std::string, avm_memcell>* strIndexed;
    std::map<double, avm_memcell>* numIndexed;
    std::map<bool, avm_memcell>* boolIndexed;
    std::map<avm_table, avm_memcell>* tableIndexed;
    std::map<unsigned int, avm_memcell>* funcIndexed;
    std::map<std::string, avm_memcell>* libfuncIndexed;

    avm_table() {
        this->refCounter = 0;
        strIndexed = new std::map<std::string, avm_memcell>();
        numIndexed = new std::map<double, avm_memcell>();
        boolIndexed = new std::map<bool, avm_memcell>();
        tableIndexed = new std::map<avm_table, avm_memcell>();
        funcIndexed = new std::map<unsigned int, avm_memcell>();
        libfuncIndexed = new std::map<std::string, avm_memcell>();
    }

    ~avm_table() {
        delete strIndexed;
        delete numIndexed;
        delete boolIndexed;
        delete tableIndexed;
        delete funcIndexed;
        delete libfuncIndexed;
    }

    avm_table& operator--();
    avm_table& operator++();
};

avm_table& avm_table::operator--() {
    assert(this->refCounter > 0);
    if (--this->refCounter == 1) this->~avm_table();
}

avm_table& avm_table::operator++() {
    ++this->refCounter;
    return *this;
}

// Variables
std::stack<avm_memcell> avm_memcell_stack{};
#endif




// avm_table* table = new avm_table();  OK
//         table--;
// avm_table* table = new avm_table(); Maybe OK
//      table->--;