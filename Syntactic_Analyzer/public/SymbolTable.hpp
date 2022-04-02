#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <unordered_map>
#include <list>

#include "Symbol.hpp"


class SymbolTable {

private:
    std::unordered_multimap<std::string, Symbol*> m_table;
    unsigned int m_size;
    unsigned int maxScope;

    void printSymbols(unsigned int scope) {
        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getScope() == scope)
                std::cout << it->second->toString() << std::endl;
        }
    }

public:
    SymbolTable() {
        m_table = std::unordered_multimap<std::string, Symbol*>();
        m_size = 0;
        maxScope = 0;
    }

    bool contains(std::string id) {
        return m_table.find(id) != m_table.end();
    }

    bool contains(std::string id, Symbol_T type) {
        auto it = m_table.find(id);
        while (it != m_table.end()) {
            if (it->second->getType() == type && it->second->getId() == id) return true;
            it++;
        }
        
        return false;
    }

    bool contains(std::string id, unsigned int scope) {
        auto it = m_table.find(id);
        while (it != m_table.end()) {
            if (it->second->getScope() == scope) return true;
            it++;
        }
        return false;
    }

    Symbol* get(std::string id, unsigned int scope) {
        auto it = m_table.find(id);
        while (it != m_table.end()) {
            if (it->second->getScope() == scope) return (it->second);
            it++;
        }

        return NULL;
    }

    Symbol* get(std::string id) {
        auto search = m_table.find(id);
        return search == m_table.end() ? NULL : search->second;
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


    int insert(std::string id, Symbol* symbol) {
        int isVar = -1;
        if (symbol == NULL) return 0;

        if(contains(symbol->getId()) == 1){
            if(symbol->getType() == USER_FUNCTION ){
                isVar = 0;
            } else if((symbol->getType() == GLOBAL_VARIABLE) || (symbol->getType() == LOCAL_VARIABLE)){
                isVar = 1;
            } else {
                isVar = -1;
            }

            if(contains(symbol->getId(),symbol->getType()) != 1){
                if(isVar == 0){
                    std::cout << "error: variable redefined as a function" << std::endl;
                    return 0;
                }
                else if (isVar == 1){
                    std::cout << "error: function used as an l-value" << std::endl;
                    return 0;
                }
            } 
        } 


        if (symbol->getScope() > maxScope)
            maxScope = symbol->getScope();

        m_table.insert({ id, symbol });

        return 0;
    }

    void printSymTable() {
        for (auto i = 0; i <= maxScope; i++) {
            std::cout << "-----------\t Scope #" << std::to_string(i) << "\t-----------" << std::endl;
            printSymbols(i);
            std::cout << std::endl << std::endl;
        }
    }

};

#endif