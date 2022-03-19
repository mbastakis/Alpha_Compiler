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
    extern int Current_Line();

    int found_errors = 0;
    int function_open = 0;

    /*TODO break,continue*/
    int flag_loop=0;

    int i = 1;

    /* Function Declarations */
     void yyerror (char const *s) {      
        fprintf (stderr, "%s\n", s);
        fprintf(stderr, "at line %d,  before token: %s \n", yylineno, yytext);
        fprintf(stderr, "INPUT NOT VALID\n");
        found_errors = 1;
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
%type<expression> lvalue

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
            $$ = $1 + $3;
            printf("expr + expr, Line: %d\n" ,Current_Line());
    }
    | expr SUBTRACTION expr {
            $$ = $1 - $3;
            printf("expr - expr, Line: %d\n" ,Current_Line());
        
    }
    | expr MULTIPLICATION expr {
            $$ = $1 * $3;
            printf("expr * expr, Line: %d\n" ,Current_Line());
        
    }
    | expr DIVISION expr {
            $$ = $1 / $3;
            printf("expr / expr, Line: %d\n" ,Current_Line());
        
    }
    | expr MODULO expr {
            $$ = $1 % $3;
            printf("expr %% expr, Line: %d\n" ,Current_Line());
        
    }
    | expr GREATER_THAN expr {
            $$ = $1 > $3;
            printf("expr > expr, Line: %d\n" ,Current_Line());
        
    }
    | expr LESS_THAN expr {
            $$ = $1 < $3;
            printf("expr < expr, Line: %d\n" ,Current_Line());
        
    }
    | expr GREATER_OR_EQUAL expr {
            $$ = $1 >= $3;
            printf("expr >= expr, Line: %d\n" ,Current_Line());
        
    }
    | expr LESS_OR_EQUAL expr {
            $$ = $1 <= $3;
            printf("expr <= expr, Line: %d\n" ,Current_Line());
        
    }
    | expr EQUALITY expr {
            $$ = $1 == $3;
            printf("expr == expr, Line: %d\n" ,Current_Line());
        
    }
    | expr INEQUALITY expr {
            $$ = $1 != $3;
            printf("expr != expr, Line: %d\n" ,Current_Line());
        
    }
    | expr AND expr {
            $$ = $1 and $3;
            printf("expr AND expr, Line: %d\n" ,Current_Line());
        
    }
    | expr OR expr {
            $$ = $1 or $3;
            printf("expr OR expr, Line: %d\n" ,Current_Line());
    }
    | term {
            
            $$ = $1;
            SymTable.symbolTable.insert(1,"int",$1);
            std::cout<<SymTable.symbolTable.begin();
    };

term
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        $$ = ($2);
        printf("left expr right, Line: %d\n" ,Current_Line());
    }
    | SUBTRACTION expr %prec UNARY_MINUS {
        $$ = - $2;
        printf("unary minus, Line: %d\n" ,Current_Line());
    }
    | NOT expr {
        $$ = not $2;
        printf("NOT expr, Line: %d\n" ,Current_Line());
    }
    | INCREMENT lvalue {
        $$ = $$ + 1;
        printf("increment lvalue, Line: %d\n" ,Current_Line());
    }
    | lvalue INCREMENT {
        $$ = $$ + 1;
        printf("lvalue increment, Line: %d\n" ,Current_Line());
    }
    | DECREMENT lvalue {
        $$ = $$ - 1;
        printf("decrement lvalue, Line: %d\n" ,Current_Line());
    }
    | lvalue DECREMENT {
        $$ = $$ - 1;
        printf("lvalue decrement, Line: %d\n" ,Current_Line());
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
        printf("id, Line: %d\n" ,Current_Line());
    }
    | LOCAL ID {
        printf("local id, Line: %d\n" ,Current_Line());
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
        printf("normcall, Line: %d\n" ,Current_Line());
    }

methodcall
    : DOUBLE_DOT ID LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        printf("method call, Line: %d\n" ,Current_Line());
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
        printf("object elist, Line: %d\n" ,Current_Line());
    }
    | LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {
        printf("object indexed, Line: %d\n" ,Current_Line());
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
    : LEFT_CURLY_BRACKET {function_open++;} statements RIGHT_CURLY_BRACKET {function_open--;} {
        
    };

funcdef
    : FUNCTION {i = Current_Line();} ID LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {
        printf("function id, Line: %d\n" ,i);
    }
    | FUNCTION {i = Current_Line();} LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {
        printf("function, Line: %d\n" ,i);
    };

const
    : INTEGER {
        printf("integer, Line: %d\n" ,Current_Line());
    }   
    | REAL{
        printf("real, Line: %d\n" ,Current_Line());
    }
    | STRING{
        printf("string, Line: %d\n" ,Current_Line());
    }
    | NIL{
        printf("NIL, Line: %d\n" ,Current_Line());
    }
    | TRUE{
        printf("true, Line: %d\n" ,Current_Line());
    }
    | FALSE{
        printf("false, Line: %d\n" ,Current_Line());
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

/* TODO: Check if variables have been declared */

ifstmt
    : IF {i = Current_Line();} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt %prec PUREIF {
        printf("pure if, Line: %d\n" ,i);
    }
    | IF {i = Current_Line();} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt ELSE stmt {
        printf("if else, Line: %d\n" ,i);
    };

whilestmt
    : WHILE {i = Current_Line();} LEFT_PARENTHESES expr RIGHT_PARENTHESES stmt {
        printf("while, Line: %d\n" ,i);
    };

forstmt 
    : FOR {i = Current_Line();} LEFT_PARENTHESES elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESES stmt {
        printf("for, Line: %d\n" ,i);
    };

returnstmt
    : RETURN SEMICOLON {
        if(function_open == 0){
            printf("Error: return outside of function, Line: %d\n" ,Current_Line());
        } 
        else {
            printf("return, Line: %d\n" ,Current_Line());
        }
        
    }
    | RETURN expr SEMICOLON {
        printf("return expr, Line: %d\n" ,Current_Line());
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