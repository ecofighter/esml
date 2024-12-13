#include <stdlib.h>

#include "syntax.h"

VId *new_vid(char *value) {
  VId *vid = (VId *)malloc(sizeof(VId));
  vid->value = value;
  return vid;
}

void free_vid(VId *vid) {
  free(vid->value);
  free(vid);
}

VIdList *new_vidlist(VId *vid, VIdList *next) {
  VIdList *vidlist = (VIdList *)malloc(sizeof(VIdList));
  vidlist->vid = vid;
  vidlist->next = next;
  return vidlist;
}

void free_vidlist(VIdList *vidlist) {
  if (vidlist->next != NULL) {
    free_vidlist(vidlist->next);
  }
  free_vid(vidlist->vid);
  free(vidlist);
}

LongVId *new_longvid_nonqualified(VId *vid) {
  LongVId *longvid = (LongVId *)malloc(sizeof(LongVId));
  longvid->kind = LONGVID_NONQUALIFIED;
  longvid->u.nonqualified.vid = vid;
  return longvid;
}

LongVId *new_longvid_qualified(StrIdList *strids, VId *vid) {
  LongVId *longvid = (LongVId *)malloc(sizeof(LongVId));
  longvid->kind = LONGVID_QUALIFIED;
  longvid->u.qualified.strids = strids;
  longvid->u.qualified.vid = vid;
  return longvid;
}

void free_longvid(LongVId *longvid) {
  switch (longvid->kind) {
  case LONGVID_NONQUALIFIED:
    free_vid(longvid->u.nonqualified.vid);
    break;
  case LONGVID_QUALIFIED:
    free_stridlist(longvid->u.qualified.strids);
    free_vid(longvid->u.qualified.vid);
    break;
  }
  free(longvid);
}

TyVar *new_tyvar(char *value) {
  TyVar *tyvar = (TyVar *)malloc(sizeof(TyVar));
  tyvar->value = value;
  return tyvar;
}

void free_tyvar(TyVar *tyvar) {
  free(tyvar->value);
  free(tyvar);
}

TyVarSeq *new_tyvarseq(TyVar *tyvar, TyVarSeq *next) {
  TyVarSeq *tyvarseq = (TyVarSeq *)malloc(sizeof(TyVarSeq));
  tyvarseq->tyvar = tyvar;
  tyvarseq->next = next;
  return tyvarseq;
}

void free_tyvarseq(TyVarSeq *tyvarseq) {
  if (tyvarseq->next != NULL) {
    free_tyvarseq(tyvarseq->next);
  }
  free_tyvar(tyvarseq->tyvar);
  free(tyvarseq);
}

TyCon *new_tycon(char *value) {
  TyCon *tycon = (TyCon *)malloc(sizeof(TyCon));
  tycon->value = value;
  return tycon;
}

void free_tycon(TyCon *tycon) {
  free(tycon->value);
  free(tycon);
}

LongTyCon *new_longtycon_nonqualified(TyCon *tycon) {
  LongTyCon *longtycon = (LongTyCon *)malloc(sizeof(LongTyCon));
  longtycon->kind = LONGTYCON_NONQUALIFIED;
  longtycon->u.nonqualified.tycon = tycon;
  return longtycon;
}

LongTyCon *new_longtycon_qualified(StrIdList *strids, TyCon *tycon) {
  LongTyCon *longtycon = (LongTyCon *)malloc(sizeof(LongTyCon));
  longtycon->kind = LONGTYCON_QUALIFIED;
  longtycon->u.qualified.strids = strids;
  longtycon->u.qualified.tycon = tycon;
  return longtycon;
}

void free_longtycon(LongTyCon *longtycon) {
  switch (longtycon->kind) {
  case LONGTYCON_NONQUALIFIED:
    free_tycon(longtycon->u.nonqualified.tycon);
    break;
  case LONGTYCON_QUALIFIED:
    free_stridlist(longtycon->u.qualified.strids);
    free_tycon(longtycon->u.qualified.tycon);
    break;
  }
  free(longtycon);
}

Lab *new_lab_alphanumeric(char *value) {
  Lab *lab = (Lab *)malloc(sizeof(Lab));
  lab->kind = LAB_ALPHANUMERIC;
  lab->value = value;
  return lab;
}

Lab *new_lab_numeric(char *value) {
  Lab *lab = (Lab *)malloc(sizeof(Lab));
  lab->kind = LAB_NUMERIC;
  lab->value = value;
  return lab;
}

void free_lab(Lab *lab) {
  free(lab->value);
  free(lab);
}

StrId *new_strid(char *value) {
  StrId *strid = (StrId *)malloc(sizeof(StrId));
  strid->value = value;
  return strid;
}

void free_strid(StrId *strid) {
  free(strid->value);
  free(strid);
}

StrIdList *new_stridlist(StrIdList *upper, StrId *strid) {
  StrIdList *stridlist = (StrIdList *)malloc(sizeof(StrIdList));
  stridlist->upper = upper;
  stridlist->strid = strid;
  return stridlist;
}

void free_stridlist(StrIdList *stridlist) {
  if (stridlist->upper != NULL) {
    free_stridlist(stridlist->upper);
  }
  free_strid(stridlist->strid);
  free(stridlist);
}

LongStrId *new_longstrid_nonqualified(StrId *strid) {
  LongStrId *longstrid = (LongStrId *)malloc(sizeof(LongStrId));
  longstrid->kind = LONGSTRID_NONQUALIFIED;
  longstrid->u.nonqualified.strid = strid;
  return longstrid;
}

LongStrId *new_longstrid_qualified(StrIdList *strids, StrId *strid) {
  LongStrId *longstrid = (LongStrId *)malloc(sizeof(LongStrId));
  longstrid->kind = LONGSTRID_QUALIFIED;
  longstrid->u.qualified.strids = strids;
  longstrid->u.qualified.strid = strid;
  return longstrid;
}

void free_longstrid(LongStrId *longstrid) {
  switch (longstrid->kind) {
  case LONGSTRID_NONQUALIFIED:
    free_strid(longstrid->u.nonqualified.strid);
    break;
  case LONGSTRID_QUALIFIED:
    free_stridlist(longstrid->u.qualified.strids);
    free_strid(longstrid->u.qualified.strid);
    break;
  }
  free(longstrid);
}

LongStrIdList *new_longstridlist(LongStrId *longstrid, LongStrIdList *next) {
  LongStrIdList *longstridlist = (LongStrIdList *)malloc(sizeof(LongStrIdList));
  longstridlist->longstrid = longstrid;
  longstridlist->next = next;
  return longstridlist;
}

void free_longstridlist(LongStrIdList *longstridlist) {
  if (longstridlist->next != NULL) {
    free_longstridlist(longstridlist->next);
  }
  free_longstrid(longstridlist->longstrid);
  free(longstridlist);
}

Constant *new_constant_integer(char *value) {
  Constant *constant = (Constant *)malloc(sizeof(Constant));
  constant->kind = CONSTANT_INTEGER;
  constant->u.value = value;
  return constant;
}

void free_constant(Constant *constant) {
  free(constant->u.value);
  free(constant);
}

AtPat *new_atpat_wildcard(void) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  atpat->kind = ATPAT_WILDCARD;
  return atpat;
}

AtPat *new_atpat_special_constant(Constant *scon) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  atpat->kind = ATPAT_SPECIAL_CONSTANT;
  atpat->u.special_constant.scon = scon;
  return atpat;
}

AtPat *new_atpat_value_identifier(int op_prefixed, LongVId *longvid) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  atpat->kind = ATPAT_VALUE_IDENTIFIER;
  atpat->u.value_identifier.op_prefixed = op_prefixed;
  atpat->u.value_identifier.longvid = longvid;
  return atpat;
}

AtPat *new_atpat_record(PatRow *patrow) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  atpat->kind = ATPAT_RECORD;
  atpat->u.record.patrow = patrow;
  return atpat;
}

AtPat *new_atpat_parened_pat(Pat *pat) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  atpat->kind = ATPAT_PARENED_PAT;
  atpat->u.parened_pat.pat = pat;
  return atpat;
}

void free_atpat(AtPat *atpat) {
  switch (atpat->kind) {
  case ATPAT_WILDCARD:
    break;
  case ATPAT_SPECIAL_CONSTANT:
    free_constant(atpat->u.special_constant.scon);
    break;
  case ATPAT_VALUE_IDENTIFIER:
    free_longvid(atpat->u.value_identifier.longvid);
    break;
  case ATPAT_RECORD:
    free_patrow(atpat->u.record.patrow);
    break;
  case ATPAT_PARENED_PAT:
    free_pat(atpat->u.parened_pat.pat);
    break;
  }
  free(atpat);
}

PatRow *new_patrow_wildcard(void) {
  PatRow *patrow = (PatRow *)malloc(sizeof(PatRow));
  patrow->kind = PATROW_WILDCARD;
  return patrow;
}

PatRow *new_patrow_pattern_row(Lab *lab, Pat *pat, PatRow *next) {
  PatRow *patrow = (PatRow *)malloc(sizeof(PatRow));
  patrow->kind = PATROW_PATTERN_ROW;
  patrow->u.pattern_row.lab = lab;
  patrow->u.pattern_row.pat = pat;
  patrow->u.pattern_row.next = next;
  return patrow;
}

void free_patrow(PatRow *patrow) {
  if (patrow->kind == PATROW_PATTERN_ROW) {
    free_lab(patrow->u.pattern_row.lab);
    free_pat(patrow->u.pattern_row.pat);
    if (patrow->u.pattern_row.next != NULL) {
      free_patrow(patrow->u.pattern_row.next);
    }
  }
  free(patrow);
}

Pat *new_pat_atomic(AtPat *atpat) {
  Pat *pat = (Pat *)malloc(sizeof(Pat));
  pat->kind = PAT_ATOMIC;
  pat->u.atomic.atpat = atpat;
  return pat;
}

Pat *new_pat_constructed_pattern(int op_prefixed, LongVId *longvid,
                                 AtPat *atpat) {
  Pat *constructed = (Pat *)malloc(sizeof(Pat));
  constructed->kind = PAT_CONSTRUCTED_PATTERN;
  constructed->u.constructed_pattern.op_prefixed = op_prefixed;
  constructed->u.constructed_pattern.longvid = longvid;
  constructed->u.constructed_pattern.atpat = atpat;
  return constructed;
}

Pat *new_pat_infixed_value_construction(Pat *pat1, VId *vid, Pat *pat2) {
  Pat *infixed = (Pat *)malloc(sizeof(Pat));
  infixed->kind = PAT_INFIXED_VALUE_CONSTRUCTION;
  infixed->u.infixed_value_construction.pat1 = pat1;
  infixed->u.infixed_value_construction.vid = vid;
  infixed->u.infixed_value_construction.pat2 = pat2;
  return infixed;
}

Pat *new_pat_typed(Pat *pat, Ty *ty) {
  Pat *typed = (Pat *)malloc(sizeof(Pat));
  typed->kind = PAT_TYPED;
  typed->u.typed.pat = pat;
  typed->u.typed.ty = ty;
  return typed;
}

Pat *new_pat_layered(int op_prefixed, VId *vid, Ty *ty, Pat *pat) {
  Pat *layered = (Pat *)malloc(sizeof(Pat));
  layered->kind = PAT_LAYERED;
  layered->u.layered.op_prefixed = op_prefixed;
  layered->u.layered.vid = vid;
  layered->u.layered.ty = ty;
  layered->u.layered.pat = pat;
  return layered;
}

void free_pat(Pat *pat) {
  switch (pat->kind) {
  case PAT_ATOMIC:
    free_atpat(pat->u.atomic.atpat);
    break;
  case PAT_CONSTRUCTED_PATTERN:
    free_longvid(pat->u.constructed_pattern.longvid);
    free_atpat(pat->u.constructed_pattern.atpat);
    break;
  case PAT_INFIXED_VALUE_CONSTRUCTION:
    free_pat(pat->u.infixed_value_construction.pat1);
    free_vid(pat->u.infixed_value_construction.vid);
    free_pat(pat->u.infixed_value_construction.pat2);
    break;
  case PAT_TYPED:
    free_pat(pat->u.typed.pat);
    free_ty(pat->u.typed.ty);
    break;
  case PAT_LAYERED:
    free_vid(pat->u.layered.vid);
    free_ty(pat->u.layered.ty);
    free_pat(pat->u.layered.pat);
    break;
  }
  free(pat);
}

Ty *new_ty_type_variable(TyVar *tyvar) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  ty->kind = TY_TYPE_VARIABLE;
  ty->u.type_variable.tyvar = tyvar;
  return ty;
}

Ty *new_ty_record_type_expression(TyRow *tyrow) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  ty->kind = TY_RECORD_TYPE_EXPRESSION;
  ty->u.record_type_expression.tyrow = tyrow;
  return ty;
}

Ty *new_ty_type_construction(TySeq *tyseq, LongTyCon *longtycon) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  ty->kind = TY_TYPE_CONSTRUCTION;
  ty->u.type_construction.tyseq = tyseq;
  ty->u.type_construction.longtycon = longtycon;
  return ty;
}

Ty *new_ty_function_type_expression(Ty *arg_ty, Ty *res_ty) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  ty->kind = TY_FUNCTION_TYPE_EXPRESSION;
  ty->u.function_type_expression.arg_ty = arg_ty;
  ty->u.function_type_expression.res_ty = res_ty;
  return ty;
}

Ty *new_ty_parened_ty(Ty *ty) {
  Ty *parened = (Ty *)malloc(sizeof(Ty));
  parened->kind = TY_PARENED_TY;
  parened->u.parened_ty.ty = ty;
  return parened;
}

void free_ty(Ty *ty) {
  switch (ty->kind) {
  case TY_TYPE_VARIABLE:
    free_tyvar(ty->u.type_variable.tyvar);
    break;
  case TY_RECORD_TYPE_EXPRESSION:
    free_tyrow(ty->u.record_type_expression.tyrow);
    break;
  case TY_TYPE_CONSTRUCTION:
    free_tyseq(ty->u.type_construction.tyseq);
    free_longtycon(ty->u.type_construction.longtycon);
    break;
  case TY_FUNCTION_TYPE_EXPRESSION:
    free_ty(ty->u.function_type_expression.arg_ty);
    free_ty(ty->u.function_type_expression.res_ty);
    break;
  case TY_PARENED_TY:
    free_ty(ty->u.parened_ty.ty);
    break;
  }
  free(ty);
}

TySeq *new_tyseq(Ty *ty, TySeq *next) {
  TySeq *tyseq = (TySeq *)malloc(sizeof(TySeq));
  tyseq->ty = ty;
  tyseq->next = next;
  return tyseq;
}

void free_tyseq(TySeq *tyseq) {
  if (tyseq->next != NULL) {
    free_tyseq(tyseq->next);
  }
  free_ty(tyseq->ty);
  free(tyseq);
}

TyRow *new_tyrow(Lab *lab, Ty *ty, TyRow *next) {
  TyRow *tyrow = (TyRow *)malloc(sizeof(TyRow));
  tyrow->lab = lab;
  tyrow->ty = ty;
  tyrow->next = next;
  return tyrow;
}

void free_tyrow(TyRow *tyrow) {
  free_lab(tyrow->lab);
  free_ty(tyrow->ty);
  if (tyrow->next != NULL) {
    free_tyrow(tyrow->next);
  }
  free(tyrow);
}

AtExp *new_atexp_special_constant(Constant *scon) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  atexp->kind = ATEXP_SPECIAL_CONSTANT;
  atexp->u.special_constant.scon = scon;
  return atexp;
}

AtExp *new_atexp_value_identifier(int op_prefixed, LongVId *longvid) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  atexp->kind = ATEXP_VALUE_IDENTIFIER;
  atexp->u.value_identifier.op_prefixed = op_prefixed;
  atexp->u.value_identifier.longvid = longvid;
  return atexp;
}

AtExp *new_atexp_record(ExpRow *exprow) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  atexp->kind = ATEXP_RECORD;
  atexp->u.record.exprow = exprow;
  return atexp;
}

AtExp *new_atexp_local_declaration(Dec *dec, Exp *exp) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  atexp->kind = ATEXP_LOCAL_DECLARATION;
  atexp->u.local_declaration.dec = dec;
  atexp->u.local_declaration.exp = exp;
  return atexp;
}

AtExp *new_atexp_parened_exp(Exp *exp) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  atexp->kind = ATEXP_PARENED_EXP;
  atexp->u.parened_exp.exp = exp;
  return atexp;
}

void free_atexp(AtExp *atexp) {
  switch (atexp->kind) {
  case ATEXP_SPECIAL_CONSTANT:
    free_constant(atexp->u.special_constant.scon);
    break;
  case ATEXP_VALUE_IDENTIFIER:
    free_longvid(atexp->u.value_identifier.longvid);
    break;
  case ATEXP_RECORD:
    free_exprow(atexp->u.record.exprow);
    break;
  case ATEXP_LOCAL_DECLARATION:
    free_dec(atexp->u.local_declaration.dec);
    free_exp(atexp->u.local_declaration.exp);
    break;
  case ATEXP_PARENED_EXP:
    free_exp(atexp->u.parened_exp.exp);
    break;
  }
  free(atexp);
}

ExpRow *new_exprow(Lab *lab, Exp *exp, ExpRow *next) {
  ExpRow *exprow = (ExpRow *)malloc(sizeof(ExpRow));
  exprow->lab = lab;
  exprow->exp = exp;
  exprow->next = next;
  return exprow;
}

void free_exprow(ExpRow *exprow) {
  free_lab(exprow->lab);
  free_exp(exprow->exp);
  if (exprow->next != NULL) {
    free_exprow(exprow->next);
  }
  free(exprow);
}

Exp *new_exp_atomic(AtExp *atexp) {
  Exp *atomic = (Exp *)malloc(sizeof(Exp));
  atomic->kind = EXP_ATOMIC;
  atomic->u.atomic.atexp = atexp;
  return atomic;
}

Exp *new_exp_application(Exp *exp, AtExp *atexp) {
  Exp *application = (Exp *)malloc(sizeof(Exp));
  application->kind = EXP_APPLICATION;
  application->u.application.exp = exp;
  application->u.application.atexp = atexp;
  return application;
}

Exp *new_exp_infixed_application(Exp *exp1, VId *vid, Exp *exp2) {
  Exp *infixed = (Exp *)malloc(sizeof(Exp));
  infixed->kind = EXP_INFIXED_APPLICATION;
  infixed->u.infixed_application.exp1 = exp1;
  infixed->u.infixed_application.vid = vid;
  infixed->u.infixed_application.exp2 = exp2;
  return infixed;
}

Exp *new_exp_typed(Exp *exp, Ty *ty) {
  Exp *typed = (Exp *)malloc(sizeof(Exp));
  typed->kind = EXP_TYPED;
  typed->u.typed.exp = exp;
  typed->u.typed.ty = ty;
  return typed;
}

Exp *new_exp_handle_exception(Exp *exp, Match *match) {
  Exp *handle = (Exp *)malloc(sizeof(Exp));
  handle->kind = EXP_HANDLE_EXCEPTION;
  handle->u.handle_exception.exp = exp;
  handle->u.handle_exception.match = match;
  return handle;
}

Exp *new_exp_raise_exception(Exp *exp) {
  Exp *raise = (Exp *)malloc(sizeof(Exp));
  raise->kind = EXP_RAISE_EXCEPTION;
  raise->u.raise_exception.exp = exp;
  return raise;
}

Exp *new_exp_function(Match *match) {
  Exp *function = (Exp *)malloc(sizeof(Exp));
  function->kind = EXP_FUNCTION;
  function->u.function.match = match;
  return function;
}

void free_exp(Exp *exp) {
  switch (exp->kind) {
  case EXP_ATOMIC:
    free_atexp(exp->u.atomic.atexp);
    break;
  case EXP_APPLICATION:
    free_exp(exp->u.application.exp);
    free_atexp(exp->u.application.atexp);
    break;
  case EXP_INFIXED_APPLICATION:
    free_exp(exp->u.infixed_application.exp1);
    free_vid(exp->u.infixed_application.vid);
    free_exp(exp->u.infixed_application.exp2);
    break;
  case EXP_TYPED:
    free_exp(exp->u.typed.exp);
    free_ty(exp->u.typed.ty);
    break;
  case EXP_HANDLE_EXCEPTION:
    free_exp(exp->u.handle_exception.exp);
    free_match(exp->u.handle_exception.match);
    break;
  case EXP_RAISE_EXCEPTION:
    free_exp(exp->u.raise_exception.exp);
    break;
  case EXP_FUNCTION:
    free_match(exp->u.function.match);
    break;
  }
  free(exp);
}

Match *new_match(Mrule *mrule, Match *next) {
  Match *match = (Match *)malloc(sizeof(Match));
  match->mrule = mrule;
  match->next = next;
  return match;
}

void free_match(Match *match) {
  free_mrule(match->mrule);
  if (match->next != NULL) {
    free_match(match->next);
  }
  free(match);
}

Mrule *new_mrule(Pat *pat, Exp *exp) {
  Mrule *mrule = (Mrule *)malloc(sizeof(Mrule));
  mrule->pat = pat;
  mrule->exp = exp;
  return mrule;
}

void free_mrule(Mrule *mrule) {
  free_pat(mrule->pat);
  free_exp(mrule->exp);
  free(mrule);
}

Dec *new_dec_value_declaration(TyVarSeq *tyvarseq, ValBind *valbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  dec->kind = DEC_VALUE_DECLARATION;
  dec->u.value_declaration.tyvarseq = tyvarseq;
  dec->u.value_declaration.valbind = valbind;
  return dec;
}

Dec *new_dec_type_declaration(TypBind *typbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  dec->kind = DEC_TYPE_DECLARATION;
  dec->u.type_declaration.typbind = typbind;
  return dec;
}

Dec *new_dec_datatype_declaration(DatBind *datbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  dec->kind = DEC_DATATYPE_DECLARATION;
  dec->u.datatype_declaration.datbind = datbind;
  return dec;
}

Dec *new_dec_datatype_replication(TyCon *tycon, LongTyCon *longtycon) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  dec->kind = DEC_DATATYPE_REPLICATION;
  dec->u.datatype_replication.tycon = tycon;
  dec->u.datatype_replication.longtycon = longtycon;
  return dec;
}

Dec *new_dec_abstype_declaration(DatBind *datbind, Dec *dec) {
  Dec *abstype = (Dec *)malloc(sizeof(Dec));
  abstype->kind = DEC_ABSTYPE_DECLARATION;
  abstype->u.abstype_declaration.datbind = datbind;
  abstype->u.abstype_declaration.dec = dec;
  return abstype;
}

Dec *new_dec_exception_declaration(ExBind *exbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  dec->kind = DEC_EXCEPTION_DECLARATION;
  dec->u.exception_declaration.exbind = exbind;
  return dec;
}

Dec *new_dec_local_declaration(Dec *dec1, Dec *dec2) {
  Dec *local = (Dec *)malloc(sizeof(Dec));
  local->kind = DEC_LOCAL_DECLARATION;
  local->u.local_declaration.dec1 = dec1;
  local->u.local_declaration.dec2 = dec2;
  return local;
}

Dec *new_dec_open_declaration(LongStrIdList *longstridlist) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  dec->kind = DEC_OPEN_DECLARATION;
  dec->u.open_declaration.longstridlist = longstridlist;
  return dec;
}

Dec *new_dec_sequential_declaration(Dec *dec1, Dec *dec2) {
  Dec *sequential = (Dec *)malloc(sizeof(Dec));
  sequential->kind = DEC_SEQUENTIAL_DECLARATION;
  sequential->u.sequential_declaration.dec1 = dec1;
  sequential->u.sequential_declaration.dec2 = dec2;
  return sequential;
}

Dec *new_dec_infix_l_directive(char *d, VIdList *vidlist) {
  Dec *infixl = (Dec *)malloc(sizeof(Dec));
  infixl->kind = DEC_INFIX_L_DIRECTIVE;
  infixl->u.infix_l_directive.d = d;
  infixl->u.infix_l_directive.vidlist = vidlist;
  return infixl;
}

Dec *new_dec_infix_r_directive(char *d, VIdList *vidlist) {
  Dec *infixr = (Dec *)malloc(sizeof(Dec));
  infixr->kind = DEC_INFIX_R_DIRECTIVE;
  infixr->u.infix_r_directive.d = d;
  infixr->u.infix_r_directive.vidlist = vidlist;
  return infixr;
}

Dec *new_dec_nonfix_directive(VIdList *vidlist) {
  Dec *nonfix = (Dec *)malloc(sizeof(Dec));
  nonfix->kind = DEC_NONFIX_DIRECTIVE;
  nonfix->u.nonfix_directive.vidlist = vidlist;
  return nonfix;
}

void free_dec(Dec *dec) {
  switch (dec->kind) {
  case DEC_VALUE_DECLARATION:
    free_tyvarseq(dec->u.value_declaration.tyvarseq);
    free_valbind(dec->u.value_declaration.valbind);
    break;
  case DEC_TYPE_DECLARATION:
    free_typbind(dec->u.type_declaration.typbind);
    break;
  case DEC_DATATYPE_DECLARATION:
    free_datbind(dec->u.datatype_declaration.datbind);
    break;
  case DEC_DATATYPE_REPLICATION:
    free_tycon(dec->u.datatype_replication.tycon);
    free_longtycon(dec->u.datatype_replication.longtycon);
    break;
  case DEC_ABSTYPE_DECLARATION:
    free_datbind(dec->u.abstype_declaration.datbind);
    free_dec(dec->u.abstype_declaration.dec);
    break;
  case DEC_EXCEPTION_DECLARATION:
    free_exbind(dec->u.exception_declaration.exbind);
    break;
  case DEC_LOCAL_DECLARATION:
    free_dec(dec->u.local_declaration.dec1);
    free_dec(dec->u.local_declaration.dec2);
    break;
  case DEC_OPEN_DECLARATION:
    free_longstridlist(dec->u.open_declaration.longstridlist);
    break;
  case DEC_EMPTY_DECLARATION:
    break;
  case DEC_SEQUENTIAL_DECLARATION:
    free_dec(dec->u.sequential_declaration.dec1);
    free_dec(dec->u.sequential_declaration.dec2);
    break;
  case DEC_INFIX_L_DIRECTIVE:
    free(dec->u.infix_l_directive.d);
    free_vidlist(dec->u.infix_l_directive.vidlist);
    break;
  case DEC_INFIX_R_DIRECTIVE:
    free(dec->u.infix_r_directive.d);
    free_vidlist(dec->u.infix_r_directive.vidlist);
    break;
  case DEC_NONFIX_DIRECTIVE:
    free_vidlist(dec->u.nonfix_directive.vidlist);
    break;
  }
  free(dec);
}

ValBind *new_valbind_bind(Pat *pat, Exp *exp, ValBind *next) {
  ValBind *bind = (ValBind *)malloc(sizeof(ValBind));
  bind->kind = VALBIND_BIND;
  bind->u.bind.pat = pat;
  bind->u.bind.exp = exp;
  bind->u.bind.next = next;
  return bind;
}

ValBind *new_valbind_rec(ValBind *valbind) {
  ValBind *rec = (ValBind *)malloc(sizeof(ValBind));
  rec->kind = VALBIND_REC;
  rec->u.rec.valbind = valbind;
  return rec;
}

void free_valbind(ValBind *valbind) {
  switch (valbind->kind) {
  case VALBIND_BIND:
    free_pat(valbind->u.bind.pat);
    free_exp(valbind->u.bind.exp);
    if (valbind->u.bind.next != NULL) {
      free_valbind(valbind->u.bind.next);
    }
    break;
  case VALBIND_REC:
    free_valbind(valbind->u.rec.valbind);
    break;
  }
  free(valbind);
}

TypBind *new_typbind(TyVarSeq *tyvarseq, TyCon *tycon, Ty *ty, TypBind *next) {
  TypBind *typbind = (TypBind *)malloc(sizeof(TypBind));
  typbind->tyvarseq = tyvarseq;
  typbind->tycon = tycon;
  typbind->ty = ty;
  typbind->next = next;
  return typbind;
}

void free_typbind(TypBind *typbind) {
  free_tyvarseq(typbind->tyvarseq);
  free_tycon(typbind->tycon);
  free_ty(typbind->ty);
  if (typbind->next != NULL) {
    free_typbind(typbind->next);
  }
  free(typbind);
}

DatBind *new_datbind(TyVarSeq *tyvarseq, TyCon *tycon, ConBind *conbind,
                     DatBind *next) {
  DatBind *datbind = (DatBind *)malloc(sizeof(DatBind));
  datbind->tyvarseq = tyvarseq;
  datbind->tycon = tycon;
  datbind->conbind = conbind;
  datbind->next = next;
  return datbind;
}

void free_datbind(DatBind *datbind) {
  free_tyvarseq(datbind->tyvarseq);
  free_tycon(datbind->tycon);
  free_conbind(datbind->conbind);
  if (datbind->next != NULL) {
    free_datbind(datbind->next);
  }
  free(datbind);
}

ConBind *new_conbind(int op_prefixed, VId *vid, Ty *ty, ConBind *next) {
  ConBind *conbind = (ConBind *)malloc(sizeof(ConBind));
  conbind->op_prefixed = op_prefixed;
  conbind->vid = vid;
  conbind->ty = ty;
  conbind->next = next;
  return conbind;
}

void free_conbind(ConBind *conbind) {
  free_vid(conbind->vid);
  free_ty(conbind->ty);
  if (conbind->next != NULL) {
    free_conbind(conbind->next);
  }
  free(conbind);
}

ExBind *new_exbind_declaration(int op_prefixed, VId *vid, Ty *ty,
                               ExBind *next) {
  ExBind *exbind = (ExBind *)malloc(sizeof(ExBind));
  exbind->u.declaration.op_prefixed = op_prefixed;
  exbind->u.declaration.vid = vid;
  exbind->u.declaration.ty = ty;
  exbind->next = next;
  return exbind;
}

ExBind *new_exbind_replication(int op_prefixed_vid, VId *vid,
                               int op_prefixed_longvid, LongVId *longvid,
                               ExBind *next) {
  ExBind *exbind = (ExBind *)malloc(sizeof(ExBind));
  exbind->u.replication.op_prefixed_vid = op_prefixed_vid;
  exbind->u.replication.vid = vid;
  exbind->u.replication.op_prefixed_longvid = op_prefixed_longvid;
  exbind->u.replication.longvid = longvid;
  exbind->next = next;
  return exbind;
}

void free_exbind(ExBind *exbind) {
  switch (exbind->kind) {
  case EXBIND_DECLARATION:
    free_vid(exbind->u.declaration.vid);
    free_ty(exbind->u.declaration.ty);
    break;
  case EXBIND_REPLICATION:
    free_vid(exbind->u.replication.vid);
    free_longvid(exbind->u.replication.longvid);
    break;
  }
  if (exbind->next != NULL) {
    free_exbind(exbind->next);
  }
  free(exbind);
}
