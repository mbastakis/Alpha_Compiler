#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <iostream>

typedef enum {
    GLOBAL_VARIABLE,
    LOCAL_VARIABLE,
    FORMAL_ARGUMENT,
    LIBRARY_FUNCTION,
    USER_FUNCTION
} Symbol_T;

class Symbol {

private:
    std::string m_id;
    Symbol_T m_type;
    unsigned int m_scope;
    unsigned int m_line;

public:
    Symbol() = default;
    ~Symbol() = default;

    Symbol(std::string id, Symbol_T type, unsigned int scope, unsigned int line) {
        m_id = id;
        m_type = type;
        m_scope = scope;
        m_line = line;
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


};

#endif