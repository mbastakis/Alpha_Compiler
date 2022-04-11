#include <iostream>
#include "Symbol.hpp"
#include "SymbolTable.hpp"


int main() {
    SymbolTable symtable = SymbolTable();

    symtable.insert(new Symbol("x", GLOBALVAR, 2, 0, true));
    symtable.insert(new Symbol("x", GLOBALVAR, 2, 4, true));
    symtable.insert(new Symbol("x", GLOBALVAR, 2, 3, true));

    std::cout << symtable.lookup("x", 10)->toString() << std::endl;
}