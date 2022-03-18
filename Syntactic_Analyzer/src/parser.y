/* Definitions */
%{
    /* Defines */
    #define FUNC 1
    #define VAR 2

    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>
    #include <map>

    

    /* External Variables */
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    extern unsigned int tokenCounter;
    extern std::stack<unsigned int> commentStack;
    extern int yylex();

    /* Function Declarations */
     void yyerror (char const *s) {
        fprintf (stderr, "%s\n", s);
    }

    /* SymTable */
    class SymTable {
    public:
        std::map<int, std::string> symbolTable;
    private:

    };

%}

/* Specifies the initial symbol of our grammar. */
%start program

/* Union of all the types that a symbol can have. */
%union {
    int integer;
    double real;
    char* string;
    unsigned int expression;
}

/* Terminal Symbols */
%token<string>  IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR
                LOCAL TRUE FALSE NIL
%token<string>  ASSIGNMENT ADDITION SUBTRACTION MULTIPLICATION DIVISION MODULO
                EQUALITY INEQUALITY INCREMENT DECREMENT GREATER_THAN LESS_THAN
                GREATER_OR_EQUAL LESS_OR_EQUAL UNARY_MINUS
%token<string>  LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET LEFT_SQUARE_BRACKET
                RIGHT_SQUARE_BRACKET LEFT_PARENTHESES RIGHT_PARENTHESES
                SEMICOLON COMMA COLON DOUBLE_COLON DOT DOUBLE_DOT
%token<string>  STRING ID
%token<integer> INTEGER
%token<real>    REAL
%token<string>  ERROR

/* Non Terminal Symbols */
/* %type<Edw 8elei tupo enos entry ston symbol table> symbol_table_entry */
%type<expression> expr
%type<expression> assignexpr
%type<expression> term
%type<expression> primary

/* Rules for priority and associativeness */
%right ASSIGNMENT
%left OR
%left AND
%nonassoc EQUALITY INEQUALITY
%nonassoc GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%left ADDITION SUBTRACTION
%left MULTIPLICATION DIVISION MODULO
%right NOT INCREMENT DECREMENT UNARY_MINUS
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

    }
    | CONTINUE SEMICOLON {

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
        $$ = $1;
    };

term
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {

    }
    | SUBTRACTION expr %prec UNARY_MINUS {

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
        $$ = FUNC;
    }
    | const {

    };

lvalue
    : ID {

    }
    | LOCAL ID {

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
    : LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET{

    };

funcdef
    : FUNCTION ID LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {

    }
    | FUNCTION LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {

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
    commentStack = std::stack<unsigned int>();
    tokenCounter = 0;

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

    return 0;
}