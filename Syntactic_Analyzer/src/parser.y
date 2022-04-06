/* Definitions */
%{
    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>

    #include "../public/Symbol.hpp"
    #include "../public/SymbolTable.hpp"

    /* Defines */
    #define FUNC 1
    #define VAR 2

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
    int is_double=0;
    int is_call=0;
    int is_dot=0;
    int is_stmt=0;

    std::stack<std::string> prFunction;

    int currentLine = 1;
    int newNameFunction=1;
    std::string newName="";


    /* Function Definitions */
     void yyerror (char const *s) {      
        fprintf (stderr, "%s ", s);
        fprintf(stderr, "at line %d.\n", yylineno);
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
//%type<integer> block

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
        is_stmt=0;
    }
    | whilestmt {
        is_stmt=0;
    }
    | forstmt{
        is_stmt=0;
    }
    | returnstmt {
        is_stmt=0;
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
        
    }
    | lvalue INCREMENT {

    }
    | DECREMENT lvalue {

    }
    | lvalue DECREMENT {

    }
    | primary {
    };

assignexpr
    : lvalue ASSIGNMENT expr {  
       if(is_double!=1 && is_dot!=1){ 
        if(symtable.contains($2, LOCALVAR) == 1){
            break; /* LOCALs have already been inserted */
        }
        if(symtable.contains($2, USERFUNC) == 1){
            yyerror("Error: Function used as an l-value ");
        }
        if(symtable.contains($2)) break;
        
        else if($1->getType() == GLOBALVAR || $1->getType() == LOCALVAR) {
            
            symtable.insert(new Symbol($1->getId(), $1->getType(), $1->getLine(), $1->getScope(), true));
        }else {
            yyerror("Error: Not valid variable ");
        }
       }
            
    };

primary
    : lvalue {       
       if(is_double!=1 && is_dot!=1 && is_stmt!=1){
        if($1->getType()>=0 && $1->getType()<=4){
            
            if($1->getType() == GLOBALVAR || $1->getType() == LOCALVAR) {   
                if(!$1->getId().empty()){      
                    symtable.insert(new Symbol($1->getId(), $1->getType(), $1->getLine(), $1->getScope(), true));
                }
             }else {
                yyerror("Error: Not valid variable");
            }
        }
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
        is_dot=0;
        is_double=0;
        
        if (symtable.recursiveLookup($1, currentScope)==-1){ //the symbol does not exist
            if (currentScope == 0){ 
                    $$ = new Symbol($1, GLOBALVAR, yylineno, currentScope, true);
            } else {
                    $$ = new Symbol($1, LOCALVAR, yylineno, currentScope, true);
            }
        } else {
            
            Symbol* symbol=symtable.getNearestSymbol($1, currentScope);
            if (symtable.recursiveLookup($1, currentScope)>0) { //the symbol exist but it is not global
                // if(symtable.contains($1,currentScope) != 1 && symtable.contains($1,LIBRARYFUNC) != 1  && is_call!=1){            
                //     std::cout<<"Error: variable "<< $1 <<" not accessible in "<< prFunction.top() << " at line "<<yylineno <<std::endl;
                // }
                if (symbol->getType()==USERFUNC){
                    $$ = new Symbol($1, USERFUNC, yylineno, currentScope, true);
                } else {
                    /*CHECK IF IT EXIST IN A BLOCK WITH NO FUNCTION AND IF IT ISNT PRINT ERROR*/
                }
            } else {
                if (symbol->getType()==LIBRARYFUNC) {
                    $$ = new Symbol($1, LIBRARYFUNC, yylineno, currentScope, true);
                } else {
                   
                    $$ = NULL;
                }
            }
            
        }
        is_call=0;
    }
    | LOCAL ID {
        is_dot=0;
        is_double=0;
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
        is_call=0;
    }
    | DOUBLE_COLON ID {
        is_dot=0;
        is_double=1;
        is_call=0;
        if(!symtable.contains($2))
            yyerror("Error: variable does not exist");
        
        else if(!symtable.contains($2,0))
            yyerror("Error: the variable is not global");
        
        
        
    }
    | member {

    };

member
    : lvalue DOT ID {
        is_dot=1;
    }
    | lvalue LEFT_SQUARE_BRACKET expr RIGHT_CURLY_BRACKET {

    }
    | call DOT ID {

    }
    | call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {

    };

call
    : call LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        
    }
    | lvalue callsufix {
        is_call=1;
               
        if(!$1->getId().empty()){
            if(is_stmt==0 && symtable.contains($1->getId(),USERFUNC) != 1){
                if (currentScope == 0) {
                        symtable.insert(new Symbol($1->getId(), GLOBALVAR, yylineno, currentScope, true));
                    } else {
                        symtable.insert(new Symbol($1->getId(), LOCALVAR, yylineno, currentScope, true));
                    }
                } 
            else if(symtable.contains($1->getId(),USERFUNC) != 1 && symtable.contains($1->getId(),LIBRARYFUNC) != 1 && is_double!=1) {
                yyerror("Error: This function does not exist");
            }
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
    : LEFT_CURLY_BRACKET {currentScope++;

       // std::cout<< "hello"<<std::endl;
        /*if ($$==1)) {
            std::cout<<"We have a function at line "<< currentLine <<std::endl;
        } else {
            std::cout<<"We do not have a function at line "<< currentLine <<std::endl;
        }*/
    
    } statements RIGHT_CURLY_BRACKET { currentScope--; } {
        symtable.hide(currentScope + 1);
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
        } LEFT_PARENTHESES idlist RIGHT_PARENTHESES { function_open++; } block { /*$9=1;*/ function_open--; prFunction.pop();} {        
        
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
    : WHILE {currentLine = yylineno; stmt_open++;is_stmt=1;} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt {stmt_open--;} {
    };

forstmt 
    : FOR {currentLine = yylineno; stmt_open++;is_stmt=1;} LEFT_PARENTHESES elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESES stmt {stmt_open--;} {
        
    };

returnstmt
    : RETURN SEMICOLON {
        is_stmt=1;
        if(function_open == 0){
            printf("Error: return outside of function, Line: %d\n" ,yylineno);
        } 
               
    }
    | RETURN{is_stmt=1;} expr SEMICOLON {
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