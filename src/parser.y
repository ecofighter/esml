%code top {
#include <stdlib.h>
#include <stdio.h>

#include "syntax.h"
#include "parse_state.h"
#include "parser.h"
#include "lexer.h"
}
%code provides {
extern int parse_stdin(ParseState *state);
}

%pure-parser
%locations
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner } { ParseState *state }
%union {
  int int_val;
  char *string;
  VId *vid;
  VIdList *vidlist;
  LongVId *longvid;
  TyVar *tyvar;
  TyVarSeq *tyvarseq;
  TyCon *tycon;
  LongTyCon *longtycon;
  Lab *lab;
  StrId *strid;
  StrIdList *stridlist;
  LongStrId *longstrid;
  LongStrIdList *longstridlist;
  Constant *constant;
  AtPat *atpat;
  PatRow *patrow;
  Pat *pat;
  Ty *ty;
  TySeq *tyseq;
  TyRow *tyrow;
  AtExp *atexp;
  ExpRow *exprow;
  Exp *exp;
  Match *match;
  Mrule *mrule;
  Dec *dec;
  ValBind *valbind;
  TypBind *typbind;
  DatBind *datbind;
  ConBind *conbind;
  ExBind *exbind;
}

%token ABSTYPE AND ANDALSO AS
%token CASE
%token DATATYPE DO
%token ELSE END EXCEPTION
%token FN FUN
%token HANDLE
%token IF IN INFIX INFIXR
%token LET LOCAL
%token NONFIX
%token OF OP OPEN ORELSE
%token RAISE REC
%token THEN TYPE
%token VAL
%token WITH WITHTYPE WHILE
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token COMMA COLON SEMICOLON DOTDOTDOT DOT
%token UNDERBAR BAR EQUAL DARROW ARROW HASH
%token NUMERIC INTEGER WORD REAL
%token TYVAR IDENTIFIER
%token ERROR

%type <string> numeric integer word real identifier
%type <int_val> OP_option
%type <constant> scon
%type <vid> vid_bind vid
%type <vidlist> vid_list1
%type <longvid> longvid_bind longvid
%type <tyvar> tyvar
%type <tyvarseq> tyvar_comma_list1 tyvarseq1 tyvarseq
%type <tycon> tycon
%type <longtycon> longtycon
%type <lab> lab
%type <strid> strid
%type <stridlist> qualifying_strid_list1
%type <longstrid> longstrid
%type <longstridlist> longstridlist1
%type <atpat> atpat_nonid atpat
%type <patrow> patrow
%type <pat> pat
%type <ty> atty conty ty
%type <tyseq> ty_comma_list2 tyseq
%type <tyrow> tyrow
%type <atexp> atexp
%type <exprow> exprow
%type <exp> exp
%type <match> match
%type <mrule> mrule
%type <dec> dec
%type <valbind> valbind
%type <typbind> typbind
%type <datbind> datbind
%type <conbind> conbind
%type <exbind> exbind

%nonassoc WITHTYPE
%left SHARING
%right SEMICOLON
%right VAL FUN TYPE EQTYPE DATATYPE ABSTYPE EXCEPTION STRUCTURE SIGNATURE FUNCTOR
%right LOCAL OPEN INFIX INFIXR NONFIX INCLUDE
%right AND
%left DARROW
%left BAR
%left DO
%left ELSE
%left RAISE
%right HANDLE
%right ORELSE
%right ANDALSO
%right AS
%left COLON
%right ARROW

%start program

%%
program
: dec { parse_state_set_result(state, $1); }
;

numeric
: NUMERIC
    { int len = yyget_leng(scanner);
      char *text = (char *)malloc(len + 1);
      memcpy(text, yyget_text(scanner), len);
      text[len] = '\0';
      $$ = (char *)parse_state_register_node(state, text); }
;

integer
: INTEGER
    { int len = yyget_leng(scanner);
      char *text = (char *)malloc(len + 1);
      memcpy(text, yyget_text(scanner), len);
      text[len] = '\0';
      $$ = (char *)parse_state_register_node(state, text); }
;

word
: WORD
    { int len = yyget_leng(scanner);
      char *text = (char *)malloc(len + 1);
      memcpy(text, yyget_text(scanner), len);
      text[len] = '\0';
      $$ = (char *)parse_state_register_node(state, text); }
;

real
: REAL
    { int len = yyget_leng(scanner);
      char *text = (char *)malloc(len + 1);
      memcpy(text, yyget_text(scanner), len);
      text[len] = '\0';
      $$ = (char *)parse_state_register_node(state, text); }
;

identifier
: IDENTIFIER
    { int len = yyget_leng(scanner);
      char *text = (char *)malloc(len + 1);
      memcpy(text, yyget_text(scanner), len);
      text[len] = '\0';
      $$ = (char *)parse_state_register_node(state, text); }
;

OP_option
: OP { $$ = 1; }
| /* empty */ { $$ = 0; }
;

scon
: numeric
    { $$ = (Constant *)parse_state_register_node(state, new_constant_integer($1)); }
| integer
    { $$ = (Constant *)parse_state_register_node(state, new_constant_integer($1)); }
;

qualifying_strid_list1
: qualifying_strid_list1 strid DOT
    { $$ = (StrIdList *)parse_state_register_node(state, new_stridlist($1, $2)); }
| strid DOT
    { $$ = (StrIdList *)parse_state_register_node(state, new_stridlist(NULL, $1)); }
;

vid
: identifier
    { $$ = (VId *)parse_state_register_node(state, new_vid($1)); }
| EQUAL
    { char *eq = (char *)malloc(2);
      eq[0] = '='; eq[1] = '\0';
      $$ = (VId *)parse_state_register_node(state, new_vid((char *)parse_state_register_node(state, eq))); }
;

vid_list1
: vid vid_list1
    { $$ = (VIdList *)parse_state_register_node(state, new_vidlist($1, $2)); }
| vid
    { $$ = (VIdList *)parse_state_register_node(state, new_vidlist($1, NULL)); }
;

longvid
: vid
    { $$ = (LongVId *)parse_state_register_node(state, new_longvid_nonqualified($1)); }
| qualifying_strid_list1 vid
    { $$ = (LongVId *)parse_state_register_node(state, new_longvid_qualified($1, $2)); }
;

vid_bind
: identifier
    { $$ = (VId *)parse_state_register_node(state, new_vid($1)); }
;

longvid_bind
: vid_bind
    { $$ = (LongVId *)parse_state_register_node(state, new_longvid_nonqualified($1)); }
| qualifying_strid_list1 vid_bind
    { $$ = (LongVId *)parse_state_register_node(state, new_longvid_qualified($1, $2)); }
;

tyvar
: TYVAR
    { int len = yyget_leng(scanner);
      char *text = (char *)malloc(len + 1);
      memcpy(text, yyget_text(scanner), len);
      text[len] = '\0';
      $$ = (TyVar *)parse_state_register_node(state, new_tyvar(parse_state_register_node(state, text))); }
;

tyvar_comma_list1
: tyvar COMMA tyvar_comma_list1
    { $$ = (TyVarSeq *)parse_state_register_node(state, new_tyvarseq($1, $3)); }
| tyvar
    { $$ = (TyVarSeq *)parse_state_register_node(state, new_tyvarseq($1, NULL)); }
;

tyvarseq1
: tyvar
    { $$ = (TyVarSeq *)parse_state_register_node(state, new_tyvarseq($1, NULL)); }
| LPAREN tyvar_comma_list1 RPAREN
    { $$ = $2; }
;

tyvarseq
: tyvarseq1
    { $$ = $1; }
| /* empty */
    { $$ = NULL; }
;

tycon
: identifier
    { $$ = (TyCon *)parse_state_register_node(state, new_tycon($1)); }
;

longtycon
: tycon
    { $$ = (LongTyCon *)parse_state_register_node(state, new_longtycon_nonqualified($1)); }
| qualifying_strid_list1 tycon
    { $$ = (LongTyCon *)parse_state_register_node(state, new_longtycon_qualified($1, $2)); }
;

lab
: identifier
    { $$ = (Lab *)parse_state_register_node(state, new_lab_alphanumeric($1)); }
| numeric
    { $$ = (Lab *)parse_state_register_node(state, new_lab_numeric($1)); }
;

strid
: identifier
    { $$ = (StrId *)parse_state_register_node(state, new_strid($1)); }
;

longstrid
: strid
    { $$ = (LongStrId *)parse_state_register_node(state, new_longstrid_nonqualified($1)); }
| qualifying_strid_list1 strid
    { $$ = (LongStrId *)parse_state_register_node(state, new_longstrid_qualified($1, $2)); }
;

longstridlist1
: longstrid longstridlist1
    { $$ = (LongStrIdList *)parse_state_register_node(state, new_longstridlist($1, $2)); }
| longstrid
    { $$ = (LongStrIdList *)parse_state_register_node(state, new_longstridlist($1, NULL)); }
;

atpat_nonid
: UNDERBAR
    { $$ = (AtPat *)parse_state_register_node(state, new_atpat_wildcard()); }
| scon
    { $$ = (AtPat *)parse_state_register_node(state, new_atpat_special_constant($1)); }
| LBRACE RBRACE
    { $$ = (AtPat *)parse_state_register_node(state, new_atpat_record(NULL)); }
| LBRACE patrow RBRACE
    { $$ = (AtPat *)parse_state_register_node(state, new_atpat_record($2)); }
| LPAREN pat RPAREN
    { $$ = (AtPat *)parse_state_register_node(state, new_atpat_parened_pat($2)); }
;

atpat
: atpat_nonid
    { $$ = $1; }
| OP_option longvid_bind
    { $$ = (AtPat *)parse_state_register_node(state, new_atpat_value_identifier($1, $2)); }
;

patrow
: lab EQUAL pat
    { $$ = (PatRow *)parse_state_register_node(state, new_patrow_pattern_row($1, $3, NULL)); }
| lab EQUAL pat COMMA patrow
    { $$ = (PatRow *)parse_state_register_node(state, new_patrow_pattern_row($1, $3, $5)); }
| DOTDOTDOT
    { $$ = (PatRow *)parse_state_register_node(state, new_patrow_wildcard()); }
;

pat
: atpat
    { $$ = (Pat *)parse_state_register_node(state, new_pat_atomic($1)); }
/* TODO infxed */
| OP_option vid_bind COLON ty
    { LongVId *longvid = (LongVId *)parse_state_register_node(state, new_longvid_nonqualified($2));
      AtPat *atpat = (AtPat *)parse_state_register_node(state, new_atpat_value_identifier($1, longvid));
      Pat *pat_atomic = (Pat *)parse_state_register_node(state, new_pat_atomic(atpat));
      $$ = (Pat *)parse_state_register_node(state, new_pat_typed(pat_atomic, $4)); }
| atpat_nonid COLON ty
    { Pat *atpat_nonid = (Pat *)parse_state_register_node(state, new_pat_atomic($1));
      $$ = (Pat *)parse_state_register_node(state, new_pat_typed(atpat_nonid, $3)); }
| OP_option longvid_bind atpat
    { $$ = (Pat *)parse_state_register_node(state, new_pat_constructed_pattern($1, $2, $3)); }
| OP_option longvid_bind atpat COLON ty
    { Pat *cons_pat = (Pat *)parse_state_register_node(state, new_pat_constructed_pattern($1, $2, $3));
      $$ = (Pat *)parse_state_register_node(state, new_pat_typed(cons_pat, $5)); }
| OP_option vid_bind AS pat
    { $$ = (Pat *)parse_state_register_node(state, new_pat_layered($1, $2, NULL, $4)); }
| OP_option vid_bind COLON ty AS pat
    { $$ = (Pat *)parse_state_register_node(state, new_pat_layered($1, $2, $4, $6)); }
;

atty
: tyvar
    { $$ = (Ty *)parse_state_register_node(state, new_ty_type_variable($1)); }
| LBRACE RBRACE
    { $$ = (Ty *)parse_state_register_node(state, new_ty_record_type_expression(NULL)); }
| LBRACE tyrow RBRACE
    { $$ = (Ty *)parse_state_register_node(state, new_ty_record_type_expression($2)); }
| LPAREN ty RPAREN
    { $$ = (Ty *)parse_state_register_node(state, new_ty_parened_ty($2)); }
;

conty
: atty
    { $$ = $1; }
| tyseq longtycon
    { $$ = (Ty *)parse_state_register_node(state, new_ty_type_construction($1, $2)); }
;

ty
: conty
    { $$ = $1; }
| conty ARROW ty
    { $$ = (Ty *)parse_state_register_node(state, new_ty_function_type_expression($1, $3)); }
;

ty_comma_list2
: ty COMMA ty
    { $$ = (TySeq *)parse_state_register_node(state, new_tyseq($1, new_tyseq($3, NULL))); }
| ty COMMA ty_comma_list2
    { $$ = (TySeq *)parse_state_register_node(state, new_tyseq($1, $3)); }
;

tyseq
: conty
    { $$ = (TySeq *)parse_state_register_node(state, new_tyseq($1, NULL)); }
| /* empty */
    { $$ = NULL; }
| LPAREN ty_comma_list2 RPAREN
    { $$ = $2; }
;

tyrow
: lab COLON ty
    { $$ = (TyRow *)parse_state_register_node(state, new_tyrow($1, $3, NULL)); }
| lab COLON ty COMMA tyrow
    { $$ = (TyRow *)parse_state_register_node(state, new_tyrow($1, $3, $5)); }
;

atexp
: scon
    { $$ = (AtExp *)parse_state_register_node(state, new_atexp_special_constant($1)); }
| OP_option longvid
    { $$ = (AtExp *)parse_state_register_node(state, new_atexp_value_identifier($1, $2)); }
| LBRACE RBRACE
    { $$ = (AtExp *)parse_state_register_node(state, new_atexp_record(NULL)); }
| LBRACE exprow RBRACE
    { $$ = (AtExp *)parse_state_register_node(state, new_atexp_record($2)); }
| LET dec IN exp END
    { $$ = (AtExp *)parse_state_register_node(state, new_atexp_local_declaration($2, $4)); }
| LPAREN exp RPAREN
    { $$ = (AtExp *)parse_state_register_node(state, new_atexp_parened_exp($2)); }
;

exprow
: lab EQUAL exp COMMA exprow
    { $$ = (ExpRow *)parse_state_register_node(state, new_exprow($1, $3, $5)); }
| lab EQUAL exp
    { $$ = (ExpRow *)parse_state_register_node(state, new_exprow($1, $3, NULL)); }
;

exp
: atexp
    { $$ = (Exp *)parse_state_register_node(state, new_exp_atomic($1)); }
/* TODO: infixed exp */
| exp COLON ty
    { $$ = (Exp *)parse_state_register_node(state, new_exp_typed($1, $3)); }
| exp HANDLE match
    { $$ = (Exp *)parse_state_register_node(state, new_exp_handle_exception($1, $3)); }
| RAISE exp
    { $$ = (Exp *)parse_state_register_node(state, new_exp_raise_exception($2)); }
| FN match
    { $$ = (Exp *)parse_state_register_node(state, new_exp_function($2)); }
;

match
: mrule BAR match
    { $$ = (Match *)parse_state_register_node(state, new_match($1, $3)); }
| mrule %prec DARROW
    { $$ = (Match *)parse_state_register_node(state, new_match($1, NULL)); }
;

mrule
: pat DARROW exp
    { $$ = (Mrule *)parse_state_register_node(state, new_mrule($1, $3)); }
;

dec
: VAL valbind
    { $$ = (Dec *)parse_state_register_node(state, new_dec_value_declaration(NULL, $2)); }
| VAL tyvarseq1 valbind
    { $$ = (Dec *)parse_state_register_node(state, new_dec_value_declaration($2, $3)); }
| TYPE typbind
    { $$ = (Dec *)parse_state_register_node(state, new_dec_type_declaration($2)); }
| DATATYPE datbind
    { $$ = (Dec *)parse_state_register_node(state, new_dec_datatype_declaration($2)); }
| DATATYPE tycon EQUAL DATATYPE longtycon
    { $$ = (Dec *)parse_state_register_node(state, new_dec_datatype_replication($2, $5)); }
| ABSTYPE datbind WITH dec END
    { $$ = (Dec *)parse_state_register_node(state, new_dec_abstype_declaration($2, $4)); }
| EXCEPTION exbind
    { $$ = (Dec *)parse_state_register_node(state, new_dec_exception_declaration($2)); }
| LOCAL dec IN dec END
    { $$ = (Dec *)parse_state_register_node(state, new_dec_local_declaration($2, $4)); }
| OPEN longstridlist1
    { $$ = (Dec *)parse_state_register_node(state, new_dec_open_declaration($2)); }
| dec SEMICOLON dec
    { $$ = (Dec *)parse_state_register_node(state, new_dec_sequential_declaration($1, $3)); }
| dec dec %prec SEMICOLON
    { $$ = (Dec *)parse_state_register_node(state, new_dec_sequential_declaration($1, $2)); }
| INFIX vid_list1
    { $$ = (Dec *)parse_state_register_node(state, new_dec_infix_l_directive(NULL, $2)); }
| INFIX numeric vid_list1
    { $$ = (Dec *)parse_state_register_node(state, new_dec_infix_l_directive($2, $3)); }
| INFIXR vid_list1
    { $$ = (Dec *)parse_state_register_node(state, new_dec_infix_r_directive(NULL, $2)); }
| INFIXR numeric vid_list1
    { $$ = (Dec *)parse_state_register_node(state, new_dec_infix_r_directive($2, $3)); }
| NONFIX vid_list1
    { $$ = (Dec *)parse_state_register_node(state, new_dec_nonfix_directive($2)); }
;

valbind
: pat EQUAL exp AND valbind
    { $$ = (ValBind *)parse_state_register_node(state, new_valbind_bind($1, $3, $5)); }
| pat EQUAL exp
    { $$ = (ValBind *)parse_state_register_node(state, new_valbind_bind($1, $3, NULL)); }
| REC valbind
    { $$ = (ValBind *)parse_state_register_node(state, new_valbind_rec($2)); }
;

typbind
: tyvarseq tycon EQUAL ty
    { $$ = (TypBind *)parse_state_register_node(state, new_typbind($1, $2, $4, NULL)); }
| tyvarseq tycon EQUAL ty AND typbind
    { $$ = (TypBind *)parse_state_register_node(state, new_typbind($1, $2, $4, $6)); }
;

datbind
: tycon EQUAL conbind
    { $$ = (DatBind *)parse_state_register_node(state, new_datbind(NULL, $1, $3, NULL)); }
| tyvarseq1 tycon EQUAL conbind
    { $$ = (DatBind *)parse_state_register_node(state, new_datbind($1, $2, $4, NULL)); }
| tycon EQUAL conbind AND datbind
    { $$ = (DatBind *)parse_state_register_node(state, new_datbind(NULL, $1, $3, $5)); }
| tyvarseq1 tycon EQUAL conbind AND datbind
    { $$ = (DatBind *)parse_state_register_node(state, new_datbind($1, $2, $4, $6)); }
;

conbind
: OP_option vid_bind
    { $$ = (ConBind *)parse_state_register_node(state, new_conbind($1, $2, NULL, NULL)); }
| OP_option vid_bind OF ty
    { $$ = (ConBind *)parse_state_register_node(state, new_conbind($1, $2, $4, NULL)); }
| OP_option vid_bind BAR conbind
    { $$ = (ConBind *)parse_state_register_node(state, new_conbind($1, $2, NULL, $4)); }
| OP_option vid_bind OF ty BAR conbind
    { $$ = (ConBind *)parse_state_register_node(state, new_conbind($1, $2, $4, $6)); }
;

exbind
: OP_option vid_bind
    { $$ = (ExBind *)parse_state_register_node(state, new_exbind_declaration($1, $2, NULL, NULL)); }
| OP_option vid_bind OF ty
    { $$ = (ExBind *)parse_state_register_node(state, new_exbind_declaration($1, $2, $4, NULL)); }
| OP_option vid_bind AND exbind
    { $$ = (ExBind *)parse_state_register_node(state, new_exbind_declaration($1, $2, NULL, $4)); }
| OP_option vid_bind OF ty AND exbind
    { $$ = (ExBind *)parse_state_register_node(state, new_exbind_declaration($1, $2, $4, $6)); }
| OP_option vid_bind EQUAL OP_option longvid_bind
    { $$ = (ExBind *)parse_state_register_node(state, new_exbind_replication($1, $2, $4, $5, NULL)); }
| OP_option vid_bind EQUAL OP_option longvid_bind AND exbind
    { $$ = (ExBind *)parse_state_register_node(state, new_exbind_replication($1, $2, $4, $5, $7)); }
;

%%

void yyerror(YYLTYPE *yylloc, yyscan_t scanner, ParseState *state, char *msg) {
    parse_state_register_error(state, msg, yylloc->first_line, yylloc->first_column);
    return;
}

int parse_stdin(ParseState *state) {
    yyscan_t scanner;
    yylex_init_extra(0, &scanner);
    int result = yyparse(scanner, state);
    yylex_destroy(scanner);
    return result;
}
