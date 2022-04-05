#include <iostream>

#include "Symbol.hpp"
#include "SymbolTable.hpp"

int main() {
    SymbolTable symtable = SymbolTable();

    symtable.insert(new Symbol("loln", FORMAL_ARGUMENT, 10, 1));
    symtable.insert(new Symbol("le", FORMAL_ARGUMENT, 5, 1));
    symtable.insert(new Symbol("li", FORMAL_ARGUMENT, 4, 2));
    symtable.insert(new Symbol("lu", FORMAL_ARGUMENT, 2, 3));
    symtable.insert(new Symbol("la", FORMAL_ARGUMENT, 3, 4));
    symtable.insert(new Symbol("lo", FORMAL_ARGUMENT, 6, 5));
    symtable.insert(new Symbol("lola", FORMAL_ARGUMENT, 20, 3));
    symtable.insert(new Symbol("loln", FORMAL_ARGUMENT, 112, 4));

    // auto symList = symtable.getSymbols("lo");

    // for (auto it = symList.begin(); it != symList.end(); it++) {
    //     std::cout << (*it)->toString() << std::endl;
    // }
    // symtable.printSymTable();

    std::cout << symtable.getNearestSymbol("lo", 4)->toString() << std::endl;
}