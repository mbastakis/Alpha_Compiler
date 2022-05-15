/* Definitions */
%{
    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>
    #include <fstream>
    #include <stack>
    #include <vector>

    #include "../public/Symbol.hpp"
    #include "../public/SymbolTable.hpp"
    #include "../public/IntermediateCode.hpp"

    /* Defines */
    #define FUNCTION_TYPE 6969

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
    std::stack<unsigned int> scopeOffsetStack;
    std::stack<bool> blockStack;
    unsigned int currentScope;

    bool isFunc;
    int functionOpen;
    int stmtOpen;
    int currentLine;
    int newNameFunction;
    std::string newName;
    std::string currentFunctionName;

    /* Offset Usage */
    /* Note, isws xreiastoume kapoio stack apo offsets gia emfolebmenes sunartisis */
    unsigned int programVarOffset;
    unsigned int functionLocalOffset;
    unsigned int formalArgOffset;
    unsigned int scopeSpaceCounter;

    /* Quad */
    std::vector<Quad*> Quads;


    /* Function Definitions */
     void red() {
         std::cout << "\033[0;31m";
     }

     void reset() {
         std::cout << "\033[0;37m";
     }

     void yyerror (const std::string errorMsg) {
         red();
         std::cout << "Error: at line: " << yylineno << ", " << errorMsg << std::endl;
         reset();
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
    //Expr* expression;
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
%type<expression> const
%type<symbol> lvalue
// EVA
// %type<string> funcname
%type<integer> funcbody
%type<symbol> funcprefix
%type<symbol> funcdef

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
        if(stmtOpen == 0)
            yyerror("break outside of statement");
    }
    | CONTINUE SEMICOLON {
        if(stmtOpen == 0)
            yyerror("continue outside of statement");
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
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot add non numeric value");
    }
    | expr SUBTRACTION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot subtract non numeric value");
    }
    | expr MULTIPLICATION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot multiply non numeric value");

    }
    | expr DIVISION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot divide non numeric value");
    }
    | expr MODULO expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot do the mod operation with non numeric value");
    }
    | expr GREATER_THAN expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr LESS_THAN expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr GREATER_OR_EQUAL expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr LESS_OR_EQUAL expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr EQUALITY expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr INEQUALITY expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr AND expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | expr OR expr {
        if( $1 == FUNCTION_TYPE || $3 == FUNCTION_TYPE)
            yyerror("Cannot compare with a function");
    }
    | term {
        $$ = $1;
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
        } else if ( !symbol->isActive() ) {
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
        } else if ( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | lvalue DECREMENT {
        Symbol* symbol = $1;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot decrement the value of a function.");
        } else if ( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | primary {
        $$ = $1;
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

        if( symbol != NULL && symbol->getType() == USERFUNC)
            $$ = USERFUNCTION_EXPR;
        else if(symbol != NULL && symbol->getType() == LIBRARYFUNC)
            $$ = LIBRARYFUNCTION_EXPR;
        else
            $$ = VAR_EXPR;
    }
    | call {
    }
    | objectdef {
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES {
    }
    | const {
        $$ = $1;
    };

lvalue
    : ID {
        Symbol* search = symtable.recursiveLookup($1, currentScope, blockStack);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search == NULL ) {// If no symbol was found.
            std::cout << "New id: " << $1 << " scopespace: " << getCurrentScopespace() << std::endl;
            $$ = new Symbol($1, type, yylineno, currentScope, false);
            $$->setOffset(getCurrentScopeOffset());
            incCurrentScopeOffset();
        }
        else {
            if( search->getType() == SYMERROR ) {
                yyerror("cannot access this variable.");
                $$ = NULL;
            }else
                $$ = search;
        }
    }
    | LOCAL ID {
        Symbol* search = symtable.lookup($2, currentScope);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search != NULL && search->getScope() == currentScope )
            $$ = search;
        else if( !symtable.contains($2, LIBRARYFUNC) )
            $$ = new Symbol($2, type, yylineno, currentScope, false);
        else if( symtable.contains($2, LIBRARYFUNC) ) {
            yyerror("trying to shadow a Library Function.");
            $$ = NULL;
        }

        incCurrentScopeOffset();

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
    : LEFT_CURLY_BRACKET {currentScope++; blockStack.push(isFunc); isFunc = false;} statements RIGHT_CURLY_BRACKET {symtable.hide(currentScope--); blockStack.pop();} {
    };

// EVA
funcname
    : ID {
        currentFunctionName = $1;
    }
    | %empty {
        currentFunctionName = "_f" + std::to_string(newNameFunction++);
    }
    ;

funcprefix
    : FUNCTION {currentLine = yylineno;} funcname {
        // currentFunctionName = "_Error_";
        // functionStack.push($3);
        scopeOffsetStack.push(getCurrentScopeOffset());
        incCurrentScopeOffset();
        resetFormalArgsOffset();

        if(symtable.contains(currentFunctionName, LIBRARYFUNC)) {
            yyerror("function shadows library function.");
        } else if (symtable.scopeLookup(currentFunctionName, currentScope) != NULL) {
            yyerror("function already exists.");
        } else {
            functionStack.push(currentFunctionName);
            Symbol* function_symbol = new Symbol(currentFunctionName, USERFUNC, currentLine, currentScope, true);
            // function_symbol->setOffset(getCurrentScopeOffset());
            symtable.insert(function_symbol);
            $$ = function_symbol;
            emit(OP_FUNCSTART, NULL, NULL, symbolToExpr(function_symbol) , nextQuadLabel(), yylineno);
            std::cout << "Entering function " << currentFunctionName << " curr offset " << getCurrentScopeOffset() << std::endl;
            incCurrentScopeOffset();
        }
    }
    ;

funcargs
    : LEFT_PARENTHESES {
        enterScopespace();
        scopeOffsetStack.push(getCurrentScopeOffset());
    } idlist {
        resetFunctionLocalOffset();
    } RIGHT_PARENTHESES {
        functionOpen++;
        isFunc = true;
        enterScopespace();
        resetFunctionLocalOffset();
    }
    ;

funcbody
    : block {
        restoreCurrentScopeOffset(scopeOffsetStack.top());
        scopeOffsetStack.pop();
        exitScopepace();
        $$ = getCurrentScopeOffset();
    }
    ;

funcdef
    : funcprefix funcargs {
        enterScopespace();
        resetFunctionLocalOffset();
    } funcbody {
        exitScopepace();
        functionOpen--;
        Symbol* function_symbol = new Symbol(functionStack.top(), USERFUNC, currentLine, currentScope, true);
        functionStack.pop();
        emit(OP_FUNCEND, NULL, NULL, symbolToExpr(function_symbol), nextQuadLabel(), yylineno);
        restoreCurrentScopeOffset(scopeOffsetStack.top());
        scopeOffsetStack.pop();
    }
    ;

// funcdef
//     : FUNCTION {currentLine = yylineno;} ID {
//         currentFunctionName = "_Error_";
//         functionStack.push($3);
//         if(symtable.contains($3, LIBRARYFUNC)) {
//             yyerror("function shadows library function.");
//         } else if (symtable.scopeLookup($3, currentScope) != NULL) {
//             yyerror("function already exists.");
//         } else {
//             symtable.insert(new Symbol($3, USERFUNC, currentLine, currentScope, true));
//             currentFunctionName = $3;
//         }


//     } LEFT_PARENTHESES idlist RIGHT_PARENTHESES {functionOpen++; isFunc = true;} block {
//         functionOpen--;
//         functionStack.pop();
//     }
//     | FUNCTION{
//         currentLine = yylineno;
//         newName= "_f" + std::to_string(newNameFunction++);
//         functionStack.push(newName);
//         symtable.insert(new Symbol(newName, USERFUNC, currentLine, currentScope, true));
//         currentFunctionName = newName;

//     } LEFT_PARENTHESES idlist RIGHT_PARENTHESES {functionOpen++; isFunc = true;} block {
//         functionOpen--;
//         functionStack.pop();
//     };

const
    : INTEGER {
        $$ = CONST_NUMBER_EXPR;
    }
    | REAL{
        $$ = CONST_NUMBER_EXPR;
    }
    | STRING{
        $$ = CONST_STRING_EXPR;
    }
    | NIL{
        $$ = NIL_EXPR;
    }
    | TRUE{
        $$ = CONST_BOOLEAN_EXPR;
    }
    | FALSE{
        $$ = CONST_BOOLEAN_EXPR;
    };

idlist
    : ID nextid {
        if(currentFunctionName.compare("_Error_") != 0) {
                Symbol* function = symtable.lookup(currentFunctionName, currentScope);
            if(symtable.contains($1, LIBRARYFUNC)) {
                yyerror("formal argument shadows library function.");
            } else if (function->containsArgument($1)){
                yyerror("formal argument redeclaration.");
            } else {
                std::cout << "new formal: " << $1 << std::endl;
                Symbol* newSym = new Symbol($1, FORMALVAR, yylineno, currentScope+1, true);
                newSym->setOffset(getCurrentScopeOffset());
                symtable.insert(newSym);
                function->insertArgument(newSym);
                incCurrentScopeOffset();
            }
        }
    }
    | %empty
    ;

nextid
    : COMMA ID nextid {
        if( currentFunctionName.compare("_Error_") != 0 ) {
            Symbol* function = symtable.lookup(currentFunctionName, currentScope);
            if(symtable.contains($2, LIBRARYFUNC)) {
                yyerror("formal argument shadows library function.");
            } else if (function->containsArgument($2)){
                yyerror("formal argument redeclaration.");
            } else {
                std::cout << "new formal: " << $2 << std::endl;
                Symbol* newSym = new Symbol($2, FORMALVAR, yylineno, currentScope+1, true);
                newSym->setOffset(getCurrentScopeOffset());
                symtable.insert(newSym);
                function->insertArgument(newSym);
                incCurrentScopeOffset();
            }
        }
    }
    | %empty
    ;

ifstmt
    : IF LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt %prec PUREIF {
    }
    | IF LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt ELSE stmt {
    };

whilestmt
    : WHILE{currentLine = yylineno; stmtOpen++;} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt {stmtOpen--;} {
    };

forstmt
    : FOR{currentLine = yylineno; stmtOpen++;} LEFT_PARENTHESES elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESES stmt {stmtOpen--;} {

    };

returnstmt
    : RETURN SEMICOLON {
        if(functionOpen == 0)
            yyerror("return outside of function");

    }
    | RETURN expr SEMICOLON {
        if(functionOpen == 0)
            yyerror("return outside of function");

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
    blockStack = std::stack<bool>();

    currentScope = 0;
    functionOpen = 0;
    stmtOpen = 0;
    newNameFunction = 1;
    newName = "";
    isFunc = false;

    programVarOffset = 0;
    functionLocalOffset = 0;
    formalArgOffset = 0;
    scopeSpaceCounter = 1;

    Quads = std::vector<Quad*>();

    // Start the parser
    yyparse();

    // EVA
    printQuads();


    // Ending Lexical Analysis
    if ( argc > 1)
        fclose(yyin);

    if ( argc == 3) {
        symtable.printSymbolsInFile(argv[2]);
    } else
        symtable.printSymTable();

    return 0;
}