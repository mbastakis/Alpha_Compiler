#include <iostream>
#include "Symbol.hpp"
#include "SymbolTable.hpp"


int main() {
    SymbolTable symtable = SymbolTable();
    std::stack<bool> stack = std::stack<bool>();
    stack.push(true);
    stack.push(true);
    stack.push(true);
    stack.push(true);

    symtable.insert(new Symbol("x", LOCALVAR, 2, 1, true));

    std::cout << symtable.recursiveLookup("x", 1, stack)->toString() << std::endl;
}