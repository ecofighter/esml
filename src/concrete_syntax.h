#ifndef CONCRETE_SYNTAX_H
#define CONCRETE_SYNTAX_H

#include <stdbool.h>

typedef struct CVId CVId;
typedef struct CVIdList CVIdList;
typedef struct CLongVId CLongVId;
typedef struct CQualifiedVId CQualifiedVId;
typedef struct CTyVar CTyVar;
typedef struct CTyVarList CTyVarList;
typedef struct CTyCon CTyCon;
typedef struct CQualifiedTyCon CQualifiedTyCon;
typedef struct CLongTyCon CLongTyCon;
typedef struct CLab CLab;
typedef struct CStrId CStrId;
typedef struct CQualifiedStrId CQualifiedStrId;
typedef struct CLongStrId CLongStrId;
typedef struct CLongStrIdList CLongStrIdList;
typedef struct CConstant CConstant;
typedef struct CAtPat CAtPat;
typedef struct CAtPatList CAtPatList;
typedef struct CPatRow CPatRow;
typedef struct CPat CPat;
typedef struct CPatList CPatList;
typedef struct CTy CTy;
typedef struct CTyList CTyList;
typedef struct CTyRow CTyRow;
typedef struct CAtExp CAtExp;
typedef struct CAtExpList CAtExpList;
typedef struct CExpRow CExpRow;
typedef struct CExp CExp;
typedef struct CExpList CExpList;
typedef struct CMatch CMatch;
typedef struct CMrule CMrule;
typedef struct CDec CDec;
typedef struct CValBind CValBind;
typedef struct CFValBind CFValBind;
typedef struct CFMatch CFMatch;
typedef struct CFMrule CFMrule;
typedef struct CTypBind CTypBind;
typedef struct CDatBind CDatBind;
typedef struct CConBind CConBind;
typedef struct CExBind CExBind;

struct CVId {
  char *value;
};

struct CVIdList {
  CVId *vid;
  CVIdList *next;
};

struct CQualifiedVId {
  char *value;
};

typedef enum CLongVIdKind {
  CLONGVID_NONQUALIFIED,
  CLONGVID_QUALIFIED,
} CLongVIdKind;

struct CLongVId {
  CLongVIdKind kind;
  union {
    struct {
      CVId *vid;
    } nonqualified;
    struct {
      CQualifiedVId *qualified_vid;
    } qualified;
  } u;
};

struct CTyVar {
  char *value;
};

struct CTyVarList {
  CTyVar *tyvar;
  CTyVarList *next;
};

struct CTyCon {
  char *value;
};

struct CQualifiedTyCon {
  char *value;
};

typedef enum CLongTyConKind {
  CLONGTYCON_NONQUALIFIED,
  CLONGTYCON_QUALIFIED,
} CLongTyConKind;

struct CLongTyCon {
  CLongTyConKind kind;
  union {
    struct {
      CTyCon *tycon;
    } nonqualified;
    struct {
      CQualifiedTyCon *qualified_tycon;
    } qualified;
  } u;
};

typedef enum CLabKind {
  CLAB_ALPHANUMERIC,
  CLAB_NUMERIC,
} CLabKind;

struct CLab {
  CLabKind kind;
  char *value;
};

struct CStrId {
  char *value;
};

struct CQualifiedStrId {
  char *value;
};

typedef enum CLongStrIdKind {
  CLONGSTRID_NONQUALIFIED,
  CLONGSTRID_QUALIFIED,
} CLongStrIdKind;

struct CLongStrId {
  CLongStrIdKind kind;
  union {
    struct {
      CStrId *strid;
    } nonqualified;
    struct {
      CQualifiedStrId *qualified_strid;
    } qualified;
  } u;
};

struct CLongStrIdList {
  CLongStrId *longstrid;
  CLongStrIdList *next;
};

typedef enum CConstantKind {
  CCONSTANT_INTEGER,
} CConstantKind;

struct CConstant {
  CConstantKind kind;
  union {
    char *value;
  } u;
};

typedef enum CAtPatKind {
  CATPAT_WILDCARD,
  CATPAT_SPECIAL_CONSTANT,
  CATPAT_VALUE_IDENTIFIER,
  CATPAT_RECORD,
  CATPAT_ZERO_TUPLE,
  CATPAT_N_TUPLE,
  CATPAT_LIST,
  CATPAT_PARENED_PAT,
} CAtPatKind;

struct CAtPat {
  CAtPatKind kind;
  union {
    /* wildcard */
    struct {
      CConstant *scon;
    } special_constant;
    struct {
      bool op_prefixed;
      CLongVId *longvid;
    } value_identifier;
    struct {
      CPatRow *patrow;
    } record;
    /* zero tuple */
    struct {
      CPatList *patlist;
    } n_tuple;
    struct {
      CPatList *patlist;
    } list;
    struct {
      CPat *pat;
    } parened_pat;
  } u;
};

struct CAtPatList {
  CAtPat *atpat;
  CAtPatList *next;
};

typedef enum CPatRowKind {
  CPATROW_WILDCARD,
  CPATROW_PATTERN_ROW,
  CPATROW_LABEL_AS_VARIABLE,
} CPatRowKind;

struct CPatRow {
  CPatRowKind kind;
  union {
    /* wildcard */
    struct {
      CLab *lab;
      CPat *pat;
      CPatRow *next;
    } pattern_row;
    struct {
      CVId *vid;
      CTy *ty;
      CPat *pat;
      CPatRow *next;
    } label_as_variable;
  } u;
};

typedef enum CPatKind {
  CPAT_ATOMIC,
  CPAT_ATPATLIST,
  CPAT_TYPED,
  CPAT_LAYERED,
} CPatKind;

struct CPat {
  CPatKind kind;
  union {
    struct {
      CAtPat *atpat;
    } atomic;
    struct {
      CAtPatList *atpatlist;
    } atpatlist;
    struct {
      CPat *pat;
      CTy *ty;
    } typed;
    struct {
      bool op_prefixed;
      CVId *vid;
      CTy *ty;
      CPat *pat;
    } layered;
  } u;
};

struct CPatList {
  CPat *pat;
  CPatList *next;
};

typedef enum CTyKind {
  CTY_TYPE_VARIABLE,
  CTY_RECORD_TYPE_EXPRESSION,
  CTY_TYPE_CONSTRUCTION,
  CTY_TUPLE_TYPE,
  CTY_FUNCTION_TYPE_EXPRESSION,
  CTY_PARENED_TY,
} CTyKind;

struct CTy {
  CTyKind kind;
  union {
    struct {
      CTyVar *tyvar;
    } type_variable;
    struct {
      CTyRow *tyrow;
    } record_type_expression;
    struct {
      CTyList *tyseq;
      CLongTyCon *longtycon;
    } type_construction;
    struct {
      CTyList *tylist;
    } tuple_type;
    struct {
      CTy *arg_ty;
      CTy *res_ty;
    } function_type_expression;
    struct {
      CTy *ty;
    } parened_ty;
  } u;
};

struct CTyList {
  CTy *ty;
  CTyList *next;
};

struct CTyRow {
  CLab *lab;
  CTy *ty;
  CTyRow *next;
};

typedef enum CAtExpKind {
  CATEXP_SPECIAL_CONSTANT,
  CATEXP_VALUE_IDENTIFIER,
  CATEXP_RECORD,
  CATEXP_RECORD_SELECTOR,
  CATEXP_ZERO_TUPLE,
  CATEXP_N_TUPLE,
  CATEXP_LIST,
  CATEXP_SEQUENCE,
  CATEXP_LOCAL_DECLARATION,
  CATEXP_PARENED_EXP,
} CAtExpKind;

struct CAtExp {
  CAtExpKind kind;
  union {
    struct {
      CConstant *scon;
    } special_constant;
    struct {
      bool op_prefixed;
      CLongVId *longvid;
    } value_identifier;
    struct {
      CExpRow *exprow;
    } record;
    struct {
      CLab *lab;
    } record_selector;
    /* zero tuple */
    struct {
      CExpList *explist;
    } n_tuple;
    struct {
      CExpList *explist;
    } list;
    struct {
      CExpList *explist;
    } sequence;
    struct {
      CDec *dec;
      CExp *exp;
    } local_declaration;
    struct {
      CExp *exp;
    } parened_exp;
  } u;
};

struct CAtExpList {
  CAtExp *atexp;
  CAtExpList *next;
};

struct CExpRow {
  CLab *lab;
  CExp *exp;
  CExpRow *next;
};

typedef enum CExpKind {
  CEXP_ATOMIC,
  CEXP_ATEXPLIST,
  CEXP_TYPED,
  CEXP_CONJUNCTION,
  CEXP_DISJUNCTION,
  CEXP_HANDLE_EXCEPTION,
  CEXP_RAISE_EXCEPTION,
  CEXP_CONDITIONAL,
  CEXP_ITERATION,
  CEXP_CASE_ANALYSIS,
  CEXP_FUNCTION,
} CExpKind;

struct CExp {
  CExpKind kind;
  union {
    struct {
      CAtExp *atexp;
    } atomic;
    struct {
      CAtExpList *atexplist;
    } atexplist;
    struct {
      CExp *exp;
      CTy *ty;
    } typed;
    struct {
      CExp *exp1;
      CExp *exp2;
    } conjuction;
    struct {
      CExp *exp1;
      CExp *exp2;
    } disjuction;
    struct {
      CExp *exp;
      CMatch *match;
    } handle_exception;
    struct {
      CExp *exp;
    } raise_exception;
    struct {
      CExp *exp1;
      CExp *exp2;
      CExp *exp3;
    } conditional;
    struct {
      CExp *exp1;
      CExp *exp2;
    } iteration;
    struct {
      CExp *exp;
      CMatch *match;
    } case_analysis;
    struct {
      CMatch *match;
    } function;
  } u;
};

struct CExpList {
  CExp *exp;
  CExpList *next;
};

struct CMatch {
  CMrule *mrule;
  CMatch *next;
};

struct CMrule {
  CPat *pat;
  CExp *exp;
};

typedef enum CDecKind {
  CDEC_VALUE_DECLARATION,
  CDEC_FUNCTION_DECLARATION,
  CDEC_TYPE_DECLARATION,
  CDEC_DATATYPE_DECLARATION,
  CDEC_DATATYPE_REPLICATION,
  CDEC_ABSTYPE_DECLARATION,
  CDEC_EXCEPTION_DECLARATION,
  CDEC_LOCAL_DECLARATION,
  CDEC_OPEN_DECLARATION,
  CDEC_EMPTY_DECLARATION,
  CDEC_SEQUENTIAL_DECLARATION,
  CDEC_INFIX_L_DIRECTIVE,
  CDEC_INFIX_R_DIRECTIVE,
  CDEC_NONFIX_DIRECTIVE,
} CDecKind;

struct CDec {
  CDecKind kind;
  union {
    struct {
      CTyVarList *tyvarseq;
      CValBind *valbind;
    } value_declaration;
    struct {
      CTyVarList *tyvarseq;
      CFValBind *fvalbind;
    } function_declaration;
    struct {
      CTypBind *typbind;
    } type_declaration;
    struct {
      CDatBind *datbind;
      CTypBind *typbind;
    } datatype_declaration;
    struct {
      CTyCon *tycon;
      CLongTyCon *longtycon;
    } datatype_replication;
    struct {
      CDatBind *datbind;
      CTypBind *typbind;
      CDec *dec;
    } abstype_declaration;
    struct {
      CExBind *exbind;
    } exception_declaration;
    struct {
      CDec *dec1;
      CDec *dec2;
    } local_declaration;
    struct {
      CLongStrIdList *longstridlist;
    } open_declaration;
    struct {
      CDec *dec1;
      CDec *dec2;
    } sequential_declaration;
    struct {
      char *d;
      CVIdList *vidlist;
    } infix_l_directive;
    struct {
      char *d;
      CVIdList *vidlist;
    } infix_r_directive;
    struct {
      CVIdList *vidlist;
    } nonfix_directive;
  } u;
};

typedef enum CValBindKind {
  CVALBIND_BIND,
  CVALBIND_REC,
} CValBindKind;

struct CValBind {
  CValBindKind kind;
  union {
    struct {
      CPat *pat;
      CExp *exp;
      CValBind *next;
    } bind;
    struct {
      CValBind *valbind;
    } rec;
  } u;
};

struct CFMatch {
  CFMrule *fmrule;
  CFMatch *next;
};

struct CFMrule {
  CAtPatList *atpatlist;
  CTy *ty;
  CExp *exp;
};

struct CFValBind {
  CFMatch *fmatch;
  CFValBind *next;
};

struct CTypBind {
  CTyVarList *tyvarseq;
  CTyCon *tycon;
  CTy *ty;
  CTypBind *next;
};

struct CDatBind {
  CTyVarList *tyvarseq;
  CTyCon *tycon;
  CConBind *conbind;
  CDatBind *next;
};

struct CConBind {
  bool op_prefixed;
  CVId *vid;
  CTy *ty;
  CConBind *next;
};

typedef enum CExBindKind {
  CEXBIND_DECLARATION,
  CEXBIND_REPLICATION,
} CExBindKind;

struct CExBind {
  CExBindKind kind;
  union {
    struct {
      bool op_prefixed;
      CVId *vid;
      CTy *ty;
    } declaration;
    struct {
      bool op_prefixed_vid;
      CVId *vid;
      bool op_prefixed_longvid;
      CLongVId *longvid;
    } replication;
  } u;
  CExBind *next;
};

CVId *new_c_vid(char *value);
void free_c_vid(CVId *vid);
CVIdList *new_c_vidlist(CVId *vid, CVIdList *next);
void free_c_vidlist(CVIdList *vidlist);
CQualifiedVId *new_c_qualified_vid(char *value);
void free_c_qualified_vid(CQualifiedVId *qualified_vid);
CLongVId *new_c_longvid_nonqualified(CVId *vid);
CLongVId *new_c_longvid_qualified(CQualifiedVId *qualified_vid);
void free_c_longvid(CLongVId *longvid);
CTyVar *new_c_tyvar(char *value);
void free_c_tyvar(CTyVar *tyvar);
CTyVarList *new_c_tyvarlist(CTyVar *tyvar, CTyVarList *next);
void free_c_tyvarlist(CTyVarList *tyvarseq);
CTyCon *new_c_tycon(char *value);
void free_c_tycon(CTyCon *tycon);
CQualifiedTyCon *new_c_qualified_tycon(char *value);
void free_c_qualified_tycon(CQualifiedTyCon *qualified_tycon);
CLongTyCon *new_c_longtycon_nonqualified(CTyCon *tycon);
CLongTyCon *new_c_longtycon_qualified(CQualifiedTyCon *qualified_tycon);
void free_c_longtycon(CLongTyCon *longtycon);
CLab *new_c_lab_alphanumeric(char *value);
CLab *new_c_lab_numeric(char *value);
void free_c_lab(CLab *lab);
CStrId *new_c_strid(char *value);
void free_c_strid(CStrId *strid);
CQualifiedStrId *new_c_qualified_strid(char *value);
void free_c_qualified_strid(CQualifiedStrId *qualified_strid);
CLongStrId *new_c_longstrid_nonqualified(CStrId *strid);
CLongStrId *new_c_longstrid_qualified(CQualifiedStrId *qualified_strid);
void free_c_longstrid(CLongStrId *longstrid);
CLongStrIdList *new_c_longstridlist(CLongStrId *longstrid,
                                    CLongStrIdList *next);
void free_c_longstridlist(CLongStrIdList *longstridlist);
CConstant *new_c_constant_integer(char *value);
void free_c_constant(CConstant *constant);
CAtPat *new_c_atpat_wildcard(void);
CAtPat *new_c_atpat_special_constant(CConstant *scon);
CAtPat *new_c_atpat_value_identifier(bool op_prefixed, CLongVId *longvid);
CAtPat *new_c_atpat_record(CPatRow *patrow);
CAtPat *new_c_atpat_zero_tuple(void);
CAtPat *new_c_atpat_n_tuple(CPatList *patlist);
CAtPat *new_c_atpat_list(CPatList *patlist);
CAtPat *new_c_atpat_parened_pat(CPat *pat);
void free_c_atpat(CAtPat *atpat);
CAtPatList *new_c_atpatlist(CAtPat *atpat, CAtPatList *next);
void free_c_atpatlist(CAtPatList *atpatlist);
CPatRow *new_c_patrow_wildcard(void);
CPatRow *new_c_patrow_pattern_row(CLab *lab, CPat *pat, CPatRow *next);
void free_c_patrow(CPatRow *patrow);
CPat *new_c_pat_atomic(CAtPat *atpat);
CPat *new_c_pat_atpatlist(CAtPatList *list);
CPat *new_c_pat_typed(CPat *pat, CTy *ty);
CPat *new_c_pat_layered(bool op_prefixed, CVId *vid, CTy *ty, CPat *pat);
void free_c_pat(CPat *pat);
CPatList *new_c_patlist(CPat *pat, CPatList *next);
void free_c_patlist(CPatList *patlist);
CTy *new_c_ty_type_variable(CTyVar *tyvar);
CTy *new_c_ty_record_type_expression(CTyRow *tyrow);
CTy *new_c_ty_type_construction(CTyList *tyseq, CLongTyCon *longtycon);
CTy *new_c_ty_tuple_type(CTyList *tylist);
CTy *new_c_ty_function_type_expression(CTy *arg_ty, CTy *res_ty);
CTy *new_c_ty_parened_ty(CTy *ty);
void free_c_ty(CTy *ty);
CTyList *new_c_tylist(CTy *ty, CTyList *next);
void free_c_tylist(CTyList *tylist);
CTyRow *new_c_tyrow(CLab *lab, CTy *ty, CTyRow *next);
void free_c_tyrow(CTyRow *tyrow);
CAtExp *new_c_atexp_special_constant(CConstant *scon);
CAtExp *new_c_atexp_value_identifier(bool op_prefixed, CLongVId *longvid);
CAtExp *new_c_atexp_record(CExpRow *exprow);
CAtExp *new_c_atexp_record_selector(CLab *lab);
CAtExp *new_c_atexp_zero_tuple(void);
CAtExp *new_c_atexp_n_tuple(CExpList *explist);
CAtExp *new_c_atexp_list(CExpList *explist);
CAtExp *new_c_atexp_sequence(CExpList *explist);
CAtExp *new_c_atexp_local_declaration(CDec *dec, CExp *exp);
CAtExp *new_c_atexp_parened_exp(CExp *exp);
void free_c_atexp(CAtExp *atexp);
CAtExpList *new_c_atexplist(CAtExp *atexp, CAtExpList *next);
void free_c_atexplist(CAtExpList *atexplist);
CExpRow *new_c_exprow(CLab *lab, CExp *exp, CExpRow *next);
void free_c_exprow(CExpRow *exprow);
CExp *new_c_exp_atomic(CAtExp *atexp);
CExp *new_c_exp_atexplist(CAtExpList *atexplist);
CExp *new_c_exp_typed(CExp *exp, CTy *ty);
CExp *new_c_exp_conjunction(CExp *exp1, CExp *exp2);
CExp *new_c_exp_disjunction(CExp *exp1, CExp *exp2);
CExp *new_c_exp_handle_exception(CExp *exp, CMatch *match);
CExp *new_c_exp_raise_exception(CExp *exp);
CExp *new_c_exp_conditional(CExp *exp1, CExp *exp2, CExp *exp3);
CExp *new_c_exp_iteration(CExp *exp1, CExp *exp2);
CExp *new_c_exp_case_analysis(CExp *exp, CMatch *match);
CExp *new_c_exp_function(CMatch *match);
void free_c_exp(CExp *exp);
CExpList *new_c_explist(CExp *exp, CExpList *next);
void free_c_explist(CExpList *explist);
CMatch *new_c_match(CMrule *mrule, CMatch *next);
void free_c_match(CMatch *match);
CMrule *new_c_mrule(CPat *pat, CExp *exp);
void free_c_mrule(CMrule *mrule);
CDec *new_c_dec_value_declaration(CTyVarList *tyvarseq, CValBind *valbind);
CDec *new_c_dec_function_declaration(CTyVarList *tyvarseq, CFValBind *fvalbind);
CDec *new_c_dec_type_declaration(CTypBind *typbind);
CDec *new_c_dec_datatype_declaration(CDatBind *datbind, CTypBind *typbind);
CDec *new_c_dec_datatype_replication(CTyCon *tycon, CLongTyCon *longtycon);
CDec *new_c_dec_abstype_declaration(CDatBind *datbind, CTypBind *typbind,
                                    CDec *dec);
CDec *new_c_dec_exception_declaration(CExBind *exbind);
CDec *new_c_dec_local_declaration(CDec *dec1, CDec *dec2);
CDec *new_c_dec_open_declaration(CLongStrIdList *longstridlist);
CDec *new_c_dec_sequential_declaration(CDec *dec1, CDec *dec2);
CDec *new_c_dec_infix_l_directive(char *d, CVIdList *vidlist);
CDec *new_c_dec_infix_r_directive(char *d, CVIdList *vidlist);
CDec *new_c_dec_nonfix_directive(CVIdList *vidlist);
void free_c_dec(CDec *dec);
CValBind *new_c_valbind_bind(CPat *pat, CExp *exp, CValBind *next);
CValBind *new_c_valbind_rec(CValBind *valbind);
void free_c_valbind(CValBind *valbind);
CFMatch *new_c_fmatch(CFMrule *fmrule, CFMatch *next);
void free_c_fmatch(CFMatch *fmatch);
CFMrule *new_c_fmrule(CAtPatList *atpatlist, CTy *ty, CExp *exp);
void free_c_fmrule(CFMrule *fmrule);
CFValBind *new_c_fvalbind(CFMatch *fmatch, CFValBind *next);
void free_c_fvalbind(CFValBind *fvalbind);
CTypBind *new_c_typbind(CTyVarList *tyvarseq, CTyCon *tycon, CTy *ty,
                        CTypBind *next);
void free_c_typbind(CTypBind *typbind);
CDatBind *new_c_datbind(CTyVarList *tyvarseq, CTyCon *tycon, CConBind *conbind,
                        CDatBind *next);
void free_c_datbind(CDatBind *datbind);
CConBind *new_c_conbind(bool op_prefixed, CVId *vid, CTy *ty, CConBind *next);
void free_c_conbind(CConBind *conbind);
CExBind *new_c_exbind_declaration(bool op_prefixed, CVId *vid, CTy *ty,
                                  CExBind *next);
CExBind *new_c_exbind_replication(bool op_prefixed_vid, CVId *vid,
                                  bool op_prefixed_longvid, CLongVId *longvid,
                                  CExBind *next);
void free_c_exbind(CExBind *exbind);
#endif // CONCRETE_SYNTAX_H
