/* Definitions */
%{
    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>

    #include "../public/Symbol.hpp"
    #include "../public/SymbolTable.hpp"

    /* Defines */
    #define FUNC 1000

    /* External Variables */
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    extern unsigned int tokenCounter;
    extern std::stack<unsigned int> commentStack;
    extern int yylex();

    /* Global Variables */
    unsigned int currentScope = 0;
    SymbolTable symtable;

    int function_open = 0;
    int stmt_open=0;

    std::stack<std::string> prFunction;
    std::stack<std::list<std::string>> blockStack;
    std::list<std::string> errorList;

    Symbol* argumentsSymbol;
    Symbol* currentSymbol;

    int currentLine = 1;
    int newNameFunction=1;
    bool isCall = false;
    std::string newName="";

    /* Function Definitions */
     void yyerror (char const *s) {      
        fprintf (stderr, "%s ", s);
        fprintf(stderr, "at line %d.\n", yylineno);
    }
    void printError (std::string str) {
        std::cerr << str <<  std::endl;
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
    : statements stmt{
        
    }
    | %empty
    ;

stmt
    : expr SEMICOLON
    | ifstmt {
    }
    | whilestmt {
    }
    | forstmt{
    }
    | returnstmt {
    }
    | BREAK SEMICOLON {
        if(stmt_open == 0){
            printf("Error: break outside of statement, Line: %d\n" ,yylineno);
        } 
        
    }
    | CONTINUE SEMICOLON {
        if(stmt_open == 0){
            printf("Error: continue outside of statement, Line: %d\n" ,yylineno);
        } 
    }
    | block 
    | funcdef
    | SEMICOLON
    ;

expr
    : assignexpr {

    }
    | expr ADDITION expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot add functions");
        }
    }
    | expr SUBTRACTION expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot subtract functions");
        }
    }
    | expr MULTIPLICATION expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot multiply functions");
        }
    }
    | expr DIVISION expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot divide functions");
        }
    }
    | expr MODULO expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot mod functions");
        }
    }
    | expr GREATER_THAN expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr LESS_THAN expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr GREATER_OR_EQUAL expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr LESS_OR_EQUAL expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr EQUALITY expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr INEQUALITY expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr AND expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
    }
    | expr OR expr {
        if($1 == FUNC || $3 == FUNC) {
            yyerror("Error: cannot compare functions");
        }
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
        if( $2 != NULL ) {
            if( $2->getType() == GLOBALVAR || $2->getType() == LOCALVAR) {
                symtable.insert($2);
            }else if( $2->getType() == USERFUNC || $2->getType() == LIBRARYFUNC ) {
                yyerror("Error: Cannot increment function");
            }
        }
    }
    | lvalue INCREMENT {
        if( $1 != NULL ) {
            if( $1->getType() == GLOBALVAR || $1->getType() == LOCALVAR) {
                symtable.insert($1);
            }else if( $1->getType() == USERFUNC || $1->getType() == LIBRARYFUNC ) {
                yyerror("Error: Cannot increment function");
            }
        }
    }
    | DECREMENT lvalue {
        if( $2 != NULL ) {
            if( $2->getType() == GLOBALVAR || $2->getType() == LOCALVAR) {
                symtable.insert($2);
            }else if( $2->getType() == USERFUNC || $2->getType() == LIBRARYFUNC ) {
                yyerror("Error: Cannot decrement function");
            }
        }
    }
    | lvalue DECREMENT {
        if( $1 != NULL ) {
            if( $1->getType() == GLOBALVAR || $1->getType() == LOCALVAR) {
                symtable.insert($1);
            }else if( $1->getType() == USERFUNC || $1->getType() == LIBRARYFUNC ) {
                yyerror("Error: Cannot decrement function");
            }
        }
    }
    | primary {
        $$ = $1;
    }
    | ERROR {
        YYABORT;
    }
    ;

assignexpr
    : lvalue ASSIGNMENT expr {  
       if( $1 != NULL ) {
            if( $1->getType() == GLOBALVAR || $1->getType() == LOCALVAR) {
                
                if($3 == FUNC){
                    Symbol_T type = symtable.contains($1->getId(), LIBRARYFUNC) ? LIBRARYFUNC : USERFUNC;
                    symtable.insert(new Symbol($1->getId(), type, $1->getLine(), $1->getScope(), true));
                }else 
                    symtable.insert($1);
            }else if( $1->getType() == USERFUNC || $1->getType() == LIBRARYFUNC ) {
                yyerror("Error: Cannot assign to a function");
            }
        }
            
    };

primary
    : lvalue {    
        if($1 != NULL && !symtable.contains($1->getId())){
            symtable.insert(new Symbol($1->getId(), $1->getType(), $1->getLine(), $1->getScope(), true));
        }
       if($1 != NULL && ($1->getType() == USERFUNC || $1->getType() == LIBRARYFUNC))
            $$ = FUNC;
        currentSymbol = $1;
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
        if (symtable.recursiveLookup($1, currentScope)==-1){ //the symbol does not exist
            if (currentScope == 0){ 
                    $$ = new Symbol($1, GLOBALVAR, yylineno, currentScope, true);
                    argumentsSymbol = new Symbol($1, GLOBALVAR, yylineno, currentScope, true);
            } else {
                    $$ = new Symbol($1, LOCALVAR, yylineno, currentScope, true);
                    argumentsSymbol = new Symbol($1, LOCALVAR, yylineno, currentScope, true);
            }
        } else {
            Symbol* symbol=symtable.getNearestSymbol($1, currentScope);
            if (symtable.recursiveLookup($1, currentScope)>0) { //the symbol exist but it is not global
                if (symbol->getType()==USERFUNC){
                    $$ = new Symbol($1, USERFUNC, yylineno, currentScope, true);
                    argumentsSymbol = new Symbol($1, USERFUNC, yylineno, currentScope, true);
                } else {
                    /*check if it exists in a block with no function and if it isn't print error */
                    if(!symtable.contains($1,currentScope)){
                        blockStack.top().push_front(std::string("Error: Cannot access ") + std::string($1) + std::string(" in scope ") + std::to_string(currentScope) + std::string(" at line ") + std::to_string(yylineno) + ".");
                   }
                   $$ = NULL;
                   argumentsSymbol = NULL;
                }
            } else {
                if (symbol->getType()==LIBRARYFUNC) {
                    $$ = new Symbol($1, LIBRARYFUNC, yylineno, currentScope, true);
                    argumentsSymbol = new Symbol($1, LIBRARYFUNC, yylineno, currentScope, true);
                } else {
                   if( symbol->getType() == USERFUNC){
                        $$ = new Symbol($1, USERFUNC, yylineno, 0, true);
                        argumentsSymbol = new Symbol($1, USERFUNC, yylineno, 0, true);
                   }
                    else {
                        $$ = NULL;
                        argumentsSymbol = NULL;
                    }
                }
            }
            
        }
    }
    | LOCAL ID {
        if (symtable.lookup($2, currentScope) == NULL){          
            if (!symtable.contains($2, LIBRARYFUNC)) {
                if (currentScope == 0) {
                    symtable.insert(new Symbol($2, GLOBALVAR, yylineno, currentScope, true));
                } else {
                    symtable.insert(new Symbol($2, LOCALVAR, yylineno, currentScope, true));
                }
            } else {
                yyerror("Error: trying to shadow library function");
            }
        }
        $$ = NULL;
    }
    | DOUBLE_COLON ID {

        
        if(!symtable.contains($2))
            yyerror("Error: variable does not exist");
        
        else if(!symtable.contains($2,0))
            yyerror("Error: the variable is not global");
        
        if(symtable.contains($2,LIBRARYFUNC) || symtable.contains($2, USERFUNC)) {
            isCall = true;
        }

        $$ = NULL;

    }
    | member {

    };

member
    : lvalue DOT ID {
    }
    | lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {

    }
    | call DOT ID {

    }
    | call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {

    };

call
    : call LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        
    }
    | lvalue callsufix {
        if(isCall) {
            isCall = false;
        }      
        else if( $1 == NULL ){
            yyerror("Error: This variable cannot be called");
        }
        else{           
            if($1->getType() ==  GLOBALVAR && !symtable.contains($1->getId())){
                symtable.insert($1);}
            else if($1->getType() ==  LOCALVAR && !symtable.contains($1->getId())){
                symtable.insert($1);}
        }
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES 
      LEFT_PARENTHESES elist RIGHT_PARENTHESES {

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
        if(argumentsSymbol != NULL && (argumentsSymbol->getType() == GLOBALVAR || argumentsSymbol->getType() == LOCALVAR)){
            if(!symtable.contains(argumentsSymbol->getId(), argumentsSymbol->getScope()))
                symtable.insert(argumentsSymbol);
        }
    }
    | %empty
    ;

nextexpr
    : COMMA expr nextexpr {
        
        if(argumentsSymbol != NULL && (argumentsSymbol->getType() == GLOBALVAR || argumentsSymbol->getType() == LOCALVAR)){
            if(!symtable.contains(argumentsSymbol->getId(), argumentsSymbol->getScope()))
                symtable.insert(argumentsSymbol);
        }

            
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
    : LEFT_CURLY_BRACKET {currentScope++;

        blockStack.push(std::list<std::string>());

    
    } statements RIGHT_CURLY_BRACKET { currentScope--; } {
        symtable.hide(currentScope + 1);
        errorList = blockStack.top();
        blockStack.pop();
    };

funcdef
    : FUNCTION {currentLine = yylineno; } ID { prFunction.push($3);
        if(symtable.contains($3, LIBRARYFUNC)) {
            yyerror("Error: function shadows library function");
        } else if (symtable.lookup($3, currentScope) != NULL) {
            yyerror("Error: function already exists");
        } else {
            symtable.insert(new Symbol($3, USERFUNC, currentLine, currentScope, true));
        }
        } LEFT_PARENTHESES idlist RIGHT_PARENTHESES { function_open++; } block { 
                function_open--; 
                prFunction.pop();
                if( !errorList.empty() ) {
                    for(auto it = errorList.begin(); it != errorList.end(); it++) {
                        printError((*it));
                    }
                }
            } {        
        
    }
    | FUNCTION {currentLine = yylineno; newName= "_f" + std::to_string(newNameFunction++);
        prFunction.push(newName);
        symtable.insert(new Symbol(newName, USERFUNC, currentLine, currentScope, true));
        
        } LEFT_PARENTHESES idlist RIGHT_PARENTHESES { function_open++; } block { function_open--; prFunction.pop();} {
        
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
        if(symtable.contains($1, LIBRARYFUNC)) {
            yyerror("Error: formal argument shadows library function");
        } else if (symtable.lookup($1, currentScope+1) != NULL){
            yyerror("Error: formal argument redeclaration");
        } else {
            symtable.insert(new Symbol($1, FORMALVAR, yylineno, currentScope+1, true));
        }
    }
    | %empty
    ;

nextid
    : COMMA ID nextid {
        if(symtable.contains($2, LIBRARYFUNC)) {
            yyerror("Error: formal argument shadows library function");
        } else if (symtable.lookup($2, currentScope+1) != NULL){
            yyerror("Error: formal argument redeclaration");
        } else {
            symtable.insert(new Symbol($2, FORMALVAR, yylineno, currentScope+1, true));
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
    : WHILE {currentLine = yylineno; stmt_open++;} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt {stmt_open--;} {
    };

forstmt 
    : FOR {currentLine = yylineno; stmt_open++;} LEFT_PARENTHESES elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESES stmt {stmt_open--;} {
        
    };

returnstmt
    : RETURN SEMICOLON {
        if(function_open == 0){
            printf("Error: return outside of function, Line: %d\n" ,yylineno);
        } 
               
    }
    | RETURN expr SEMICOLON {
        if(function_open == 0){
            printf("Error: return outside of function, Line: %d\n" ,yylineno);
        }
       
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
    commentStack = std::stack<unsigned int>();
    prFunction = std::stack<std::string>();
    blockStack = std::stack<std::list<std::string>>();
    tokenCounter = 0;
    currentScope = 0;

    yyparse();

    // Ending Lexical Analysis
    if ( argc > 1)
        fclose(yyin);

    if ( argc == 3) {
        FILE *output_file;
        output_file = fopen(argv[2], "w");
        /* printOutput(output_file); */
        fclose(output_file);
    } else
        /* printOutput(NULL); */
        symtable.printSymTable();

    return 0;
}


void checkAndInsert(Symbol* symbol) {
    if( symbol != NULL ) {
            if( symbol->getType() == GLOBALVAR || symbol->getType() == LOCALVAR) {
                symtable.insert(symbol);
            }else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) {
                yyerror("Error: Cannot increment function");
            }
    }
}