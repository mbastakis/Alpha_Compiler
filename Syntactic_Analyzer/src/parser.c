/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parser.y"

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
    int scope=0;

    /* Function Declarations */
     void yyerror (char const *s) {      
        fprintf (stderr, "%s\n", s);
        fprintf(stderr, "at line %d,  before token: %s \n", yylineno, yytext);
        fprintf(stderr, "INPUT NOT VALID\n");
        found_errors = 1;
    }

    /* Symbol */
    class Symbol {
    private:
        std::string id;
        std::string type;
        unsigned int scope;
        unsigned int line;
    public:
        Symbol(std::string _id, std::string _type, unsigned int _scope, unsigned int _line) {
            id = _id;
            scope = _scope;
            line = _line;
        }

        std::string getId() {
            return id;
        }

        std::string getType() {
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
    std::unordered_map<int, Symbol> SymbolTable;


#line 148 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    NOT = 267,
    OR = 268,
    LOCAL = 269,
    TRUE = 270,
    FALSE = 271,
    NIL = 272,
    ASSIGNMENT = 273,
    ADDITION = 274,
    SUBTRACTION = 275,
    MULTIPLICATION = 276,
    DIVISION = 277,
    MODULO = 278,
    EQUALITY = 279,
    INEQUALITY = 280,
    INCREMENT = 281,
    DECREMENT = 282,
    GREATER_THAN = 283,
    LESS_THAN = 284,
    GREATER_OR_EQUAL = 285,
    LESS_OR_EQUAL = 286,
    UNARY_MINUS = 287,
    LEFT_CURLY_BRACKET = 288,
    RIGHT_CURLY_BRACKET = 289,
    LEFT_SQUARE_BRACKET = 290,
    RIGHT_SQUARE_BRACKET = 291,
    LEFT_PARENTHESES = 292,
    RIGHT_PARENTHESES = 293,
    SEMICOLON = 294,
    COMMA = 295,
    COLON = 296,
    DOUBLE_COLON = 297,
    DOT = 298,
    DOUBLE_DOT = 299,
    STRING = 300,
    ID = 301,
    INTEGER = 302,
    REAL = 303,
    ERROR = 304,
    PUREIF = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 84 "parser.y"

    int integer;
    double real;
    char* string;
    unsigned int expression;

#line 258 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   626

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

#define YYUNDEFTOK  2
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   132,   132,   136,   139,   143,   146,   147,   148,   151,
     154,   162,   171,   172,   173,   177,   180,   184,   189,   194,
     199,   204,   209,   214,   219,   224,   229,   234,   239,   244,
     251,   255,   259,   263,   267,   271,   275,   279,   284,   289,
     292,   295,   298,   301,   306,   311,   314,   317,   321,   324,
     327,   330,   335,   338,   341,   347,   350,   355,   360,   365,
     368,   372,   375,   379,   382,   387,   393,   396,   400,   405,
     405,   405,   410,   410,   414,   414,   420,   423,   426,   429,
     432,   435,   440,   443,   447,   450,   456,   456,   461,   461,
     464,   464,   464,   469,   469,   469,   474,   474,   474,   479,
     488
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE",
  "FALSE", "NIL", "ASSIGNMENT", "ADDITION", "SUBTRACTION",
  "MULTIPLICATION", "DIVISION", "MODULO", "EQUALITY", "INEQUALITY",
  "INCREMENT", "DECREMENT", "GREATER_THAN", "LESS_THAN",
  "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "UNARY_MINUS", "LEFT_CURLY_BRACKET",
  "RIGHT_CURLY_BRACKET", "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET",
  "LEFT_PARENTHESES", "RIGHT_PARENTHESES", "SEMICOLON", "COMMA", "COLON",
  "DOUBLE_COLON", "DOT", "DOUBLE_DOT", "STRING", "ID", "INTEGER", "REAL",
  "ERROR", "PUREIF", "$accept", "program", "statements", "stmt", "expr",
  "term", "assignexpr", "primary", "lvalue", "member", "call", "callsufix",
  "normcall", "methodcall", "elist", "nextexpr", "objectdef", "indexed",
  "nextindexed", "indexedelem", "block", "$@1", "$@2", "funcdef", "$@3",
  "$@4", "const", "idlist", "nextid", "ifprefix", "$@5", "ifstmt", "$@6",
  "$@7", "$@8", "whilestmt", "$@9", "$@10", "forstmt", "$@11", "$@12",
  "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF (-156)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-75)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -156,     5,   200,  -156,  -156,  -156,  -156,   -29,    94,   -23,
     -15,   261,   -18,  -156,  -156,  -156,   261,   -12,   -12,  -156,
     237,     6,  -156,    -4,  -156,  -156,  -156,  -156,  -156,   336,
    -156,  -156,  -156,   449,  -156,     2,  -156,  -156,  -156,  -156,
     200,  -156,  -156,  -156,  -156,     7,    12,    13,    15,    21,
    -156,   357,  -156,  -156,  -156,  -156,  -156,    24,    -8,     2,
      -8,  -156,   261,   314,    23,    26,    25,   399,    28,  -156,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,  -156,   261,  -156,  -156,   261,   261,    17,
      35,  -156,  -156,  -156,   261,   261,    37,    80,   261,   261,
     261,    49,    41,  -156,    50,   154,   291,   261,  -156,  -156,
    -156,    56,  -156,  -156,    53,   569,   556,    34,    34,  -156,
    -156,  -156,   582,   582,   595,   595,   595,   595,   541,   497,
      55,  -156,    54,   476,    60,  -156,  -156,  -156,   420,   441,
      61,    41,    59,    63,    53,  -156,   261,   314,    25,   261,
    -156,  -156,   261,  -156,  -156,   200,  -156,   200,   261,    64,
      48,  -156,    71,  -156,   519,  -156,  -156,    69,    74,  -156,
    -156,   378,    71,    59,  -156,  -156,  -156,  -156,  -156,  -156,
     261,  -156,  -156,    75,   200,  -156,  -156
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    86,    93,    96,    72,     0,     0,
       0,     0,     0,    80,    81,    79,     0,     0,     0,    69,
      60,     0,    14,     0,    78,    44,    76,    77,     3,     0,
      29,    15,    37,    39,    47,    40,    41,    12,    13,    43,
       0,     6,     7,     8,     9,     0,     0,     0,     0,     0,
      99,     0,    10,    11,    32,    45,    31,     0,    33,     0,
      35,     4,     0,    62,     0,     0,    67,     0,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     0,    34,    36,     0,    60,     0,
       0,    53,    55,    56,     0,    60,     0,    88,     0,     0,
      60,     0,    83,   100,     0,     0,     0,     0,    59,    63,
      64,     0,    65,    30,    42,    27,    28,    16,    17,    18,
      19,    20,    25,    26,    21,    22,    23,    24,    38,     0,
       0,    48,     0,     0,     0,    50,    90,    89,     0,     0,
       0,    83,    85,     0,     0,    70,     0,    62,    67,    60,
      49,    57,    60,    51,    52,     0,    87,     0,     0,     0,
       0,    82,     0,    71,     0,    61,    66,     0,     0,    91,
      94,     0,     0,    85,    75,    68,    54,    58,    92,    95,
      60,    73,    84,     0,     0,    97,    98
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -156,  -156,    58,   -39,    -2,  -156,  -156,  -156,    -6,  -156,
      29,  -156,  -156,  -156,   -85,   -32,  -156,  -156,   -31,    11,
    -155,  -156,  -156,   -17,  -156,  -156,  -156,   -16,   -50,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    63,    30,    31,    32,    33,    34,
      35,    91,    92,    93,    64,   108,    36,    65,   112,    66,
      37,    61,   163,    38,    48,    49,    39,   143,   161,    40,
      45,    41,   137,   155,   178,    42,    46,   179,    43,    47,
     186,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    97,    12,   130,    68,     3,    51,   174,   -74,    54,
     134,    58,    60,     7,    56,   140,    52,   181,    11,    67,
      12,    13,    14,    15,    53,    57,    16,    87,    55,    88,
      23,     7,    17,    18,    25,    89,    90,    94,    29,    95,
     104,    20,    69,    21,    98,    96,    59,    59,    23,    99,
     100,    24,    25,    26,    27,    74,    75,    76,   102,   109,
     106,   101,   110,   131,   167,   111,   114,   168,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   132,   128,   135,   136,   129,   141,   142,   144,    62,
     149,   152,   133,   151,   173,   183,   138,   139,   154,   160,
     158,   162,   172,    29,    19,   147,    11,   176,    12,    13,
      14,    15,   177,   184,    16,   165,   169,   166,   170,   105,
      17,    18,   148,   182,     0,   159,     0,     0,     0,    20,
       0,    21,     0,    50,     0,     0,    23,     0,     0,    24,
      25,    26,    27,     0,   164,   185,     0,     0,     0,     0,
       0,     0,     0,    29,     0,    29,   171,     4,     0,     5,
       6,     7,     8,     9,    10,     0,    11,     0,    12,    13,
      14,    15,     0,     0,    16,     0,     0,     0,     0,     0,
      17,    18,    29,     0,     0,     0,     0,    19,   145,    20,
       0,    21,     0,    22,     0,     0,    23,     0,     0,    24,
      25,    26,    27,     4,     0,     5,     6,     7,     8,     9,
      10,     0,    11,     0,    12,    13,    14,    15,     0,     0,
      16,     0,     0,     0,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,     0,    20,     0,    21,     0,    22,
       0,     0,    23,     0,     0,    24,    25,    26,    27,    11,
       0,    12,    13,    14,    15,     0,     0,    16,     0,     0,
       0,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      62,     0,    20,    11,    21,    12,    13,    14,    15,    23,
       0,    16,    24,    25,    26,    27,     0,    17,    18,     0,
       0,     0,     0,     0,     0,     0,    20,     0,    21,     0,
       0,     0,    70,    23,    71,     0,    24,    25,    26,    27,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,     0,     0,    70,     0,    71,     0,     0,
       0,     0,   146,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    81,    82,     0,    70,     0,    71,
       0,     0,     0,     0,   107,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    70,     0,
      71,     0,     0,     0,     0,    83,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,    70,
       0,    71,     0,     0,     0,     0,   103,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
      70,     0,    71,     0,     0,     0,     0,   180,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    70,     0,    71,     0,     0,     0,   113,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    70,     0,    71,     0,     0,     0,   156,     0,
      72,    73,    74,    75,    76,    77,    78,    84,     0,    79,
      80,    81,    82,     0,     0,    85,    86,     0,     0,   157,
       0,     0,     0,     0,    87,     0,    88,    70,     0,    71,
       0,     0,    89,    90,     0,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    70,     0,
      71,     0,   153,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,     0,
      70,   150,    71,     0,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,     0,    70,   175,    71,     0,     0,     0,     0,     0,
      72,    73,    74,    75,    76,    77,    78,    70,     0,    79,
      80,    81,    82,     0,     0,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    72,    73,    74,    75,    76,   -75,   -75,     0,     0,
      79,    80,    81,    82,    72,    73,    74,    75,    76,     0,
       0,     0,     0,   -75,   -75,   -75,   -75
};

static const yytype_int16 yycheck[] =
{
       2,    40,    14,    88,    21,     0,     8,   162,    37,    11,
      95,    17,    18,     7,    16,   100,    39,   172,    12,    21,
      14,    15,    16,    17,    39,    37,    20,    35,    46,    37,
      42,     7,    26,    27,    46,    43,    44,    35,    40,    37,
      57,    35,    46,    37,    37,    43,    17,    18,    42,    37,
      37,    45,    46,    47,    48,    21,    22,    23,    37,    36,
      62,    46,    36,    46,   149,    40,    38,   152,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    46,    84,    46,     4,    87,    37,    46,    38,    33,
      37,    37,    94,    38,    46,   180,    98,    99,    38,    40,
      39,    38,    38,   105,    33,   107,    12,    38,    14,    15,
      16,    17,    38,    38,    20,   147,   155,   148,   157,    61,
      26,    27,   111,   173,    -1,   141,    -1,    -1,    -1,    35,
      -1,    37,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,    48,    -1,   146,   184,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   155,    -1,   157,   158,     3,    -1,     5,
       6,     7,     8,     9,    10,    -1,    12,    -1,    14,    15,
      16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    27,   184,    -1,    -1,    -1,    -1,    33,    34,    35,
      -1,    37,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,    48,     3,    -1,     5,     6,     7,     8,     9,
      10,    -1,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    35,    -1,    37,    -1,    39,
      -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,    12,
      -1,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    35,    12,    37,    14,    15,    16,    17,    42,
      -1,    20,    45,    46,    47,    48,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    37,    -1,
      -1,    -1,    11,    42,    13,    -1,    45,    46,    47,    48,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    -1,    11,    -1,    13,    -1,    -1,
      -1,    -1,    41,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    11,    -1,    13,
      -1,    -1,    -1,    -1,    40,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    -1,
      13,    -1,    -1,    -1,    -1,    39,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    11,
      -1,    13,    -1,    -1,    -1,    -1,    39,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    -1,    13,    -1,    -1,    -1,    -1,    39,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    -1,    13,    -1,    -1,    -1,    38,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    11,    -1,    13,    -1,    -1,    -1,    38,    -1,
      19,    20,    21,    22,    23,    24,    25,    18,    -1,    28,
      29,    30,    31,    -1,    -1,    26,    27,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    35,    -1,    37,    11,    -1,    13,
      -1,    -1,    43,    44,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    -1,
      13,    -1,    36,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      11,    34,    13,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    11,    34,    13,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    11,    -1,    28,
      29,    30,    31,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     3,     5,     6,     7,     8,     9,
      10,    12,    14,    15,    16,    17,    20,    26,    27,    33,
      35,    37,    39,    42,    45,    46,    47,    48,    54,    55,
      56,    57,    58,    59,    60,    61,    67,    71,    74,    77,
      80,    82,    86,    89,    92,    81,    87,    90,    75,    76,
      39,    55,    39,    39,    55,    46,    55,    37,    59,    61,
      59,    72,    33,    55,    65,    68,    70,    55,    74,    46,
      11,    13,    19,    20,    21,    22,    23,    24,    25,    28,
      29,    30,    31,    39,    18,    26,    27,    35,    37,    43,
      44,    62,    63,    64,    35,    37,    43,    54,    37,    37,
      37,    46,    37,    39,    74,    53,    55,    40,    66,    36,
      36,    40,    69,    38,    38,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      65,    46,    46,    55,    65,    46,     4,    83,    55,    55,
      65,    37,    46,    78,    38,    34,    41,    55,    70,    37,
      34,    38,    37,    36,    38,    84,    38,    38,    39,    78,
      40,    79,    38,    73,    55,    66,    69,    65,    65,    54,
      54,    55,    38,    46,    71,    34,    38,    38,    85,    88,
      39,    71,    79,    65,    38,    54,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    56,    56,    56,    56,    56,    56,    56,    57,    58,
      58,    58,    58,    58,    59,    59,    59,    59,    60,    60,
      60,    60,    61,    61,    61,    62,    62,    63,    64,    65,
      65,    66,    66,    67,    67,    68,    69,    69,    70,    72,
      73,    71,    75,    74,    76,    74,    77,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    81,    80,    83,    82,
      84,    85,    82,    87,    88,    86,    90,    91,    89,    92,
      92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     2,
       0,     3,     0,     3,     3,     2,     3,     0,     5,     0,
       0,     5,     0,     7,     0,     6,     1,     1,     1,     1,
       1,     1,     2,     0,     3,     0,     0,     5,     0,     3,
       0,     0,     6,     0,     0,     7,     0,     0,    11,     2,
       3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 132 "parser.y"
                 {
    }
#line 1661 "parser.c"
    break;

  case 3:
#line 136 "parser.y"
                     {
        
    }
#line 1669 "parser.c"
    break;

  case 5:
#line 143 "parser.y"
                     {

    }
#line 1677 "parser.c"
    break;

  case 8:
#line 148 "parser.y"
              {

    }
#line 1685 "parser.c"
    break;

  case 9:
#line 151 "parser.y"
                 {

    }
#line 1693 "parser.c"
    break;

  case 10:
#line 154 "parser.y"
                      {
        if(stmt_open == 0){
            printf("Error: break outside of statement, Line: %d\n" ,yylineno);
        } 
        else {
            printf("break, Line: %d\n" ,yylineno);
        }
    }
#line 1706 "parser.c"
    break;

  case 11:
#line 162 "parser.y"
                         {
        if(stmt_open == 0){
            printf("Error: continue outside of statement, Line: %d\n" ,yylineno);
        } 
        else {
            printf("continue, Line: %d\n" ,yylineno);
        }

    }
#line 1720 "parser.c"
    break;

  case 15:
#line 177 "parser.y"
                 {
        
    }
#line 1728 "parser.c"
    break;

  case 16:
#line 180 "parser.y"
                         {           
            (yyval.expression) = (yyvsp[-2].expression) + (yyvsp[0].expression);
            printf("expr + expr, Line: %d\n" ,yylineno);
    }
#line 1737 "parser.c"
    break;

  case 17:
#line 184 "parser.y"
                            {
            (yyval.expression) = (yyvsp[-2].expression) - (yyvsp[0].expression);
            printf("expr - expr, Line: %d\n" ,yylineno);
        
    }
#line 1747 "parser.c"
    break;

  case 18:
#line 189 "parser.y"
                               {
            (yyval.expression) = (yyvsp[-2].expression) * (yyvsp[0].expression);
            printf("expr * expr, Line: %d\n" ,yylineno);
        
    }
#line 1757 "parser.c"
    break;

  case 19:
#line 194 "parser.y"
                         {
            (yyval.expression) = (yyvsp[-2].expression) / (yyvsp[0].expression);
            printf("expr / expr, Line: %d\n" ,yylineno);
        
    }
#line 1767 "parser.c"
    break;

  case 20:
#line 199 "parser.y"
                       {
            (yyval.expression) = (yyvsp[-2].expression) % (yyvsp[0].expression);
            printf("expr %% expr, Line: %d\n" ,yylineno);
        
    }
#line 1777 "parser.c"
    break;

  case 21:
#line 204 "parser.y"
                             {
            (yyval.expression) = (yyvsp[-2].expression) > (yyvsp[0].expression);
            printf("expr > expr, Line: %d\n" ,yylineno);
        
    }
#line 1787 "parser.c"
    break;

  case 22:
#line 209 "parser.y"
                          {
            (yyval.expression) = (yyvsp[-2].expression) < (yyvsp[0].expression);
            printf("expr < expr, Line: %d\n" ,yylineno);
        
    }
#line 1797 "parser.c"
    break;

  case 23:
#line 214 "parser.y"
                                 {
            (yyval.expression) = (yyvsp[-2].expression) >= (yyvsp[0].expression);
            printf("expr >= expr, Line: %d\n" ,yylineno);
        
    }
#line 1807 "parser.c"
    break;

  case 24:
#line 219 "parser.y"
                              {
            (yyval.expression) = (yyvsp[-2].expression) <= (yyvsp[0].expression);
            printf("expr <= expr, Line: %d\n" ,yylineno);
        
    }
#line 1817 "parser.c"
    break;

  case 25:
#line 224 "parser.y"
                         {
            (yyval.expression) = (yyvsp[-2].expression) == (yyvsp[0].expression);
            printf("expr == expr, Line: %d\n" ,yylineno);
        
    }
#line 1827 "parser.c"
    break;

  case 26:
#line 229 "parser.y"
                           {
            (yyval.expression) = (yyvsp[-2].expression) != (yyvsp[0].expression);
            printf("expr != expr, Line: %d\n" ,yylineno);
        
    }
#line 1837 "parser.c"
    break;

  case 27:
#line 234 "parser.y"
                    {
            (yyval.expression) = (yyvsp[-2].expression) and (yyvsp[0].expression);
            printf("expr AND expr, Line: %d\n" ,yylineno);
        
    }
#line 1847 "parser.c"
    break;

  case 28:
#line 239 "parser.y"
                   {
            (yyval.expression) = (yyvsp[-2].expression) or (yyvsp[0].expression);
            
            printf("expr OR expr, Line: %d\n" ,yylineno);
    }
#line 1857 "parser.c"
    break;

  case 29:
#line 244 "parser.y"
           {
            (yyval.expression) = (yyvsp[0].expression);
            /*symbolTable[0] = {"x","int","1",1};
            std::cout<<symbolTable[0].name << std::endl;*/
    }
#line 1867 "parser.c"
    break;

  case 30:
#line 251 "parser.y"
                                              {
        (yyval.expression) = ((yyvsp[-1].expression));
        printf("left expr right, Line: %d\n" ,yylineno);
    }
#line 1876 "parser.c"
    break;

  case 31:
#line 255 "parser.y"
                                         {
        (yyval.expression) = - (yyvsp[0].expression);
        printf("unary minus, Line: %d\n" ,yylineno);
    }
#line 1885 "parser.c"
    break;

  case 32:
#line 259 "parser.y"
               {
        (yyval.expression) = not (yyvsp[0].expression);
        printf("NOT expr, Line: %d\n" ,yylineno);
    }
#line 1894 "parser.c"
    break;

  case 33:
#line 263 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) + 1;
        printf("increment lvalue, Line: %d\n" ,yylineno);
    }
#line 1903 "parser.c"
    break;

  case 34:
#line 267 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) + 1;
        printf("lvalue increment, Line: %d\n" ,yylineno);
    }
#line 1912 "parser.c"
    break;

  case 35:
#line 271 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) - 1;
        printf("decrement lvalue, Line: %d\n" ,yylineno);
    }
#line 1921 "parser.c"
    break;

  case 36:
#line 275 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) - 1;
        printf("lvalue decrement, Line: %d\n" ,yylineno);
    }
#line 1930 "parser.c"
    break;

  case 37:
#line 279 "parser.y"
              {
        
    }
#line 1938 "parser.c"
    break;

  case 38:
#line 284 "parser.y"
                             {
        
    }
#line 1946 "parser.c"
    break;

  case 39:
#line 289 "parser.y"
             {
        
    }
#line 1954 "parser.c"
    break;

  case 40:
#line 292 "parser.y"
           {

    }
#line 1962 "parser.c"
    break;

  case 41:
#line 295 "parser.y"
                {

    }
#line 1970 "parser.c"
    break;

  case 42:
#line 298 "parser.y"
                                                 {
        (yyval.expression) = FUNC;
    }
#line 1978 "parser.c"
    break;

  case 43:
#line 301 "parser.y"
            {

    }
#line 1986 "parser.c"
    break;

  case 44:
#line 306 "parser.y"
         {
        Symbol symbol = Symbol((yyvsp[0].string), currentScope, yylineno);
        SymbolTable.insert(std::pair<int, Symbol>(SymbolTableSize++, symbol));
        printf("id, Line: %d\n" , symbol.getLine());
    }
#line 1996 "parser.c"
    break;

  case 45:
#line 311 "parser.y"
               {
        printf("local id, Line: %d\n" ,yylineno);
    }
#line 2004 "parser.c"
    break;

  case 46:
#line 314 "parser.y"
                      {
        
    }
#line 2012 "parser.c"
    break;

  case 47:
#line 317 "parser.y"
             {
    }
#line 2019 "parser.c"
    break;

  case 48:
#line 321 "parser.y"
                    {
        
    }
#line 2027 "parser.c"
    break;

  case 49:
#line 324 "parser.y"
                                                          {

    }
#line 2035 "parser.c"
    break;

  case 50:
#line 327 "parser.y"
                  {

    }
#line 2043 "parser.c"
    break;

  case 51:
#line 330 "parser.y"
                                                         {

    }
#line 2051 "parser.c"
    break;

  case 52:
#line 335 "parser.y"
                                                    {
        
    }
#line 2059 "parser.c"
    break;

  case 53:
#line 338 "parser.y"
                       {

    }
#line 2067 "parser.c"
    break;

  case 54:
#line 342 "parser.y"
                                               {

    }
#line 2075 "parser.c"
    break;

  case 55:
#line 347 "parser.y"
               {

    }
#line 2083 "parser.c"
    break;

  case 56:
#line 350 "parser.y"
                 {

    }
#line 2091 "parser.c"
    break;

  case 57:
#line 355 "parser.y"
                                               {
        printf("normcall, Line: %d\n" ,yylineno);
    }
#line 2099 "parser.c"
    break;

  case 58:
#line 360 "parser.y"
                                                             {
        printf("method call, Line: %d\n" ,yylineno);
    }
#line 2107 "parser.c"
    break;

  case 59:
#line 365 "parser.y"
                    {

    }
#line 2115 "parser.c"
    break;

  case 61:
#line 372 "parser.y"
                          {

    }
#line 2123 "parser.c"
    break;

  case 63:
#line 379 "parser.y"
                                                     {
        printf("object elist, Line: %d\n" ,yylineno);
    }
#line 2131 "parser.c"
    break;

  case 64:
#line 382 "parser.y"
                                                       {
        printf("object indexed, Line: %d\n" ,yylineno);
    }
#line 2139 "parser.c"
    break;

  case 65:
#line 387 "parser.y"
                              {

    }
#line 2147 "parser.c"
    break;

  case 66:
#line 393 "parser.y"
                                    {

    }
#line 2155 "parser.c"
    break;

  case 68:
#line 400 "parser.y"
                                                            {
        
    }
#line 2163 "parser.c"
    break;

  case 69:
#line 405 "parser.y"
                         {function_open++; stmt_open++;}
#line 2169 "parser.c"
    break;

  case 70:
#line 405 "parser.y"
                                                                                        {function_open--; stmt_open--;}
#line 2175 "parser.c"
    break;

  case 71:
#line 405 "parser.y"
                                                                                                                        {
        
    }
#line 2183 "parser.c"
    break;

  case 72:
#line 410 "parser.y"
               {i = yylineno;}
#line 2189 "parser.c"
    break;

  case 73:
#line 410 "parser.y"
                                                                                  {
        scope+=1;
        printf("function id, Line: %d\n" ,i);
    }
#line 2198 "parser.c"
    break;

  case 74:
#line 414 "parser.y"
               {i = yylineno;}
#line 2204 "parser.c"
    break;

  case 75:
#line 414 "parser.y"
                                                                               {
        scope+=1;
        printf("function, Line: %d\n" ,i);
    }
#line 2213 "parser.c"
    break;

  case 76:
#line 420 "parser.y"
              {
        printf("integer, Line: %d\n" ,yylineno);
    }
#line 2221 "parser.c"
    break;

  case 77:
#line 423 "parser.y"
          {
        printf("real, Line: %d\n" ,yylineno);
    }
#line 2229 "parser.c"
    break;

  case 78:
#line 426 "parser.y"
            {
        printf("string, Line: %d\n" ,yylineno);
    }
#line 2237 "parser.c"
    break;

  case 79:
#line 429 "parser.y"
         {
        printf("NIL, Line: %d\n" ,yylineno);
    }
#line 2245 "parser.c"
    break;

  case 80:
#line 432 "parser.y"
          {
        printf("true, Line: %d\n" ,yylineno);
    }
#line 2253 "parser.c"
    break;

  case 81:
#line 435 "parser.y"
           {
        printf("false, Line: %d\n" ,yylineno);
    }
#line 2261 "parser.c"
    break;

  case 82:
#line 440 "parser.y"
                {

    }
#line 2269 "parser.c"
    break;

  case 84:
#line 447 "parser.y"
                      {

    }
#line 2277 "parser.c"
    break;

  case 86:
#line 456 "parser.y"
         {i = yylineno; stmt_open++;}
#line 2283 "parser.c"
    break;

  case 87:
#line 456 "parser.y"
                                                                              {

    }
#line 2291 "parser.c"
    break;

  case 88:
#line 461 "parser.y"
                    {stmt_open--;}
#line 2297 "parser.c"
    break;

  case 89:
#line 461 "parser.y"
                                                {
        printf("pure if, Line: %d\n" ,i);
    }
#line 2305 "parser.c"
    break;

  case 90:
#line 464 "parser.y"
                         {stmt_open++;}
#line 2311 "parser.c"
    break;

  case 91:
#line 464 "parser.y"
                                             {stmt_open--;}
#line 2317 "parser.c"
    break;

  case 92:
#line 464 "parser.y"
                                                            {
        printf("if else, Line: %d\n" ,i);
    }
#line 2325 "parser.c"
    break;

  case 93:
#line 469 "parser.y"
            {i = yylineno; stmt_open++;}
#line 2331 "parser.c"
    break;

  case 94:
#line 469 "parser.y"
                                                                                      {stmt_open--;}
#line 2337 "parser.c"
    break;

  case 95:
#line 469 "parser.y"
                                                                                                     {
        printf("while, Line: %d\n" ,i);
    }
#line 2345 "parser.c"
    break;

  case 96:
#line 474 "parser.y"
          {i = yylineno; stmt_open++;}
#line 2351 "parser.c"
    break;

  case 97:
#line 474 "parser.y"
                                                                                                                    {stmt_open--;}
#line 2357 "parser.c"
    break;

  case 98:
#line 474 "parser.y"
                                                                                                                                   {
        printf("for, Line: %d\n" ,i);
    }
#line 2365 "parser.c"
    break;

  case 99:
#line 479 "parser.y"
                       {
        if(function_open == 0){
            printf("Error: return outside of function, Line: %d\n" ,yylineno);
        } 
        else {
            printf("return, Line: %d\n" ,yylineno);
        }
        
    }
#line 2379 "parser.c"
    break;

  case 100:
#line 488 "parser.y"
                            {
        printf("return expr, Line: %d\n" ,yylineno);
    }
#line 2387 "parser.c"
    break;


#line 2391 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 491 "parser.y"


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
