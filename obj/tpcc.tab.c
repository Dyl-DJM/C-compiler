/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/tpcc.y"

/* tpcas.y */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "src/tree.h"
#include "src/make_anonymous.h"


void yyerror(char * s);
int yylex();
int yyparse();
extern int lineno;
extern FILE *yyin;
extern Tab_symb tab_symb1;


char * path;

/* noeud temporaire qui contient l'adresse des noeuds qui attendent leurs types qui sera récupéré plus tard*/
Node * tmp_node;

int arbre;
int symtab;

extern int has_semantical_err;





#line 107 "tpcc.tab.c"

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

#include "tpcc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_ORDER = 12,                     /* ORDER  */
  YYSYMBOL_ADDSUB = 13,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 14,                   /* DIVSTAR  */
  YYSYMBOL_NUM = 15,                       /* NUM  */
  YYSYMBOL_CHARACTER = 16,                 /* CHARACTER  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_SWITCH = 18,                    /* SWITCH  */
  YYSYMBOL_CASE = 19,                      /* CASE  */
  YYSYMBOL_DEFAULT = 20,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 21,                     /* BREAK  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* ','  */
  YYSYMBOL_24_ = 24,                       /* '('  */
  YYSYMBOL_25_ = 25,                       /* ')'  */
  YYSYMBOL_26_ = 26,                       /* '{'  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* ':'  */
  YYSYMBOL_30_ = 30,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Prog = 32,                      /* Prog  */
  YYSYMBOL_DeclVars = 33,                  /* DeclVars  */
  YYSYMBOL_Declarateurs = 34,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 35,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 36,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 37,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 38,                /* Parametres  */
  YYSYMBOL_ListTypVar = 39,                /* ListTypVar  */
  YYSYMBOL_Corps = 40,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 41,                /* SuiteInstr  */
  YYSYMBOL_Instr = 42,                     /* Instr  */
  YYSYMBOL_InstrSwitch = 43,               /* InstrSwitch  */
  YYSYMBOL_CorpsSwitch = 44,               /* CorpsSwitch  */
  YYSYMBOL_Exp = 45,                       /* Exp  */
  YYSYMBOL_TB = 46,                        /* TB  */
  YYSYMBOL_FB = 47,                        /* FB  */
  YYSYMBOL_M = 48,                         /* M  */
  YYSYMBOL_E = 49,                         /* E  */
  YYSYMBOL_T = 50,                         /* T  */
  YYSYMBOL_F = 51,                         /* F  */
  YYSYMBOL_LValue = 52,                    /* LValue  */
  YYSYMBOL_Arguments = 53,                 /* Arguments  */
  YYSYMBOL_ListExp = 54,                   /* ListExp  */
  YYSYMBOL_Val_constant = 55               /* Val_constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,     2,     2,     2,
      24,    25,     2,     2,    23,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,    22,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,   177,   215,   220,   233,   253,   258,   264,
     270,   298,   314,   318,   324,   357,   386,   393,   398,   403,
     408,   413,   420,   425,   431,   438,   452,   456,   459,   462,
     468,   475,   482,   488,   494,   500,   505,   511,   518,   523,
     528,   533,   538,   552,   557,   570,   575,   589,   594,   606,
     611,   616,   620,   623,   633,   643,   646,   668,   681,   685,
     690,   694,   730,   735,   745
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "IDENT",
  "VOID", "RETURN", "WHILE", "IF", "OR", "AND", "EQ", "ORDER", "ADDSUB",
  "DIVSTAR", "NUM", "CHARACTER", "ELSE", "SWITCH", "CASE", "DEFAULT",
  "BREAK", "';'", "','", "'('", "')'", "'{'", "'}'", "'='", "':'", "'!'",
  "$accept", "Prog", "DeclVars", "Declarateurs", "DeclFoncts", "DeclFonct",
  "EnTeteFonct", "Parametres", "ListTypVar", "Corps", "SuiteInstr",
  "Instr", "InstrSwitch", "CorpsSwitch", "Exp", "TB", "FB", "M", "E", "T",
  "F", "LValue", "Arguments", "ListExp", "Val_constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-105)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -105,    15,    59,  -105,    12,    18,    70,  -105,     9,    25,
     -10,    28,    50,  -105,  -105,  -105,    86,  -105,    51,    86,
      25,    56,    68,  -105,    38,    53,  -105,    65,    80,    39,
    -105,  -105,    90,  -105,  -105,    72,    26,    75,    78,    84,
    -105,  -105,  -105,  -105,    76,    99,    10,    88,    10,  -105,
    -105,  -105,    10,    10,    -4,   104,   107,   108,   106,   110,
    -105,  -105,    10,    10,    10,    79,    10,  -105,   117,   114,
     105,    10,  -105,    -6,  -105,    10,  -105,    10,    10,    10,
      10,    10,    35,    42,    49,  -105,    -2,   111,    10,   116,
    -105,   104,   107,   108,   106,   110,  -105,   157,   157,   119,
    -105,  -105,   117,  -105,  -105,   115,   103,   157,    -5,   118,
      62,   122,  -105,    -5,  -105,  -105,   121,   109,   126,  -105,
    -105,   130,   124,   136,   136,    62,  -105,   136,    62,   136,
     128,  -105,  -105,   132,  -105,  -105,    62,    62,  -105,  -105
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,     8,     0,     6,
       0,     0,     0,     7,     4,     9,     0,     3,     0,     0,
       0,    18,     0,    12,     0,    13,     5,     0,     0,     0,
      15,    10,     0,    11,     6,    57,     0,     0,     0,     0,
      29,    18,    16,    17,     0,     0,    59,    57,     0,    53,
      54,    27,     0,     0,     0,    39,    41,    43,    45,    47,
      49,    55,     0,     0,     0,     0,     0,    14,    61,     0,
      58,    59,    50,     0,    51,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,     0,     0,     0,
      52,    38,    40,    42,    44,    46,    48,     0,     0,     0,
      19,    25,    60,    56,    22,    20,    34,     0,     0,     0,
      34,     0,    21,     0,    63,    64,     0,    37,     0,    23,
      62,    37,     0,    18,    37,    34,    24,    18,    34,    37,
       0,    35,    32,     0,    31,    36,    34,    34,    33,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -105,  -105,   146,  -105,  -105,   161,  -105,   151,  -105,  -105,
     150,   -27,  -104,    45,   -35,    98,   100,   102,    97,   101,
     -44,   -29,   113,  -105,    69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,     6,     7,     8,    24,    25,    15,
      65,   124,   111,   125,    68,    55,    56,    57,    58,    59,
      60,    61,    69,    70,   116
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      44,    54,    43,    75,    72,    75,   118,    75,   113,    74,
     114,   115,    17,    18,    47,     3,     9,    73,    76,    90,
     100,   132,    11,    48,   134,    49,    50,    82,    83,    84,
      47,    86,   138,   139,    52,    14,    44,    96,    43,    48,
      53,    49,    50,    35,    75,    36,    37,    38,    51,    16,
      52,    75,    19,   102,    20,    26,    53,    39,    75,    28,
      97,    40,     4,    31,     5,    41,    42,    98,    44,    44,
     104,   105,    30,    12,    99,     5,    32,    44,    44,   110,
     112,   108,   109,    35,    34,    36,    37,    38,    44,    22,
      33,    23,    44,    45,    44,    44,    46,    39,    44,    62,
      44,    40,    63,    67,    66,    41,    85,    35,    64,    36,
      37,    38,    71,    35,    77,    36,    37,    38,    78,    80,
      79,    39,   108,   109,    81,    40,    75,    39,    88,    41,
     122,    40,   107,   101,    35,   123,    36,    37,    38,    87,
      35,   103,    36,    37,    38,   106,   129,   117,    39,   119,
     121,   122,    40,   126,    39,   136,   127,   122,    40,   137,
      21,    35,    41,    36,    37,    38,   128,    13,   130,   131,
      27,    29,   133,    91,   135,    39,    94,    92,     0,    40,
      93,    95,   120,    41,    89
};

static const yytype_int16 yycheck[] =
{
      29,    36,    29,     9,    48,     9,   110,     9,    13,    53,
      15,    16,    22,    23,     4,     0,     4,    52,    22,    25,
      22,   125,     4,    13,   128,    15,    16,    62,    63,    64,
       4,    66,   136,   137,    24,    26,    65,    81,    65,    13,
      30,    15,    16,     4,     9,     6,     7,     8,    22,    24,
      24,     9,    24,    88,     4,     4,    30,    18,     9,     3,
      25,    22,     3,    25,     5,    26,    27,    25,    97,    98,
      97,    98,     4,     3,    25,     5,    23,   106,   107,   106,
     107,    19,    20,     4,     4,     6,     7,     8,   117,     3,
      25,     5,   121,     3,   123,   124,    24,    18,   127,    24,
     129,    22,    24,     4,    28,    26,    27,     4,    24,     6,
       7,     8,    24,     4,    10,     6,     7,     8,    11,    13,
      12,    18,    19,    20,    14,    22,     9,    18,    23,    26,
      21,    22,    17,    22,     4,    26,     6,     7,     8,    25,
       4,    25,     6,     7,     8,    26,    22,    29,    18,    27,
      29,    21,    22,    27,    18,    27,    26,    21,    22,    27,
      14,     4,    26,     6,     7,     8,   121,     6,   123,   124,
      19,    21,   127,    75,   129,    18,    79,    77,    -1,    22,
      78,    80,   113,    26,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    32,    33,     0,     3,     5,    35,    36,    37,     4,
      34,     4,     3,    36,    26,    40,    24,    22,    23,    24,
       4,    33,     3,     5,    38,    39,     4,    38,     3,    41,
       4,    25,    23,    25,     4,     4,     6,     7,     8,    18,
      22,    26,    27,    42,    52,     3,    24,     4,    13,    15,
      16,    22,    24,    30,    45,    46,    47,    48,    49,    50,
      51,    52,    24,    24,    24,    41,    28,     4,    45,    53,
      54,    24,    51,    45,    51,     9,    22,    10,    11,    12,
      13,    14,    45,    45,    45,    27,    45,    25,    23,    53,
      25,    46,    47,    48,    49,    50,    51,    25,    25,    25,
      22,    22,    45,    25,    42,    42,    26,    17,    19,    20,
      42,    43,    42,    13,    15,    16,    55,    29,    43,    27,
      55,    29,    21,    26,    42,    44,    27,    26,    44,    22,
      44,    44,    43,    44,    43,    44,    27,    27,    43,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      37,    37,    38,    38,    39,    39,    40,    41,    41,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      43,    43,    43,    43,    43,    44,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    52,    53,    53,
      54,    54,    55,    55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     1,     2,     1,     2,
       5,     5,     1,     1,     4,     2,     4,     2,     0,     4,
       5,     7,     5,     7,     8,     5,     3,     2,     3,     1,
       7,     5,     4,     6,     0,     2,     3,     0,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     2,     3,     1,     1,     1,     4,     1,     1,     0,
       3,     1,     2,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* Prog: DeclVars DeclFoncts  */
#line 80 "src/tpcc.y"
                               {

		(yyval.node) = makeNode(PROG, lineno);

		addChild((yyval.node), (yyvsp[-1].node));
		addChild((yyval.node), (yyvsp[0].node));
		
		/* pointeur qui sera utile pour savoir la fonction actuellement traité par checkArbre*/
		Node * curr;
		int len;
		

		/* créé des bugs dans cette version donc à corriger remplir_tab($$, &tab_symb1);*/
		init_tab_symb(&tab_symb1);


 		/*Remplit Table des symboles avec les données de l'arbre*/
 		remplir_tab((yyval.node), &tab_symb1);


		/* si aucun main n'a été trouvé, on renvoie un code d'erreur*/
		int pos;

		/*	
		récupérer la position :  et ensuite récupérer le type de retour en allant regarder dans la tab des symboles
		*/
		pos = foncpos(tab_symb1 , "main");

		if(pos == -1 ||  (retourne(tab_symb1, "main") != MY_INT)){
			yyerror2("main function with int type return isn't defined \n", -1, 1);
		}
		
		

		/* on remplit curr avec la fonction "globale" en point de départ*/

		curr = makeNode(DECLFONCTS, lineno);
		len = strlen(tab_symb1.tab_fonc[GLOBALE][0].nom);
		curr->value.val = (char *) malloc((len+1)*sizeof(char));
		strcpy(curr->value.val, tab_symb1.tab_fonc[GLOBALE][0].nom);
		curr->categorie = tab_symb1.tab_fonc[GLOBALE][0].cat;
		curr->type = tab_symb1.tab_fonc[GLOBALE][0].type;


		/*Si l'option d'affichage de la table est présente*/
		if(symtab ==  1){

			printf("\n------------------------------------ Table des symboles -------------------------------------\n\n");
			show_tab_symb(tab_symb1);
			printf("\n\n");
		}

		/*Si l'option d'affichage de l'arbre est présente*/
		if(arbre == 1){

			printf("\n------------------------------------ Arbre abstrait -------------------------------------\n\n");
			printTree((yyval.node));
		}

		
		/*Verifie les appels de fonction (en vérification)*/
 		checkArbre(curr, (yyval.node), &tab_symb1);

 		/*Verifie les retours de fonction (pas fini)*/
 		checkReturns2(tab_symb1);

 		/*Vérifie les switchs*/
 		checkSwitch((yyval.node));

		/*Traduction NASM*/
		/* la traduction en assembleur n'est pas complète, donc elle peut causer des segfault
		néanmoins la partie analyse syntaxique et sémantique sont censées fonctionner parfaitement :
		sans segfault et en trouvant toutes les erreurs.
		Si toutefois vous voulez tester la partie assembleur veuillez décommenter ce bout de code.
		Des exemples de code qui fonctionnent en assembleur sont présents dans le dossier : ./test/Fichiers_Compilables
		
		*/
		/*
 		if(yyin == NULL){
		
 			ecriture_fichier($$, NULL, tab_symb1);
 		}else{

			ecriture_fichier($$, path, tab_symb1);
 		}*/
 		

		/*Suppression de l'arbre en mémoire*/
		deleteTree((yyval.node));

		/*Libération de la table en mémoire*/
		free_tab_symb(&tab_symb1);

	}
#line 1333 "tpcc.tab.c"
    break;

  case 3: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 177 "src/tpcc.y"
                                          {
		(yyval.node) = makeNode(DECLVARS, lineno);
		addChild((yyval.node), (yyvsp[-3].node));

		if(strcmp((yyvsp[-2].val), "int") == 0){

			addChild((yyval.node), makeNode(Int, lineno));
		}

		if(strcmp((yyvsp[-2].val), "char") == 0){
		
			addChild((yyval.node), makeNode(Char,lineno));
		}

		if(tmp_node != NULL){
			add_type_node(tmp_node, (yyvsp[-2].val));

			/* on s'occupe des fils du noeud qui ont le même type que le père*/
			/* il faudrait ajouter ici la partie ou pour chaque frère de tmp_node, on les parcours et on leur donne le type de $2 et aussi la catégorie VARIABLE*/
			if(tmp_node->firstChild != NULL){
				tmp_node =tmp_node->firstChild;
				while(tmp_node != NULL){
					add_type_node(tmp_node, (yyvsp[-2].val));
					tmp_node->categorie = MY_VARIABLE;
					tmp_node =tmp_node->nextSibling;
				}
			}
		}

		

		/* on vide tmp_node*/
		tmp_node = NULL;
		(yyval.node)->show = 1;

		addChild((yyval.node), (yyvsp[-1].node));

	}
#line 1376 "tpcc.tab.c"
    break;

  case 4: /* DeclVars: %empty  */
#line 215 "src/tpcc.y"
          {
		(yyval.node) = NULL;
	}
#line 1384 "tpcc.tab.c"
    break;

  case 5: /* Declarateurs: Declarateurs ',' IDENT  */
#line 220 "src/tpcc.y"
                                 {

		Node * n;

		n = makeNode(var, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[0].val)) + 1);
		strcpy(n->value.val, (yyvsp[0].val));
		n->show = 2;

		(yyval.node) = (yyvsp[-2].node);
		addChild((yyval.node), n);
	}
#line 1402 "tpcc.tab.c"
    break;

  case 6: /* Declarateurs: IDENT  */
#line 233 "src/tpcc.y"
                 {

		Node * n;

		n = makeNode(var, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[0].val)) + 1);
		strcpy(n->value.val, (yyvsp[0].val));
		n->show = 2;

		/* l'élément trouvé est une variable*/
		n->categorie = MY_VARIABLE;

		(yyval.node) = n;

		/* on remplit le noeud tmp pour pouvoir ajouter par la suite à la variable son type*/
		tmp_node = n;
	}
#line 1425 "tpcc.tab.c"
    break;

  case 7: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 253 "src/tpcc.y"
                                {
		(yyval.node) = makeNode(DECLFONCTS, lineno);
		addChild((yyval.node), (yyvsp[-1].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1435 "tpcc.tab.c"
    break;

  case 8: /* DeclFoncts: DeclFonct  */
#line 258 "src/tpcc.y"
                     {
		(yyval.node) = makeNode(DECLFONCTS, lineno);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1444 "tpcc.tab.c"
    break;

  case 9: /* DeclFonct: EnTeteFonct Corps  */
#line 264 "src/tpcc.y"
                            {
		(yyval.node) = (yyvsp[-1].node);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1453 "tpcc.tab.c"
    break;

  case 10: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 270 "src/tpcc.y"
                                          {

		Node * n;

		n = makeNode(ident, lineno);
		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[-3].val)) + 1);
		strcpy(n->value.val, (yyvsp[-3].val));
		/*n->type = 2;*/

		n->show = 2;

		/* on précise qu'il s'agit d'une fonction*/
		n->categorie = MY_FUNCTION;

		(yyval.node) = n;

		if(strcmp((yyvsp[-4].val), "int") == 0){

			addChild((yyval.node), makeNode(Int, lineno));
		}

		else if(strcmp((yyvsp[-4].val), "char") == 0){
			addChild((yyval.node), makeNode(Char, lineno));
		}

		addChild((yyval.node), (yyvsp[-1].node));

	}
#line 1486 "tpcc.tab.c"
    break;

  case 11: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 298 "src/tpcc.y"
                                         {
		Node * n;

		n = makeNode(ident, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[-3].val)) + 1);
		strcpy(n->value.val, (yyvsp[-3].val));
		n->show = 2;
		n->categorie = MY_FUNCTION;

		(yyval.node) = n;
		addChild((yyval.node), makeNode(voide, lineno));
		addChild((yyval.node), (yyvsp[-1].node));
	}
#line 1505 "tpcc.tab.c"
    break;

  case 12: /* Parametres: VOID  */
#line 314 "src/tpcc.y"
               {
		(yyval.node) = makeNode(PARAMETRES, lineno);
		addChild((yyval.node), makeNode(voide, lineno));
	}
#line 1514 "tpcc.tab.c"
    break;

  case 13: /* Parametres: ListTypVar  */
#line 318 "src/tpcc.y"
                      {
		(yyval.node) = makeNode(PARAMETRES, lineno);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1523 "tpcc.tab.c"
    break;

  case 14: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 324 "src/tpcc.y"
                                     {

		Node * n, * n_two;

		if(strcmp((yyvsp[-1].val), "int") == 0){

			n_two = makeNode(Int, lineno);
		}

		if(strcmp((yyvsp[-1].val), "char") == 0){
		
			n_two = makeNode(Char, lineno);
		}



		n = makeNode(var, lineno);

		/* on ajoute le nom de l'ident à n*/

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[0].val)) + 1);
		strcpy(n->value.val, (yyvsp[0].val));

		/* on précise la catégorie*/
		n->categorie = MY_PARAMETRE;

		n->show = 2;

		(yyval.node) = (yyvsp[-3].node);

		addChild(n, n_two);
		addSibling((yyval.node), n);
	}
#line 1561 "tpcc.tab.c"
    break;

  case 15: /* ListTypVar: TYPE IDENT  */
#line 357 "src/tpcc.y"
                      {

		Node * n, * n_two;

		n = makeNode(var, lineno);

		if(strcmp((yyvsp[-1].val), "int") == 0){

			n_two = makeNode(Int, lineno);
		}

		if(strcmp((yyvsp[-1].val), "char") == 0){
		
			n_two = makeNode(Char, lineno);
		}
		

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[0].val)) + 1);
		strcpy(n->value.val, (yyvsp[0].val));

		n->show = 2;
		n->categorie = MY_PARAMETRE;

		(yyval.node) = n;

		addChild((yyval.node), n_two);
	}
#line 1593 "tpcc.tab.c"
    break;

  case 16: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 386 "src/tpcc.y"
                                      {
		(yyval.node) = makeNode(CORPS, lineno);
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[-1].node));
	}
#line 1603 "tpcc.tab.c"
    break;

  case 17: /* SuiteInstr: SuiteInstr Instr  */
#line 393 "src/tpcc.y"
                            {
		(yyval.node) = makeNode(SUITEINSTR, lineno);
		addChild((yyval.node), (yyvsp[-1].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1613 "tpcc.tab.c"
    break;

  case 18: /* SuiteInstr: %empty  */
#line 398 "src/tpcc.y"
          {
		(yyval.node) = NULL;
	}
#line 1621 "tpcc.tab.c"
    break;

  case 19: /* Instr: LValue '=' Exp ';'  */
#line 403 "src/tpcc.y"
                              {
		(yyval.node) = makeNode(affectation, lineno);
		addChild((yyval.node), (yyvsp[-3].node));
		addChild((yyval.node), (yyvsp[-1].node));
	}
#line 1631 "tpcc.tab.c"
    break;

  case 20: /* Instr: IF '(' Exp ')' Instr  */
#line 408 "src/tpcc.y"
                                {
		(yyval.node) = makeNode(If, lineno);
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1641 "tpcc.tab.c"
    break;

  case 21: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 413 "src/tpcc.y"
                                           {
		(yyval.node) = makeNode(If, lineno);
		addChild((yyval.node), (yyvsp[-4].node));
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), makeNode(Else, lineno));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1653 "tpcc.tab.c"
    break;

  case 22: /* Instr: WHILE '(' Exp ')' Instr  */
#line 420 "src/tpcc.y"
                                   {
		(yyval.node) = makeNode(While, lineno);
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1663 "tpcc.tab.c"
    break;

  case 23: /* Instr: SWITCH '(' Exp ')' '{' InstrSwitch '}'  */
#line 425 "src/tpcc.y"
                                                 {
		(yyval.node) = makeNode(INSTR, lineno);
		addChild((yyval.node), makeNode(Switch, lineno));
		addChild((yyval.node), (yyvsp[-4].node));
		addChild((yyval.node), (yyvsp[-1].node));
	}
#line 1674 "tpcc.tab.c"
    break;

  case 24: /* Instr: SWITCH '(' Exp ')' '{' Instr InstrSwitch '}'  */
#line 431 "src/tpcc.y"
                                                       {
		(yyval.node) = makeNode(INSTR, lineno);
		addChild((yyval.node), makeNode(Switch, lineno));
		addChild((yyval.node), (yyvsp[-5].node));
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[-1].node));
	}
#line 1686 "tpcc.tab.c"
    break;

  case 25: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 438 "src/tpcc.y"
                                        {

		Node * n;

		n = makeNode(fcnt, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[-4].val)) + 1);
		strcpy(n->value.val, (yyvsp[-4].val));
		n->show = 2;

		(yyval.node) = n;

		addChild((yyval.node), (yyvsp[-2].node));
	}
#line 1705 "tpcc.tab.c"
    break;

  case 26: /* Instr: RETURN Exp ';'  */
#line 452 "src/tpcc.y"
                          {
		(yyval.node) = makeNode(Return, lineno);
		addChild((yyval.node), (yyvsp[-1].node));
	}
#line 1714 "tpcc.tab.c"
    break;

  case 27: /* Instr: RETURN ';'  */
#line 456 "src/tpcc.y"
                      {
		(yyval.node) = makeNode(Return, lineno);
	}
#line 1722 "tpcc.tab.c"
    break;

  case 28: /* Instr: '{' SuiteInstr '}'  */
#line 459 "src/tpcc.y"
                              {
		(yyval.node) = (yyvsp[-1].node);
	}
#line 1730 "tpcc.tab.c"
    break;

  case 29: /* Instr: ';'  */
#line 462 "src/tpcc.y"
               {
		(yyval.node) = NULL;
	}
#line 1738 "tpcc.tab.c"
    break;

  case 30: /* InstrSwitch: CASE Val_constant ':' '{' CorpsSwitch '}' InstrSwitch  */
#line 468 "src/tpcc.y"
                                                                {
		(yyval.node) = makeNode(INSTRSWITCH, lineno);
		addChild((yyval.node), makeNode(Case, lineno));
		addChild((yyval.node), (yyvsp[-5].node));
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1750 "tpcc.tab.c"
    break;

  case 31: /* InstrSwitch: CASE Val_constant ':' CorpsSwitch InstrSwitch  */
#line 475 "src/tpcc.y"
                                                        {
		(yyval.node) = makeNode(INSTRSWITCH, lineno);
		addChild((yyval.node), makeNode(Case, lineno));
		addChild((yyval.node), (yyvsp[-3].node));
		addChild((yyval.node), (yyvsp[-1].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1762 "tpcc.tab.c"
    break;

  case 32: /* InstrSwitch: DEFAULT ':' CorpsSwitch InstrSwitch  */
#line 482 "src/tpcc.y"
                                               {
		(yyval.node) = makeNode(INSTRSWITCH, lineno);
		addChild((yyval.node), makeNode(Default, lineno));
		addChild((yyval.node), (yyvsp[-1].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1773 "tpcc.tab.c"
    break;

  case 33: /* InstrSwitch: DEFAULT ':' '{' CorpsSwitch '}' InstrSwitch  */
#line 488 "src/tpcc.y"
                                                       {
		(yyval.node) = makeNode(INSTRSWITCH, lineno);
		addChild((yyval.node), makeNode(Default, lineno));
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1784 "tpcc.tab.c"
    break;

  case 34: /* InstrSwitch: %empty  */
#line 494 "src/tpcc.y"
         {
		(yyval.node) = NULL;
	}
#line 1792 "tpcc.tab.c"
    break;

  case 35: /* CorpsSwitch: Instr CorpsSwitch  */
#line 500 "src/tpcc.y"
                             {
		(yyval.node) = makeNode(CORPSSWITCH, lineno);
		addChild((yyval.node), (yyvsp[-1].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1802 "tpcc.tab.c"
    break;

  case 36: /* CorpsSwitch: BREAK ';' CorpsSwitch  */
#line 505 "src/tpcc.y"
                                {

		(yyval.node) = makeNode(INSTRSWITCH, lineno);
		addChild((yyval.node), makeNode(Break, lineno));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1813 "tpcc.tab.c"
    break;

  case 37: /* CorpsSwitch: %empty  */
#line 511 "src/tpcc.y"
          {
		(yyval.node) = NULL;
	}
#line 1821 "tpcc.tab.c"
    break;

  case 38: /* Exp: Exp OR TB  */
#line 518 "src/tpcc.y"
                     {
		(yyval.node) = makeNode(or, lineno);
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1831 "tpcc.tab.c"
    break;

  case 39: /* Exp: TB  */
#line 523 "src/tpcc.y"
              {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1839 "tpcc.tab.c"
    break;

  case 40: /* TB: TB AND FB  */
#line 528 "src/tpcc.y"
                     {
		(yyval.node) = makeNode(and, lineno);
		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1849 "tpcc.tab.c"
    break;

  case 41: /* TB: FB  */
#line 533 "src/tpcc.y"
              {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1857 "tpcc.tab.c"
    break;

  case 42: /* FB: FB EQ M  */
#line 538 "src/tpcc.y"
                   {

		Node * n;

		n = makeNode(order, lineno);
		n->value.val = (yyvsp[-1].val);

		n->show = 2;

		(yyval.node) = n;

		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1876 "tpcc.tab.c"
    break;

  case 43: /* FB: M  */
#line 552 "src/tpcc.y"
             {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1884 "tpcc.tab.c"
    break;

  case 44: /* M: M ORDER E  */
#line 557 "src/tpcc.y"
                     {

		Node * n;

		n = makeNode(order, lineno);
		n->value.val = (yyvsp[-1].val);
		n->show = 2;

		(yyval.node) = n;

		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1902 "tpcc.tab.c"
    break;

  case 45: /* M: E  */
#line 570 "src/tpcc.y"
             {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1910 "tpcc.tab.c"
    break;

  case 46: /* E: E ADDSUB T  */
#line 575 "src/tpcc.y"
                      {

		Node * n;

		n = makeNode(operateur, lineno);
		n->value.val = (yyvsp[-1].val);

		n->show = 2;

		(yyval.node) = n;

		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1929 "tpcc.tab.c"
    break;

  case 47: /* E: T  */
#line 589 "src/tpcc.y"
             {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1937 "tpcc.tab.c"
    break;

  case 48: /* T: T DIVSTAR F  */
#line 594 "src/tpcc.y"
                       {
		Node * n;

		n = makeNode(operateur,lineno);
		n->value.val = (yyvsp[-1].val);
		n->show = 2;

		(yyval.node) = n;

		addChild((yyval.node), (yyvsp[-2].node));
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1954 "tpcc.tab.c"
    break;

  case 49: /* T: F  */
#line 606 "src/tpcc.y"
             {
		(yyval.node) = (yyvsp[0].node);
	}
#line 1962 "tpcc.tab.c"
    break;

  case 50: /* F: ADDSUB F  */
#line 611 "src/tpcc.y"
                    {

		(yyval.node) = makeNode(operateur,lineno);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1972 "tpcc.tab.c"
    break;

  case 51: /* F: '!' F  */
#line 616 "src/tpcc.y"
                 {
		(yyval.node) = makeNode(non, lineno);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 1981 "tpcc.tab.c"
    break;

  case 52: /* F: '(' Exp ')'  */
#line 620 "src/tpcc.y"
                       {
		(yyval.node) = (yyvsp[-1].node);
	}
#line 1989 "tpcc.tab.c"
    break;

  case 53: /* F: NUM  */
#line 623 "src/tpcc.y"
               {
		Node * n;

		n = makeNode(num, lineno);
		n->value.entier = (yyvsp[0].entier);
		n->show = 0;

		(yyval.node) = n;

	}
#line 2004 "tpcc.tab.c"
    break;

  case 54: /* F: CHARACTER  */
#line 633 "src/tpcc.y"
                     {

		Node * n;

		n = makeNode(character, lineno);
		n->value.caractere = (yyvsp[0].caractere);
		n->show = 1;

		(yyval.node) = n;
	}
#line 2019 "tpcc.tab.c"
    break;

  case 55: /* F: LValue  */
#line 643 "src/tpcc.y"
                  {
		(yyval.node) = (yyvsp[0].node);
	}
#line 2027 "tpcc.tab.c"
    break;

  case 56: /* F: IDENT '(' Arguments ')'  */
#line 646 "src/tpcc.y"
                                    {

		Node * n, * father;

		father = makeNode(EXP, lineno);

		n = makeNode(fcnt, lineno);
		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[-3].val)) + 1);

		strcpy(n->value.val, (yyvsp[-3].val));
		n->show = 2;

		n->categorie = MY_FUNCTION;

		(yyval.node) = father;

		addChild(n, (yyvsp[-1].node));
		addChild((yyval.node), n);

	}
#line 2052 "tpcc.tab.c"
    break;

  case 57: /* LValue: IDENT  */
#line 668 "src/tpcc.y"
                {

		Node * n;

		n = makeNode(var, lineno);

		n->value.val = (char *) malloc(sizeof(char) * strlen((yyvsp[0].val)) + 1);
		strcpy(n->value.val, (yyvsp[0].val));
		n->show = 2;
		(yyval.node) = n;
	}
#line 2068 "tpcc.tab.c"
    break;

  case 58: /* Arguments: ListExp  */
#line 681 "src/tpcc.y"
                  {
		(yyval.node) = makeNode(ARGUMENTS, lineno);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 2077 "tpcc.tab.c"
    break;

  case 59: /* Arguments: %empty  */
#line 685 "src/tpcc.y"
          {
		(yyval.node) = NULL;
	}
#line 2085 "tpcc.tab.c"
    break;

  case 60: /* ListExp: ListExp ',' Exp  */
#line 690 "src/tpcc.y"
                           {
		(yyval.node) = (yyvsp[-2].node);
		addSibling((yyval.node), (yyvsp[0].node));
	}
#line 2094 "tpcc.tab.c"
    break;

  case 61: /* ListExp: Exp  */
#line 694 "src/tpcc.y"
               {
		(yyval.node) = (yyvsp[0].node);
	}
#line 2102 "tpcc.tab.c"
    break;

  case 62: /* Val_constant: ADDSUB Val_constant  */
#line 730 "src/tpcc.y"
                               {

		(yyval.node) = makeNode(operateur,lineno);
		addChild((yyval.node), (yyvsp[0].node));
	}
#line 2112 "tpcc.tab.c"
    break;

  case 63: /* Val_constant: NUM  */
#line 735 "src/tpcc.y"
               {
		Node * n;

		n = makeNode(num, lineno);
		n->value.entier = (yyvsp[0].entier);
		n->show = 0;

		(yyval.node) = n;

	}
#line 2127 "tpcc.tab.c"
    break;

  case 64: /* Val_constant: CHARACTER  */
#line 745 "src/tpcc.y"
                     {

		Node * n;

		n = makeNode(character, lineno);
		n->value.caractere = (yyvsp[0].caractere);
		n->show = 1;

		(yyval.node) = n;
	}
#line 2142 "tpcc.tab.c"
    break;


#line 2146 "tpcc.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 759 "src/tpcc.y"



void afficheDesc(){
	printf("\n------------------------------------ Utilisation -------------------------------------\n\n");

	printf("Il y a deux manières d'utiliser le programme on peut lancer la commande : ./tpcc [FICHIER]    => Lance l'analyseur sur le fichier donné\n");
	printf("On peut sinon y ajouter des options : \n\n   --tree (ou -t) => Affiche l'arbre\n   --help (ou -h) => Permet d'arriver sur cette section\n   --symtabs (ou -s) => Permet l'affichage de la table des symboles\n");
	printf("\nLors du lancement avec options on execute alors : ./tpcc [OPTIONS] [FICHIER]\n");
	printf("\nDes erreurs sont signifiées si : Le fichier est inexistant, plusieurs fichiers sont donnés, des options sont écrites après la mention du fichier, ou des options inexistantes sont données\n");
	printf("\nEnfin, si aucun fichier n'est donné sur la ligne de commande, c'est la sortie standard qui est analysée : ./tpcc [OPTIONS] => Analyse de l'entrée standard\n\n");
}





void yyerror(char * s){
	fprintf(stderr, "\033[1;31mERROR \033[0m: %s | \033[1mLine : %d\033[1m\n", s, lineno);
}





int ligne_commande (int argc, char *argv[], int *hflag, int *tflag, int *sflag){

    int c, val;

    opterr = 0;


    if(argc > 5){
        printf("Erreur sur la ligne de commande\n");
        return -1;
    }


    while ((c = getopt (argc, argv, "hst-")) != -1){

        if(argc < optind){

            continue;
        }

        if(optind == 1){
            val = optind;
        }else{
            val = optind - 1;
        }

        if(strcmp(argv[val], "-s") == 0 || strcmp(argv[val], "--symtabs") == 0){

            *sflag = 1;
            continue;
        }
        else if(strcmp(argv[val], "-t") == 0 || strcmp(argv[val], "--tree") == 0){

            *tflag = 1;
            continue;
        }
        else if(strcmp(argv[val], "-h") == 0 || strcmp(argv[val], "--help") == 0){

            *hflag = 1;
            continue;
        }

        fprintf(stderr, "L'option : %s n'existe pas + afficher manuel\n", argv[val]);
        return -1;
    }


    if (argc - optind > 1){
        fprintf(stderr, "Erreur sur la ligne de commande\n");
        return -1;

    }else if(argc - optind == 1){

        path = argv[optind];

    }else if(argc - optind == 0){

        path = NULL;
    }

    return 0;
}





int main(int argc, char * argv[]){

    int hflag = 0;
    int tflag = 0;
    int sflag = 0;

    arbre = 0;
    symtab = 0;


    if(ligne_commande(argc, argv, &hflag, &tflag, &sflag) == -1){
        return 3;	/*Erreur sur la ligne de commande*/
    }

    if(hflag){
        afficheDesc();
        return 0;
    }

    if(tflag){
        arbre = 1;
    }

    if(sflag){
        symtab = 1;
    }


    if(path == NULL){
        yyin = stdin;

    }else{
        yyin = fopen(path, "r");

        if(yyin == NULL){
        	fprintf(stderr, "Erreur de fichier\n");
        	return 3;
        }
    }


    /*On lance l'analyse*/
    if(yyparse() == 1){
	return 1;	/*Erreur syntaxique dans le fichier*/

    }else{

	if(has_semantical_err == 1){
		return 2;	/*Erreur sémantique dans le fichier*/
	}
    }


    return 0;	/*Aucune erreur dans le fichier*/
}





