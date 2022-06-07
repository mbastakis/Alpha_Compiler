/* Definitions */
%{
    #include <iostream>
    #include <string>
    #include <stack>
    #include <cstring>

    #include "../public/Symbol.hpp"
    #include "../public/IntermediateCode.hpp"
    #include "parser.h"

    // Globals
    enum { DEFAULT = 0, LINE_COMMENT = 1, BLOCK_COMMENT = 2 } state = DEFAULT;
    std::stack<unsigned int> commentStack;

    //Functions
    void yellow() {
         std::cout << "\033[0;33m";
    }

    void resetLex() {
         std::cout << "\033[0;37m";
     }

    char* formatEscapedCharacters(char* string){
        int stringSize = strlen(string);


        char* formatedString = new char[stringSize + 1];

        int j = 0;
        for(int i = 1; i < stringSize - 1; ++i) {
            if(string[i] != '\\') formatedString[j++] = string[i];
            else {
                switch(string[i + 1]) {
                    case 'n':
                        formatedString[j++] = '\n';
                        i++;
                        break;
                    case 't':
                        formatedString[j++] = '\t';
                        i++;
                        break;
                    case 'r':
                        formatedString[j++] = '\r';
                        i++;
                        break;
                    case 'v':
                        formatedString[j++] = '\v';
                        i++;
                        break;
                    case '\\':
                        formatedString[j++] = '\\';
                        i++;
                        break;
                    case '"':
                        formatedString[j++] = '"';
                        i++;
                        break;
                    default:
                        yellow();
                        std::cerr << "Warning: In line " << yylineno << " invalid escape character found!" << std::endl;
                        resetLex();
                        return NULL;
                }
            }
        }

        formatedString[j] = '\0';

        return formatedString;
    }
%}

/* Flex options */
%option yylineno
%option noyywrap

/* ___Flex macros___ */
/* KEYWORDS */
IF                          "if"
ELSE                        "else"
WHILE                       "while"
FOR                         "for"
FUNCTION                    "function"
RETURN                      "return"
BREAK                       "break"
CONTINUE                    "continue"
AND                         "and"
NOT                         "not"
OR                          "or"
LOCAL                       "local"
TRUE                        "true"
FALSE                       "false"
NIL                         "nil"
/* OPERATORS */
ASSIGNMENT                  "="
ADDITION                    "+"
SUBTRACTION                 "-"
MULTIPLICATION              "*"
DIVISION                    "/"
MODULO                      "%"
EQUALITY                    "=="
INEQUALITY                  "!="
INCREMENT                   "++"
DECREMENT                   "--"
GREATER_THAN                ">"
LESS_THAN                   "<"
GREATER_OR_EQUAL            ">="
LESS_OR_EQUAL               "<="
/* PANCTUATION */
LEFT_CURLY_BRACKET          "{"
RIGHT_CURLY_BRACKET         "}"
LEFT_SQUARE_BRACKET         "["
RIGHT_SQUARE_BRACKET        "]"
LEFT_PARENTHESES            "("
RIGHT_PARENTHESES           ")"
SEMICOLON                   ";"
COMMA                       ","
COLON                       ":"
DOUBLE_COLON                "::"
DOT                         "."
DOUBLE_DOT                  ".."
LINE_COMMENT                "//"
BLOCK_COMMENT_OPEN          "/*"
BLOCK_COMMENT_CLOSE         "*/"
/* REGEX */
ID                          [a-zA-Z][a-zA-Z_0-9]*
INTEGER                     [0-9]+
REAL                        [0-9]*\.[0-9]+
DELIMITER                   [\r\n \t\v\r]
STRING                      \"(\\.|[^"\\])*\"
INCOMPLETE_STRING           \"
UNKNOWN_CHARACTER           [!@#$^?`'~|\\_&]
/* Pattern Actions */
%%
{IF}                    {
                            if( state == DEFAULT )
                                return (IF);
                        }
{ELSE}                  {
                            if( state == DEFAULT )
                                return (ELSE);
                        }
{WHILE}                 {
                            if( state == DEFAULT )
                                return (WHILE);
                        }
{FOR}                   {
                            if( state == DEFAULT )
                                return (FOR);
                        }
{FUNCTION}              {
                            if( state == DEFAULT )
                                return (FUNCTION);
                        }
{RETURN}                {
                            if( state == DEFAULT )
                                return (RETURN);
                        }
{BREAK}                 {
                            if( state == DEFAULT )
                                return (BREAK);
                        }
{CONTINUE}              {
                            if( state == DEFAULT )
                                return (CONTINUE);
                        }
{AND}                   {
                            if( state == DEFAULT )
                                return (AND);
                        }
{NOT}                   {
                            if( state == DEFAULT )
                                return (NOT);
                        }
{OR}                    {
                            if( state == DEFAULT )
                                return (OR);
                        }
{LOCAL}                 {
                            if( state == DEFAULT )
                                return (LOCAL);
                        }
{TRUE}                  {
                            if( state == DEFAULT )
                                return (TRUE);
                        }
{FALSE}                 {
                            if( state == DEFAULT )
                                return (FALSE);
                        }
{NIL}                   {
                            if( state == DEFAULT )
                                return (NIL);
                        }
{ASSIGNMENT}            {
                            if( state == DEFAULT )
                                return (ASSIGNMENT);
                        }
{ADDITION}              {
                            if( state == DEFAULT )
                                return (ADDITION);
                        }
{SUBTRACTION}           {
                            if( state == DEFAULT )
                                return (SUBTRACTION);
                        }
{MULTIPLICATION}        {
                            if( state == DEFAULT )
                                return (MULTIPLICATION);
                        }
{DIVISION}              {
                            if( state == DEFAULT )
                                return (DIVISION);
                        }
{MODULO}                {
                            if( state == DEFAULT )
                                return (MODULO);
                        }
{EQUALITY}              {
                            if( state == DEFAULT )
                                return (EQUALITY);
                        }
{INEQUALITY}            {
                            if( state == DEFAULT )
                                return (INEQUALITY);
                        }
{INCREMENT}             {
                            if( state == DEFAULT )
                                return (INCREMENT);
                        }
{DECREMENT}             {
                            if( state == DEFAULT )
                                return (DECREMENT);
                        }
{GREATER_THAN}          {
                            if( state == DEFAULT )
                                return (GREATER_THAN);
                        }
{LESS_THAN}             {
                            if( state == DEFAULT )
                                return (LESS_THAN);
                        }
{GREATER_OR_EQUAL}      {
                            if( state == DEFAULT )
                                return (GREATER_OR_EQUAL);
                        }
{LESS_OR_EQUAL}         {
                            if( state == DEFAULT )
                                return (LESS_OR_EQUAL);
                        }
{LEFT_CURLY_BRACKET}    {
                            if( state == DEFAULT )
                                return (LEFT_CURLY_BRACKET);
                        }
{RIGHT_CURLY_BRACKET}   {
                            if( state == DEFAULT )
                                return (RIGHT_CURLY_BRACKET);
                        }
{LEFT_SQUARE_BRACKET}   {
                            if( state == DEFAULT )
                                return (LEFT_SQUARE_BRACKET);
                        }
{RIGHT_SQUARE_BRACKET}  {
                            if( state == DEFAULT )
                                return (RIGHT_SQUARE_BRACKET);
                        }
{LEFT_PARENTHESES}      {
                            if( state == DEFAULT )
                                return (LEFT_PARENTHESES);
                        }
{RIGHT_PARENTHESES}     {
                            if( state == DEFAULT )
                                return (RIGHT_PARENTHESES);
                        }
{SEMICOLON}             {
                            if( state == DEFAULT )
                                return (SEMICOLON);
                        }
{COMMA}                 {
                            if( state == DEFAULT )
                                return (COMMA);
                        }
{COLON}                 {
                            if( state == DEFAULT )
                                return (COLON);
                        }
{DOUBLE_COLON}          {
                            if( state == DEFAULT )
                                return (DOUBLE_COLON);
                        }
{DOT}                   {
                            if( state == DEFAULT )
                                return (DOT);
                        }
{DOUBLE_DOT}            {
                            if( state == DEFAULT )
                                return (DOUBLE_DOT);
                        }
{BLOCK_COMMENT_OPEN}    {
                            if( state != LINE_COMMENT ) {
                                commentStack.push(yylineno);
                                state = BLOCK_COMMENT;
                            }
                        }
{BLOCK_COMMENT_CLOSE}   {
                            if( state != LINE_COMMENT ) {
                                if( commentStack.empty() ) return (ERROR);
                                commentStack.pop();
                                if( commentStack.empty() ) state = DEFAULT;
                            }
                        }
{ID}                    {
                            if( state == DEFAULT) {
                                std::string str = std::string(yytext);
                                char * cStr = strcpy(new char[str.length() + 1], str.c_str());
                                yylval.string = cStr;
                                return (ID);
                            }
                        }
{INTEGER}               {
                            if( state == DEFAULT ) {
                                yylval.integer = std::stoi(yytext);
                                return (INTEGER);
                            }
                        }
{REAL}                  {
                            if( state == DEFAULT ) {
                                yylval.real = std::stod(yytext);
                                return (REAL);
                            }
                        }
{DELIMITER}             {
                            if(strcmp(yytext, "\n") == 0 && state == LINE_COMMENT)
                                state = DEFAULT;
                        }
{STRING}                {
                            if( state == DEFAULT ) {
                                char* formatedString =  formatEscapedCharacters(yytext);
                                if(formatedString == NULL) return (ERROR);
                                yylval.string = formatedString;
                                return (STRING);
                            }
                        }
{INCOMPLETE_STRING}     {
                            if(state == DEFAULT){
                                std::cerr << "Error: Incomplete string was detected at line: " << yylineno << std::endl;
                                return (ERROR);
                            }
                        }
{UNKNOWN_CHARACTER}     {
                            if(state == DEFAULT) {
                                std::cerr << "Error: Unknown character " << yytext << " found at line: " << yylineno << std::endl;
                                return (ERROR);
                            }
                        }
{LINE_COMMENT}          {
                            if( state == BLOCK_COMMENT ) unput(yytext[1]);
                            else if( state == DEFAULT ) state = LINE_COMMENT;
                        }
%%