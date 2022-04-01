/* Definitions */
%{
    /* Defines */
    #define SIZE 100
    #define FUNC 1
    #define VAR 2

    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>
    #include <unordered_map>

    /* External Variables */
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    extern unsigned int tokenCounter;
    extern std::stack<unsigned int> commentStack;
    extern int yylex();
    extern int yylineno;

    /* Global Variables */
    unsigned int currentScope = 0;
    unsigned int SymbolTableSize = 0;

    int found_errors = 0;
    int function_open = 0;
    int stmt_open=0;

    int i = 1;

    /* Function Declarations */
     void yyerror (char const *s) {      
        fprintf (stderr, "%s\n", s);
        fprintf(stderr, "at line %d,  before token: %s \n", yylineno, yytext);
        fprintf(stderr, "INPUT NOT VALID\n");
        found_errors = 1;
    }
    /*Enum type*/
    typedef enum {
        GLOBAL_VARIABLE,
        LOCAL_VARIABLE,
        FORMAL_ARGUMENT,
        LIBRARY_FUNCTION,
        USER_FUNCTION
    } symType;

    /* Symbol */
    class Symbol {
    private:
        std::string id;
        symType type;
        unsigned int scope;
        unsigned int line;
    public:
        Symbol(std::string _id, symType _type, unsigned int _scope, unsigned int _line) {
            id = _id;
            type = _type;
            scope = _scope;
            line = _line;
        }

        std::string getId() {
            return id;
        }

        symType getType() {
            return type;
        }

        unsigned int getLine() {
            return line;
        }

        unsigned int getScope() {
            return scope;
        }


    };
    
    /* SymTable */
    class SymbolTable {
    private:
        std::unordered_map<int, Symbol> table;
    public:
        SymbolTable() {
            table = std::unordered_map<int, Symbol>();
        }

        int insert(Symbol* symbol) {

        }
        
    };
    SymbolTable symtable = SymbolTable();

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
%type<expression> ifprefix

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
            $$ = $1 + $3;
            printf("expr + expr, Line: %d\n" ,yylineno);
    }
    | expr SUBTRACTION expr {
            $$ = $1 - $3;
            printf("expr - expr, Line: %d\n" ,yylineno);
        
    }
    | expr MULTIPLICATION expr {
            $$ = $1 * $3;
            printf("expr * expr, Line: %d\n" ,yylineno);
        
    }
    | expr DIVISION expr {
            $$ = $1 / $3;
            printf("expr / expr, Line: %d\n" ,yylineno);
        
    }
    | expr MODULO expr {
            $$ = $1 % $3;
            printf("expr %% expr, Line: %d\n" ,yylineno);
        
    }
    | expr GREATER_THAN expr {
            $$ = $1 > $3;
            printf("expr > expr, Line: %d\n" ,yylineno);
        
    }
    | expr LESS_THAN expr {
            $$ = $1 < $3;
            printf("expr < expr, Line: %d\n" ,yylineno);
        
    }
    | expr GREATER_OR_EQUAL expr {
            $$ = $1 >= $3;
            printf("expr >= expr, Line: %d\n" ,yylineno);
        
    }
    | expr LESS_OR_EQUAL expr {
            $$ = $1 <= $3;
            printf("expr <= expr, Line: %d\n" ,yylineno);
        
    }
    | expr EQUALITY expr {
            $$ = $1 == $3;
            printf("expr == expr, Line: %d\n" ,yylineno);
        
    }
    | expr INEQUALITY expr {
            $$ = $1 != $3;
            printf("expr != expr, Line: %d\n" ,yylineno);
        
    }
    | expr AND expr {
            $$ = $1 and $3;
            printf("expr AND expr, Line: %d\n" ,yylineno);
        
    }
    | expr OR expr {
            $$ = $1 or $3;
            
            printf("expr OR expr, Line: %d\n" ,yylineno);
    }
    | term {
            $$ = $1;
            /*symbolTable[0] = {"x","int","1",1};
            std::cout<<symbolTable[0].name << std::endl;*/
    };

term
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        $$ = ($2);
        printf("left expr right, Line: %d\n" ,yylineno);
    }
    | SUBTRACTION expr %prec UNARY_MINUS {
        $$ = - $2;
        printf("unary minus, Line: %d\n" ,yylineno);
    }
    | NOT expr {
        $$ = not $2;
        printf("NOT expr, Line: %d\n" ,yylineno);
    }
    | INCREMENT lvalue {
        $$ = $$ + 1;
        printf("increment lvalue, Line: %d\n" ,yylineno);
    }
    | lvalue INCREMENT {
        $$ = $$ + 1;
        printf("lvalue increment, Line: %d\n" ,yylineno);
    }
    | DECREMENT lvalue {
        $$ = $$ - 1;
        printf("decrement lvalue, Line: %d\n" ,yylineno);
    }
    | lvalue DECREMENT {
        $$ = $$ - 1;
        printf("lvalue decrement, Line: %d\n" ,yylineno);
    }
    | primary {
        
    };
assignexpr
    : lvalue ASSIGNMENT expr {
        
        symtable.insert($1);
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
        symType type;
        if( currentScope == 0 ) type = GLOBAL_VARIABLE;
        else type = LOCAL_VARIABLE;
        
        $$ = new Symbol($1, type, yylineno, currentScope);
    }
    | LOCAL ID {
        printf("local id, Line: %d\n" ,yylineno);
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
        printf("normcall, Line: %d\n" ,yylineno);
    }

methodcall
    : DOUBLE_DOT ID LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        printf("method call, Line: %d\n" ,yylineno);
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
        printf("object elist, Line: %d\n" ,yylineno);
    }
    | LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {
        printf("object indexed, Line: %d\n" ,yylineno);
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
    : FUNCTION {i = yylineno;} ID LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {
        
        printf("function id, Line: %d\n" ,i);
    }
    | FUNCTION {i = yylineno;} LEFT_PARENTHESES idlist RIGHT_PARENTHESES block {
        
        printf("function, Line: %d\n" ,i);
    };

const
    : INTEGER {
        printf("integer, Line: %d\n" ,yylineno);
    }   
    | REAL{
        printf("real, Line: %d\n" ,yylineno);
    }
    | STRING{
        printf("string, Line: %d\n" ,yylineno);
    }
    | NIL{
        printf("NIL, Line: %d\n" ,yylineno);
    }
    | TRUE{
        printf("true, Line: %d\n" ,yylineno);
    }
    | FALSE{
        printf("false, Line: %d\n" ,yylineno);
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

ifprefix
    : IF {i = yylineno; stmt_open++;} LEFT_PARENTHESES expr RIGHT_PARENTHESES {

    };

ifstmt
    : ifprefix stmt {stmt_open--;} %prec PUREIF {
        printf("pure if, Line: %d\n" ,i);
    }
    | ifprefix stmt ELSE {stmt_open++;} stmt {stmt_open--;} {
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
        else {
            printf("return, Line: %d\n" ,yylineno);
        }
        
    }
    | RETURN expr SEMICOLON {
        printf("return expr, Line: %d\n" ,yylineno);
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