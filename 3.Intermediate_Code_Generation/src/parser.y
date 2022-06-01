/* Definitions */
%{
    /* Includes */
    #include <stdio.h>
    #include <iostream>
    #include <stack>
    #include <fstream>
    #include <vector>
    #include <list>

    #include "../public/Symbol.hpp"
    #include "../public/SymbolTable.hpp"
    #include "../public/IntermediateCode.hpp"

    /* Defines */
    #define DEBUG 0

    /* External Variables */
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyout;
    extern FILE* yyin;
    extern int yylex();
    extern std::stack<unsigned int> commentStack;

    /* Global Variables */
    SymbolTable symtable;
    std::stack<unsigned int> scopeOffsetStack;
    std::stack<bool> blockStack;
    unsigned int currentScope;
    std::stack<int> stackLoop;
    std::stack<int> breakStack;
    std::stack<int> continueStack;

    std::stack<int> timesInLoop;
    int countLoop;

    bool isFunc;
    int functionOpen;
    int loopOpen;
    int currentLine;
    int newNameFunction;
    int betweenElistExprInFor;
    int falseJumpInFor;
    int loopJumpInFor;
    int closureJumpInFor;
    std::string newName;
    std::string currentFunctionName;
    bool hadError = false;

    int numberListOfBreak;
    int numberListOfContinue;

    /* Offset Usage */
    unsigned int programVarOffset;
    unsigned int functionLocalOffset;
    unsigned int formalArgOffset;
    unsigned int scopeSpaceCounter;
    unsigned int tempCounter;

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
        hadError = true;
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
%type<integer> ifprefix
%type<integer> elseprefix
%type<integer> funcbody
%type<integer> whilestart
%type<integer> whilecond
%type<integer> forprefix
%type<symbol> funcprefix
%type<symbol> funcdef
%type<call> callsufix
%type<call> normcall 
%type<call> methodcall



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
        resetTemp();
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
        if(loopOpen == 0)
            yyerror("break outside of loop");
        else {
            countLoop = countLoop + 1; //fix
            breakStack.push(nextQuadLabel()-1); //fix
            emit(OP_JUMP, NULL, NULL, NULL, 0, yylineno); //fix
        }
    }
    | CONTINUE SEMICOLON {
        if(loopOpen == 0)
            yyerror("continue outside of loop");
        else {
            countLoop = countLoop + 1; //fix
            continueStack.push(nextQuadLabel()-1); //fix
            emit(OP_JUMP, NULL, NULL, NULL, 0, yylineno); //fix
        }
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
        if( !isValidArithmeticOperation($1, $3) ){
            yyerror("Cannot add non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(ARITHMETIC_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_ADD, $1, $3, $$ , 0, yylineno);
        }
    }
    | expr SUBTRACTION expr {
        if( !isValidArithmeticOperation($1, $3) ){
            yyerror("Cannot subtract non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(ARITHMETIC_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_SUB, $1, $3, $$ , 0, yylineno);
        }
    }
    | expr MULTIPLICATION expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot multiply non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(ARITHMETIC_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_MUL, $1, $3, $$ , 0, yylineno);
        }

    }
    | expr DIVISION expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot divide non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(ARITHMETIC_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_DIV, $1, $3, $$ , 0, yylineno);
        }
    }
    | expr MODULO expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot do the mod operation with non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(ARITHMETIC_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_MOD, $1, $3, $$ , 0, yylineno);
        }
    }
    | expr GREATER_THAN expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot compare non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();

            emit(OP_IF_GREATER, $1, $3, NULL, nextQuadLabel()+3, yylineno);
            emit(OP_ASSIGN, newBoolExpr(false), NULL, $$, 0, yylineno);
            emit(OP_JUMP, NULL, NULL, NULL, nextQuadLabel()+2, yylineno);
            emit(OP_ASSIGN, newBoolExpr(true), NULL, $$, 0, yylineno);
        }
    }
    | expr LESS_THAN expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot compare non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();

            emit(OP_IF_LESS, $1, $3, NULL, nextQuadLabel()+3, yylineno);
            emit(OP_ASSIGN, newBoolExpr(false), NULL, $$, 0, yylineno);
            emit(OP_JUMP, NULL, NULL, NULL, nextQuadLabel()+2, yylineno);
            emit(OP_ASSIGN, newBoolExpr(true), NULL, $$, 0, yylineno);
        }
    }
    | expr GREATER_OR_EQUAL expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot compare non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();

            emit(OP_IF_GREATEQ, $1, $3, NULL, nextQuadLabel()+3, yylineno);
            emit(OP_ASSIGN, newBoolExpr(false), NULL, $$, 0, yylineno);
            emit(OP_JUMP, NULL, NULL, NULL, nextQuadLabel()+2, yylineno);
            emit(OP_ASSIGN, newBoolExpr(true), NULL, $$, 0, yylineno);
        }
    }
    | expr LESS_OR_EQUAL expr {
        if( !isValidArithmeticOperation($1, $3) ) {
            yyerror("Cannot compare non numeric value");
            $$ = NULL;
        } else {
            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();

            emit(OP_IF_LESSEQ, $1, $3, NULL, nextQuadLabel()+3, yylineno);
            emit(OP_ASSIGN, newBoolExpr(false), NULL, $$, 0, yylineno);
            emit(OP_JUMP, NULL, NULL, NULL, nextQuadLabel()+2, yylineno);
            emit(OP_ASSIGN, newBoolExpr(true), NULL, $$, 0, yylineno);
        }
    }
    | expr EQUALITY expr {
        if(!areExprTypesEq($1, $3)) {
            yyerror("Cannot compare different types");
            $$ = NULL;
         } else {
            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();

            emit(OP_IF_EQ, $1, $3, NULL, nextQuadLabel()+3, yylineno);
            emit(OP_ASSIGN, newBoolExpr(false), NULL, $$, 0, yylineno);
            emit(OP_JUMP, NULL, NULL, NULL, nextQuadLabel()+2, yylineno);
            emit(OP_ASSIGN, newBoolExpr(true), NULL, $$, 0, yylineno);
        }
    }
    | expr INEQUALITY expr {
        if(!areExprTypesEq($1, $3)) {
            yyerror("Cannot compare different types");
            $$ = NULL;
        } else {
            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();

            emit(OP_IF_NOTEQ, $1, $3, NULL, nextQuadLabel()+3, yylineno);
            emit(OP_ASSIGN, newBoolExpr(false), NULL, $$, 0, yylineno);
            emit(OP_JUMP, NULL, NULL, NULL, nextQuadLabel()+2, yylineno);
            emit(OP_ASSIGN, newBoolExpr(true), NULL, $$, 0, yylineno);
        }
    }
    | expr AND expr {
        //all values of alpha are converted in boolean
        if ($1 == NULL || $3 == NULL) {
            yyerror("An argument in operation 'and' had not type");
            $$ = NULL;
        } else {
            if($1->type == NIL_EXPR)
                $1->symbol->setId("false");
            else if($1->type != CONST_BOOLEAN_EXPR)
                $1->symbol->setId("true");

            if($3->type == NIL_EXPR)
                $3->symbol->setId("false");
            else if($3->type != CONST_BOOLEAN_EXPR)
                $3->symbol->setId("true");

            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_AND, $1, $3, $$, 0, yylineno);
        }

    }
    | expr OR expr { 
        //all values of alpha are converted in boolean
        if ($1 == NULL || $3 == NULL) {
            yyerror("An argument in operation 'or' had not type");
            $$ = NULL;
        } else {
            if($1->type == NIL_EXPR)
                $1->symbol->setId("false");
            else if($1->type != CONST_BOOLEAN_EXPR)
                $1->symbol->setId("true");

            if($3->type == NIL_EXPR)
                $3->symbol->setId("false");
            else if($3->type != CONST_BOOLEAN_EXPR)
                $3->symbol->setId("true");

            $$ = newExpression(BOOLEAN_EXPR);
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_OR, $1, $3, $$, 0, yylineno);
        }
        
    }
    | term {
        $$ = $1;
    };

term
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        $$ = $2;
    }
    | SUBTRACTION expr %prec UMINUS {
        if( $2 == NULL ) $$ = NULL;
        else {
            if (!check_arith($2)){
                yyerror("invalid arithmetic expression");
                $$ = NULL;
            }    
            else {
                $$ = newExpression(ARITHMETIC_EXPR);
                $$->symbol = newTemp();
                $$->value = $$->symbol->getId();
                emit(OP_UMINUS, $2, NULL, $$, 0, yylineno);
            }
        }
    }
    | NOT expr {
        if( $2 == NULL ) $$ = NULL;
        else {
            $$ = newExpression(VAR_EXPR);  //BOOLEAN_EXPR
            $$->symbol = newTemp();
            $$->value = $$->symbol->getId();
            emit(OP_NOT, $2, NULL, $$, 0, yylineno);
        }
    }
    | INCREMENT lvalue {
        if( $2 == NULL || $2->symbol == NULL) $$ = NULL; // An error came up, ignore.
        else {
            Symbol* symbol = $2->symbol;
            if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC || !check_arith($2) ) { // If the symbol is a function.
                yyerror("cannot increment the value of a function.");
                $$ = NULL;
            } else {
                if ( !symbol->isActive() ) {
                    symbol->setActive(true);
                    symtable.insert(symbol);
                }

                if($2->type == TABLE_ITEM_EXPR) {
                    $$ = emit_iftableitem($2, yylineno);
                    emit(OP_ADD, $$, newExprConstNum(1), $$, 0, yylineno);
                    emit(OP_TABLESETELEM, $2, $2->index, $$, 0, yylineno);
                } else {
                    emit(OP_ADD, newExprConstNum(1), $2, $2, 0, yylineno);
                    $$ = newExpression(ARITHMETIC_EXPR);

                    if(isTempSymbol($2->symbol)) {
                        $$->symbol = $2->symbol;
                    } else {
                        $$->symbol = newTemp();
                        $$->value = $$->symbol->getId();
                        emit(OP_ASSIGN, $2, NULL, $$, 0, yylineno);
                    }
                }
            }
        }
    }
    | lvalue INCREMENT {
        if( $1 == NULL || $1->symbol == NULL) $$ = NULL; // An error came up, ignore.
        else {
            Symbol* symbol = $1->symbol;
            if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC || !check_arith($1) ) { // If the symbol is different than number.
                yyerror("cannot increment something different than number.");
                $$ = NULL;
            } else {
                if ( !symbol->isActive() ) {
                    symbol->setActive(true);
                    symtable.insert(symbol);
                }
                $$ = newExpression(VAR_EXPR);
                $$->symbol = newTemp();
                $$->value = $$->symbol->getId();

                if($1->type == TABLE_ITEM_EXPR) {
                    Expr* newExpr = emit_iftableitem($1, yylineno);
                    emit(OP_ASSIGN, newExpr, NULL, $$, 0, yylineno);
                    emit(OP_ADD, newExpr, newExprConstNum(1), newExpr, 0, yylineno);
                    emit(OP_TABLESETELEM, $1, $1->index, newExpr, 0, yylineno);
                } else {
                    emit(OP_ASSIGN, $1, NULL, $$, 0, yylineno);
                    emit(OP_ADD, $1, newExprConstNum(1), $1, 0, yylineno);
                }
            }
        }
    }
    | DECREMENT lvalue {
        if( $2 == NULL || $2->symbol == NULL) $$ = NULL; // An error came up, ignore.
        else {
            Symbol* symbol = $2->symbol;
            if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC || !check_arith($2) ) { // If the symbol is a function.
                yyerror("cannot increment the value of a function.");
                $$ = NULL;
            } else {
                if ( !symbol->isActive() ) {
                    symbol->setActive(true);
                    symtable.insert(symbol);
                }

                if($2->type == TABLE_ITEM_EXPR) {
                    $$ = emit_iftableitem($2, yylineno);
                    emit(OP_SUB, $$, newExprConstNum(1), $$, 0, yylineno);
                    emit(OP_TABLESETELEM, $2, $2->index, $$, 0, yylineno);
                } else {
                    emit(OP_SUB, newExprConstNum(1), $2, $2, 0, yylineno);
                    $$ = newExpression(ARITHMETIC_EXPR);

                    if(isTempSymbol($2->symbol)) {
                        $$->symbol = $2->symbol;
                    } else {
                        $$->symbol = newTemp();
                        $$->value = $$->symbol->getId();
                        emit(OP_ASSIGN, $2, NULL, $$, 0, yylineno);
                    }
                }
            }
        }
    }
    | lvalue DECREMENT {
        if( $1 == NULL || $1->symbol == NULL) $$ = NULL; // An error came up, ignore.
        else {
            Symbol* symbol = $1->symbol;
            if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC || !check_arith($1) ) { // If the symbol is different than number.
                yyerror("cannot increment something different than number.");
                $$ = NULL;
            } else {
                if ( !symbol->isActive() ) {
                    symbol->setActive(true);
                    symtable.insert(symbol);
                }
                $$ = newExpression(VAR_EXPR);
                $$->symbol = newTemp();
                $$->value = $$->symbol->getId();

                if($1->type == TABLE_ITEM_EXPR) {
                    Expr* newExpr = emit_iftableitem($1, yylineno);
                    emit(OP_ASSIGN, newExpr, NULL, $$, 0, yylineno);
                    emit(OP_SUB, newExpr, newExprConstNum(1), newExpr, 0, yylineno);
                    emit(OP_TABLESETELEM, $1, $1->index, newExpr, 0, yylineno);
                } else {
                    emit(OP_ASSIGN, $1, NULL, $$, 0, yylineno);
                    emit(OP_SUB, $1, newExprConstNum(1), $1, 0, yylineno);
                }
            }
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

        if( $1 == NULL || $1->symbol == NULL || $3 == NULL ) $$ = NULL; // An error came up, ignore.
        else {
            Symbol* symbol = $1->symbol;
            if( symbol->getType() == USERFUNC || symbol->getType() == LIBRARYFUNC) { // The symbol is a function.
                yyerror("cannot change the value of a function.");
                $$ = NULL;
            } else if( !symbol->isActive() ) { // The symbol didn't exist.
                symbol->setActive(true);
                symtable.insert(symbol);
            }

            if($1->type == TABLE_ITEM_EXPR) {
                
                emit(OP_TABLESETELEM, $1->index, $3, $1, 0, yylineno);
                $$ = emit_iftableitem($1, yylineno);
                $$->type = ASSIGN_EXPR;
            } else {
                if($3 != NULL) {
                    emit(OP_ASSIGN, $3, NULL, $1 , 0, yylineno);
                    Expr* result;
                    result = newExpression(ASSIGN_EXPR);
                    result->symbol = newTemp();
                    emit(OP_ASSIGN, $1, NULL, result, 0, yylineno);
                    $$ = result;
                }
            }
        }
    };

primary
    : lvalue {
        if( $1 == NULL || $1->symbol == NULL) $$ = NULL; // An error came up ignore.
        else {
            $$ = emit_iftableitem($1, yylineno);
            Symbol* symbol = $1->symbol;

            if( !symbol->isActive() ) {
                symbol->setActive(true);
                symtable.insert(symbol);
            }

            if(symbol->getType() == USERFUNC)
                $$->type = USERFUNCTION_EXPR;
            else if(symbol->getType() == LIBRARYFUNC)
                $$->type = LIBRARYFUNCTION_EXPR;
            else
                $$->type = VAR_EXPR;
        }
        
    }
    | call {
    }
    | objectdef {
        $$ = $1;
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES {
        $$ = newExpression(USERFUNCTION_EXPR);
        $$->symbol = $2;
        $$->value = $$->symbol->getId();
    }
    | const {
        $$ = $1;
    };

lvalue
    : ID {
        Symbol* search = symtable.recursiveLookup($1, currentScope, blockStack);
        Symbol_T type = currentScope == 0 ? GLOBALVAR : LOCALVAR;

        if( search == NULL ) {// If no symbol was found.
            Symbol* newSymbol = new Symbol($1, type, yylineno, currentScope, false);
            newSymbol->setScopespace(getCurrentScopespace());
            newSymbol->setOffset(getCurrentScopeOffset());
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
        else if( !symtable.contains($2, LIBRARYFUNC) ) { 
            Symbol* newSymbol = new Symbol($2, type, yylineno, currentScope, false);
            newSymbol->setScopespace(getCurrentScopespace());
            newSymbol->setOffset(getCurrentScopeOffset());
            incCurrentScopeOffset();
            $$ = symbolToExpr(newSymbol);
        } else if( symtable.contains($2, LIBRARYFUNC) ) {
            yyerror("trying to shadow a Library Function.");
            $$ = NULL;
        }
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
        if($1 == NULL || $1->symbol == NULL) $$ = NULL;
        else {
            Symbol* symbol = $1->symbol;

            if( symbol == NULL ); // An error came up, ignore.
            else if( !symbol->isActive() ) { // If the symbol doesn't exist.
                symbol->setActive(true);
                symtable.insert(symbol);
            }

            $$ = member_item($1, $3, yylineno);
        }
    }
    | lvalue LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
        if( $1 == NULL || $1->symbol == NULL || $3 == NULL); // An error came up, ignore.
        else {
            Symbol* symbol = $1->symbol;
            if( !symbol->isActive() ) { // If the symbol doesn't exist.
                symbol->setActive(true);
                symtable.insert(symbol);
            }

            $$ = member_itemExpr($1, $3, yylineno);
        }
    }
    | call DOT ID {
    }
    | call LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET {
    };

call
    : call LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        if($1 == NULL) $$ = NULL;
        else $$ = make_call($1, reverseElist($3),yylineno);
    }
    | lvalue callsufix {
        if($1 == NULL) $$ = NULL;
        else {
            Expr* lva = emit_iftableitem($1, yylineno); //In case it was a table item too

            if($2->method){
                Expr* tmp = lva;
                lva = emit_iftableitem(member_item(tmp,$2->name,yylineno),yylineno);
                $2->eList.push_front(tmp); //Insert as first argument (reversed, so last)
            }
            $$ = make_call(lva, $2->eList, yylineno);

            Symbol* symbol = $1->symbol;

            if ( symbol == NULL ); // An error came up ignore.
            else if( !symbol->isActive() ) { // Symbol we are trying to call doesn't exist so we create it.
                symbol->setActive(true);
                symtable.insert(symbol);
            }
        }
    }
    | LEFT_PARENTHESES funcdef RIGHT_PARENTHESES LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        if($2 == NULL) $$ = NULL;
        else {
            Expr* func = newExpression(USERFUNCTION_EXPR);
            func->symbol = $2;
            $$ = make_call(func, reverseElist($5), yylineno);
        }
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

        $$->eList = reverseElist($2);
        $$->method = 0;
        $$->name = "NULL";
    }

methodcall
    : DOUBLE_DOT ID LEFT_PARENTHESES elist RIGHT_PARENTHESES {
        $$ = new Call();

        $$->eList = reverseElist($4);
        $$->method = 1;
        $$->name = $2;
    };

elist
    : expr nextexpr {
        $$ = $1;
        if($$ != NULL)
            $$->next = $2;
    }
    | %empty {
        $$ = NULL;
    }
    ;

nextexpr
    : COMMA expr nextexpr {
        $$ = $2;
        if($$ != NULL)
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

        $$ = newExpression(NEW_TABLE_EXPR);
        $$->symbol = newTemp();
        $$->value = $$->symbol->getId();
        emit(OP_TABLECREATE, $$, NULL, NULL, 0, yylineno);

        tmp = $2;
        while(tmp != NULL) {
            emit(OP_TABLESETELEM, newExprConstNum(i++), tmp, $$, 0, yylineno);
            tmp = tmp->next;
        }
    }
    | LEFT_SQUARE_BRACKET indexed RIGHT_SQUARE_BRACKET {
        Expr* tmp;

        $$ = newExpression(NEW_TABLE_EXPR);
        $$->symbol = newTemp();
        $$->value = $$->symbol->getId();
        emit(OP_TABLECREATE, $$, NULL, NULL, 0, yylineno);

        tmp = $2;
        while(tmp != NULL) {
            emit(OP_TABLESETELEM, tmp, tmp->index, $$, 0, yylineno);
            tmp = tmp->next;
        }
    };

indexed
    : indexedelem nextindexed {
        $$ = $1;
        if($$ != NULL)
            $$->next = $2;
    }
    ;

nextindexed
    : COMMA indexedelem nextindexed {
        $$ = $2;
        if($$ != NULL)
            $$->next = $3;
    }
    | %empty {
        $$ = NULL;
    }
    ;

indexedelem
    : LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET{
        $$ = $2;
        if($$ != NULL)
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
        
        if(symtable.contains(currentFunctionName, LIBRARYFUNC)) {
            yyerror("function shadows library function.");
            $$ = NULL;
        } else if (symtable.scopeLookup(currentFunctionName, currentScope) != NULL) {
            yyerror("function already exists.");
            $$ = NULL;
        } else {
            Symbol* function_symbol = new Symbol(currentFunctionName, USERFUNC, currentLine, currentScope, true);
            function_symbol->setAddressQuad(nextQuadLabel());
            emit(OP_FUNCSTART, symbolToExpr(function_symbol), NULL, NULL, 0, yylineno);

            scopeOffsetStack.push(getCurrentScopeOffset()); //Save current offset
            incCurrentScopeOffset();
            enterScopespace(); //Entering function arguments scope space
            resetFormalArgsOffset(); //Start formals from zero

            symtable.insert(function_symbol);
            $$ = function_symbol;
        }
    }
    ;

funcargs
    : LEFT_PARENTHESES idlist RIGHT_PARENTHESES {
        functionOpen++;
        isFunc = true;
        stackLoop.push(loopOpen);
        loopOpen=0;
        enterScopespace(); //Now entering function locals space
        resetFunctionLocalOffset(); //Start counting locals from zero
    }
    ;

funcbody
    : block {
        $$ = getCurrentScopeOffset(); //Extract #total locals
        exitScopespace();  //Exiting function locals space
     }
    ;

funcdef
    : funcprefix funcargs funcbody {
        if($1 == NULL) $$ = NULL;
        else{
            exitScopespace(); //Exiting function definition space
            $1->setTotalLocals($3); //Store #locals in symbol entry

            restoreCurrentScopeOffset(scopeOffsetStack.top()); //Restore previous scope offset
            scopeOffsetStack.pop();

            functionOpen--;
            loopOpen = stackLoop.top();
            stackLoop.pop();
            $$ = $1; //The function definition returns the symbol
            emit(OP_FUNCEND, symbolToExpr($1), NULL, NULL, 0, yylineno);
            //patchLabel for jump
        }
    }
    ;

const
    : INTEGER {
        $$ = newExprConstNum(yylval.integer);
    }
    | REAL{
        $$ = newDoubleExpr(yylval.real);
    }
    | STRING{
        $$ = newExprConstString(yylval.string);
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
        if(currentFunctionName.compare("_Error_") != 0) { //It could never be _Error_
                Symbol* function = symtable.lookup(currentFunctionName, currentScope);
            if(symtable.contains($1, LIBRARYFUNC)) {
                yyerror("formal argument shadows library function.");
                $$ = NULL;
            } else if (function->containsArgument($1)){
                yyerror("formal argument redeclaration.");
                $$ = NULL;
            } else {
                Symbol* newSym = new Symbol($1, FORMALVAR, yylineno, currentScope+1, true);
                newSym->setScopespace(FORMAL_ARG);
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

nextid
    : COMMA ID nextid {
        if( currentFunctionName.compare("_Error_") != 0 ) { //It could never be _Error_
            Symbol* function = symtable.lookup(currentFunctionName, currentScope);
            if(symtable.contains($2, LIBRARYFUNC)) {
                yyerror("formal argument shadows library function.");
                $$ = NULL;
            } else if (function->containsArgument($2)){
                yyerror("formal argument redeclaration.");
                $$ = NULL;
            } else {
                Symbol* newSym = new Symbol($2, FORMALVAR, yylineno, currentScope+1, true);
                newSym->setScopespace(FORMAL_ARG);
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
        emit(OP_IF_EQ, $3, newExprConstBool(true), NULL, nextQuadLabel() + 2, yylineno);
        $$ = nextQuadLabel();

        emit(OP_JUMP, NULL, NULL, NULL, 0, yylineno);

    };

elseprefix
    : ELSE {
        $$ = nextQuadLabel();

        emit(OP_JUMP, NULL, NULL, NULL, 0, yylineno);

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
        timesInLoop.push(countLoop);
        countLoop = 0;
        $$ = nextQuadLabel();

    };

whilecond
    : LEFT_PARENTHESES expr RIGHT_PARENTHESES {
        emit(OP_IF_EQ, $2, newExprConstBool(true), NULL, nextQuadLabel() + 2, yylineno);
        $$ = nextQuadLabel();
        emit(OP_JUMP, NULL, NULL, NULL, 0, yylineno);

    };

whilestmt
    : whilestart {currentLine = yylineno; loopOpen++;} whilecond stmt {loopOpen--;} {

        emit(OP_JUMP, NULL, NULL, NULL, $1, yylineno);
        patchlabel($3, nextQuadLabel());

        patchlist(breakStack, nextQuadLabel(), countLoop); //fix
        patchlist(continueStack, $1, countLoop); //fix
        countLoop = timesInLoop.top(); //fix
        timesInLoop.pop(); //fix
    };


forprefix
    : FOR{currentLine = yylineno; loopOpen++;} LEFT_PARENTHESES elist SEMICOLON {betweenElistExprInFor = nextQuadLabel();} expr SEMICOLON {
        timesInLoop.push(countLoop); //fix
        countLoop = 0; //fix 

        $$ = nextQuadLabel();
        emit(OP_IF_EQ, $7, newExprConstBool(true), NULL, 0, yylineno);
    };

forstmt
    : forprefix { falseJumpInFor = betweenFor();} elist RIGHT_PARENTHESES { loopJumpInFor = betweenFor();} stmt { closureJumpInFor = betweenFor(); loopOpen--;} {
            
            patchlabel($1, loopJumpInFor +1);
            patchlabel(falseJumpInFor, nextQuadLabel());
            patchlabel(loopJumpInFor, betweenElistExprInFor);
            patchlabel(closureJumpInFor-1, falseJumpInFor+1);

            patchlist(breakStack, nextQuadLabel(), countLoop); //fix
            patchlist(continueStack, falseJumpInFor, countLoop); //fix
            countLoop = timesInLoop.top(); //fix
            timesInLoop.pop(); //fix

    };

returnstmt
    : RETURN SEMICOLON {
        if(functionOpen == 0)
            yyerror("return outside of function");
        else {
            emit(OP_RET, NULL, NULL, NULL, 0, yylineno);
        }

    }
    | RETURN expr SEMICOLON {
        if(functionOpen == 0)
            yyerror("return outside of function");
        else {

            emit(OP_RET, $2, NULL, NULL, 0, yylineno);
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
    blockStack = std::stack<bool>();
    stackLoop = std::stack<int>();
    breakStack = std::stack<int>();
    continueStack = std::stack<int>();

    timesInLoop = std::stack<int>();
    countLoop = 0;

    numberListOfBreak = -1;
    numberListOfContinue = -1;

    currentScope = 0;
    functionOpen = 0;
    loopOpen = 0;
    newNameFunction = 1;
    newName = "";
    isFunc = false;

    programVarOffset = 0;
    functionLocalOffset = 0;
    formalArgOffset = 0;
    scopeSpaceCounter = 1;
    tempCounter = 1;

   

    Quads = std::vector<Quad*>();
    Quads.push_back(new Quad()); //dummy quad

    // Start the parser
    yyparse();

    // Ending Lexical Analysis
    if ( argc > 1) 
        fclose(yyin);

    if(hadError) {
        std::cout << "Program compiled with errors, terminating..." << std::endl;
        if (!DEBUG) return 0;
    }

    if ( argc == 3 ) {
        printQuadsInFile(argv[2]);
        symtable.printSymbolsInFile(argv[2]);
    } else {
        printQuads();
        symtable.printSymTable();
    }

    return 0;
}