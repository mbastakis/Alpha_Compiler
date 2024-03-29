#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <map>
#include <list>
#include <stack>
#include <fstream>

#include "Symbol.hpp"

class SymbolTable {

private:
    std::multimap<std::string, Symbol*> m_table;
    unsigned int m_size;
    unsigned int m_maxScope;

    static bool compare(Symbol* first, Symbol* second) {
        return first->getLine() < second->getLine();
    }

    void printSymbols(unsigned int scope) {
        auto symList = std::list<Symbol*>();
        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getScope() == scope)
                symList.push_back(it->second);
        }
        symList.sort(compare);

        for (auto it = symList.begin(); it != symList.end(); ++it) {
            std::cout << (*it)->toString() << std::endl;
        }
    }

public:
    SymbolTable() {
        m_table = std::multimap<std::string, Symbol*>();
        m_size = 0;
        m_maxScope = 0;

        insert(new Symbol("print", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("input", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("objectmemberkeys", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("objecttotalmembers", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("objectcopy", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("totalarguments", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("argument", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("typeof", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("strtonum", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("sqrt", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("cos", LIBRARYFUNC, 0, 0, true));
        insert(new Symbol("sin", LIBRARYFUNC, 0, 0, true));
    }

    bool contains(std::string id) {
        return m_table.find(id) != m_table.end();
    }

    bool contains(std::string id, Symbol_T type) {
        auto it = m_table.find(id);
        while (it != m_table.end()) {
            if (it->second->getType() == type && it->second->getId() == id && it->second->isActive()) return true;
            it++;
        }
        return false;
    }

    bool contains(std::string id, unsigned int scope) {
        auto it = m_table.find(id);
        while (it != m_table.end()) {
            if (it->second->getScope() == scope && it->second->getId() == id && it->second->isActive()) return true;
            it++;
        }
        return false;
    }

    Symbol* get(std::string id, unsigned int scope) {
        auto it = m_table.find(id);
        while (it != m_table.end()) {
            if (it->second->getScope() == scope && it->second->getId().compare(id) == 0) return (it->second);
            it++;
        }

        return NULL;
    }

    Symbol* get(std::string id) {
        auto search = m_table.find(id);
        return search == m_table.end() ? NULL : search->second;
    }

    Symbol* getNearestSymbol(std::string id, int scope) {
        while (scope >= 0) {
            Symbol* search = get(id, scope);
            if (search != NULL && search->isActive()) return search;
            scope--;
        }
        return NULL;
    }

    Symbol* recursiveLookup(std::string id, int scope, std::stack<bool> blockStack) {
        Symbol* search = lookup(id, scope); // Search for a symbol with id.
        if (search == NULL) return NULL;    // It doesn't exist.

        int activeScope = scope;
        if (!blockStack.empty()) {
            bool isFunctionBlock = blockStack.top();
            blockStack.pop();
            while (!blockStack.empty() && isFunctionBlock != true) {    // Calculate the minimum scope that we can access.
                activeScope--;
                isFunctionBlock = blockStack.top();
                blockStack.pop();
            }
        }

        if (search->getScope() < activeScope && // Check if we don't have access to that scope and return error.
            search->getScope() != 0 &&
            search->getType() != USERFUNC &&
            search->getType() != LIBRARYFUNC)
            return new Symbol("_Error_", SYMERROR, 0, 0, false);
        else
            return search;  // We have access return the variable.
    }

    Symbol* scopeLookup(std::string id, int currentScope) {
        auto symList = getSymbols(currentScope);
        for (auto it = symList.begin(); it != symList.end(); it++) {
            if ((*it)->isActive() && (*it)->getId().compare(id) == 0) return (*it);
        }
        return NULL;
    }

    unsigned int count(std::string id) {
        return m_table.count(id);
    }

    std::list<Symbol*> getSymbols(unsigned int scope) {
        auto symList = std::list<Symbol*>();

        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getScope() == scope)
                symList.push_back(it->second);
        }

        return symList;
    }

    std::list<Symbol*> getSymbols(std::string id) {
        auto symList = std::list<Symbol*>();

        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getId().compare(id) == 0)
                symList.push_back(it->second);
        }

        return symList;
    }

    int getScope(std::string id, Symbol_T type) {
        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getType() == type && it->second->getId() == id)
                return it->second->getScope();
        }
        return -1;
    }


    void insert(Symbol* symbol) {
        if (symbol->getScope() > m_maxScope)
            m_maxScope = symbol->getScope();

        m_table.insert({ symbol->getId(), symbol });
    }

    Symbol* lookup(std::string id, int currentScope) {

        while (currentScope >= 0) {

            auto symList = getSymbols(currentScope);
            for (auto it = symList.begin(); it != symList.end(); it++) {
                if ((*it)->isActive() && (*it)->getId().compare(id) == 0) return (*it);
            }
            currentScope--;
        }

        return NULL;
    }

    void hide(unsigned int scope) {
        auto symList = getSymbols(scope);

        for (auto it = symList.begin(); it != symList.end(); it++) {
            (*it)->setActive(false);
        }
    }

    void printSymTable() {
        for (auto i = 0; i <= m_maxScope; i++) {
            std::cout << "-----------\t Scope #" << std::to_string(i) << "\t-----------" << std::endl;
            printSymbols(i);
            std::cout << std::endl << std::endl;
        }
    }

    void removeSymbol(std::string id, unsigned int scope) {
        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getScope() == scope && it->second->getId().compare(id) == 0)
                m_table.erase(it);
        }
    }

    void printSymbolsInFile(char* argv) {
        std::ofstream myfile;
        myfile.open(argv, std::ios_base::app);

        for (auto i = 0; i <= m_maxScope; i++) {
            myfile << "-----------\t Scope #" << std::to_string(i) << "\t-----------" << std::endl;


            auto symList = std::list<Symbol*>();
            for (auto it = m_table.begin(); it != m_table.end(); ++it) {
                if (it->second->getScope() == i)
                    symList.push_back(it->second);
            }
            symList.sort(compare);

            for (auto it = symList.begin(); it != symList.end(); ++it) {
                myfile << (*it)->toString() << std::endl;
            }


            myfile << std::endl << std::endl;
        }

        myfile.close();
    }

};

#endif