%code top {
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "concrete_syntax.h"
#include "parse_state.h"
#include "parser.h"
#include "lexer.h"
#include "utils.h"
}
%code provides {
extern int parse_stdin(ParseState *state);
}

%pure-parser
%locations
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner } { ParseState *state }
%union {
  bool bool_val;
  char *string;
  CVId *vid;
  CVIdList *vidlist;
  CQualifiedVId *qualified_vid;
  CLongVId *longvid;
  CTyVar *tyvar;
  CTyVarList *tyvarlist;
  CTyCon *tycon;
  CQualifiedTyCon *qualified_tycon;
  CLongTyCon *longtycon;
  CLab *lab;
  CStrId *strid;
  CQualifiedStrId *qualified_strid;
  CLongStrId *longstrid;
  CLongStrIdList *longstridlist;
  CConstant *constant;
  CAtPat *atpat;
  CAtPatList *atpatlist;
  CPatRow *patrow;
  CPat *pat;
  CPatList *patlist;
  CTy *ty;
  CTyList *tylist;
  CTyRow *tyrow;
  CAtExp *atexp;
  CAtExpList *atexplist;
  CExpRow *exprow;
  CExp *exp;
  CExpList *explist;
  CMatch *match;
  CMrule *mrule;
  CDec *dec;
  CValBind *valbind;
  CFValBind *fvalbind;
  CFMatch *fmatch;
  CFMrule *fmrule;
  CTypBind *typbind;
  CDatBind *datbind;
  CConBind *conbind;
  CExBind *exbind;
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
%token COMMA COLON SEMICOLON DOTDOTDOT
%token UNDERBAR BAR EQUAL ASTERISK DARROW ARROW HASH
%token NUMERIC INTEGER WORD REAL
%token TYVAR IDENTIFIER QUALIFIED_IDENTIFIER
%token ERROR

%type <string> numeric integer word real identifier qualified_identifier
%type <bool_val> OP_option
%type <constant> scon
%type <vid> vid_bind vid
%type <vidlist> vid_list1
%type <qualified_vid> qualified_vid
%type <longvid> longvid longvid_bind
%type <tyvar> tyvar
%type <tyvarlist> tyvar_comma_list1 tyvarseq1 tyvarseq
%type <tycon> tycon
%type <qualified_tycon> qualified_tycon
%type <longtycon> longtycon
%type <lab> lab
%type <strid> strid
%type <qualified_strid> qualified_strid
%type <longstrid> longstrid
%type <longstridlist> longstridlist1
%type <atpat> atpat_nonid atpat
%type <atpatlist> atpat_list1 atpat_list2
%type <patrow> patrow
%type <pat> pat
%type <patlist> pat_comma_list2 pat_comma_list1 pat_comma_list
%type <ty> atty conty tuplety ty
%type <tylist> conty_asterisk_list2 ty_comma_list2 tyseq
%type <tyrow> tyrow
%type <atexp> atexp
%type <atexplist> atexp_list2
%type <exprow> exprow
%type <exp> exp
%type <explist> exp_comma_list2 exp_comma_list1 exp_comma_list exp_semicolon_list2
%type <match> match
%type <mrule> mrule
%type <dec> dec
%type <valbind> valbind
%type <fvalbind> fvalbind
%type <fmatch> fmatch
%type <fmrule> fmrule
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
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (char *)parse_state_register_node(state, text); }
;

integer
: INTEGER
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (char *)parse_state_register_node(state, text); }
;

word
: WORD
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (char *)parse_state_register_node(state, text); }
;

real
: REAL
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (char *)parse_state_register_node(state, text); }
;

identifier
: IDENTIFIER
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (char *)parse_state_register_node(state, text); }
;

qualified_identifier
: QUALIFIED_IDENTIFIER
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (char *)parse_state_register_node(state, text); }
;

OP_option
: OP
    { $$ = true; }
| /* empty */
    { $$ = false; }
;

scon
: numeric
    { $$ = (CConstant *)parse_state_register_node(state, new_c_constant_integer($1)); }
| integer
    { $$ = (CConstant *)parse_state_register_node(state, new_c_constant_integer($1)); }
;

vid
: identifier
    { $$ = (CVId *)parse_state_register_node(state, new_c_vid($1)); }
| EQUAL
    { char *eq = (char *)malloc(2);
      eq[0] = '='; eq[1] = '\0';
      $$ = (CVId *)parse_state_register_node(state, new_c_vid((char *)parse_state_register_node(state, eq))); }
| ASTERISK
    { char *asterisk = (char *)malloc(2);
      asterisk[0] = '*'; asterisk[1] = '\0';
      $$ = (CVId *)parse_state_register_node(state, new_c_vid((char *)parse_state_register_node(state, asterisk))); }
;

vid_list1
: vid vid_list1
    { $$ = (CVIdList *)parse_state_register_node(state, new_c_vidlist($1, $2)); }
| vid
    { $$ = (CVIdList *)parse_state_register_node(state, new_c_vidlist($1, NULL)); }
;

qualified_vid
: qualified_identifier
    { $$ = (CQualifiedVId *)parse_state_register_node(state, new_c_qualified_vid($1)); }
;

longvid
: vid
    { $$ = (CLongVId *)parse_state_register_node(state, new_c_longvid_nonqualified($1)); }
| qualified_vid
    { $$ = (CLongVId *)parse_state_register_node(state, new_c_longvid_qualified($1)); }
;

vid_bind
: identifier
    { $$ = (CVId *)parse_state_register_node(state, new_c_vid($1)); }
| ASTERISK
    { char *asterisk = (char *)malloc(2);
      asterisk[0] = '*'; asterisk[1] = '\0';
      $$ = (CVId *)parse_state_register_node(state, new_c_vid((char *)parse_state_register_node(state, asterisk))); }
;

longvid_bind
: vid_bind
    { $$ = (CLongVId *)parse_state_register_node(state, new_c_longvid_nonqualified($1)); }
| qualified_vid
    { $$ = (CLongVId *)parse_state_register_node(state, new_c_longvid_qualified($1)); }
;
tyvar
: TYVAR
    { char *text = esml_strdup(yyget_text(scanner));
      $$ = (CTyVar *)parse_state_register_node(state, new_c_tyvar(parse_state_register_node(state, text))); }
;

tyvar_comma_list1
: tyvar COMMA tyvar_comma_list1
    { $$ = (CTyVarList *)parse_state_register_node(state, new_c_tyvarlist($1, $3)); }
| tyvar
    { $$ = (CTyVarList *)parse_state_register_node(state, new_c_tyvarlist($1, NULL)); }
;

tyvarseq1
: tyvar
    { $$ = (CTyVarList *)parse_state_register_node(state, new_c_tyvarlist($1, NULL)); }
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
    { $$ = (CTyCon *)parse_state_register_node(state, new_c_tycon($1)); }
;

qualified_tycon
: qualified_identifier
    { $$ = (CQualifiedTyCon *)parse_state_register_node(state, new_c_qualified_tycon($1)); }
;

longtycon
: tycon
    { $$ = (CLongTyCon *)parse_state_register_node(state, new_c_longtycon_nonqualified($1)); }
| qualified_tycon
    { $$ = (CLongTyCon *)parse_state_register_node(state, new_c_longtycon_qualified($1)); }
;

lab
: identifier
    { $$ = (CLab *)parse_state_register_node(state, new_c_lab_alphanumeric($1)); }
| numeric
    { $$ = (CLab *)parse_state_register_node(state, new_c_lab_numeric($1)); }
;

strid
: identifier
    { $$ = (CStrId *)parse_state_register_node(state, new_c_strid($1)); }
;

qualified_strid
: qualified_identifier
    { $$ = (CQualifiedStrId *)parse_state_register_node(state, new_c_qualified_strid($1)); }
;

longstrid
: strid
    { $$ = (CLongStrId *)parse_state_register_node(state, new_c_longstrid_nonqualified($1)); }
| qualified_strid
    { $$ = (CLongStrId *)parse_state_register_node(state, new_c_longstrid_qualified($1)); }
;

longstridlist1
: longstrid longstridlist1
    { $$ = (CLongStrIdList *)parse_state_register_node(state, new_c_longstridlist($1, $2)); }
| longstrid
    { $$ = (CLongStrIdList *)parse_state_register_node(state, new_c_longstridlist($1, NULL)); }
;

// TODO
atpat_nonid
: UNDERBAR
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_wildcard()); }
| scon
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_special_constant($1)); }
| LBRACE RBRACE
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_record(NULL)); }
| LBRACE patrow RBRACE
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_record($2)); }
| LPAREN RPAREN
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_zero_tuple()); }
| LPAREN pat_comma_list2 RPAREN
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_n_tuple($2)); }
| LBRACKET pat_comma_list RBRACKET
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_list($2)); }
| LPAREN pat RPAREN
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_parened_pat($2)); }
;

atpat
: atpat_nonid
    { $$ = $1; }
| OP_option longvid_bind
    { $$ = (CAtPat *)parse_state_register_node(state, new_c_atpat_value_identifier($1, $2)); }
;

atpat_list1
: atpat
    { $$ = (CAtPatList *)parse_state_register_node(state, new_c_atpatlist($1, NULL)); }
| atpat atpat_list1
    { $$ = (CAtPatList *)parse_state_register_node(state, new_c_atpatlist($1, $2)); }
;

atpat_list2
: atpat atpat
    { CAtPatList *arg = (CAtPatList *)parse_state_register_node(state, new_c_atpatlist($2, NULL));
      $$ = (CAtPatList *)parse_state_register_node(state, new_c_atpatlist($1, arg)); }
| atpat atpat_list2
    { $$ = (CAtPatList *)parse_state_register_node(state, new_c_atpatlist($1, $2)); }
;

patrow
: lab EQUAL pat
    { $$ = (CPatRow *)parse_state_register_node(state, new_c_patrow_pattern_row($1, $3, NULL)); }
| lab EQUAL pat COMMA patrow
    { $$ = (CPatRow *)parse_state_register_node(state, new_c_patrow_pattern_row($1, $3, $5)); }
| DOTDOTDOT
    { $$ = (CPatRow *)parse_state_register_node(state, new_c_patrow_wildcard()); }
;

pat
: atpat
    { $$ = (CPat *)parse_state_register_node(state, new_c_pat_atomic($1)); }
| atpat_list2
    { $$ = (CPat *)parse_state_register_node(state, new_c_pat_atpatlist($1)); }
| atpat_nonid COLON ty
    { CPat *atpat_nonid = (CPat *)parse_state_register_node(state, new_c_pat_atomic($1));
      $$ = (CPat *)parse_state_register_node(state, new_c_pat_typed(atpat_nonid, $3)); }
| atpat_list2 COLON ty { /* TODO */ }
| OP_option vid_bind COLON ty
    { CLongVId *longvid =
        (CLongVId *)parse_state_register_node(state, new_c_longvid_nonqualified($2));
      CAtPat *atpat =
        (CAtPat *)parse_state_register_node(state, new_c_atpat_value_identifier($1, longvid));
      CPat *pat_atomic = (CPat *)parse_state_register_node(state, new_c_pat_atomic(atpat));
      $$ = (CPat *)parse_state_register_node(state, new_c_pat_typed(pat_atomic, $4)); }
| OP_option qualified_identifier COLON ty
    { CQualifiedVId *qualified_vid =
        (CQualifiedVId *)parse_state_register_node(state, new_c_qualified_vid($2));
      CLongVId *longvid =
        (CLongVId *)parse_state_register_node(state, new_c_longvid_qualified(qualified_vid));
      CAtPat *atpat =
        (CAtPat *)parse_state_register_node(state, new_c_atpat_value_identifier($1, longvid));
      CPat *pat_atomic = (CPat *)parse_state_register_node(state, new_c_pat_atomic(atpat));
      $$ = (CPat *)parse_state_register_node(state, new_c_pat_typed(pat_atomic, $4)); }
| OP_option vid_bind AS pat
    { $$ = (CPat *)parse_state_register_node(state, new_c_pat_layered($1, $2, NULL, $4)); }
| OP_option vid_bind COLON ty AS pat
    { $$ = (CPat *)parse_state_register_node(state, new_c_pat_layered($1, $2, $4, $6)); }
;

pat_comma_list2
: pat COMMA pat
    { CPatList *tmp = (CPatList *)parse_state_register_node(state, new_c_patlist($3, NULL));
      $$ = (CPatList *)parse_state_register_node(state, new_c_patlist($1, tmp)); }
| pat COMMA pat_comma_list2
    { $$ = (CPatList *)parse_state_register_node(state, new_c_patlist($1, $3)); }
;

pat_comma_list1
: pat
    { $$ = (CPatList *)parse_state_register_node(state, new_c_patlist($1, NULL)); }
| pat COMMA pat_comma_list1
    { $$ = (CPatList *)parse_state_register_node(state, new_c_patlist($1, $3)); }
;

pat_comma_list
: /* emptry */
    { $$ = NULL; }
| pat_comma_list1
    { $$ = $1; }
;

atty
: tyvar
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_type_variable($1)); }
| LBRACE RBRACE
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_record_type_expression(NULL)); }
| LBRACE tyrow RBRACE
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_record_type_expression($2)); }
| LPAREN ty RPAREN
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_parened_ty($2)); }
;

conty
: atty
    { $$ = $1; }
| tyseq longtycon
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_type_construction($1, $2)); }
;

conty_asterisk_list2
: conty ASTERISK conty
    { CTyList *tmp = (CTyList *)parse_state_register_node(state, new_c_tylist($3, NULL));
      $$ = (CTyList *)parse_state_register_node(state, new_c_tylist($1, tmp)); }
| conty ASTERISK conty_asterisk_list2
    { $$ = (CTyList *)parse_state_register_node(state, new_c_tylist($1, $3)); }
;

tuplety
: conty_asterisk_list2
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_tuple_type($1)); }
| conty
    { $$ = $1; }
;

ty
: tuplety
    { $$ = $1; }
| tuplety ARROW ty
    { $$ = (CTy *)parse_state_register_node(state, new_c_ty_function_type_expression($1, $3)); }
;

ty_comma_list2
: ty COMMA ty
    { CTyList *tmp = (CTyList *)parse_state_register_node(state, new_c_tylist($3, NULL));
      $$ = (CTyList *)parse_state_register_node(state, new_c_tylist($1, tmp)); }
| ty COMMA ty_comma_list2
    { $$ = (CTyList *)parse_state_register_node(state, new_c_tylist($1, $3)); }
;

tyseq
: conty
    { $$ = (CTyList *)parse_state_register_node(state, new_c_tylist($1, NULL)); }
| /* empty */
    { $$ = NULL; }
| LPAREN ty_comma_list2 RPAREN
    { $$ = $2; }
;

tyrow
: lab COLON ty
    { $$ = (CTyRow *)parse_state_register_node(state, new_c_tyrow($1, $3, NULL)); }
| lab COLON ty COMMA tyrow
    { $$ = (CTyRow *)parse_state_register_node(state, new_c_tyrow($1, $3, $5)); }
;

atexp
: scon
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_special_constant($1)); }
| OP_option longvid
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_value_identifier($1, $2)); }
| LBRACE RBRACE
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_record(NULL)); }
| LBRACE exprow RBRACE
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_record($2)); }
| HASH lab
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_record_selector($2)); }
| LPAREN RPAREN
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_zero_tuple()); }
| LPAREN exp_comma_list2 RPAREN
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_n_tuple($2)); }
| LBRACKET exp_comma_list RBRACKET
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_list($2)); }
| LPAREN exp_semicolon_list2 RPAREN
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_sequence($2)); }
| LET dec IN exp END
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_local_declaration($2, $4)); }
| LPAREN exp RPAREN
    { $$ = (CAtExp *)parse_state_register_node(state, new_c_atexp_parened_exp($2)); }
;

atexp_list2
: atexp atexp
    { CAtExpList *tmp = (CAtExpList *)parse_state_register_node(state, new_c_atexplist($2, NULL));
      $$ = (CAtExpList *)parse_state_register_node(state, new_c_atexplist($1, tmp)); }
| atexp atexp_list2
    { $$ = (CAtExpList *)parse_state_register_node(state, new_c_atexplist($1, $2)); }
;

exprow
: lab EQUAL exp COMMA exprow
    { $$ = (CExpRow *)parse_state_register_node(state, new_c_exprow($1, $3, $5)); }
| lab EQUAL exp
    { $$ = (CExpRow *)parse_state_register_node(state, new_c_exprow($1, $3, NULL)); }
;

exp
: atexp
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_atomic($1)); }
| atexp_list2
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_atexplist($1)); }
| exp COLON ty
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_typed($1, $3)); }
| exp ANDALSO exp
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_conjunction($1, $3)); }
| exp ORELSE exp
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_disjunction($1, $3)); }
| exp HANDLE match
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_handle_exception($1, $3)); }
| RAISE exp
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_raise_exception($2)); }
| IF exp THEN exp ELSE exp
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_conditional($2, $4, $6)); }
| WHILE exp DO exp
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_iteration($2, $4)); }
| CASE exp OF match
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_case_analysis($2, $4)); }
| FN match
    { $$ = (CExp *)parse_state_register_node(state, new_c_exp_function($2)); }
;

exp_comma_list2
: exp COMMA exp
    { CExpList *tmp = (CExpList *)parse_state_register_node(state, new_c_explist($3, NULL));
      $$ = (CExpList *)parse_state_register_node(state, new_c_explist($1, tmp)); }
| exp COMMA exp_comma_list2
    { $$ = (CExpList *)parse_state_register_node(state, new_c_explist($1, $3)); }
;

exp_comma_list1
: exp
    { $$ = (CExpList *)parse_state_register_node(state, new_c_explist($1, NULL)); }
| exp COMMA exp_comma_list1
    { $$ = (CExpList *)parse_state_register_node(state, new_c_explist($1, $3)); }
;

exp_comma_list
: /* empty */
    { $$ = NULL; }
| exp_comma_list1
    { $$ = $1; }
;

exp_semicolon_list2
: exp SEMICOLON exp
    { CExpList *tmp = (CExpList *)parse_state_register_node(state, new_c_explist($3, NULL));
      $$ = (CExpList *)parse_state_register_node(state, new_c_explist($1, tmp)); }
| exp SEMICOLON exp_semicolon_list2
    { $$ = (CExpList *)parse_state_register_node(state, new_c_explist($1, $3)); }
;

match
: mrule BAR match
    { $$ = (CMatch *)parse_state_register_node(state, new_c_match($1, $3)); }
| mrule %prec DARROW
    { $$ = (CMatch *)parse_state_register_node(state, new_c_match($1, NULL)); }
;

mrule
: pat DARROW exp
    { $$ = (CMrule *)parse_state_register_node(state, new_c_mrule($1, $3)); }
;

/* TODO */
dec
: VAL valbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_value_declaration(NULL, $2)); }
| VAL tyvarseq1 valbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_value_declaration($2, $3)); }
| FUN fvalbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_function_declaration(NULL, $2)); }
| FUN tyvarseq1 fvalbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_function_declaration($2, $3)); }
| TYPE typbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_type_declaration($2)); }
| DATATYPE datbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_datatype_declaration($2, NULL)); }
| DATATYPE datbind WITHTYPE typbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_datatype_declaration($2, $4)); }
| DATATYPE tycon EQUAL DATATYPE longtycon
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_datatype_replication($2, $5)); }
| ABSTYPE datbind WITH dec END
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_abstype_declaration($2, NULL, $4)); }
| ABSTYPE datbind WITHTYPE typbind WITH dec END
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_abstype_declaration($2, $4, $6)); }
| EXCEPTION exbind
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_exception_declaration($2)); }
| LOCAL dec IN dec END
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_local_declaration($2, $4)); }
| OPEN longstridlist1
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_open_declaration($2)); }
| dec SEMICOLON dec
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_sequential_declaration($1, $3)); }
| dec dec %prec SEMICOLON
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_sequential_declaration($1, $2)); }
| INFIX vid_list1
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_infix_l_directive(NULL, $2)); }
| INFIX numeric vid_list1
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_infix_l_directive($2, $3)); }
| INFIXR vid_list1
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_infix_r_directive(NULL, $2)); }
| INFIXR numeric vid_list1
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_infix_r_directive($2, $3)); }
| NONFIX vid_list1
    { $$ = (CDec *)parse_state_register_node(state, new_c_dec_nonfix_directive($2)); }
;

valbind
: pat EQUAL exp AND valbind
    { $$ = (CValBind *)parse_state_register_node(state, new_c_valbind_bind($1, $3, $5)); }
| pat EQUAL exp
    { $$ = (CValBind *)parse_state_register_node(state, new_c_valbind_bind($1, $3, NULL)); }
| REC valbind
    { $$ = (CValBind *)parse_state_register_node(state, new_c_valbind_rec($2)); }
;

fvalbind
: fmatch
    { $$ = (CFValBind *)parse_state_register_node(state, new_c_fvalbind($1, NULL)); }
| fmatch AND fvalbind
    { $$ = (CFValBind *)parse_state_register_node(state, new_c_fvalbind($1, $3)); }
;

fmatch
: fmrule
    { $$ = (CFMatch *)parse_state_register_node(state, new_c_fmatch($1, NULL)); }
| fmrule BAR fmatch
    { $$ = (CFMatch *)parse_state_register_node(state, new_c_fmatch($1, $3)); }
;

fmrule
: atpat_list1 EQUAL exp
    { $$ = (CFMrule *)parse_state_register_node(state, new_c_fmrule($1, NULL, $3)); }
| atpat_list1 COLON ty EQUAL exp
    { $$ = (CFMrule *)parse_state_register_node(state, new_c_fmrule($1, $3, $5)); }
;

typbind
: tyvarseq tycon EQUAL ty
    { $$ = (CTypBind *)parse_state_register_node(state, new_c_typbind($1, $2, $4, NULL)); }
| tyvarseq tycon EQUAL ty AND typbind
    { $$ = (CTypBind *)parse_state_register_node(state, new_c_typbind($1, $2, $4, $6)); }
;

datbind
: tycon EQUAL conbind
    { $$ = (CDatBind *)parse_state_register_node(state, new_c_datbind(NULL, $1, $3, NULL)); }
| tyvarseq1 tycon EQUAL conbind
    { $$ = (CDatBind *)parse_state_register_node(state, new_c_datbind($1, $2, $4, NULL)); }
| tycon EQUAL conbind AND datbind
    { $$ = (CDatBind *)parse_state_register_node(state, new_c_datbind(NULL, $1, $3, $5)); }
| tyvarseq1 tycon EQUAL conbind AND datbind
    { $$ = (CDatBind *)parse_state_register_node(state, new_c_datbind($1, $2, $4, $6)); }
;

conbind
: OP_option vid_bind
    { $$ = (CConBind *)parse_state_register_node(state, new_c_conbind($1, $2, NULL, NULL)); }
| OP_option vid_bind OF ty
    { $$ = (CConBind *)parse_state_register_node(state, new_c_conbind($1, $2, $4, NULL)); }
| OP_option vid_bind BAR conbind
    { $$ = (CConBind *)parse_state_register_node(state, new_c_conbind($1, $2, NULL, $4)); }
| OP_option vid_bind OF ty BAR conbind
    { $$ = (CConBind *)parse_state_register_node(state, new_c_conbind($1, $2, $4, $6)); }
;

exbind
: OP_option vid_bind
    { $$ = (CExBind *)parse_state_register_node(state, new_c_exbind_declaration($1, $2, NULL, NULL)); }
| OP_option vid_bind OF ty
    { $$ = (CExBind *)parse_state_register_node(state, new_c_exbind_declaration($1, $2, $4, NULL)); }
| OP_option vid_bind AND exbind
    { $$ = (CExBind *)parse_state_register_node(state, new_c_exbind_declaration($1, $2, NULL, $4)); }
| OP_option vid_bind OF ty AND exbind
    { $$ = (CExBind *)parse_state_register_node(state, new_c_exbind_declaration($1, $2, $4, $6)); }
| OP_option vid_bind EQUAL OP_option longvid_bind
    { $$ = (CExBind *)parse_state_register_node(state, new_c_exbind_replication($1, $2, $4, $5, NULL)); }
| OP_option vid_bind EQUAL OP_option longvid_bind AND exbind
    { $$ = (CExBind *)parse_state_register_node(state, new_c_exbind_replication($1, $2, $4, $5, $7)); }
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
