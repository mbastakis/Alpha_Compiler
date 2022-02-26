/* Definitions */
%{  
    #include <queue>
    #include <iostream>
    #include <string>
    
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
                + m_content;
            }

    };

    // Globals
    unsigned int tokenCounter = 0;
    std::queue<alpha_token_t*> tokenQueue;
    
   
%}

/* Flex options */
%option yylineno
%option prefix="alpha_yy"
%option noyywrap

/* ___Flex macros___ */
/* KEYWORDS */
IF                         "if"
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
                            yylval->setNumline(yylineno);
                            yylval->setNumtoken(++tokenCounter);
                            yylval->setContent(yytext);
                            yylval->setTokenCategory("KEYWORD");
                            yylval->setTokenType("IF");
                            yylval->setContentType("enumerated");
                            return 1;
                        }
    
{ELSE}                  {

                        }
                            
{WHILE}                 {

                        }
                            
{FOR}                   {
        
                        }

{FUNCTION}              {
        
                        }                  
                            
{RETURN}                {
        
                        }  
     
{BREAK}                 {
        
                        } 
                            
{CONTINUE}              {
        
                        } 
                            
{AND}                   {
        
                        }

{NOT}                   {
        
                        }    

{OR}                    {
        
                        }  

{LOCAL}                 {
        
                        }    

{TRUE}                  {
    
                        }  
{FALSE}                 {
        
                        } 

{NIL}                   {
        
                        }
{ASSIGNMENT}            {
        
                        }
{ADDITION}              {
        
                        }
{SUBTRACTION}           {
        
                        }
{MULTIPLICATION}        {
        
                        }
{DIVISION}              {
        
                        }
{MODULO}                {

                        }                                                                               
{EQUALITY}              {

                        }
{INEQUALITY}            {

                        }
{INCREMENT}             {

                        }
{DECREMENT}             {

                        }
{GREATER_THAN}          {

                        }
{LESS_THAN}             {

                        }                        
{GREATER_OR_EQUAL}      {

                        }
{LESS_OR_EQUAL}         {

                        }


{LEFT_CURLY_BRACKET}    {

                        }
    
{RIGHT_CURLY_BRACKET}   {

                        }

{LEFT_SQUARE_BRACKET}   {

                        }
    
{RIGHT_SQUARE_BRACKET}  {

                        }

{LEFT_PARENTHESES}      {
        
                        }

{RIGHT_PARENTHESES}     {
        
                        }

{SEMICOLON}             {
        
                        }

{COMMA}                 {
        
                        }
                            
{COLON}                 {
        
                        }

{DOUBLE_COLON}          {
        
                        }

{DOT}                   {
        
                        }

{DOUBLE_DOT}            {
        
                        }

{LINE_COMMENT}          {
        
                        }
                            
{BLOCK_COMMENT_OPEN}    {

                        }

{BLOCK_COMMENT_CLOSE}   {

                        }


{ID}                    {

                        }
{INTEGER}               {

                        }
{REAL}                  {

                        }
{DELIMITER}             {

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

    // Main Loop
    while(true) {
        alpha_token_t* token = new alpha_token_t();
        int isSuccess = alpha_yylex(token);
        
        // switch
        if (isSuccess) {
            tokenQueue.push(token);
        }
        std::cout << token->toString() << std::endl;
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
