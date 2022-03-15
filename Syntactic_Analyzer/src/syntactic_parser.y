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

    /* SymTable */
    class SymTable {
    public:

    private:
        
    };

%}

/* Specifies the initial symbol of our grammar. */
%start program

/* Union of all the types that a symbol can have. */
%union {
    std::string string;
    int integer;
    double real;
    unsigned int expr_t;
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
%token<string>  STRING ID ERROR
%token<integer> INTEGER
%token<real>    REAL

/* Non Terminal Symbols */
%type</*Edw 8elei tupo enos entry ston symbol table*/> symbol_table_entry
%type<expr_t> expr
%type<expr_t> assignexpr
%type<expr_t> term
%type<expr_t> primary

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
    : statements stmt
    | /* End of recursion */
    ;

stmt
    : expr SEMICOLON {

    }
    | ifstmt {

    }
    | whilestmt {

    }
    | forstmt {

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
    | /* End of recursion */
    ;

nextexpr
    : COMMA expr nextexpr {

    }
    | /* End of recursion */
    ;

objectdef
    : LEFT_SQUARE_BRACKET elist RIGHT_SQUARE_BRACKET {

    }
    | LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {

    };

indexed
    :
    | indexedelem nextindexed {

    }
    | /* End of recursion */
    ;

nextindexed
    : COMMA indexedelem nextindexed {

    }
    | /* End of recursion */
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
    : INTEGER
    | REAL
    | STRING
    | NIL
    | TRUE
    | FALSE;

idlist
    : ID nextid {

    }
    | /* End of recursion */
    ;

nextid
    : COMMA ID nextid {

    }
    | /* End of recursion */
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