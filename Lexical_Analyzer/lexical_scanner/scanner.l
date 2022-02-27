/* Definitions */
%{  
    #include <queue>
    #include <iostream>
    #include <string>
    #include <stack>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    
    /* 
     * return 1 -> if yylval was successfuly created.
     * return 0 -> if yylval was not created.
     */
    #define YY_DECL int alpha_yylex (alpha_token_t* yylval)

    class alpha_token_t {
        private:
            unsigned int m_numline;
            unsigned int m_numToken;
            char*        m_content;
            char*        m_token_category;
            char*        m_token_type;
            char*        m_content_type;

        public:
            alpha_token_t(unsigned int numline = 0,
                            unsigned int numToken = 0 ,
                            char* content = "" ,
                            char* tokenCategory = "",
                            char* tokenType = "",
                            char* contentType = "" )
            {
                m_numline = numline;
                m_numToken = numToken;
                m_content = content;
                m_token_category = tokenCategory;
                m_token_type = tokenType;
                m_content_type = contentType;
            }

            unsigned int getNumline() {
                return m_numline;
            }

            void setNumline(unsigned int numline) {
                m_numline = numline;
            }

            unsigned int getnumToken() {
                return m_numToken;
            }

            void setNumtoken(unsigned int numtoken) {
                m_numToken = numtoken;
            }

            char* getContent() {
                return m_content;
            }

            void setContent(char* content) {
                m_content = content;
            }

            char* getTokenCategory() {
                return m_token_category;
            }

            void setTokenCategory(char* tokenCategory) {
                m_token_category = tokenCategory;
            }

            char* getTokenType() {
                return m_token_type;
            }

            void setTokenType(char* type) {
                m_token_type = type;
            }

            char* getContentType() {
                return m_content_type;
            }

            void setContentType(char* contentType) {
                m_content_type = contentType;
            }

            std::string toString() {
                return  std::to_string(m_numline) + ":   " \
                + "#" + std::to_string(m_numToken) + "   " \
                + "\"" + m_content + "\"" + "   " \
                + m_token_category + "   " \ 
                + "\"" +  m_token_type + "\"" + "   " \
                + "<-" + m_content_type + "\n";
            }

    };

    // Globals
    enum lex_state_t { DEFAULT = 0, LINE_COMMENT = 1, BLOCK_COMMENT = 2 } state;
    unsigned int tokenCounter;
    std::queue<alpha_token_t*> tokenQueue;
    std::stack<unsigned int> commentStack;
%}

/* Flex options */
%option yylineno
%option prefix="alpha_yy"
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

/* Pattern Actions */
%%
{IF}                    {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("IF");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
    
{ELSE}                  {   
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("ELSE");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                            
{WHILE}                 {   
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("WHILE");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                            
{FOR}                   {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("FOR");
                            yylval->setContentType("enumerated");
                            return 1;        
                        }

{FUNCTION}              {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("FUNCTION");
                            yylval->setContentType("enumerated");
                            return 1;
                        }                  
                            
{RETURN}                {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("RETURN");
                            yylval->setContentType("enumerated");
                            return 1;
                        }  
     
{BREAK}                 {   
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("BREAK");
                            yylval->setContentType("enumerated");
                            return 1;
                        } 
                            
{CONTINUE}              {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("CONTINUE");
                            yylval->setContentType("enumerated");
                            return 1;
                        } 
                            
{AND}                   {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("AND");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{NOT}                   {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("NOT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }    

{OR}                    {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("OR");
                            yylval->setContentType("enumerated");
                            return 1;
                        }  

{LOCAL}                 {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("LOCAL");
                            yylval->setContentType("enumerated");
                            return 1;
                        }    

{TRUE}                  {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("TRUE");
                            yylval->setContentType("enumerated");
                            return 1;
                        }  
                        
{FALSE}                 {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("FALSE");
                            yylval->setContentType("enumerated");
                            return 1;
                        } 

{NIL}                   {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("NIL");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{ASSIGNMENT}            {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("ASSIGNMENT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{ADDITION}              {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("ADDITION");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{SUBTRACTION}           {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("SUBTRACTION");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{MULTIPLICATION}        {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("MULTIPLICATION");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{DIVISION}              {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("DIVISION");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{MODULO}                {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("MODULO");
                            yylval->setContentType("enumerated");
                            return 1;
                        }   
                                                                                                    
{EQUALITY}              {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("EQUALITY");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{INEQUALITY}            {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("INEQUALITY");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{INCREMENT}             {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("INCREMENT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{DECREMENT}             {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("DECREMENT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{GREATER_THAN}          {
                            if( state != DEFAULT ) return 0;    
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("GREATER_THAN");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                        
{LESS_THAN}             {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("LESS_THAN");
                            yylval->setContentType("enumerated");
                            return 1;
                        }            

{GREATER_OR_EQUAL}      {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("GREATER_OR_EQUAL");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{LESS_OR_EQUAL}         {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("OPERATOR");
                            yylval->setTokenType("LESS_OR_EQUAL");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{LEFT_CURLY_BRACKET}    {   
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PUNCTUATION");
                            yylval->setTokenType("LEFT_CURLY_BRACKET");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
{RIGHT_CURLY_BRACKET}    {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PUNCTUATION");
                            yylval->setTokenType("RIGHT_CURLY_BRACKET");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
{LEFT_SQUARE_BRACKET}   {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PUNCTUATION");
                            yylval->setTokenType("LEFT_SQUARE_BRACKET");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
    
{RIGHT_SQUARE_BRACKET}  {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("RIGHT_SQUARE_BRACKET");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{LEFT_PARENTHESES}      {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("LEFT_PARENTHESES");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{RIGHT_PARENTHESES}     {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("RIGHT_PARENTHESES");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{SEMICOLON}             {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("SEMICOLON");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{COMMA}                 {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("COMMA");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                            
{COLON}                 {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("COLON");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{DOUBLE_COLON}          {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PANCTUATION");
                            yylval->setTokenType("DOUBLE_COLON");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{DOT}                   {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PUNCTUATION");
                            yylval->setTokenType("DOT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{DOUBLE_DOT}            {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("PUNCTUATION");
                            yylval->setTokenType("DOUBLE_DOT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }

{LINE_COMMENT}          {
                            if( state != DEFAULT ) return 0;
                            state = LINE_COMMENT;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("COMMENT");
                            yylval->setTokenType("LINE_COMMENT");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
                            
{BLOCK_COMMENT_OPEN}    {
                            if( state == LINE_COMMENT ) return 0;
                            commentStack.push(yylineno);
                            state = BLOCK_COMMENT;
                            return 0;
                        }

{BLOCK_COMMENT_CLOSE}   {
                            if( state == LINE_COMMENT ) return 0;
                            if( commentStack.empty() ) {
                                alpha_token_t* mult = new alpha_token_t(yylineno, ++tokenCounter, "*", "OPERATOR", "MULTIPLICATION", "enumerated");
                                alpha_token_t* div = new alpha_token_t(yylineno, ++tokenCounter, "/", "OPERATOR", "DIVISION", "enumerated");
                                tokenQueue.push(mult);
                                tokenQueue.push(div);
                                return 0;
                            }
                            unsigned int lastCommentLine = commentStack.top();
                            commentStack.pop();
                            
                            std::string blockCommentRange = std::to_string(lastCommentLine) + " - " + std::to_string(yylineno);
                            char* blockCommentRange_cstr = new char[blockCommentRange.length() + 1];
                            strcpy(blockCommentRange_cstr, blockCommentRange.c_str());
                            if(commentStack.empty()) {
                                state = DEFAULT;
                                yylval->setNumline(lastCommentLine);
                                yylval->setNumtoken(++tokenCounter);
                                yylval->setContent(blockCommentRange_cstr);
                                yylval->setTokenCategory("COMMENT");
                                yylval->setTokenType("BLOCK_COMMENT");
                                yylval->setContentType("enumerated");
                            } else {
                                yylval->setNumline(lastCommentLine);
                                yylval->setNumtoken(++tokenCounter);
                                yylval->setContent(blockCommentRange_cstr);
                                yylval->setTokenCategory("COMMENT");
                                yylval->setTokenType("NESTED_COMMENT");
                                yylval->setContentType("enumerated");
                            }

                            return 1;
                        }


{ID}                    {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("ID");
                            yylval->setContentType("char*");
                            return 1;
                        }
                        
{INTEGER}               {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("INTEGER");
                            yylval->setTokenType(yytext);
                            yylval->setContentType("int");
                            return 1;
                        }
                        
{REAL}                  {
                            if( state != DEFAULT ) return 0;
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("REAL");
                            yylval->setTokenType("yytext");
                            yylval->setContentType("real");
                            return 1;
                        }

{DELIMITER}             {
                            if(strcmp(yytext, "\n") == 0 && state == LINE_COMMENT) {
                                    state = DEFAULT;
                            }
                        }

{STRING}                {
                            
                        }
                            
                                   
%%

int main(int argc, char** argv) {
    // Argument Checking.
    if(argc > 3) {
        fprintf(stderr, "Too many input arguments\n");
        return 1;
    }
    if (argc > 1) {
        if (!(alpha_yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    } else {
        alpha_yyin = stdin;       
    }
    
    // Initialization
    tokenQueue = std::queue<alpha_token_t*>();
    commentStack = std::stack<unsigned int>();
    tokenCounter = 0;
    state = DEFAULT;

    // Main Loop
    while(true) {
        alpha_token_t* token = new alpha_token_t();
        int isSuccess = alpha_yylex(token);
        
        switch( isSuccess ) {
            case 0:
                break;
            case 1:
                tokenQueue.push(token);
                std::cout << token->toString() << std::endl;
                break;
        }
    }

    // Ending Lexical Analysis
    if ( argc > 1)
        fclose(alpha_yyin);

    if ( argc == 3) {
        FILE *output_file;
        output_file = fopen(argv[2], "w");
        // TODO grafoume sto arxeio.
        fclose(output_file);
    } else
        // TODO grafoume sto terminal.

    return 0;
    
}


/*
if ()
*/
