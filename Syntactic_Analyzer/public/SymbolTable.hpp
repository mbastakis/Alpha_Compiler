#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <map>
#include <list>

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

    int recursiveLookup(std::string id, int scope) {
        //if symbol exist in a not global scope
        while (scope > 0) {
            Symbol* search = get(id, scope);
            if (search != NULL && search->isActive()) return scope;
            scope--;
        }
        //if symbol exist in global scope
        if (contains(id, scope)) return 0; 
        return -1;
    }

    unsigned int count(std::string id) {
        return m_table.count(id);
    }

    std::list<Symbol*> getSymbols(unsigned int scope) {
        auto symList = std::list<Symbol*>();

        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getScope() == scope )
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


    int insert(Symbol* symbol) {
        if (symbol->getScope() > m_maxScope)
            m_maxScope = symbol->getScope();

        m_table.insert({ symbol->getId(), symbol });

        return 0;
    }

    Symbol* lookup(std::string id, unsigned int scope) {
        auto symList = getSymbols(id);

        for (auto it = symList.begin(); it != symList.end(); it++) {
            if ((*it)->getScope() == scope && (*it)->isActive())
                return (*it);
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

};

#endif