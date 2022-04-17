/* Definitions */
%{
    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>
    #include <fstream>
    #include <stack>

    #include "../public/Symbol.hpp"
    #include "../public/SymbolTable.hpp"

    /* External Variables */
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyout;
    extern FILE* yyin;
    extern int yylex();
    extern std::stack<unsigned int> commentStack;

    /* Global Variables */
    SymbolTable symtable;
    std::stack<std::string> functionStack;
    unsigned int currentScope;
    


    /* Function Definitions */
     void yyerror (const std::string errorMsg) {
         std::cout << "Error: at line: " << yylineno << ", " << errorMsg << std::endl;
     }
%}

/* Specifies the initial symbol of our grammar. */
%start program

/* Better error messages */
%define parse.error verbose

/* Union of all the types that a symbol can have. */
%union {
    int integer;
    double real;
    char* string;
    unsigned int expression;
    Symbol* symbol;
}

/* Terminal Symbols */
%token<string>  IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR
                LOCAL TRUE FALSE NIL
%token<string>  ASSIGNMENT ADDITION SUBTRACTION MULTIPLICATION DIVISION MODULO
                EQUALITY INEQUALITY INCREMENT DECREMENT GREATER_THAN LESS_THAN
                GREATER_OR_EQUAL LESS_OR_EQUAL
%token<string>  UMINUS
%token<string>  LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET LEFT_SQUARE_BRACKET
                RIGHT_SQUARE_BRACKET LEFT_PARENTHESES RIGHT_PARENTHESES
                SEMICOLON COMMA COLON DOUBLE_COLON DOT DOUBLE_DOT
%token<string>  ID
%token<integer> INTEGER
%token<real>    REAL
%token<string>  STRING
%token<string>  ERROR

/* Non Terminal Symbols */
%type<expression> expr
%type<expression> assignexpr
%type<expression> term
%type<expression> primary
%type<symbol> lvalue

/* Rules for priority and associativeness.*/
%right ASSIGNMENT
%left OR
%left AND
%nonassoc EQUALITY INEQUALITY
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL
%left ADDITION SUBTRACTION
%left MULTIPLICATION DIVISION MODULO
%right NOT INCREMENT DECREMENT UMINUS
%left DOT DOUBLE_DOT
%left LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%left LEFT_PARENTHESES RIGHT_PARENTHESES
%nonassoc PUREIF
%nonassoc ELSE

/* Grammar */
%%
program
    : statements {
    };

statements
    : statements stmt {   
    }
    | %empty
    ;

stmt
    : expr SEMICOLON {
    }
    | ifstmt {
    }
    | whilestmt {
    }
    | forstmt{
    }
    | returnstmt {
    }
    | BREAK SEMICOLON {
    }
    | CONTINUE SEMICOLON {
    }
    | block {
    }
    | funcdef {
    }
    | SEMICOLON {
    }
    ;

expr
    : assignexpr {
    }
    | expr ADDITION expr {

    }
    | expr SUBTRACTION expr {

    }
    | expr MULTIPLICATION expr {

    }
    | expr DIVISION expr {

    }
    | expr MODULO expr {
    }
    | expr GREATER_THAN expr {

    }
    | expr LESS_THAN expr {

    }
    | expr GREATER_OR_EQUAL expr {

    }
    | expr LESS_OR_EQUAL expr {

    }
    | expr EQUALITY expr {

    }
    | expr INEQUALITY expr {

    }
    | expr AND expr {

    }
    | expr OR expr {

    }
    | term {
    };

term
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
    }
    | SUBTRACTION expr %prec UMINUS {
    }
    | NOT expr {
    }
    | INCREMENT lvalue {
        Symbol* symbol = $2;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot increment the value of a function.");
        }else if ( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | lvalue INCREMENT {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot increment the value of a function.");
        }else if ( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | DECREMENT lvalue {
        Symbol* symbol = $2;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot decrement the value of a function.");
        }else if ( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | lvalue DECREMENT {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot decrement the value of a function.");
        }else if ( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | primary {
    }
    | ERROR {
    }
    ;

assignexpr
    : lvalue ASSIGNMENT expr {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC) { // The symbol is a function.
            yyerror("cannot change the value of a function.");
        } else if( !symbol->isActive() ) { // The symbol didn't exist.
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    };

primary
    : lvalue {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up ignore.
        else if( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | call {
    }
    | objectdef {
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES {
    }
    | const {
    };

lvalue 
    : ID {
        Symbol* search = symtable.lookup($1, currentScope);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search == NULL ) // If no symbol was found.
            $$ = new Symbol($1, type, yylineno, currentScope, false);
        else if( !functionStack.empty() ) { // If we are in a function.
            if ( search->getScope() == 0 || 
                    search->getScope() == currentScope || 
                    search->getType() == USERFUNC ||
                    search->getType() == LIBRARYFUNC)
            {
                $$ = search;
            }
            else {
                yyerror("unable to access this variable.");
                $$ = NULL;
            } 
        } else // If not in a function and the symbol was found.
            $$ = search;
        
    }
    | LOCAL ID {
        Symbol* search = symtable.lookup($2, currentScope);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search != NULL && search->getScope() == currentScope )
            $$ = search;
        else if( !symtable.contains($2, LIBRARYFUNC) )
            $$ = new Symbol($2, type, yylineno, currentScope, false);
        else if( symtable.contains($2, LIBRARYFUNC) )
            yyerror("trying to shadow a Library Function.");

    }
    | DOUBLE_COLON ID {
        Symbol* search = symtable.get($2, 0);

        if( search == NULL ){
            yyerror("the global symbol you are trying to access doesn't exist.");
            $$ = NULL;
        } else
            $$ = search;
            
    }
    | member {
        $$ = NULL;
    };

member
    : lvalue DOT ID {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up, ignore.
        else if( !symbol->isActive() ) { // If the symbol doesn't exist.
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up, ignore.
        else if( !symbol->isActive() ) { // If the symbol doesn't exist.
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | call DOT ID {
    }
    | call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
    };

call
    : call LEFT_PARENTHESES elist RIGHT_PARENTHESES {
    }
    | lvalue callsufix {
        Symbol* symbol = $1;

        if ( symbol == NULL ); // An error came up ignore.
        else if( !symbol->isActive() ) { // Symbol we are trying to call doesn't exist so we create it.
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES LEFT_PARENTHESES elist RIGHT_PARENTHESES {
    };

callsufix
    : normcall {
        
    }
    | methodcall {
        
    };

normcall 
    : LEFT_PARENTHESES elist RIGHT_PARENTHESES {
    }

methodcall
    : DOUBLE_DOT ID LEFT_PARENTHESES elist RIGHT_PARENTHESES {
    };

elist
    : expr nextexpr {
    }
    | %empty
    ;

nextexpr
    : COMMA expr nextexpr {        
    }
    | %empty
    ;

objectdef
    : LEFT_SQUARE_BRACKET elist RIGHT_SQUARE_BRACKET {
    }
    | LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {
    };

indexed
    : indexedelem nextindexed {
    }
    ;

nextindexed
    : COMMA indexedelem nextindexed {
    }
    | %empty
    ;

indexedelem
    : LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET{

    };

block
    : LEFT_CURLY_BRACKET {currentScope++;} statements RIGHT_CURLY_BRACKET {symtable.hide(currentScope--);} {
    };

funcdef
    : FUNCTION ID {
        // TODO: check if valid function.
        functionStack.push($2);
    } LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {        
        
    }
    | FUNCTION LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {
        functionStack.pop();
    };

const
    : INTEGER {

    }
    | REAL{

    }
    | STRING{

    }
    | NIL{

    }
    | TRUE{

    }
    | FALSE{

    };

idlist
    : ID nextid {
    }
    | %empty
    ;

nextid
    : COMMA ID nextid {
    }
    | %empty
    ;

ifstmt
    : IF LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt %prec PUREIF {
    }
    | IF LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt ELSE stmt {
    };

whilestmt
    : WHILE LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt {
    };

forstmt 
    : FOR LEFT_PARENTHESES elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESES stmt {
        
    };

returnstmt
    : RETURN SEMICOLON {        
    }
    | RETURN expr SEMICOLON {
    };
%%

int main(int argc, char** argv) {
    // Argument Checking.
    if(argc > 3) {
        fprintf(stderr, "Too many input arguments\n");
        return 1;
    }
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            std::cerr << "Cannot read file: " << argv[1] << std::endl;
            return 1;
        }
    } else {
        yyin = stdin;
    }
    
    // Initialization
    symtable = SymbolTable();
    functionStack = std::stack<std::string>();
    currentScope = 0;

    yyparse();
    

    // Ending Lexical Analysis
    if ( argc > 1)
        fclose(yyin);

    if ( argc == 3) {
        symtable.printSymbolsInFile(argv[2]);
    } else
        symtable.printSymTable();

    return 0;
}