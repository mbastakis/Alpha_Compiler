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

    std::string prFuc; 

    int i = 1;

    /* Function Definitions */
     void yyerror (char const *s) {      
        fprintf (stderr, "%s\n", s);
        fprintf(stderr, "at line %d,  before token: %s \n", yylineno, yytext);
        fprintf(stderr, "INPUT NOT VALID\n");
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
    : expr SEMICOLON {
        
    }
    | ifstmt 
    | whilestmt 
    | forstmt {

    }
    | returnstmt {

    }
    | BREAK SEMICOLON {
        if(stmt_open == 0){
            printf("Error: break outside of statement, Line: %d\n" ,yylineno);
        } 
        else {
            printf("break, Line: %d\n" ,yylineno);
        }
        
    }
    | CONTINUE SEMICOLON {
        if(stmt_open == 0){
            printf("Error: continue outside of statement, Line: %d\n" ,yylineno);
        } 
        else {
            printf("continue, Line: %d\n" ,yylineno);
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
        
    };

primary
    : lvalue {

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
        //std::cout<<$ 1<<std::endl;
        if(symtable.contains($1) != 1 || (symtable.contains($1, USER_FUNCTION) == 1)){
            
            if (currentScope == 0)
                symtable.insert($1, new Symbol($1, GLOBAL_VARIABLE, yylineno, currentScope));
            else    {
                symtable.insert($1, new Symbol($1, LOCAL_VARIABLE, yylineno, currentScope));
            }
        } 
        else if(symtable.contains($1) == 1 && symtable.contains($1,GLOBAL_VARIABLE) != 1 && symtable.contains($1,currentScope-1) != 1){
            
            std::cout<<"error: variable "<< $1 <<" not accessible in "<< prFuc <<std::endl;
        } 
        else if(symtable.contains($1,LOCAL_VARIABLE) == 1 && symtable.contains($1,currentScope) != 1 && symtable.contains($1,GLOBAL_VARIABLE) != 1){
            
            std::cout<<"error: "<< $1 <<" not accessible in "<< prFuc <<std::endl;
        }
               
        
    }
    | LOCAL ID {
        symtable.insert($2, new Symbol($2, LOCAL_VARIABLE, yylineno, currentScope));
    }
    | DOUBLE_COLON ID {

    }
    | member {

    };

member
    : lvalue DOT ID {

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
    : LEFT_CURLY_BRACKET {function_open++; stmt_open++; currentScope++;} statements RIGHT_CURLY_BRACKET {function_open--; stmt_open--; currentScope--;} {
        
    };

funcdef
    : FUNCTION {i = yylineno; } ID {prFuc = $3;} LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {   
       // std::cout<<$ 3<<std::endl;
        symtable.insert($3, new Symbol($3, USER_FUNCTION, i, currentScope));

    }
    | FUNCTION {i = yylineno;} LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {
        
        // WHAT TO DO??? 
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
        symtable.insert($1, new Symbol($1, FORMAL_ARGUMENT, yylineno, currentScope));
    }
    | %empty
    ;

nextid
    : COMMA ID nextid {
        symtable.insert($2, new Symbol($2, FORMAL_ARGUMENT, yylineno, currentScope));
    }
    | %empty
    ;

ifstmt
    : IF LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt %prec PUREIF {
        printf("pure if, Line: %d\n" ,i);
    }
    | IF LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt ELSE stmt {
        printf("if else, Line: %d\n" ,i);
    };

whilestmt
    : WHILE {i = yylineno; stmt_open++;} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt {stmt_open--;} {
        printf("while, Line: %d\n" ,i);
    };

forstmt 
    : FOR {i = yylineno; stmt_open++;} LEFT_PARENTHESES elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESES stmt {stmt_open--;} {
        printf("for, Line: %d\n" ,i);
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
    tokenCounter = 0;
    currentScope = 0;

    /*symtable.insert("print", new Symbol("print", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("input", new Symbol("input", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("objectmemberkeys", new Symbol("objectmemberkeys", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("objecttotalmembers", new Symbol("objecttotalmembers", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("objectcopy", new Symbol("objectcopy", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("totalarguments", new Symbol("totalarguments", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("argument", new Symbol("argument", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("typeof", new Symbol("typeof", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("strtonum", new Symbol("strtonum", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("sqrt", new Symbol("sqrt", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("cos", new Symbol("cos", LIBRARY_FUNCTION, 0, 0));
    symtable.insert("sin", new Symbol("sin", LIBRARY_FUNCTION, 0, 0));*/

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