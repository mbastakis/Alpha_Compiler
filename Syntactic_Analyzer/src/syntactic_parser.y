/* Definitions */
%{
    /* Includes */

    /* External Variables */
    extern int yylineno;
    extern char* yytext;
    extern std::stack<unsigned int> commentStack;

    /* Function Declarations */
    void yyerror(char* bisonProvidedMessage);
    void yylex(void);

%}

/* Specifies the initial symbol of our grammar. */
%start program

/* Union of all the types that a symbol can have. */
%union {
    std::string string;
    int integer;
    double real;
}

/* Terminal Symbols */
%token<string>

/* Grammar */
%%

%%