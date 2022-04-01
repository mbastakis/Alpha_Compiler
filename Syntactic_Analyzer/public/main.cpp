#include <iostream>

#include "Symbol.hpp"
#include "SymbolTable.hpp"

int main() {
    SymbolTable symtable = SymbolTable();

    symtable.insert("loln", new Symbol("loln", FORMAL_ARGUMENT, 10, 1));
    symtable.insert("lo", new Symbol("lo", FORMAL_ARGUMENT, 1, 3));
    symtable.insert("lo", new Symbol("lo", FORMAL_ARGUMENT, 1, 3));
    symtable.insert("lo", new Symbol("lo", FORMAL_ARGUMENT, 1, 2));
    symtable.insert("lo", new Symbol("lo", FORMAL_ARGUMENT, 1, 4));
    symtable.insert("lo", new Symbol("lo", FORMAL_ARGUMENT, 1, 2));
    symtable.insert("lola", new Symbol("lola", FORMAL_ARGUMENT, 20, 3));
    symtable.insert("loln", new Symbol("loln", FORMAL_ARGUMENT, 112, 4));

    auto symList = symtable.getSymbols("");

    for (auto it = symList.begin(); it != symList.end(); it++) {
        std::cout << (*it)->toString() << std::endl;
    }
    symtable.printSymTable();
}