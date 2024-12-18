%{
#include "syntax.h"
#include "parse_state.h"
#include "parser.h"

#define comment_nest_level yyextra

#define YY_USER_ACTION                                                                \
  yylloc->first_line = yylloc->last_line = yylineno; yylloc->first_column = yycolumn; \
  if (yylineno == yylloc->first_line) yycolumn += yyleng;                             \
  else { for (yycolumn = 1; yytext[yyleng - yycolumn] != '\n'; ++yycolumn) {} }
%}

%option always-interactive
%option yylineno noyywrap noinput nounput
%option extra-type="int"
%option reentrant
%option bison-bridge bison-locations

%x COMMENT

letter [a-zA-Z]
symbol [-!%&$#+/:<=>?@\\~`|*^]
digit [0-9]
hexdigit [0-9a-fA-F]
alphanumeric_id {letter}({letter}|{digit}|[_'])*
symbolic_id {symbol}+
qualified_id ({alphanumeric_id}\.)+({alphanumeric_id}|{symbolic_id}|"="|"*")
tyvar "'"({letter}|{digit}|[_'])*

%%

<INITIAL>[ \t\n]+ { /* skip white space */ }
<INITIAL>"abstype" { return ABSTYPE; }
<INITIAL>"and" { return AND; }
<INITIAL>"andalso" { return ANDALSO; }
<INITIAL>"as" { return AS; }
<INITIAL>"case" { return CASE; }
<INITIAL>"datatype" { return DATATYPE; }
<INITIAL>"do" { return DO; }
<INITIAL>"else" { return ELSE; }
<INITIAL>"end" { return END; }
<INITIAL>"exception" { return EXCEPTION; }
<INITIAL>"fn" { return FN; }
<INITIAL>"fun" { return FUN; }
<INITIAL>"handle" { return HANDLE; }
<INITIAL>"if" { return IF; }
<INITIAL>"in" { return IN; }
<INITIAL>"infix" { return INFIX; }
<INITIAL>"infixr" { return INFIXR; }
<INITIAL>"let" { return LET; }
<INITIAL>"local" { return LOCAL; }
<INITIAL>"nonfix" { return NONFIX; }
<INITIAL>"of" { return OF; }
<INITIAL>"op" { return OP; }
<INITIAL>"open" { return OPEN; }
<INITIAL>"orelse" { return ORELSE; }
<INITIAL>"raise" { return RAISE; }
<INITIAL>"rec" { return REC; }
<INITIAL>"then" { return THEN; }
<INITIAL>"type" { return TYPE; }
<INITIAL>"val" { return VAL; }
<INITIAL>"with" { return WITH; }
<INITIAL>"withtype" { return WITHTYPE; }
<INITIAL>"while" { return WHILE; }
<INITIAL>"(*" {
  comment_nest_level++;
  BEGIN(COMMENT);
}
<INITIAL>"*)" {
  return ERROR;
}
<INITIAL>"(" { return LPAREN; }
<INITIAL>")" { return RPAREN; }
<INITIAL>"[" { return LBRACKET; }
<INITIAL>"]" { return RBRACKET; }
<INITIAL>"{" { return LBRACE; }
<INITIAL>"}" { return RBRACE; }
<INITIAL>"," { return COMMA; }
<INITIAL>":" { return COLON; }
<INITIAL>";" { return SEMICOLON; }
<INITIAL>"..." { return DOTDOTDOT; }
<INITIAL>"_" { return UNDERBAR; }
<INITIAL>"|" { return BAR; }
<INITIAL>"=" { return EQUAL; }
<INITIAL>"*" { return ASTERISK; }
<INITIAL>"=>" { return DARROW; }
<INITIAL>"->" { return ARROW; }
<INITIAL>"#" { return HASH; }

<INITIAL>[1-9][0-9]* { return NUMERIC; }
<INITIAL>~?[0-9]+ { return INTEGER; }
<INITIAL>~?[0-9]+(\.[0-9]+)?([eE]~?[0-9]+)? { return REAL; }
<INITIAL>{tyvar} { return TYVAR; }
<INITIAL>{alphanumeric_id} { return IDENTIFIER; }
<INITIAL>{symbolic_id} { return IDENTIFIER; }
<INITIAL>{qualified_id} { return QUALIFIED_IDENTIFIER; }

<COMMENT>"(*" {
  comment_nest_level++;
}
<COMMENT>"*"+")" {
  comment_nest_level--;
  if (comment_nest_level == 0) {
    BEGIN(INITIAL);
  }
}
<COMMENT>[^\*\(\)]* {/* skip comment */}
<COMMENT>"*"+[^\*\(\)]* {/* skip comment */}
<COMMENT><<EOF>> { return ERROR; }

%%
