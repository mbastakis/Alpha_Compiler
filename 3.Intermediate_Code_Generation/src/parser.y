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
    std::stack<int> jumpStack;

    bool isFunc;
    int functionOpen;
    int stmtOpen;
    int currentLine;
    int newNameFunction;
    int betweenElistExprInFor;
    int falseJumpInFor;
    int loopJumpInFor;
    int closureJumpInFor;
    std::string newName;
    std::string currentFunctionName;

    /* Offset Usage */
    /* Note, isws xreiastoume kapoio stack apo offsets gia emfolebmenes sunartisis */
    unsigned int programVarOffset;
    unsigned int functionLocalOffset;
    unsigned int formalArgOffset;
    unsigned int scopeSpaceCounter;
    unsigned int tempNameCounter;

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
    Expr* expression;
    Symbol* symbol;
    Call* call;
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
%type<expression> lvalue
%type<integer> ifprefix
%type<integer> elseprefix
%type<integer> funcbody
%type<symbol> funcprefix
%type<symbol> funcdef
%type<expression> objectdef
%type<expression> elist
%type<expression> nextexpr
%type<expression> indexed
%type<expression> nextindexed
%type<expression> indexedelem
%type<expression> member
%type<expression> call
%type<expression> idlist
%type<expression> nextid
%type<call> callsufix normcall methodcall
%type<integer> whilestart
%type<integer> whilecond
%type<integer> forprefix

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
        //resetTemp();
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
        $$ = $1;
    }
    | expr ADDITION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot add non numeric value");
        else {
            Expr_T a ;
            // if ($1->type==CONST_NUMBER_EXPR && $3->type==CONST_NUMBER_EXPR){
            //     a = CONST_NUMBER_EXPR;
            // } else {
            //     a = NUMBER_EXPR;
            // }
            a = ARITHMETIC_EXPR;

            Symbol* symbol;
            Expr* result;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            result = changeType(result, a);
            emit(OP_ADD, $1, $3, result , yylineno, 0);
            $$ = result;
        }
    }
    | expr SUBTRACTION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot subtract non numeric value");
        else {
            Expr_T a ;
            a = ARITHMETIC_EXPR;

            Symbol* symbol;
            Expr* result;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            result = changeType(result, a);
            emit(OP_SUB, $1, $3, result , yylineno, 0);
            $$ = result;
        }
    }
    | expr MULTIPLICATION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot multiply non numeric value");
        else {
            Expr_T a ;
            a = ARITHMETIC_EXPR;

            Symbol* symbol;
            Expr* result;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            result = changeType(result, a);
            emit(OP_MUL, $1, $3, result , yylineno, 0);
            $$ = result;
        }

    }
    | expr DIVISION expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot divide non numeric value");
        else {
            Expr_T a ;
            a = ARITHMETIC_EXPR;

            Symbol* symbol;
            Expr* result;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            result = changeType(result, a);
            emit(OP_DIV, $1, $3, result , yylineno, 0);
            $$ = result;
        }
    }
    | expr MODULO expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot do the mod operation with non numeric value");
        else {
            Expr_T a ;
            a = ARITHMETIC_EXPR;

            Symbol* symbol;
            Expr* result;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            result = changeType(result, a);
            emit(OP_MOD, $1, $3, result , yylineno, 0);
            $$ = result;
        }
    }
    | expr GREATER_THAN expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot compare non numeric value");
        else {
            Symbol* symbol;
            Expr* result, *varBool1, *varBool2;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            varBool1 = symbolToExpr(symbol);
            varBool2 = symbolToExpr(symbol);

            emit(OP_IF_GREATER, $1, $3, NULL, yylineno, nextQuadLabel()+3);
            result = changeType(result, BOOLEAN_EXPR);

            varBool1 = changeType(varBool1, CONST_BOOLEAN_EXPR);
            varBool1 = changeValue(varBool1, false);

            emit(OP_ASSIGN, varBool1, NULL, result , yylineno, 0);
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, nextQuadLabel()+2);

            varBool2 = changeType(varBool2, CONST_BOOLEAN_EXPR);
            varBool2 = changeValue(varBool2, true);
            emit(OP_ASSIGN, varBool2, NULL, result , yylineno, 0);

            $$ = result;
        }
    }
    | expr LESS_THAN expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot compare non numeric value");
        else {
            Symbol* symbol;
            Expr* result, *varBool1, *varBool2;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            varBool1 = symbolToExpr(symbol);
            varBool2 = symbolToExpr(symbol);

            emit(OP_IF_LESS, $1, $3, NULL , yylineno, nextQuadLabel()+3);
            result = changeType(result, BOOLEAN_EXPR);

            varBool1 = changeType(varBool1, CONST_BOOLEAN_EXPR);
            varBool1 = changeValue(varBool1, false);

            emit(OP_ASSIGN, varBool1, NULL, result , yylineno, 0);
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, nextQuadLabel()+2);

            varBool2 = changeType(varBool2, CONST_BOOLEAN_EXPR);
            varBool2 = changeValue(varBool2, true);
            emit(OP_ASSIGN, varBool2, NULL, result , yylineno, 0);

            $$ = result;
        }
    }
    | expr GREATER_OR_EQUAL expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot compare non numeric value");
        else {
            Symbol* symbol;
            Expr* result, *varBool1, *varBool2;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            varBool1 = symbolToExpr(symbol);
            varBool2 = symbolToExpr(symbol);

            emit(OP_IF_GREATEQ, $1, $3, NULL , yylineno, nextQuadLabel()+3);
            result = changeType(result, BOOLEAN_EXPR);

            varBool1 = changeType(varBool1, CONST_BOOLEAN_EXPR);
            varBool1 = changeValue(varBool1, false);

            emit(OP_ASSIGN, varBool1, NULL, result , yylineno, 0);
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, nextQuadLabel()+2);

            varBool2 = changeType(varBool2, CONST_BOOLEAN_EXPR);
            varBool2 = changeValue(varBool2, true);
            emit(OP_ASSIGN, varBool2, NULL, result , yylineno, 0);

            $$ = result;
        }
    }
    | expr LESS_OR_EQUAL expr {
        if( !isValidArithmeticOperation($1, $3) )
            yyerror("Cannot compare non numeric value");
        else {
            Symbol* symbol;
            Expr* result, *varBool1, *varBool2;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            varBool1 = symbolToExpr(symbol);
            varBool2 = symbolToExpr(symbol);

            emit(OP_IF_LESSEQ, $1, $3, NULL , yylineno, nextQuadLabel()+3);
            result = changeType(result, BOOLEAN_EXPR);

            varBool1 = changeType(varBool1, CONST_BOOLEAN_EXPR);
            varBool1 = changeValue(varBool1, false);

            emit(OP_ASSIGN, varBool1, NULL, result , yylineno, 0);
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, nextQuadLabel()+2);

            varBool2 = changeType(varBool2, CONST_BOOLEAN_EXPR);
            varBool2 = changeValue(varBool2, true);
            emit(OP_ASSIGN, varBool2, NULL, result , yylineno, 0);

            $$ = result;
        }
    }
    | expr EQUALITY expr {
        if(!areExprTypesEq($1, $3))
            yyerror("Cannot compare different types");
         else {
            Symbol* symbol;
            Expr* result, *varBool1, *varBool2;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            varBool1 = symbolToExpr(symbol);
            varBool2 = symbolToExpr(symbol);

            emit(OP_IF_EQ, $1, $3, NULL , yylineno, nextQuadLabel()+3);
            result = changeType(result, BOOLEAN_EXPR);

            varBool1 = changeType(varBool1, CONST_BOOLEAN_EXPR);
            varBool1 = changeValue(varBool1, false);

            emit(OP_ASSIGN, varBool1, NULL, result , yylineno, 0);
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, nextQuadLabel()+2);

            varBool2 = changeType(varBool2, CONST_BOOLEAN_EXPR);
            varBool2 = changeValue(varBool2, true);
            emit(OP_ASSIGN, varBool2, NULL, result , yylineno, 0);

            $$ = result;
        }
    }
    | expr INEQUALITY expr {
        if(!areExprTypesEq($1, $3))
            yyerror("Cannot compare different types");
         else {
            Symbol* symbol;
            Expr* result, *varBool1, *varBool2;
            symbol = newTempSymbol();
            result = symbolToExpr(symbol);
            varBool1 = symbolToExpr(symbol);
            varBool2 = symbolToExpr(symbol);

            emit(OP_IF_NOTEQ, $1, $3, NULL , yylineno, nextQuadLabel()+3);
            result = changeType(result, BOOLEAN_EXPR);

            varBool1 = changeType(varBool1, CONST_BOOLEAN_EXPR);
            varBool1 = changeValue(varBool1, false);

            emit(OP_ASSIGN, varBool1, NULL, result , yylineno, 0);
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, nextQuadLabel()+2);

            varBool2 = changeType(varBool2, CONST_BOOLEAN_EXPR);
            varBool2 = changeValue(varBool2, true);
            emit(OP_ASSIGN, varBool2, NULL, result , yylineno, 0);

            $$ = result;
        }
    }
    | expr AND expr {
        //if() yyerror("Cannot compare with a function");
        Expr_T a ;
        a = NUMBER_EXPR;

        Symbol* symbol;
        Expr* result;
        symbol = newTempSymbol();
        result = symbolToExpr(symbol);
        result = changeType(result, a);
        emit(OP_AND, $1, $3, result , yylineno, 0);
        $$ = result;
    }
    | expr OR expr {
        // if() yyerror("Cannot compare with a function");
        Expr_T a ;
        a = NUMBER_EXPR;

        Symbol* symbol;
        Expr* result;
        symbol = newTempSymbol();
        result = symbolToExpr(symbol);
        result = changeType(result, a);
        emit(OP_OR, $1, $3, result , yylineno, 0);
        $$ = result;
    }
    | term {
        $$ = $1;
    };

term
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        $$ = $2;
    }
    | SUBTRACTION expr %prec UMINUS {
        if (!isValidArithmeticExpr($2)) yyerror("invalid arithmetic expression");

        $$ = newExprType(ARITHMETIC_EXPR);
        Symbol* newSymbol = newTempSymbol();
        symtable.insert(newSymbol);
        $$->symbol = newSymbol;
        $$->value = newSymbol->getId();
        emit(OP_UMINUS, $2, NULL, $$, yylineno, 0);
    }
    | NOT expr {
        $$ = newExprType(BOOLEAN_EXPR);
        Symbol* newSymbol = newTempSymbol();
        symtable.insert(newSymbol);
        $$->symbol = newSymbol;
        $$->value = newSymbol->getId();
        emit(OP_NOT, $2, NULL, $$, yylineno, 0);
    }
    | INCREMENT lvalue {
        Symbol* symbol = $2->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot increment the value of a function.");
        } else if ( !symbol->isActive() ) {
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }

        if($2->type == TABLE_ITEM_EXPR) {
            $$ = emit_iftableitem($2, yylineno);
            emit(OP_ADD, newIntegerExpr(1), $$, $$, yylineno, 0);
            emit(OP_TABLESETELEM, $2, $2->index, $$, yylineno, 0);
        } else {
            emit(OP_ADD, newIntegerExpr(1), $2, $2, yylineno, 0);
            $$ = newExprType(ARITHMETIC_EXPR);

            if(isTempSymbol($2->symbol)) {
                $$->symbol = $2->symbol;
            } else {
                Symbol* newSymbol = newTempSymbol();
                symtable.insert(newSymbol);
                $$->symbol = newSymbol;
                $$->value = newSymbol->getId();
                emit(OP_ASSIGN, $2, NULL, $$, yylineno, 0);
            }
        }
    }
    | lvalue INCREMENT {
        Symbol* symbol = $1->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot increment the value of a function.");
        }else if ( !symbol->isActive() ) {
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }

        $$ = newExprType(VAR_EXPR);
        Symbol* newSymbol = newTempSymbol();
        symtable.insert(newSymbol);
        $$->symbol = newSymbol;
        $$->value = newSymbol->getId();
        emit(OP_ASSIGN, $1, NULL, $$, yylineno, 0);

        if($1->type == TABLE_ITEM_EXPR) {
            Expr* newExpr = emit_iftableitem($1, yylineno);
            emit(OP_ASSIGN, newExpr, NULL, $$, yylineno, 0);
            emit(OP_ADD, newExpr, newExpr, newIntegerExpr(1), yylineno, 0);
            emit(OP_TABLESETELEM, $1->index, $1, newExpr, yylineno, 0);
        } else {
            emit(OP_ADD, newIntegerExpr(1), $1, $1, yylineno, 0);
        }
    }
    | DECREMENT lvalue {
        Symbol* symbol = $2->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot decrement the value of a function.");
        } else if ( !symbol->isActive() ) {
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }

        if($2->type == TABLE_ITEM_EXPR) {
            $$ = emit_iftableitem($2, yylineno);
            emit(OP_SUB, newIntegerExpr(1), $$, $$, yylineno, 0);           
            emit(OP_TABLESETELEM, $2, $2->index, $$, yylineno, 0);
        } else {
            emit(OP_SUB, $2, $2, newIntegerExpr(1), yylineno, 0);
            $$ = newExprType(ARITHMETIC_EXPR);

            if(isTempSymbol($2->symbol)) {
                $$->symbol = $2->symbol;
            } else {
                Symbol* newSymbol = newTempSymbol();
                symtable.insert(newSymbol);
                $$->symbol = newSymbol;
                $$->value = newSymbol->getId();
                emit(OP_ASSIGN, $2, NULL, $$, yylineno, 0);
            }
        }
    }
    | lvalue DECREMENT {
        Symbol* symbol = $1->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC ) { // If the symbol is a function.
            yyerror("cannot decrement the value of a function.");
        } else if ( !symbol->isActive() ) {
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }

        $$ = newExprType(VAR_EXPR);
        Symbol* newSymbol = newTempSymbol();
        symtable.insert(newSymbol);
        $$->symbol = newSymbol;
        $$->value = newSymbol->getId();

        if($1->type == TABLE_ITEM_EXPR) {
            Expr* newExpr = emit_iftableitem($1, yylineno);
            emit(OP_ASSIGN, newExpr, NULL, $$, yylineno, 0);
            emit(OP_SUB, newExpr, newExpr, newIntegerExpr(1), yylineno, 0);
            emit(OP_TABLESETELEM, $1, $1->index, newExpr, yylineno, 0);
        } else {
            emit(OP_ASSIGN, $1, NULL, $$, yylineno, 0);
            emit(OP_SUB, newIntegerExpr(1), $1, $1, yylineno, 0);
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
        Symbol* symbol = $1->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC) { // The symbol is a function.
            yyerror("cannot change the value of a function.");
        } else if( !symbol->isActive() ) { // The symbol didn't exist.
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }

        if($1->type == TABLE_ITEM_EXPR) {
            std::cout<<"hello"<<std::endl;
            emit(OP_TABLESETELEM, $3, $1->index, $1, yylineno, 0);
            $$ = emit_iftableitem($1, yylineno);
            $$->type = ASSIGN_EXPR;
        } else {
            emit(OP_ASSIGN, $3, NULL, $1 , yylineno, 0);

            /*$$ = newExprType(ASSIGN_EXPR);
            if(isTempSymbol($1->symbol)) {
                $$->symbol = $1->symbol;
            } else {
                Symbol* newSymbol = newTempSymbol();
                symtable.insert(newSymbol);
                $$->symbol = newSymbol;
                $$->value = newSymbol->getId();
                emit(OP_ASSIGN, $1, NULL, $$, yylineno,0);
            }*/
        }
    };

primary
    : lvalue {
         Symbol* symbol = $1->symbol;

        if( symbol == NULL ); // An error came up ignore.
        else if( !symbol->isActive() ) {
            symbol->setActive(true);
            symtable.insert(symbol);
        }

        if( symbol != NULL && symbol->getType() == USERFUNC)
            $$->type = USERFUNCTION_EXPR;
        else if(symbol != NULL && symbol->getType() == LIBRARYFUNC)
            $$->type = LIBRARYFUNCTION_EXPR;
        else
            $$->type = VAR_EXPR;
            
        $$ = emit_iftableitem($1, yylineno);
    }
    | call {
    }
    | objectdef {
        $$ = $1;
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES {
        $$ = newExprType(USERFUNCTION_EXPR);
        $$->symbol = $2;
    }
    | const {
        $$ = $1;
    };

lvalue
    : ID {
        Symbol* search = symtable.recursiveLookup($1, currentScope, blockStack);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search == NULL ) {// If no symbol was found.
            // std::cout << "New id: " << $1 << " scopespace: " << getCurrentScopespace() << std::endl;
            Symbol* newSymbol = new Symbol($1, type, yylineno, currentScope, false);
            newSymbol->setOffset(getCurrentScopeOffset());
            symtable.insert(newSymbol);
            incCurrentScopeOffset();
            $$ = symbolToExpr(newSymbol);
        }
        else {
            if( search->getType() == SYMERROR ) {
                yyerror("cannot access this variable.");
                $$ = NULL;
            }else
                $$ = symbolToExpr(search);
        }
    }
    | LOCAL ID {
        Symbol* search = symtable.lookup($2, currentScope);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search != NULL && search->getScope() == currentScope )
            $$ = symbolToExpr(search);
        else if( !symtable.contains($2, LIBRARYFUNC) )
            $$ = symbolToExpr(new Symbol($2, type, yylineno, currentScope, false));
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
            $$ = symbolToExpr(search);

    }
    | member {
        $$ = $1;
    };

member 
    : lvalue DOT ID {
        Symbol* symbol = $1->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( !symbol->isActive() ) { // If the symbol doesn't exist.
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }
        //std::cout<<"hello"<<std::endl;
        $$ = emit_table($1, newStringExpr(yylval.string), yylineno);
    }
    | lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
        Symbol* symbol = $1->symbol;

        if( symbol == NULL ); // An error came up, ignore.
        else if( !symbol->isActive() ) { // If the symbol doesn't exist.
            // symbol->setActive(true);
            // symtable.insert(symbol);
        }
        $$ = emit_table($1, $3, yylineno);
    }
    | call DOT ID {
    }
    | call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
    };

call 
    : call LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        $$ = make_call($1, reverseElist($3),yylineno);
    }
    | lvalue callsufix {
        Expr* lva = emit_iftableitem($1, yylineno);

        if($2->method){
            Expr* tmp = lva;
            lva = emit_iftableitem(member_item(tmp,$2->name,yylineno),yylineno);
            $2->revElist.push_front(tmp);
        }
        $$ = make_call(lva,$2->revElist,yylineno);

        Symbol* symbol = $1->symbol;

        if ( symbol == NULL ); // An error came up ignore.
        else if( !symbol->isActive() ) { // Symbol we are trying to call doesn't exist so we create it.
            symbol->setActive(true);
            symtable.insert(symbol);
        }
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        Expr* func = newExprType(USERFUNCTION_EXPR);
        func->symbol = $2;
        $$ = make_call(func, reverseElist($5), yylineno);
    };

callsufix
    : normcall {
        $$ = $1;
    }
    | methodcall {
        $$ = $1;
    };

normcall
    : LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        $$ = new Call();

        $$->revElist = reverseElist($2);
        $$->method = 0;
        $$->name = "NULL";
    }

methodcall
    : DOUBLE_DOT ID LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        $$ = new Call();

        $$->revElist = reverseElist($4);
        $$->method = 1;
        $$->name = $2;
    };

elist
    : expr nextexpr {
        $$ = $1;
        $$->next = $2;
    }
    | %empty {
        $$ = NULL;
    }
    ;

nextexpr
    : COMMA expr nextexpr {
        $$ = $2;
        $$->next = $3;
    }
    | %empty {
        $$ = NULL;
    }
    ;

objectdef
    : LEFT_SQUARE_BRACKET elist RIGHT_SQUARE_BRACKET {
        Expr* tmp;
        int i = 0;

        $$ = newExprType(NEW_TABLE_EXPR);
        Symbol* newSymbol = newTempSymbol();
        symtable.insert(newSymbol);
        $$->symbol = newSymbol;
        $$->value = newSymbol->getId();
        std::string val = newSymbol->getId();
        std::cerr << "symbol: " << val << std::endl;
        emit(OP_TABLECREATE, $$, NULL, NULL, yylineno, 0);

        tmp = $2;
        while(tmp != NULL) {
            emit(OP_TABLESETELEM, tmp, newIntegerExpr(i++),$$, yylineno, 0);
            tmp = tmp->next;
        }
    }
    | LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {
        Expr* tmp;

        $$ = newExprType(NEW_TABLE_EXPR);
        Symbol* newSymbol = newTempSymbol();
        symtable.insert(newSymbol);
        $$->symbol = newSymbol;
        $$->value = newSymbol->getId();
        emit(OP_TABLECREATE, $$, NULL, NULL, yylineno, 0);

        tmp = $2;
        while(tmp != NULL) {
            emit(OP_TABLESETELEM, $$, tmp, tmp->index, yylineno, 0);
            tmp = tmp->next;
        }
    };

indexed
    : indexedelem nextindexed {
        $$ = $1;
        $$->next = $2;
    }
    ;

nextindexed
    : COMMA indexedelem nextindexed {
        $$ = $2;
        $$->next = $3;
    }
    | %empty {
        $$ = NULL;
    }
    ;

indexedelem
    : LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET{
        $$ = $2;
        $$->index = $4;
    };

block
    : LEFT_CURLY_BRACKET {currentScope++; blockStack.push(isFunc); isFunc = false;} statements RIGHT_CURLY_BRACKET {symtable.hide(currentScope--); blockStack.pop();} {
    };

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
            symtable.insert(function_symbol);
            $$ = function_symbol;
            jumpStack.push(Quads.size());
            emit(OP_JUMP, NULL, NULL, NULL, yylineno, 0);
            emit(OP_FUNCSTART, symbolToExpr(function_symbol), NULL, NULL, yylineno, 0);
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
        emit(OP_FUNCEND, symbolToExpr(function_symbol), NULL, NULL, yylineno, 0);
        Quads[jumpStack.top()]->label = Quads.size() + 1;
        jumpStack.pop();
        restoreCurrentScopeOffset(scopeOffsetStack.top());
        scopeOffsetStack.pop();
    }
    ;

const
    : INTEGER {
        $$ = newIntegerExpr(yylval.integer);
    }
    | REAL{
        $$ = newDoubleExpr(yylval.real);
    }
    | STRING{
        $$ = newStringExpr(yylval.string);
    }
    | NIL{
        $$ = newNilExpr();
    }
    | TRUE{
        $$ = newBoolExpr(true);
    }
    | FALSE{
        $$ = newBoolExpr(false);
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
                // std::cout << "new formal: " << $1 << std::endl;
                Symbol* newSym = new Symbol($1, FORMALVAR, yylineno, currentScope+1, true);
                newSym->setOffset(getCurrentScopeOffset());
                symtable.insert(newSym);
                function->insertArgument(newSym);
                incCurrentScopeOffset();
                $$ = symbolToExpr(newSym);
            }
        }
    }
    | %empty { //This code does nothing
        $$ = NULL;
    }
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
                // std::cout << "new formal: " << $2 << std::endl;
                Symbol* newSym = new Symbol($2, FORMALVAR, yylineno, currentScope+1, true);
                newSym->setOffset(getCurrentScopeOffset());
                symtable.insert(newSym);
                function->insertArgument(newSym);
                incCurrentScopeOffset();
                $$ = symbolToExpr(newSym);
            }
        }
    }
    | %empty { 
        $$ = NULL;
    }
    ;

ifprefix
    : IF LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        Symbol* symbol;
        Expr* varBool;
        symbol = newTempSymbol();
        varBool = symbolToExpr(symbol);
        varBool = changeType(varBool, CONST_BOOLEAN_EXPR);
        varBool = changeValue(varBool, true);

        emit(OP_IF_EQ, $3, varBool, NULL, yylineno, nextQuadLabel() + 2);
        $$ = nextQuadLabel();

        emit(OP_JUMP, NULL, NULL, NULL, yylineno, 0);

    };

elseprefix
    : ELSE {
        $$ = nextQuadLabel();

        emit(OP_JUMP, NULL, NULL, NULL, yylineno, 0);

    };

ifstmt
    : ifprefix stmt %prec PUREIF {

        patchlabel($1, nextQuadLabel());
    }
    | ifprefix stmt elseprefix stmt {

        patchlabel($1, $3 + 1);
        patchlabel($3, nextQuadLabel());

    };

whilestart
    : WHILE {
        $$ = nextQuadLabel(); 

    };

whilecond
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        Symbol* symbol;
        Expr* varBool;
        symbol = newTempSymbol();
        varBool = symbolToExpr(symbol);
        varBool = changeType(varBool, CONST_BOOLEAN_EXPR);
        varBool = changeValue(varBool, true);
        emit(OP_IF_EQ, $2, varBool, NULL, yylineno, nextQuadLabel() + 2);
        $$ = nextQuadLabel()-1;
        emit(OP_JUMP, NULL, NULL, NULL, yylineno, 0);
        
    };

whilestmt
    : whilestart {currentLine = yylineno; stmtOpen++;} whilecond stmt {stmtOpen--;} {
        
        emit(OP_JUMP, NULL, NULL, NULL, yylineno, $1);
        patchlabel($3, nextQuadLabel()-1);

    };


forprefix
    : FOR{currentLine = yylineno; stmtOpen++;} LEFT_PARENTHESES elist SEMICOLON {betweenElistExprInFor = nextQuadLabel();} expr SEMICOLON {
        std::cout << "forprefix: " << betweenElistExprInFor << std::endl;
        Symbol* symbol;
        Expr* varBool;
        symbol = newTempSymbol();
        varBool = symbolToExpr(symbol);
        varBool = changeType(varBool, CONST_BOOLEAN_EXPR);
        varBool = changeValue(varBool, true);
        $$ = nextQuadLabel();
        emit(OP_IF_EQ, $7, varBool, NULL, yylineno, 0);
    };

forstmt
    : forprefix { falseJumpInFor = betweenFor();} elist RIGHT_PARENTHESES { loopJumpInFor = betweenFor();} stmt { closureJumpInFor = betweenFor(); stmtOpen--;} {
            std::cerr << "forprefix " << $1 << std::endl;
            std::cerr << "falsejumpinfor "<< falseJumpInFor << std::endl;
            std::cerr << "closurejmpinfor " << closureJumpInFor << std::endl;
            patchlabel($1, loopJumpInFor + 1);
            patchlabel(falseJumpInFor, nextQuadLabel());
            patchlabel(loopJumpInFor, betweenElistExprInFor);
            patchlabel(closureJumpInFor-1, falseJumpInFor+1);

    };

returnstmt
    : RETURN SEMICOLON {
        if(functionOpen == 0)
            yyerror("return outside of function");
        else {
            emit(OP_RET, NULL, NULL, NULL, yylineno, 0);
        }

    }
    | RETURN expr SEMICOLON {
        if(functionOpen == 0)
            yyerror("return outside of function");
        else {

            emit(OP_RET, $2, NULL, NULL, yylineno, 0);
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
    functionStack = std::stack<std::string>();
    blockStack = std::stack<bool>();
    jumpStack = std::stack<int>();

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
    tempNameCounter = 1;

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