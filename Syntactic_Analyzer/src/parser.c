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
    



#line 121 "parser.c"

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
#line 57 "parser.y"

    int integer;
    double real;
    char* string;
    unsigned int expression;

#line 231 "parser.c"

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
#define YYLAST   616

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

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
       0,   104,   104,   108,   111,   115,   118,   119,   120,   123,
     126,   129,   132,   133,   134,   138,   141,   145,   150,   155,
     160,   165,   170,   175,   180,   185,   190,   195,   200,   204,
     212,   216,   220,   224,   228,   232,   236,   240,   244,   248,
     251,   254,   257,   260,   265,   268,   271,   274,   278,   281,
     284,   287,   292,   295,   298,   304,   307,   312,   317,   322,
     325,   329,   332,   336,   339,   344,   350,   353,   357,   362,
     362,   362,   367,   367,   370,   370,   375,   378,   381,   384,
     387,   390,   395,   398,   402,   405,   411,   411,   414,   414,
     419,   419,   424,   424,   429,   438
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
  "$@4", "const", "idlist", "nextid", "ifstmt", "$@5", "$@6", "whilestmt",
  "$@7", "forstmt", "$@8", "returnstmt", YY_NULLPTR
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

#define YYPACT_NINF (-151)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-75)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -151,     2,   167,  -151,  -151,  -151,  -151,   -30,   204,   -22,
     -16,   265,   -37,  -151,  -151,  -151,   265,    -4,    -4,  -151,
     241,     4,  -151,   -17,  -151,  -151,  -151,  -151,  -151,   318,
    -151,  -151,  -151,   452,  -151,    10,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,   -11,    -5,     3,    11,    12,    22,
    -151,   339,  -151,  -151,  -151,  -151,  -151,    53,    60,    10,
      60,  -151,   265,    89,    25,    41,    42,   381,    43,  -151,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,  -151,   265,  -151,  -151,   265,   265,    37,
      38,  -151,  -151,  -151,   265,   265,    39,   265,   265,   265,
     265,    51,    47,  -151,    56,   118,   295,   265,  -151,  -151,
    -151,    63,  -151,  -151,    61,   572,   559,    34,    34,  -151,
    -151,  -151,   585,   585,   206,   206,   206,   206,   544,   500,
      67,  -151,    64,   479,    69,  -151,   402,   423,   444,    76,
      47,    82,    78,    61,  -151,   265,    89,    42,   265,  -151,
    -151,   265,  -151,  -151,   167,   167,   167,   265,    93,    90,
    -151,   106,  -151,   522,  -151,  -151,   103,   104,  -151,   142,
    -151,   360,   106,    82,  -151,  -151,  -151,  -151,   167,   265,
    -151,  -151,  -151,   109,   167,  -151
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    86,    90,    92,    72,     0,     0,
       0,     0,     0,    80,    81,    79,     0,     0,     0,    69,
      60,     0,    14,     0,    78,    44,    76,    77,     3,     0,
      29,    15,    37,    39,    47,    40,    41,    12,    13,    43,
       6,     7,     8,     9,     0,     0,     0,     0,     0,     0,
      94,     0,    10,    11,    32,    45,    31,     0,    33,     0,
      35,     4,     0,    62,     0,     0,    67,     0,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     0,    34,    36,     0,    60,     0,
       0,    53,    55,    56,     0,    60,     0,     0,     0,     0,
      60,     0,    83,    95,     0,     0,     0,     0,    59,    63,
      64,     0,    65,    30,    42,    27,    28,    16,    17,    18,
      19,    20,    25,    26,    21,    22,    23,    24,    38,     0,
       0,    48,     0,     0,     0,    50,     0,     0,     0,     0,
      83,    85,     0,     0,    70,     0,    62,    67,    60,    49,
      57,    60,    51,    52,     0,     0,     0,     0,     0,     0,
      82,     0,    71,     0,    61,    66,     0,     0,    87,     0,
      91,     0,     0,    85,    75,    68,    54,    58,     0,    60,
      73,    84,    89,     0,     0,    93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,    87,  -150,    -8,  -151,  -151,  -151,    18,  -151,
      26,  -151,  -151,  -151,   -73,     8,  -151,  -151,     9,    48,
    -147,  -151,  -151,   -20,  -151,  -151,  -151,    21,   -23,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    29,    30,    31,    32,    33,    34,
      35,    91,    92,    93,    64,   108,    36,    65,   112,    66,
      37,    61,   162,    38,    48,    49,    39,   142,   160,    40,
      44,    45,    41,    46,    42,    47,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    68,     3,    54,   168,   169,   170,   -74,    56,    55,
      12,     7,    63,    67,   174,   130,    11,    52,    12,    13,
      14,    15,   134,    53,    16,   180,    97,   139,   182,    69,
      17,    18,    98,    57,   185,    58,    60,   104,    23,    20,
      99,    21,    25,    59,    59,    94,    23,    95,   100,    24,
      25,    26,    27,    96,   106,    74,    75,    76,   101,   102,
       7,   109,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   166,   128,   110,   167,   129,
      63,   114,   111,   131,   132,   135,   133,    63,   140,   136,
     137,   138,    63,   141,   143,    87,    62,    88,   148,   146,
      70,   151,    71,    89,    90,   150,   183,   153,    72,    73,
      74,    75,    76,    77,    78,   157,   161,    79,    80,    81,
      82,     4,   159,     5,     6,     7,     8,     9,    10,   107,
      11,   172,    12,    13,    14,    15,   173,   163,    16,    19,
      63,   176,   177,    63,    17,    18,   178,   184,   105,   171,
     181,    19,   144,    20,   164,    21,   165,    22,     0,   147,
      23,   158,     0,    24,    25,    26,    27,     0,     0,     0,
       4,    63,     5,     6,     7,     8,     9,    10,     0,    11,
       0,    12,    13,    14,    15,     0,     0,    16,     0,     0,
       0,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,     0,    20,     0,    21,     0,    22,     0,     0,    23,
       0,     0,    24,    25,    26,    27,    11,     0,    12,    13,
      14,    15,     0,     0,    16,    72,    73,    74,    75,    76,
      17,    18,     0,     0,   -75,   -75,   -75,   -75,     0,    20,
       0,    21,     0,    50,     0,     0,    23,     0,     0,    24,
      25,    26,    27,    11,     0,    12,    13,    14,    15,     0,
       0,    16,     0,     0,     0,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    62,     0,    20,    11,    21,    12,
      13,    14,    15,    23,     0,    16,    24,    25,    26,    27,
       0,    17,    18,     0,     0,     0,     0,     0,     0,     0,
      20,     0,    21,     0,     0,     0,    70,    23,    71,     0,
      24,    25,    26,    27,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,    81,    82,     0,     0,    70,
       0,    71,     0,     0,     0,     0,   145,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
      70,     0,    71,     0,     0,     0,     0,    83,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    70,     0,    71,     0,     0,     0,     0,   103,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    70,     0,    71,     0,     0,     0,     0,   179,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,    70,     0,    71,     0,     0,     0,   113,
       0,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,    70,     0,    71,     0,     0,     0,
     154,     0,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,    82,    70,     0,    71,     0,     0,
       0,   155,     0,    72,    73,    74,    75,    76,    77,    78,
      84,     0,    79,    80,    81,    82,     0,     0,    85,    86,
       0,     0,   156,     0,     0,     0,     0,    87,     0,    88,
      70,     0,    71,     0,     0,    89,    90,     0,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    70,     0,    71,     0,   152,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,     0,    70,   149,    71,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,     0,    70,   175,    71,     0,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    78,
      70,     0,    79,    80,    81,    82,     0,     0,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,    72,    73,    74,    75,    76,   -75,
     -75,     0,     0,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       8,    21,     0,    11,   154,   155,   156,    37,    16,    46,
      14,     7,    20,    21,   161,    88,    12,    39,    14,    15,
      16,    17,    95,    39,    20,   172,    37,   100,   178,    46,
      26,    27,    37,    37,   184,    17,    18,    57,    42,    35,
      37,    37,    46,    17,    18,    35,    42,    37,    37,    45,
      46,    47,    48,    43,    62,    21,    22,    23,    46,    37,
       7,    36,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,   148,    84,    36,   151,    87,
      88,    38,    40,    46,    46,    46,    94,    95,    37,    97,
      98,    99,   100,    46,    38,    35,    33,    37,    37,   107,
      11,    37,    13,    43,    44,    38,   179,    38,    19,    20,
      21,    22,    23,    24,    25,    39,    38,    28,    29,    30,
      31,     3,    40,     5,     6,     7,     8,     9,    10,    40,
      12,    38,    14,    15,    16,    17,    46,   145,    20,    33,
     148,    38,    38,   151,    26,    27,     4,    38,    61,   157,
     173,    33,    34,    35,   146,    37,   147,    39,    -1,   111,
      42,   140,    -1,    45,    46,    47,    48,    -1,    -1,    -1,
       3,   179,     5,     6,     7,     8,     9,    10,    -1,    12,
      -1,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    35,    -1,    37,    -1,    39,    -1,    -1,    42,
      -1,    -1,    45,    46,    47,    48,    12,    -1,    14,    15,
      16,    17,    -1,    -1,    20,    19,    20,    21,    22,    23,
      26,    27,    -1,    -1,    28,    29,    30,    31,    -1,    35,
      -1,    37,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,    48,    12,    -1,    14,    15,    16,    17,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    35,    12,    37,    14,
      15,    16,    17,    42,    -1,    20,    45,    46,    47,    48,
      -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    37,    -1,    -1,    -1,    11,    42,    13,    -1,
      45,    46,    47,    48,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    11,
      -1,    13,    -1,    -1,    -1,    -1,    41,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    -1,    13,    -1,    -1,    -1,    -1,    39,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    -1,    13,    -1,    -1,    -1,    -1,    39,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    11,    -1,    13,    -1,    -1,    -1,    -1,    39,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    11,    -1,    13,    -1,    -1,    -1,    38,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    11,    -1,    13,    -1,    -1,    -1,
      38,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    11,    -1,    13,    -1,    -1,
      -1,    38,    -1,    19,    20,    21,    22,    23,    24,    25,
      18,    -1,    28,    29,    30,    31,    -1,    -1,    26,    27,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    35,    -1,    37,
      11,    -1,    13,    -1,    -1,    43,    44,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    -1,    13,    -1,    36,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    11,    34,    13,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    11,    34,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      11,    -1,    28,    29,    30,    31,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     3,     5,     6,     7,     8,     9,
      10,    12,    14,    15,    16,    17,    20,    26,    27,    33,
      35,    37,    39,    42,    45,    46,    47,    48,    54,    55,
      56,    57,    58,    59,    60,    61,    67,    71,    74,    77,
      80,    83,    85,    87,    81,    82,    84,    86,    75,    76,
      39,    55,    39,    39,    55,    46,    55,    37,    59,    61,
      59,    72,    33,    55,    65,    68,    70,    55,    74,    46,
      11,    13,    19,    20,    21,    22,    23,    24,    25,    28,
      29,    30,    31,    39,    18,    26,    27,    35,    37,    43,
      44,    62,    63,    64,    35,    37,    43,    37,    37,    37,
      37,    46,    37,    39,    74,    53,    55,    40,    66,    36,
      36,    40,    69,    38,    38,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      65,    46,    46,    55,    65,    46,    55,    55,    55,    65,
      37,    46,    78,    38,    34,    41,    55,    70,    37,    34,
      38,    37,    36,    38,    38,    38,    38,    39,    78,    40,
      79,    38,    73,    55,    66,    69,    65,    65,    54,    54,
      54,    55,    38,    46,    71,    34,    38,    38,     4,    39,
      71,    79,    54,    65,    38,    54
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
      77,    77,    78,    78,    79,    79,    81,    80,    82,    80,
      84,    83,    86,    85,    87,    87
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
       1,     1,     2,     0,     3,     0,     0,     6,     0,     8,
       0,     6,     0,    10,     2,     3
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
#line 104 "parser.y"
                 {
    }
#line 1626 "parser.c"
    break;

  case 3:
#line 108 "parser.y"
                     {
        
    }
#line 1634 "parser.c"
    break;

  case 5:
#line 115 "parser.y"
                     {

    }
#line 1642 "parser.c"
    break;

  case 8:
#line 120 "parser.y"
              {

    }
#line 1650 "parser.c"
    break;

  case 9:
#line 123 "parser.y"
                 {

    }
#line 1658 "parser.c"
    break;

  case 10:
#line 126 "parser.y"
                      {

    }
#line 1666 "parser.c"
    break;

  case 11:
#line 129 "parser.y"
                         {

    }
#line 1674 "parser.c"
    break;

  case 15:
#line 138 "parser.y"
                 {
        
    }
#line 1682 "parser.c"
    break;

  case 16:
#line 141 "parser.y"
                         {           
            (yyval.expression) = (yyvsp[-2].expression) + (yyvsp[0].expression);
            printf("expr + expr, Line: %d\n" ,Current_Line());
    }
#line 1691 "parser.c"
    break;

  case 17:
#line 145 "parser.y"
                            {
            (yyval.expression) = (yyvsp[-2].expression) - (yyvsp[0].expression);
            printf("expr - expr, Line: %d\n" ,Current_Line());
        
    }
#line 1701 "parser.c"
    break;

  case 18:
#line 150 "parser.y"
                               {
            (yyval.expression) = (yyvsp[-2].expression) * (yyvsp[0].expression);
            printf("expr * expr, Line: %d\n" ,Current_Line());
        
    }
#line 1711 "parser.c"
    break;

  case 19:
#line 155 "parser.y"
                         {
            (yyval.expression) = (yyvsp[-2].expression) / (yyvsp[0].expression);
            printf("expr / expr, Line: %d\n" ,Current_Line());
        
    }
#line 1721 "parser.c"
    break;

  case 20:
#line 160 "parser.y"
                       {
            (yyval.expression) = (yyvsp[-2].expression) % (yyvsp[0].expression);
            printf("expr %% expr, Line: %d\n" ,Current_Line());
        
    }
#line 1731 "parser.c"
    break;

  case 21:
#line 165 "parser.y"
                             {
            (yyval.expression) = (yyvsp[-2].expression) > (yyvsp[0].expression);
            printf("expr > expr, Line: %d\n" ,Current_Line());
        
    }
#line 1741 "parser.c"
    break;

  case 22:
#line 170 "parser.y"
                          {
            (yyval.expression) = (yyvsp[-2].expression) < (yyvsp[0].expression);
            printf("expr < expr, Line: %d\n" ,Current_Line());
        
    }
#line 1751 "parser.c"
    break;

  case 23:
#line 175 "parser.y"
                                 {
            (yyval.expression) = (yyvsp[-2].expression) >= (yyvsp[0].expression);
            printf("expr >= expr, Line: %d\n" ,Current_Line());
        
    }
#line 1761 "parser.c"
    break;

  case 24:
#line 180 "parser.y"
                              {
            (yyval.expression) = (yyvsp[-2].expression) <= (yyvsp[0].expression);
            printf("expr <= expr, Line: %d\n" ,Current_Line());
        
    }
#line 1771 "parser.c"
    break;

  case 25:
#line 185 "parser.y"
                         {
            (yyval.expression) = (yyvsp[-2].expression) == (yyvsp[0].expression);
            printf("expr == expr, Line: %d\n" ,Current_Line());
        
    }
#line 1781 "parser.c"
    break;

  case 26:
#line 190 "parser.y"
                           {
            (yyval.expression) = (yyvsp[-2].expression) != (yyvsp[0].expression);
            printf("expr != expr, Line: %d\n" ,Current_Line());
        
    }
#line 1791 "parser.c"
    break;

  case 27:
#line 195 "parser.y"
                    {
            (yyval.expression) = (yyvsp[-2].expression) and (yyvsp[0].expression);
            printf("expr AND expr, Line: %d\n" ,Current_Line());
        
    }
#line 1801 "parser.c"
    break;

  case 28:
#line 200 "parser.y"
                   {
            (yyval.expression) = (yyvsp[-2].expression) or (yyvsp[0].expression);
            printf("expr OR expr, Line: %d\n" ,Current_Line());
    }
#line 1810 "parser.c"
    break;

  case 29:
#line 204 "parser.y"
           {
            
            (yyval.expression) = (yyvsp[0].expression);
            SymTable.symbolTable.insert(1,"int",(yyvsp[0].expression));
            std::cout<<SymTable.symbolTable.begin();
    }
#line 1821 "parser.c"
    break;

  case 30:
#line 212 "parser.y"
                                              {
        (yyval.expression) = ((yyvsp[-1].expression));
        printf("left expr right, Line: %d\n" ,Current_Line());
    }
#line 1830 "parser.c"
    break;

  case 31:
#line 216 "parser.y"
                                         {
        (yyval.expression) = - (yyvsp[0].expression);
        printf("unary minus, Line: %d\n" ,Current_Line());
    }
#line 1839 "parser.c"
    break;

  case 32:
#line 220 "parser.y"
               {
        (yyval.expression) = not (yyvsp[0].expression);
        printf("NOT expr, Line: %d\n" ,Current_Line());
    }
#line 1848 "parser.c"
    break;

  case 33:
#line 224 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) + 1;
        printf("increment lvalue, Line: %d\n" ,Current_Line());
    }
#line 1857 "parser.c"
    break;

  case 34:
#line 228 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) + 1;
        printf("lvalue increment, Line: %d\n" ,Current_Line());
    }
#line 1866 "parser.c"
    break;

  case 35:
#line 232 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) - 1;
        printf("decrement lvalue, Line: %d\n" ,Current_Line());
    }
#line 1875 "parser.c"
    break;

  case 36:
#line 236 "parser.y"
                       {
        (yyval.expression) = (yyval.expression) - 1;
        printf("lvalue decrement, Line: %d\n" ,Current_Line());
    }
#line 1884 "parser.c"
    break;

  case 37:
#line 240 "parser.y"
              {
    }
#line 1891 "parser.c"
    break;

  case 38:
#line 244 "parser.y"
                             {
    }
#line 1898 "parser.c"
    break;

  case 39:
#line 248 "parser.y"
             {

    }
#line 1906 "parser.c"
    break;

  case 40:
#line 251 "parser.y"
           {

    }
#line 1914 "parser.c"
    break;

  case 41:
#line 254 "parser.y"
                {

    }
#line 1922 "parser.c"
    break;

  case 42:
#line 257 "parser.y"
                                                 {
        (yyval.expression) = FUNC;
    }
#line 1930 "parser.c"
    break;

  case 43:
#line 260 "parser.y"
            {

    }
#line 1938 "parser.c"
    break;

  case 44:
#line 265 "parser.y"
         {
        printf("id, Line: %d\n" ,Current_Line());
    }
#line 1946 "parser.c"
    break;

  case 45:
#line 268 "parser.y"
               {
        printf("local id, Line: %d\n" ,Current_Line());
    }
#line 1954 "parser.c"
    break;

  case 46:
#line 271 "parser.y"
                      {
        
    }
#line 1962 "parser.c"
    break;

  case 47:
#line 274 "parser.y"
             {
    }
#line 1969 "parser.c"
    break;

  case 48:
#line 278 "parser.y"
                    {
        
    }
#line 1977 "parser.c"
    break;

  case 49:
#line 281 "parser.y"
                                                          {

    }
#line 1985 "parser.c"
    break;

  case 50:
#line 284 "parser.y"
                  {

    }
#line 1993 "parser.c"
    break;

  case 51:
#line 287 "parser.y"
                                                         {

    }
#line 2001 "parser.c"
    break;

  case 52:
#line 292 "parser.y"
                                                    {
        
    }
#line 2009 "parser.c"
    break;

  case 53:
#line 295 "parser.y"
                       {

    }
#line 2017 "parser.c"
    break;

  case 54:
#line 299 "parser.y"
                                               {

    }
#line 2025 "parser.c"
    break;

  case 55:
#line 304 "parser.y"
               {

    }
#line 2033 "parser.c"
    break;

  case 56:
#line 307 "parser.y"
                 {

    }
#line 2041 "parser.c"
    break;

  case 57:
#line 312 "parser.y"
                                               {
        printf("normcall, Line: %d\n" ,Current_Line());
    }
#line 2049 "parser.c"
    break;

  case 58:
#line 317 "parser.y"
                                                             {
        printf("method call, Line: %d\n" ,Current_Line());
    }
#line 2057 "parser.c"
    break;

  case 59:
#line 322 "parser.y"
                    {

    }
#line 2065 "parser.c"
    break;

  case 61:
#line 329 "parser.y"
                          {

    }
#line 2073 "parser.c"
    break;

  case 63:
#line 336 "parser.y"
                                                     {
        printf("object elist, Line: %d\n" ,Current_Line());
    }
#line 2081 "parser.c"
    break;

  case 64:
#line 339 "parser.y"
                                                       {
        printf("object indexed, Line: %d\n" ,Current_Line());
    }
#line 2089 "parser.c"
    break;

  case 65:
#line 344 "parser.y"
                              {

    }
#line 2097 "parser.c"
    break;

  case 66:
#line 350 "parser.y"
                                    {

    }
#line 2105 "parser.c"
    break;

  case 68:
#line 357 "parser.y"
                                                            {
        
    }
#line 2113 "parser.c"
    break;

  case 69:
#line 362 "parser.y"
                         {function_open++;}
#line 2119 "parser.c"
    break;

  case 70:
#line 362 "parser.y"
                                                                           {function_open--;}
#line 2125 "parser.c"
    break;

  case 71:
#line 362 "parser.y"
                                                                                              {
        
    }
#line 2133 "parser.c"
    break;

  case 72:
#line 367 "parser.y"
               {i = Current_Line();}
#line 2139 "parser.c"
    break;

  case 73:
#line 367 "parser.y"
                                                                                        {
        printf("function id, Line: %d\n" ,i);
    }
#line 2147 "parser.c"
    break;

  case 74:
#line 370 "parser.y"
               {i = Current_Line();}
#line 2153 "parser.c"
    break;

  case 75:
#line 370 "parser.y"
                                                                                     {
        printf("function, Line: %d\n" ,i);
    }
#line 2161 "parser.c"
    break;

  case 76:
#line 375 "parser.y"
              {
        printf("integer, Line: %d\n" ,Current_Line());
    }
#line 2169 "parser.c"
    break;

  case 77:
#line 378 "parser.y"
          {
        printf("real, Line: %d\n" ,Current_Line());
    }
#line 2177 "parser.c"
    break;

  case 78:
#line 381 "parser.y"
            {
        printf("string, Line: %d\n" ,Current_Line());
    }
#line 2185 "parser.c"
    break;

  case 79:
#line 384 "parser.y"
         {
        printf("NIL, Line: %d\n" ,Current_Line());
    }
#line 2193 "parser.c"
    break;

  case 80:
#line 387 "parser.y"
          {
        printf("true, Line: %d\n" ,Current_Line());
    }
#line 2201 "parser.c"
    break;

  case 81:
#line 390 "parser.y"
           {
        printf("false, Line: %d\n" ,Current_Line());
    }
#line 2209 "parser.c"
    break;

  case 82:
#line 395 "parser.y"
                {

    }
#line 2217 "parser.c"
    break;

  case 84:
#line 402 "parser.y"
                      {

    }
#line 2225 "parser.c"
    break;

  case 86:
#line 411 "parser.y"
         {i = Current_Line();}
#line 2231 "parser.c"
    break;

  case 87:
#line 411 "parser.y"
                                                                                         {
        printf("pure if, Line: %d\n" ,i);
    }
#line 2239 "parser.c"
    break;

  case 88:
#line 414 "parser.y"
         {i = Current_Line();}
#line 2245 "parser.c"
    break;

  case 89:
#line 414 "parser.y"
                                                                                      {
        printf("if else, Line: %d\n" ,i);
    }
#line 2253 "parser.c"
    break;

  case 90:
#line 419 "parser.y"
            {i = Current_Line();}
#line 2259 "parser.c"
    break;

  case 91:
#line 419 "parser.y"
                                                                               {
        printf("while, Line: %d\n" ,i);
    }
#line 2267 "parser.c"
    break;

  case 92:
#line 424 "parser.y"
          {i = Current_Line();}
#line 2273 "parser.c"
    break;

  case 93:
#line 424 "parser.y"
                                                                                                             {
        printf("for, Line: %d\n" ,i);
    }
#line 2281 "parser.c"
    break;

  case 94:
#line 429 "parser.y"
                       {
        if(function_open == 0){
            printf("Error: return outside of function, Line: %d\n" ,Current_Line());
        } 
        else {
            printf("return, Line: %d\n" ,Current_Line());
        }
        
    }
#line 2295 "parser.c"
    break;

  case 95:
#line 438 "parser.y"
                            {
        printf("return expr, Line: %d\n" ,Current_Line());
    }
#line 2303 "parser.c"
    break;


#line 2307 "parser.c"

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
#line 441 "parser.y"


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
