#ifndef MEMORY_CELL
#define MEMORY_CELL

#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <variant>

typedef enum {
    NUMBER_M = 0,
    STRING_M,
    BOOL_M,
    TABLE_M,
    USERFUNC_M,
    LIBFUNC_M,
    NIL_M,
    UNDEFINED_M
} avm_memcell_t;

std::string avm_memcell_t_to_string[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undefined"
};

class avm_memcell;

class avm_table {
public:
    unsigned int refCounter;
    std::map<std::string, avm_memcell*>* strIndexed;
    std::map<double, avm_memcell*>* numIndexed;
    std::map<bool, avm_memcell*>* boolIndexed;
    std::map<avm_table, avm_memcell*>* tableIndexed;
    std::map<unsigned int, avm_memcell*>* funcIndexed;
    std::map<std::string, avm_memcell*>* libfuncIndexed;

    avm_table() {
        this->refCounter = 0;
        strIndexed = new std::map<std::string, avm_memcell*>();
        numIndexed = new std::map<double, avm_memcell*>();
        boolIndexed = new std::map<bool, avm_memcell*>();
        tableIndexed = new std::map<avm_table, avm_memcell*>();
        funcIndexed = new std::map<unsigned int, avm_memcell*>();
        libfuncIndexed = new std::map<std::string, avm_memcell*>();
    }

    ~avm_table() {
        delete strIndexed;
        delete numIndexed;
        delete boolIndexed;
        delete tableIndexed;
        delete funcIndexed;
        delete libfuncIndexed;
    }

    avm_memcell* get(avm_memcell* i);
    void set(avm_memcell*, avm_memcell*);

    unsigned int getTotal() {
        return strIndexed->size() + numIndexed->size();
    }


    avm_table& operator--();
    avm_table& operator++();
};

avm_table& avm_table::operator--() {
    assert(this->refCounter > 0);
    if (--this->refCounter == 0) this->~avm_table();
    return *this;
}

avm_table& avm_table::operator++() {
    ++this->refCounter;
    return *this;
}

class avm_memcell {
public:
    avm_memcell_t type;
    std::variant<double, std::string, bool, avm_table*, unsigned int> data;

    avm_memcell() {
        this->type = UNDEFINED_M;
    }

    void copy(avm_memcell* copy) {
        this->type = copy->type;
        switch (copy->data.index()) {
        case 0:
            this->data = std::get<double>(copy->data);
            break;
        case 1:
            this->data = std::get<std::string>(copy->data);
            break;
        case 2:
            this->data = std::get<bool>(copy->data);
            break;
        case 3:
            this->data = copy->data;
            break;
        case 4:
            this->data = std::get<unsigned int>(copy->data);
            break;
        default:
            assert(0);
        }
    }

    avm_memcell(avm_memcell_t type) {
        this->type = type;
    }

    void avm_memcellclear() {
        if (this->type == UNDEFINED_M) return;

        if (this->type == STRING_M) {
            std::get<std::string>(this->data).erase();
        }
        else if (this->type == TABLE_M) {
            assert(std::get<avm_table*>(this->data));
            std::get<avm_table*>(this->data)--;
        }
        this->type = UNDEFINED_M;
    }

    std::string to_string() {
        switch (this->data.index()) {
        case 0:
            return  std::to_string(std::get<double>(this->data));
            break;
        case 1:
            return  std::get<std::string>(this->data);
            break;
        case 2:
            return  (std::get<bool>(this->data) == true ? "true" : "false");
            break;
        case 3:
            return  "table[" + std::to_string(std::get<TABLE_M>(this->data)->getTotal()) + "] refrenced: " + std::to_string(std::get<TABLE_M>(this->data)->refCounter);
            break;
        case 4:
            return std::to_string(std::get<unsigned int>(this->data));
            break;
        default:
            assert(0);
        }
    }

};

avm_memcell* avm_table::get(avm_memcell* i) {
    switch (i->type)
    {
    case NUMBER_M:
        return this->numIndexed->find(std::get<double>(i->data))->second;
        break;
    case STRING_M:
        return this->strIndexed->find(std::get<std::string>(i->data))->second;
        break;
    default:
        return NULL;
    }
}

void avm_table::set(avm_memcell* i, avm_memcell* c) {
    switch (i->type)
    {
    case NUMBER_M:
        this->numIndexed->at(std::get<double>(i->data)) = c;
        break;
    case STRING_M:
        this->strIndexed->at(std::get<std::string>(i->data)) = c;
        break;
    default:
        break;
    }
}

#endif


// avm_table* table = new avm_table();  OK
//         table--;
// avm_table* table = new avm_table(); Maybe OK
//      table->--;