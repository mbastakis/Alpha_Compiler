#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <iostream>

typedef enum {
    GLOBAL_VARIABLE = 0,
    LOCAL_VARIABLE,
    FORMAL_ARGUMENT,
    LIBRARY_FUNCTION,
    USER_FUNCTION
} Symbol_T;

static const char* enum_str[] =
{ "global variable", "local variable", "formal argument", "library function", "user function" };

class Symbol {

private:
    std::string m_id;
    Symbol_T m_type;
    unsigned int m_scope;
    unsigned int m_line;

public:
    Symbol() = default;
    ~Symbol() = default;

    Symbol(std::string id, Symbol_T type, unsigned int line, unsigned int scope) {
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