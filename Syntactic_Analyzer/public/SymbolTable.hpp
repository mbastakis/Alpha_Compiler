#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <unordered_map>
#include "Symbol.hpp"


class SymbolTable {

private:
    std::unordered_map<int, Symbol> m_table;
    unsigned int m_size;

public:
    SymbolTable() {
        m_table = std::unordered_map<int, Symbol>();
        m_size = 0;
    }

    int insert(Symbol* symbol) {
        return 0;
    }

};

#endif