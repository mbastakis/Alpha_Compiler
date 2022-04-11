#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <iostream>
#include <list>

typedef enum {
    GLOBALVAR = 0,
    LOCALVAR,
    FORMALVAR,
    LIBRARYFUNC,
    USERFUNC
} Symbol_T;

static const char* enum_str[] =
{ "global variable", "local variable", "formal argument", "library function", "user function" };

class Symbol {

private:
    std::string m_id;
    Symbol_T m_type;
    unsigned int m_scope;
    unsigned int m_line;
    bool m_isActive;
    std::list<Symbol*> m_argsList;

public:
    Symbol() = default;
    ~Symbol() = default;

    Symbol(std::string id, Symbol_T type, unsigned int line, unsigned int scope, bool isActive) {
        m_id = id;
        m_type = type;
        m_scope = scope;
        m_line = line;
        m_isActive = isActive;
        m_argsList = std::list<Symbol*>();
    }

    std::string getId() {
        return m_id;
    }

    Symbol_T getType() {
        return m_type;
    }

    unsigned int getLine() {
        return m_line;
    }

    unsigned int getScope() {
        return m_scope;
    }

    bool isActive() {
        return m_isActive;
    }

    void setActive(bool boolean) {
        m_isActive = boolean;
    }

    void setId(std::string id) {
        m_id = id;
    }

    void setType(Symbol_T type) {
        m_type = type;
    }

    void setLine(unsigned int line) {
        m_line = line;
    }

    void setScope(unsigned int scope) {
        m_scope = scope;
    }

    void insertArgument(Symbol* symbol) {
        m_argsList.push_back(symbol);
    }

    Symbol* getArgument(std::string id) {
        for (auto it = m_argsList.begin(); it != m_argsList.end(); it++) {
            if ((*it)->getId().compare(id) == 0) return (*it);
        }

        return NULL;
    }

    bool containsArgument(std::string id) {
        for (auto it = m_argsList.begin(); it != m_argsList.end(); it++) {
            if ((*it)->getId().compare(id) == 0) return true;
        }

        return false;
    }

    /*number of arguments in a function*/

    std::string toString() {
        std::string qm = "\"";
        std::string lb = "[";
        std::string rb = "]";
        std::string lp = "(";
        std::string rp = ")";
        std::string sp = " ";

        return (qm + m_id + qm + sp + \
            lb + enum_str[m_type] + rb + sp + \
            lp + "line " + std::to_string(m_line) + rp + sp + \
            lp + "scope " + std::to_string(m_scope) + rp + sp
            );
    }


};

#endif