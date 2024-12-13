#ifndef SYNTAX_H
#define SYNTAX_H

struct VId;
typedef struct VId VId;
struct VIdList;
typedef struct VIdList VIdList;
struct LongVId;
typedef struct LongVId LongVId;
struct TyVar;
typedef struct TyVar TyVar;
struct TyVarSeq;
typedef struct TyVarSeq TyVarSeq;
struct TyCon;
typedef struct TyCon TyCon;
struct LongTyCon;
typedef struct LongTyCon LongTyCon;
struct Lab;
typedef struct Lab Lab;
struct StrId;
typedef struct StrId StrId;
struct StrIdList;
typedef struct StrIdList StrIdList;
struct LongStrId;
typedef struct LongStrId LongStrId;
struct LongStrIdList;
typedef struct LongStrIdList LongStrIdList;
struct Constant;
typedef struct Constant Constant;
struct AtPat;
typedef struct AtPat AtPat;
struct PatRow;
typedef struct PatRow PatRow;
struct Pat;
typedef struct Pat Pat;
struct Ty;
typedef struct Ty Ty;
struct TySeq;
typedef struct TySeq TySeq;
struct TyRow;
typedef struct TyRow TyRow;
struct AtExp;
typedef struct AtExp AtExp;
struct ExpRow;
typedef struct ExpRow ExpRow;
struct Exp;
typedef struct Exp Exp;
struct Match;
typedef struct Match Match;
struct Mrule;
typedef struct Mrule Mrule;
struct Dec;
typedef struct Dec Dec;
struct ValBind;
typedef struct ValBind ValBind;
struct TypBind;
typedef struct TypBind TypBind;
struct DatBind;
typedef struct DatBind DatBind;
struct ConBind;
typedef struct ConBind ConBind;
struct ExBind;
typedef struct ExBind ExBind;

typedef struct VId {
  char *value;
} VId;

typedef struct VIdList {
  VId *vid;
  VIdList *next;
} VIdList;

typedef enum LongVIdKind {
  LONGVID_NONQUALIFIED,
  LONGVID_QUALIFIED,
} LongVIdKind;

typedef struct LongVId {
  LongVIdKind kind;
  union {
    struct {
      VId *vid;
    } nonqualified;
    struct {
      StrIdList *strids;
      VId *vid;
    } qualified;
  } u;
} LongVId;

typedef struct TyVar {
  char *value;
} TyVar;

typedef struct TyVarSeq {
  TyVar *tyvar;
  TyVarSeq *next;
} TyVarSeq;

typedef struct TyCon {
  char *value;
} TyCon;

typedef enum LongTyConKind {
  LONGTYCON_NONQUALIFIED,
  LONGTYCON_QUALIFIED,
} LongTyConKind;

typedef struct LongTyCon {
  LongTyConKind kind;
  union {
    struct {
      TyCon *tycon;
    } nonqualified;
    struct {
      StrIdList *strids;
      TyCon *tycon;
    } qualified;
  } u;
} LongTyCon;

typedef enum LabKind {
  LAB_ALPHANUMERIC,
  LAB_NUMERIC,
} LabKind;

typedef struct Lab {
  LabKind kind;
  char *value;
} Lab;

typedef struct StrId {
  char *value;
} StrId;

typedef struct StrIdList {
  StrIdList *upper;
  StrId *strid;
} StrIdList;

typedef enum LongStrIdKind {
  LONGSTRID_NONQUALIFIED,
  LONGSTRID_QUALIFIED,
} LongStrIdKind;

typedef struct LongStrId {
  LongStrIdKind kind;
  union {
    struct {
      StrId *strid;
    } nonqualified;
    struct {
      StrIdList *strids;
      StrId *strid;
    } qualified;
  } u;
} LongStrId;

typedef struct LongStrIdList {
  LongStrId *longstrid;
  LongStrIdList *next;
} LongStrIdList;

typedef enum ConstantKind {
  CONSTANT_INTEGER,
} ConstantKind;

typedef struct Constant {
  ConstantKind kind;
  union {
    char *value;
  } u;
} Constant;

typedef enum AtPatKind {
  ATPAT_WILDCARD,
  ATPAT_SPECIAL_CONSTANT,
  ATPAT_VALUE_IDENTIFIER,
  ATPAT_RECORD,
  ATPAT_PARENED_PAT,
} AtPatKind;

typedef struct AtPat {
  AtPatKind kind;
  union {
    /* wildcard */
    struct {
      Constant *scon;
    } special_constant;
    struct {
      int op_prefixed;
      LongVId *longvid;
    } value_identifier;
    struct {
      PatRow *patrow;
    } record;
    struct {
      Pat *pat;
    } parened_pat;
  } u;
} AtPat;

typedef enum PatRowKind {
  PATROW_WILDCARD,
  PATROW_PATTERN_ROW,
} PatRowKind;

typedef struct PatRow {
  PatRowKind kind;
  union {
    /* wildcard */
    struct {
      Lab *lab;
      Pat *pat;
      PatRow *next;
    } pattern_row;
  } u;
} PatRow;

typedef enum PatKind {
  PAT_ATOMIC,
  PAT_CONSTRUCTED_PATTERN,
  PAT_INFIXED_VALUE_CONSTRUCTION,
  PAT_TYPED,
  PAT_LAYERED,
} PatKind;

typedef struct Pat {
  PatKind kind;
  union {
    struct {
      AtPat *atpat;
    } atomic;
    struct {
      int op_prefixed;
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
      int op_prefixed;
      VId *vid;
      Ty *ty;
      Pat *pat;
    } layered;
  } u;
} Pat;

typedef enum TyKind {
  TY_TYPE_VARIABLE,
  TY_RECORD_TYPE_EXPRESSION,
  TY_TYPE_CONSTRUCTION,
  TY_FUNCTION_TYPE_EXPRESSION,
  TY_PARENED_TY,
} TyKind;

typedef struct Ty {
  TyKind kind;
  union {
    struct {
      TyVar *tyvar;
    } type_variable;
    struct {
      TyRow *tyrow;
    } record_type_expression;
    struct {
      TySeq *tyseq;
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
} Ty;

typedef struct TySeq {
  Ty *ty;
  TySeq *next;
} TySeq;

typedef struct TyRow {
  Lab *lab;
  Ty *ty;
  TyRow *next;
} TyRow;

typedef enum AtExpKind {
  ATEXP_SPECIAL_CONSTANT,
  ATEXP_VALUE_IDENTIFIER,
  ATEXP_RECORD,
  ATEXP_LOCAL_DECLARATION,
  ATEXP_PARENED_EXP,
} AtExpKind;

typedef struct AtExp {
  AtExpKind kind;
  union {
    struct {
      Constant *scon;
    } special_constant;
    struct {
      int op_prefixed;
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
} AtExp;

typedef struct ExpRow {
  Lab *lab;
  Exp *exp;
  ExpRow *next;
} ExpRow;

typedef enum ExpKind {
  EXP_ATOMIC,
  EXP_APPLICATION,
  EXP_INFIXED_APPLICATION,
  EXP_TYPED,
  EXP_HANDLE_EXCEPTION,
  EXP_RAISE_EXCEPTION,
  EXP_FUNCTION,
} ExpKind;

typedef struct Exp {
  ExpKind kind;
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
} Exp;

typedef struct Match {
  Mrule *mrule;
  Match *next;
} Match;

typedef struct Mrule {
  Pat *pat;
  Exp *exp;
} Mrule;

typedef enum DecKind {
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
} DecKind;

typedef struct Dec {
  DecKind kind;
  union {
    struct {
      TyVarSeq *tyvarseq;
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
} Dec;

typedef enum ValBindKind {
  VALBIND_BIND,
  VALBIND_REC,
} ValBindKind;

typedef struct ValBind {
  ValBindKind kind;
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
} ValBind;

typedef struct TypBind {
  TyVarSeq *tyvarseq;
  TyCon *tycon;
  Ty *ty;
  TypBind *next;
} TypBind;

typedef struct DatBind {
  TyVarSeq *tyvarseq;
  TyCon *tycon;
  ConBind *conbind;
  DatBind *next;
} DatBind;

typedef struct ConBind {
  int op_prefixed;
  VId *vid;
  Ty *ty;
  ConBind *next;
} ConBind;

typedef enum ExBindKind {
  EXBIND_DECLARATION,
  EXBIND_REPLICATION,
} ExBindKind;

typedef struct ExBind {
  ExBindKind kind;
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
} ExBind;

VId *new_vid(char *value);
void free_vid(VId *vid);
VIdList *new_vidlist(VId *vid, VIdList *next);
void free_vidlist(VIdList *vidlist);
LongVId *new_longvid_nonqualified(VId *vid);
LongVId *new_longvid_qualified(StrIdList *strids, VId *vid);
void free_longvid(LongVId *longvid);
TyVar *new_tyvar(char *value);
void free_tyvar(TyVar *tyvar);
TyVarSeq *new_tyvarseq(TyVar *tyvar, TyVarSeq *next);
void free_tyvarseq(TyVarSeq *tyvarseq);
TyCon *new_tycon(char *value);
void free_tycon(TyCon *tycon);
LongTyCon *new_longtycon_nonqualified(TyCon *tycon);
LongTyCon *new_longtycon_qualified(StrIdList *strids, TyCon *tycon);
void free_longtycon(LongTyCon *longtycon);
Lab *new_lab_alphanumeric(char *value);
Lab *new_lab_numeric(char *value);
void free_lab(Lab *lab);
StrId *new_strid(char *value);
void free_strid(StrId *strid);
StrIdList *new_stridlist(StrIdList *upper, StrId *strid);
void free_stridlist(StrIdList *stridlist);
LongStrId *new_longstrid_nonqualified(StrId *strid);
LongStrId *new_longstrid_qualified(StrIdList *strids, StrId *strid);
void free_longstrid(LongStrId *longstrid);
LongStrIdList *new_longstridlist(LongStrId *longstrid, LongStrIdList *next);
void free_longstridlist(LongStrIdList *longstridlist);
Constant *new_constant_integer(char *value);
void free_constant(Constant *constant);
AtPat *new_atpat_wildcard(void);
AtPat *new_atpat_special_constant(Constant *scon);
AtPat *new_atpat_value_identifier(int op_prefixed, LongVId *longvid);
AtPat *new_atpat_record(PatRow *patrow);
AtPat *new_atpat_parened_pat(Pat *pat);
void free_atpat(AtPat *atpat);
PatRow *new_patrow_wildcard(void);
PatRow *new_patrow_pattern_row(Lab *lab, Pat *pat, PatRow *next);
void free_patrow(PatRow *patrow);
Pat *new_pat_atomic(AtPat *atpat);
Pat *new_pat_constructed_pattern(int op_prefixed, LongVId *longvid,
                                 AtPat *atpat);
Pat *new_pat_infixed_value_construction(Pat *pat1, VId *vid, Pat *pat2);
Pat *new_pat_typed(Pat *pat, Ty *ty);
Pat *new_pat_layered(int op_prefixed, VId *vid, Ty *ty, Pat *pat);
void free_pat(Pat *pat);
Ty *new_ty_type_variable(TyVar *tyvar);
Ty *new_ty_record_type_expression(TyRow *tyrow);
Ty *new_ty_type_construction(TySeq *tyseq, LongTyCon *longtycon);
Ty *new_ty_function_type_expression(Ty *arg_ty, Ty *res_ty);
Ty *new_ty_parened_ty(Ty *ty);
void free_ty(Ty *ty);
TySeq *new_tyseq(Ty *ty, TySeq *next);
void free_tyseq(TySeq *tyseq);
TyRow *new_tyrow(Lab *lab, Ty *ty, TyRow *next);
void free_tyrow(TyRow *tyrow);
AtExp *new_atexp_special_constant(Constant *scon);
AtExp *new_atexp_value_identifier(int op_prefixed, LongVId *longvid);
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
Dec *new_dec_value_declaration(TyVarSeq *tyvarseq, ValBind *valbind);
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
TypBind *new_typbind(TyVarSeq *tyvarseq, TyCon *tycon, Ty *ty, TypBind *next);
void free_typbind(TypBind *typbind);
DatBind *new_datbind(TyVarSeq *tyvarseq, TyCon *tycon, ConBind *conbind,
                     DatBind *next);
void free_datbind(DatBind *datbind);
ConBind *new_conbind(int op_prefixed, VId *vid, Ty *ty, ConBind *next);
void free_conbind(ConBind *conbind);
ExBind *new_exbind_declaration(int op_prefixed, VId *vid, Ty *ty, ExBind *next);
ExBind *new_exbind_replication(int op_prefixed_vid, VId *vid,
                               int op_prefixed_longvid, LongVId *longvid,
                               ExBind *next);
void free_exbind(ExBind *exbind);
#endif // SYNTAX_H
