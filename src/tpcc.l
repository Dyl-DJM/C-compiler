%{
/* tpcas.lex */

#include "src/tree.h"
#include "tpcc.tab.h"

int lineno = 1;


%}

%x COMM
%option nounput
%option noinput
%option noyywrap
%option yylineno
%%

\/\* BEGIN COMM;
<COMM>. ;
<COMM>\n lineno++;
<COMM>\*\/ BEGIN INITIAL;

\/\/.* ;


\'[^']\'  {yylval.caractere = yytext[1]; return CHARACTER; }

\'\\n\' {yylval.caractere = '\n'; return CHARACTER; }

\'\\r\' {yylval.caractere = '\r'; return CHARACTER; }

\'\\t\' {yylval.caractere = '\t'; return CHARACTER; }


\'\\.?\' {yylval.caractere = '\t'; return CHARACTER; }


[0-9]+  {yylval.entier = atoi(yytext);return NUM;}


default  {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext); return DEFAULT;}
case  return CASE;

while   return WHILE;
if      return IF;
else    return ELSE;

switch return SWITCH;
break return BREAK;

(int|char) {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext); return TYPE;}
void   return VOID;


return   return RETURN;

(==|!=) {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext); return EQ;}

[+-] {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext);return ADDSUB;}

[*/%] {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext); return DIVSTAR;}

(<|<=|>|>=) {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext); return ORDER;}

\|\|  return OR;
&&  return AND;


[ \t]   ;
[\n]    lineno++;

\( return yytext[0];

\) return yytext[0];

\{ return yytext[0];

\} return yytext[0];

\; return yytext[0];

\, return yytext[0];

\= return yytext[0];

\! return yytext[0];

\: return yytext[0];


[a-zA-Z_][a-zA-Z_0-9]*   {yylval.val = (char *) malloc((sizeof(char) * strlen(yytext)) + 1); strcpy(yylval.val, yytext);  return IDENT;}


. return yytext[0];
<<EOF>> return 0;
%%


/*AVOIR UN PROBLÈME DE BOUCLE INFINIE  = AVOIR UN NOEUD FILS AU NOEUD PARENT EGAL AU PERE


Ex :

  $$ = n;

  addChild($$, n);

*/