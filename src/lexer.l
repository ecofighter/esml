%{
#include "syntax.h"
#include "parser.h"

static int line;
static int column;
static int comment_nest_level;

int yywrap(void);
extern void yyerror(const char *msg);
void yy_user_init();
static void yy_user_action();
#define YY_USER_INIT yy_user_init()
#define YY_USER_ACTION yy_user_action();
%}
%option always-interactive
%x COMMENT

letter [a-zA-Z]
symbol [-!%&$#+/:<=>?@\\~`|*^]
digit [0-9]
hexdigit [0-9a-fA-F]
alphanumeric_id {letter}({letter}|{digit}|[_'])*
symbolic_id {symbol}+
tyvar "'"({letter}|{digit}|[_'])*

%%

<INITIAL>\n {
  line++;
  column = 0;
}
<INITIAL>[ \t]+ { /* skip white space */ }
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
  yyerror("unmatched comment");
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
<INITIAL>"." { return DOT; }
<INITIAL>"_" { return UNDERBAR; }
<INITIAL>"|" { return BAR; }
<INITIAL>"=" { return EQUAL; }
<INITIAL>"=>" { return DARROW; }
<INITIAL>"->" { return ARROW; }
<INITIAL>"#" { return HASH; }

<INITIAL>[1-9][0-9]* {
  yylval.token.text = (char *)malloc(yyleng + 1);
  memcpy(yylval.token.text, yytext, yyleng);
  yylval.token.text[yyleng] = '\0';
  return NUMERIC;
}
<INITIAL>~?[0-9]+ {
  yylval.token.text = (char *)malloc(yyleng + 1);
  memcpy(yylval.token.text, yytext, yyleng);
  yylval.token.text[yyleng] = '\0';
  return INTEGER;
}
<INITIAL>~?[0-9]+(\.[0-9]+)?(E~?[0-9]+)? {
  yylval.token.text = (char *)malloc(yyleng + 1);
  memcpy(yylval.token.text, yytext, yyleng);
  yylval.token.text[yyleng] = '\0';
  return REAL;
}
<INITIAL>{tyvar} {
  yylval.token.text = (char *)malloc(yyleng+1);
  memcpy(yylval.token.text, yytext, yyleng);
  yylval.token.text[yyleng] = '\0';
  return TYVAR;
}
<INITIAL>{alphanumeric_id} {
  yylval.token.text = (char *)malloc(yyleng+1);
  memcpy(yylval.token.text, yytext, yyleng);
  yylval.token.text[yyleng] = '\0';
  return IDENTIFIER;
}
<INITIAL>{symbolic_id} {
  yylval.token.text = (char *)malloc(yyleng+1);
  memcpy(yylval.token.text, yytext, yyleng);
  yylval.token.text[yyleng] = '\0';
  return IDENTIFIER;
}

<COMMENT>\n {
  line++;
  column = 0;
}
<COMMENT>"(*" {
  comment_nest_level++;
}
<COMMENT>"*"+")" {
  comment_nest_level--;
  if (comment_nest_level == 0) {
    BEGIN(INITIAL);
  }
}
<COMMENT>[^\*\(\)\n]* {/* skip comment */}
<COMMENT>"*"+[^\*\(\)\n]* {/* skip comment */}
<COMMENT><<EOF>> { yyerror("EOF in comment"); }

%%
int yywrap() {
    return 1;
}

void yy_user_init() {
  comment_nest_level = 0;
  line = 1;
  column = 0;
  BEGIN(INITIAL);
}

static void yy_user_action() {
  yylval.token.line = line;
  yylval.token.column = column;
  column += yyleng;
}
