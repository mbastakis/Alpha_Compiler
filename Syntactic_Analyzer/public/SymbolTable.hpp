#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <map>
#include <list>

#include "Symbol.hpp"

class SymbolTable {

private:
    std::multimap<std::string, Symbol*> m_table;
    unsigned int m_size;
    unsigned int maxScope;

    static bool compare (Symbol* first, Symbol* second) {
        return first->getLine() < second->getLine();
    }

    void printSymbols(unsigned int scope) {
        auto symList = std::list<Symbol*>();
        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getScope() == scope)
                symList.push_back(it->second);
        }
        symList.sort(compare);

        for (auto it = symList.begin(); it != symList.end(); ++it ) {
            std::cout << (*it)->toString() << std::endl;
        }
    }

public:
    SymbolTable() {
        m_table = std::multimap<std::string, Symbol*>();
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
            if (it->second->getScope() == scope && it->second->getId() == id) return true;
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
            if(  search != NULL ) return search;
            scope--;
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

    int checkLibraryFunction(std::string name){
        if(name.compare("print")==0 || name.compare("input")==0 || name.compare("objectmemberkeys")==0 || name.compare("objecttotalmembers")==0
           || name.compare("objectcopy") == 0 || name.compare("totalarguments") == 0 || name.compare("argument") == 0 || name.compare("typeof")==0
            || name.compare("strtonum") == 0 || name.compare("sqrt") == 0 || name.compare("cos") == 0 || name.compare("sin") == 0) {
            return -1;
        }
        return 0;
    }

    int getScope(std::string id,Symbol_T type) {

        for (auto it = m_table.begin(); it != m_table.end(); ++it) {
            if (it->second->getType() == type && it->second->getId() == id)
                return it->second->getScope();
        }
        return -1;
    }


    int insert(Symbol* symbol) {
        
        if (symbol == NULL) return 0;

        

        if(contains(symbol->getId()) == 1){
            if(symbol->getType() == USER_FUNCTION ){
            
                if(contains(symbol->getId(),symbol->getType()) != 1){  
                    if((contains(symbol->getId(),FORMAL_ARGUMENT) == 1 && symbol->getScope() == getScope(symbol->getId(),FORMAL_ARGUMENT)) || 
                        contains(symbol->getId(),LOCAL_VARIABLE) == 1 && symbol->getScope() == getScope(symbol->getId(),LOCAL_VARIABLE) ||
                        contains(symbol->getId(),GLOBAL_VARIABLE) == 1){
                        std::cout << "error: variable redefined as a function at line "<< symbol->getLine() << std::endl;
                        return 0;
                    }
                }
            } else if(symbol->getType() == GLOBAL_VARIABLE || symbol->getType() == LOCAL_VARIABLE){
                
                if(contains(symbol->getId(),symbol->getType()) != 1 ){
                    if((contains(symbol->getId(),USER_FUNCTION) == 1 && symbol->getScope() == getScope(symbol->getId(),USER_FUNCTION))){                       
                        std::cout << "error: function used as an l-value at line " << symbol->getLine() << std::endl;
                        return 0;                       
                    }
                } 
            } /*else if(symbol->getType() == LOCAL_VARIABLE){ // THE SAME LINE WITH GLOBAL VARIABLE
                if(contains(symbol->getId(),USER_FUNCTION) == 1 ){
                    std::cout << "error: function used as an l-value at line " << symbol->getLine() << std::endl;
                        return 0;
                }
            } */   
        }


        if (symbol->getScope() > maxScope)
            maxScope = symbol->getScope();

        m_table.insert({ symbol->getId(), symbol });

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