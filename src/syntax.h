#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdbool.h>

typedef struct VId VId;
typedef struct VIdList VIdList;
typedef struct LongVId LongVId;
typedef struct TyVar TyVar;
typedef struct TyVarList TyVarList;
typedef struct TyCon TyCon;
typedef struct LongTyCon LongTyCon;
typedef struct Lab Lab;
typedef struct StrId StrId;
typedef struct StrIdList StrIdList;
typedef struct LongStrId LongStrId;
typedef struct LongStrIdList LongStrIdList;
typedef struct Constant Constant;
typedef struct AtPat AtPat;
typedef struct PatRow PatRow;
typedef struct Pat Pat;
typedef struct Ty Ty;
typedef struct TyList TyList;
typedef struct TyRow TyRow;
typedef struct AtExp AtExp;
typedef struct ExpRow ExpRow;
typedef struct Exp Exp;
typedef struct Match Match;
typedef struct Mrule Mrule;
typedef struct Dec Dec;
typedef struct ValBind ValBind;
typedef struct TypBind TypBind;
typedef struct DatBind DatBind;
typedef struct ConBind ConBind;
typedef struct ExBind ExBind;

struct VId {
  char *value;
};

struct VIdList {
  VId *vid;
  VIdList *next;
};

struct LongVId {
  enum {
    LONGVID_NONQUALIFIED,
    LONGVID_QUALIFIED,
  } kind;
  union {
    struct {
      VId *vid;
    } nonqualified;
    struct {
      StrIdList *stridlist;
      VId *vid;
    } qualified;
  } u;
};

struct TyVar {
  char *value;
};

struct TyVarList {
  TyVar *tyvar;
  TyVarList *next;
};

struct TyCon {
  char *value;
};

struct LongTyCon {
  enum {
    LONGTYCON_NONQUALIFIED,
    LONGTYCON_QUALIFIED,
  } kind;
  union {
    struct {
      TyCon *tycon;
    } nonqualified;
    struct {
      StrIdList *stridlist;
      TyCon *tycon;
    } qualified;
  } u;
};

struct Lab {
  enum {
    LAB_ALPHANUMERIC,
    LAB_NUMERIC,
  } kind;
  union {
    struct {
      char *value;
    } alphanumeric;
    struct {
      int value;
    } numeric;
  } u;
};

struct StrId {
  char *value;
};

struct StrIdList {
  StrId *strid;
  StrIdList *next;
};

struct LongStrId {
  enum {
    LONGSTRID_NONQUALIFIED,
    LONGSTRID_QUALIFIED,
  } kind;
  union {
    struct {
      StrId *strid;
    } nonqualified;
    struct {
      StrIdList *stridlist;
      StrId *strid;
    } qualified;
  } u;
};

struct LongStrIdList {
  LongStrId *longstrid;
  LongStrIdList *next;
};

struct Constant {
  enum {
    CONSTANT_INTEGER,
  } kind;
  union {
    struct {
      int value;
    } integer;
  } u;
};

struct AtPat {
  enum {
    ATPAT_WILDCARD,
    ATPAT_SPECIAL_CONSTANT,
    ATPAT_VALUE_IDENTIFIER,
    ATPAT_RECORD,
    ATPAT_PARENED_PAT,
  } kind;
  union {
    /* wildcard */
    struct {
      Constant *scon;
    } special_constant;
    struct {
      bool op_prefixed;
      LongVId *longvid;
    } value_identifier;
    struct {
      PatRow *patrow;
    } record;
    struct {
      Pat *pat;
    } parened_pat;
  } u;
};

struct PatRow {
  enum {
    PATROW_WILDCARD,
    PATROW_PATTERN_ROW,
  } kind;
  union {
    /* wildcard */
    struct {
      Lab *lab;
      Pat *pat;
      PatRow *next;
    } pattern_row;
  } u;
};

struct Pat {
  enum {
    PAT_ATOMIC,
    PAT_CONSTRUCTED_PATTERN,
    PAT_INFIXED_VALUE_CONSTRUCTION,
    PAT_TYPED,
    PAT_LAYERED,
  } kind;
  union {
    struct {
      AtPat *atpat;
    } atomic;
    struct {
      bool op_prefixed;
      LongVId *longvid;
      AtPat *atpat;
    } constructed_pattern;
    struct {
      Pat *pat1;
      VId *vid;
      Pat *pat2;
    } infixed_value_construction;
    struct {
      Pat *pat;
      Ty *ty;
    } typed;
    struct {
      bool op_prefixed;
      VId *vid;
      Ty *ty;
      Pat *pat;
    } layered;
  } u;
};

struct Ty {
  enum {
    TY_TYPE_VARIABLE,
    TY_RECORD_TYPE_EXPRESSION,
    TY_TYPE_CONSTRUCTION,
    TY_FUNCTION_TYPE_EXPRESSION,
    TY_PARENED_TY,
  } kind;
  union {
    struct {
      TyVar *tyvar;
    } type_variable;
    struct {
      TyRow *tyrow;
    } record_type_expression;
    struct {
      TyList *tylist;
      LongTyCon *longtycon;
    } type_construction;
    struct {
      Ty *arg_ty;
      Ty *res_ty;
    } function_type_expression;
    struct {
      Ty *ty;
    } parened_ty;
  } u;
};

struct TyList {
  Ty *ty;
  TyList *next;
};

struct TyRow {
  Lab *lab;
  Ty *ty;
  TyRow *next;
};

struct AtExp {
  enum {
    ATEXP_SPECIAL_CONSTANT,
    ATEXP_VALUE_IDENTIFIER,
    ATEXP_RECORD,
    ATEXP_LOCAL_DECLARATION,
    ATEXP_PARENED_EXP,
  } kind;
  union {
    struct {
      Constant *scon;
    } special_constant;
    struct {
      bool op_prefixed;
      LongVId *longvid;
    } value_identifier;
    struct {
      ExpRow *exprow;
    } record;
    struct {
      Dec *dec;
      Exp *exp;
    } local_declaration;
    struct {
      Exp *exp;
    } parened_exp;
  } u;
};

struct ExpRow {
  Lab *lab;
  Exp *exp;
  ExpRow *next;
};

struct Exp {
  enum {
    EXP_ATOMIC,
    EXP_APPLICATION,
    EXP_INFIXED_APPLICATION,
    EXP_TYPED,
    EXP_HANDLE_EXCEPTION,
    EXP_RAISE_EXCEPTION,
    EXP_FUNCTION,
  } kind;
  union {
    struct {
      AtExp *atexp;
    } atomic;
    struct {
      Exp *exp;
      AtExp *atexp;
    } application;
    struct {
      Exp *exp1;
      VId *vid;
      Exp *exp2;
    } infixed_application;
    struct {
      Exp *exp;
      Ty *ty;
    } typed;
    struct {
      Exp *exp;
      Match *match;
    } handle_exception;
    struct {
      Exp *exp;
    } raise_exception;
    struct {
      Match *match;
    } function;
  } u;
};

struct Match {
  Mrule *mrule;
  Match *next;
};

struct Mrule {
  Pat *pat;
  Exp *exp;
};

struct Dec {
  enum {
    DEC_VALUE_DECLARATION,
    DEC_TYPE_DECLARATION,
    DEC_DATATYPE_DECLARATION,
    DEC_DATATYPE_REPLICATION,
    DEC_ABSTYPE_DECLARATION,
    DEC_EXCEPTION_DECLARATION,
    DEC_LOCAL_DECLARATION,
    DEC_OPEN_DECLARATION,
    DEC_EMPTY_DECLARATION,
    DEC_SEQUENTIAL_DECLARATION,
    DEC_INFIX_L_DIRECTIVE,
    DEC_INFIX_R_DIRECTIVE,
    DEC_NONFIX_DIRECTIVE,
  } kind;
  union {
    struct {
      TyVarList *tyvarlist;
      ValBind *valbind;
    } value_declaration;
    struct {
      TypBind *typbind;
    } type_declaration;
    struct {
      DatBind *datbind;
    } datatype_declaration;
    struct {
      TyCon *tycon;
      LongTyCon *longtycon;
    } datatype_replication;
    struct {
      DatBind *datbind;
      Dec *dec;
    } abstype_declaration;
    struct {
      ExBind *exbind;
    } exception_declaration;
    struct {
      Dec *dec1;
      Dec *dec2;
    } local_declaration;
    struct {
      LongStrIdList *longstridlist;
    } open_declaration;
    struct {
      Dec *dec1;
      Dec *dec2;
    } sequential_declaration;
    struct {
      char *d;
      VIdList *vidlist;
    } infix_l_directive;
    struct {
      char *d;
      VIdList *vidlist;
    } infix_r_directive;
    struct {
      VIdList *vidlist;
    } nonfix_directive;
  } u;
};

struct ValBind {
  enum {
    VALBIND_BIND,
    VALBIND_REC,
  } kind;
  union {
    struct {
      Pat *pat;
      Exp *exp;
      ValBind *next;
    } bind;
    struct {
      ValBind *valbind;
    } rec;
  } u;
};

struct TypBind {
  TyVarList *tyvarlist;
  TyCon *tycon;
  Ty *ty;
  TypBind *next;
};

struct DatBind {
  TyVarList *tyvarlist;
  TyCon *tycon;
  ConBind *conbind;
  DatBind *next;
};

struct ConBind {
  bool op_prefixed;
  VId *vid;
  Ty *ty;
  ConBind *next;
};

struct ExBind {
  enum {
    EXBIND_DECLARATION,
    EXBIND_REPLICATION,
  } kind;
  union {
    struct {
      int op_prefixed;
      VId *vid;
      Ty *ty;
    } declaration;
    struct {
      int op_prefixed_vid;
      VId *vid;
      int op_prefixed_longvid;
      LongVId *longvid;
    } replication;
  } u;
  ExBind *next;
};

VId *new_vid(char *value);
void free_vid(VId *vid);
VIdList *new_vidlist(VId *vid, VIdList *next);
void free_vidlist(VIdList *vidlist);
LongVId *new_longvid_nonqualified(VId *vid);
LongVId *new_longvid_qualified(StrIdList *stridlist, VId *vid);
void free_longvid(LongVId *longvid);
TyVar *new_tyvar(char *value);
void free_tyvar(TyVar *tyvar);
TyVarList *new_tyvarlist(TyVar *tyvar, TyVarList *next);
void free_tyvarlist(TyVarList *tyvarlist);
TyCon *new_tycon(char *value);
void free_tycon(TyCon *tycon);
LongTyCon *new_longtycon_nonqualified(TyCon *tycon);
LongTyCon *new_longtycon_qualified(StrIdList *stridlist, TyCon *tycon);
void free_longtycon(LongTyCon *longtycon);
Lab *new_lab_alphanumeric(char *value);
Lab *new_lab_numeric(int value);
void free_lab(Lab *lab);
StrId *new_strid(char *value);
void free_strid(StrId *strid);
StrIdList *new_stridlist(StrId *strid, StrIdList *next);
void free_stridlist(StrIdList *stridlist);
LongStrId *new_longstrid_nonqualified(StrId *strid);
LongStrId *new_longstrid_qualified(StrIdList *stridlist, StrId *strid);
void free_longstrid(LongStrId *longstrid);
LongStrIdList *new_longstridlist(LongStrId *longstrid, LongStrIdList *next);
void free_longstridlist(LongStrIdList *longstridlist);
Constant *new_constant_integer(int value);
void free_constant(Constant *constant);
AtPat *new_atpat_wildcard(void);
AtPat *new_atpat_special_constant(Constant *scon);
AtPat *new_atpat_value_identifier(bool op_prefixed, LongVId *longvid);
AtPat *new_atpat_record(PatRow *patrow);
AtPat *new_atpat_parened_pat(Pat *pat);
void free_atpat(AtPat *atpat);
PatRow *new_patrow_wildcard(void);
PatRow *new_patrow_pattern_row(Lab *lab, Pat *pat, PatRow *next);
void free_patrow(PatRow *patrow);
Pat *new_pat_atomic(AtPat *atpat);
Pat *new_pat_constructed_pattern(bool op_prefixed, LongVId *longvid,
                                 AtPat *atpat);
Pat *new_pat_infixed_value_construction(Pat *pat1, VId *vid, Pat *pat2);
Pat *new_pat_typed(Pat *pat, Ty *ty);
Pat *new_pat_layered(bool op_prefixed, VId *vid, Ty *ty, Pat *pat);
void free_pat(Pat *pat);
Ty *new_ty_type_variable(TyVar *tyvar);
Ty *new_ty_record_type_expression(TyRow *tyrow);
Ty *new_ty_type_construction(TyList *tylist, LongTyCon *longtycon);
Ty *new_ty_function_type_expression(Ty *arg_ty, Ty *res_ty);
Ty *new_ty_parened_ty(Ty *ty);
void free_ty(Ty *ty);
TyList *new_tylist(Ty *ty, TyList *next);
void free_tylist(TyList *tylist);
TyRow *new_tyrow(Lab *lab, Ty *ty, TyRow *next);
void free_tyrow(TyRow *tyrow);
AtExp *new_atexp_special_constant(Constant *scon);
AtExp *new_atexp_value_identifier(bool op_prefixed, LongVId *longvid);
AtExp *new_atexp_record(ExpRow *exprow);
AtExp *new_atexp_local_declaration(Dec *dec, Exp *exp);
AtExp *new_atexp_parened_exp(Exp *exp);
void free_atexp(AtExp *atexp);
ExpRow *new_exprow(Lab *lab, Exp *exp, ExpRow *next);
void free_exprow(ExpRow *exprow);
Exp *new_exp_atomic(AtExp *atexp);
Exp *new_exp_application(Exp *exp, AtExp *atexp);
Exp *new_exp_infixed_application(Exp *exp1, VId *vid, Exp *exp2);
Exp *new_exp_typed(Exp *exp, Ty *ty);
Exp *new_exp_handle_exception(Exp *exp, Match *match);
Exp *new_exp_raise_exception(Exp *exp);
Exp *new_exp_function(Match *match);
void free_exp(Exp *exp);
Match *new_match(Mrule *mrule, Match *next);
void free_match(Match *match);
Mrule *new_mrule(Pat *pat, Exp *exp);
void free_mrule(Mrule *mrule);
Dec *new_dec_value_declaration(TyVarList *tyvarlist, ValBind *valbind);
Dec *new_dec_type_declaration(TypBind *typbind);
Dec *new_dec_datatype_declaration(DatBind *datbind);
Dec *new_dec_datatype_replication(TyCon *tycon, LongTyCon *longtycon);
Dec *new_dec_abstype_declaration(DatBind *datbind, Dec *dec);
Dec *new_dec_exception_declaration(ExBind *exbind);
Dec *new_dec_local_declaration(Dec *dec1, Dec *dec2);
Dec *new_dec_open_declaration(LongStrIdList *longstridlist);
Dec *new_dec_sequential_declaration(Dec *dec1, Dec *dec2);
Dec *new_dec_infix_l_directive(char *d, VIdList *vidlist);
Dec *new_dec_infix_r_directive(char *d, VIdList *vidlist);
Dec *new_dec_nonfix_directive(VIdList *vidlist);
void free_dec(Dec *dec);
ValBind *new_valbind_bind(Pat *pat, Exp *exp, ValBind *next);
ValBind *new_valbind_rec(ValBind *valbind);
void free_valbind(ValBind *valbind);
TypBind *new_typbind(TyVarList *tyvarlist, TyCon *tycon, Ty *ty, TypBind *next);
void free_typbind(TypBind *typbind);
DatBind *new_datbind(TyVarList *tyvarlist, TyCon *tycon, ConBind *conbind,
                     DatBind *next);
void free_datbind(DatBind *datbind);
ConBind *new_conbind(bool op_prefixed, VId *vid, Ty *ty, ConBind *next);
void free_conbind(ConBind *conbind);
ExBind *new_exbind_declaration(bool op_prefixed, VId *vid, Ty *ty,
                               ExBind *next);
ExBind *new_exbind_replication(bool op_prefixed_vid, VId *vid,
                               bool op_prefixed_longvid, LongVId *longvid,
                               ExBind *next);
void free_exbind(ExBind *exbind);
#endif // SYNTAX_H
