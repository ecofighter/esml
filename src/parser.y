%{
#include <stdlib.h>
#include "syntax.h"

extern void yyerror(const char *msg);
extern int yylex(void);
Dec *parse_result;
%}

%union {
  struct {
    char *text;
    int line;
    int column;
  } token;
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
};

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
%token <token> NUMERIC INTEGER WORD REAL
%token <token> TYVAR IDENTIFIER
%token ERROR

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
: dec { parse_result = $1; }
;

OP_option
: OP { $$ = 1; }
| /* empty */ { $$ = 0; }
;

scon
: NUMERIC { $$ = new_constant_integer($1.text); }
| INTEGER { $$ = new_constant_integer($1.text); }
;

qualifying_strid_list1
: qualifying_strid_list1 strid DOT { $$ = new_stridlist($1, $2); }
| strid DOT { $$ = new_stridlist(NULL, $1); }
;

vid
: IDENTIFIER { $$ = new_vid($1.text); }
| EQUAL { char *eq = (char *)malloc(2); eq[0] = '='; eq[1] = '\0'; $$ = new_vid(eq); }
;

vid_list1
: vid vid_list1 { $$ = new_vidlist($1, $2); }
| vid { $$ = new_vidlist($1, NULL); }
;

longvid
: vid { $$ = new_longvid_nonqualified($1); }
| qualifying_strid_list1 vid { $$ = new_longvid_qualified($1, $2); }
;

vid_bind
: IDENTIFIER { $$ = new_vid($1.text); }
;

longvid_bind
: vid_bind { $$ = new_longvid_nonqualified($1); }
| qualifying_strid_list1 vid_bind { $$ = new_longvid_qualified($1, $2); }
;

tyvar
: TYVAR { $$ = new_tyvar($1.text); }
;

tyvar_comma_list1
: tyvar COMMA tyvar_comma_list1 { $$ = new_tyvarseq($1, $3); }
| tyvar { $$ = new_tyvarseq($1, NULL); }
;

tyvarseq1
: tyvar { $$ = new_tyvarseq($1, NULL); }
| LPAREN tyvar_comma_list1 RPAREN { $$ = $2; }

tyvarseq
: tyvarseq1 { $$ = $1; }
| /* empty */ { $$ = NULL; }
;

tycon
: IDENTIFIER { $$ = new_tycon($1.text); }
;

longtycon
: tycon { $$ = new_longtycon_nonqualified($1); }
| qualifying_strid_list1 tycon { $$ = new_longtycon_qualified($1, $2); }
;

lab
: IDENTIFIER { $$ = new_lab_alphanumeric($1.text); }
| NUMERIC { $$ = new_lab_numeric($1.text); }
;

strid
: IDENTIFIER { $$ = new_strid($1.text); }
;

longstrid
: strid { $$ = new_longstrid_nonqualified($1); }
| qualifying_strid_list1 strid { $$ = new_longstrid_qualified($1, $2); }
;

longstridlist1
: longstrid longstridlist1 { $$ = new_longstridlist($1, $2); }
| longstrid { $$ = new_longstridlist($1, NULL); }
;

atpat_nonid
: UNDERBAR { $$ = new_atpat_wildcard(); }
| scon { $$ = new_atpat_special_constant($1); }
| LBRACE RBRACE { $$ = new_atpat_record(NULL); }
| LBRACE patrow RBRACE { $$ = new_atpat_record($2); }
| LPAREN pat RPAREN { $$ = new_atpat_parened_pat($2); }
;

atpat
: atpat_nonid { $$ = $1; }
| OP_option longvid_bind { $$ = new_atpat_value_identifier($1, $2); }
;

patrow
: lab EQUAL pat { $$ = new_patrow_pattern_row($1, $3, NULL); }
| lab EQUAL pat COMMA patrow { $$ = new_patrow_pattern_row($1, $3, $5); }
| DOTDOTDOT { $$ = new_patrow_wildcard(); }
;

pat
: atpat { $$ = new_pat_atomic($1); }
/* TODO infxed */
| OP_option vid_bind COLON ty
  { $$ = new_pat_typed(new_pat_atomic(new_atpat_value_identifier($1, new_longvid_nonqualified($2))), $4); }
| atpat_nonid COLON ty { $$ = new_pat_typed(new_pat_atomic($1), $3); }
| OP_option longvid_bind atpat { $$ = new_pat_constructed_pattern($1, $2, $3); }
| OP_option longvid_bind atpat COLON ty { $$ = new_pat_typed(new_pat_constructed_pattern($1, $2, $3), $5); }
| OP_option vid_bind AS pat { $$ = new_pat_layered($1, $2, NULL, $4); }
| OP_option vid_bind COLON ty AS pat { $$ = new_pat_layered($1, $2, $4, $6); }
;

atty
: tyvar { $$ = new_ty_type_variable($1); }
| LBRACE RBRACE { $$ = new_ty_record_type_expression(NULL); }
| LBRACE tyrow RBRACE { $$ = new_ty_record_type_expression($2); }
| LPAREN ty RPAREN { $$ = new_ty_parened_ty($2); }
;

conty
: atty { $$ = $1; }
| tyseq longtycon { $$ = new_ty_type_construction($1, $2); }
;

ty
: conty
| conty ARROW ty { $$ = new_ty_function_type_expression($1, $3); }
;

ty_comma_list2
: ty COMMA ty { $$ = new_tyseq($1, new_tyseq($3, NULL)); }
| ty COMMA ty_comma_list2 { $$ = new_tyseq($1, $3); }
;

tyseq
: conty { $$ = new_tyseq($1, NULL); }
| /* empty */ { $$ = NULL; }
| LPAREN ty_comma_list2 RPAREN { $$ = $2; }
;

tyrow
: lab COLON ty { $$ = new_tyrow($1, $3, NULL); }
| lab COLON ty COMMA tyrow { $$ = new_tyrow($1, $3, $5); }
;

atexp
: scon { $$ = new_atexp_special_constant($1); }
| OP_option longvid { $$ = new_atexp_value_identifier($1, $2); }
| LBRACE RBRACE { $$ = new_atexp_record(NULL); }
| LBRACE exprow RBRACE { $$ = new_atexp_record($2); }
| LET dec IN exp END { $$ = new_atexp_local_declaration($2, $4); }
| LPAREN exp RPAREN { $$ = new_atexp_parened_exp($2); }
;

exprow
: lab EQUAL exp COMMA exprow { $$ = new_exprow($1, $3, $5); }
| lab EQUAL exp { $$ = new_exprow($1, $3, NULL); }
;

exp
: atexp { $$ = new_exp_atomic($1); }
/* infixed exp */
| exp COLON ty { $$ = new_exp_typed($1, $3); }
| exp HANDLE match { $$ = new_exp_handle_exception($1, $3); }
| RAISE exp { $$ = new_exp_raise_exception($2); }
| FN match { $$ = new_exp_function($2); }
;

match
: mrule BAR match { $$ = new_match($1, $3); }
| mrule %prec DARROW { $$ = new_match($1, NULL); }
;

mrule
: pat DARROW exp { $$ = new_mrule($1, $3); }
;

dec
: VAL valbind { $$ = new_dec_value_declaration(NULL, $2); }
| VAL tyvarseq1 valbind { $$ = new_dec_value_declaration($2, $3); }
| TYPE typbind { $$ = new_dec_type_declaration($2); }
| DATATYPE datbind { $$ = new_dec_datatype_declaration($2); }
| DATATYPE tycon EQUAL DATATYPE longtycon { $$ = new_dec_datatype_replication($2, $5); }
| ABSTYPE datbind WITH dec END { $$ = new_dec_abstype_declaration($2, $4); }
| EXCEPTION exbind { $$ = new_dec_exception_declaration($2); }
| LOCAL dec IN dec END { $$ = new_dec_local_declaration($2, $4); }
| OPEN longstridlist1 { $$ = new_dec_open_declaration($2); }
| dec SEMICOLON dec { $$ = new_dec_sequential_declaration($1, $3); }
| dec dec %prec SEMICOLON { $$ = new_dec_sequential_declaration($1, $2); }
| INFIX vid_list1 { $$ = new_dec_infix_l_directive(NULL, $2); }
| INFIX NUMERIC vid_list1 { $$ = new_dec_infix_l_directive($2.text, $3); }
| INFIXR vid_list1 { $$ = new_dec_infix_r_directive(NULL, $2); }
| INFIXR NUMERIC vid_list1 { $$ = new_dec_infix_r_directive($2.text, $3); }
| NONFIX vid_list1 { $$ = new_dec_nonfix_directive($2); }
;

valbind
: pat EQUAL exp AND valbind { $$ = new_valbind_bind($1, $3, $5); }
| pat EQUAL exp { $$ = new_valbind_bind($1, $3, NULL); }
| REC valbind { $$ = new_valbind_rec($2); }
;

typbind
: tyvarseq tycon EQUAL ty { $$ = new_typbind($1, $2, $4, NULL); }
| tyvarseq tycon EQUAL ty AND typbind { $$ = new_typbind($1, $2, $4, $6); }
;

datbind
: tycon EQUAL conbind { $$ = new_datbind(NULL, $1, $3, NULL); }
| tyvarseq1 tycon EQUAL conbind { $$ = new_datbind($1, $2, $4, NULL); }
| tycon EQUAL conbind AND datbind { $$ = new_datbind(NULL, $1, $3, $5); }
| tyvarseq1 tycon EQUAL conbind AND datbind { $$ = new_datbind($1, $2, $4, $6); }
;

conbind
: OP_option vid_bind { $$ = new_conbind($1, $2, NULL, NULL); }
| OP_option vid_bind OF ty { $$ = new_conbind($1, $2, $4, NULL); }
| OP_option vid_bind BAR conbind { $$ = new_conbind($1, $2, NULL, $4); }
| OP_option vid_bind OF ty BAR conbind { $$ = new_conbind($1, $2, $4, $6); }
;

exbind
: OP_option vid_bind { $$ = new_exbind_declaration($1, $2, NULL, NULL); }
| OP_option vid_bind OF ty { $$ = new_exbind_declaration($1, $2, $4, NULL); }
| OP_option vid_bind AND exbind { $$ = new_exbind_declaration($1, $2, NULL, $4); }
| OP_option vid_bind OF ty AND exbind { $$ = new_exbind_declaration($1, $2, $4, $6); }
| OP_option vid_bind EQUAL OP_option longvid_bind { $$ = new_exbind_replication($1, $2, $4, $5, NULL); }
| OP_option vid_bind EQUAL OP_option longvid_bind AND exbind { $$ = new_exbind_replication($1, $2, $4, $5, $7); }
;
%%
