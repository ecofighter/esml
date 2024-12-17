#include <stdlib.h>
#include <string.h>

#include "syntax.h"

VId *new_vid(char *value) {
  VId *vid = (VId *)malloc(sizeof(VId));
  if (vid == NULL) {
    return NULL;
  }
  vid->value = value;
  return vid;
}

void free_vid(VId *vid) {
  if (vid == NULL) {
    return;
  }
  free(vid->value);
  free(vid);
}

VIdList *new_vidlist(VId *vid, VIdList *next) {
  VIdList *vidlist = (VIdList *)malloc(sizeof(VIdList));
  if (vidlist == NULL) {
    return NULL;
  }
  vidlist->vid = vid;
  vidlist->next = next;
  return vidlist;
}

void free_vidlist(VIdList *vidlist) {
  if (vidlist == NULL) {
    return;
  }
  free_vid(vidlist->vid);
  VIdList *tmp = vidlist->next;
  free(vidlist);
  if (tmp != NULL) {
    free_vidlist(tmp);
  }
}

LongVId *new_longvid_nonqualified(VId *vid) {
  LongVId *longvid = (LongVId *)malloc(sizeof(LongVId));
  if (longvid == NULL) {
    return NULL;
  }
  longvid->kind = LONGVID_NONQUALIFIED;
  longvid->u.nonqualified.vid = vid;
  return longvid;
}

LongVId *new_longvid_qualified(StrIdList *stridlist, VId *vid) {
  LongVId *longvid = (LongVId *)malloc(sizeof(LongVId));
  if (longvid == NULL) {
    return NULL;
  }
  longvid->kind = LONGVID_QUALIFIED;
  longvid->u.qualified.stridlist = stridlist;
  longvid->u.qualified.vid = vid;
  return longvid;
}

void free_longvid(LongVId *longvid) {
  if (longvid == NULL) {
    return;
  }
  switch (longvid->kind) {
  case LONGVID_NONQUALIFIED:
    free_vid(longvid->u.nonqualified.vid);
    break;
  case LONGVID_QUALIFIED:
    free_stridlist(longvid->u.qualified.stridlist);
    free_vid(longvid->u.qualified.vid);
    break;
  }
  free(longvid);
}

TyVar *new_tyvar(char *value) {
  TyVar *tyvar = (TyVar *)malloc(sizeof(TyVar));
  if (tyvar == NULL) {
    return NULL;
  }
  tyvar->value = value;
  return tyvar;
}

void free_tyvar(TyVar *tyvar) {
  if (tyvar == NULL) {
    return;
  }
  free(tyvar->value);
  free(tyvar);
}

TyVarList *new_tyvarlist(TyVar *tyvar, TyVarList *next) {
  TyVarList *tyvarlist = (TyVarList *)malloc(sizeof(TyVarList));
  if (tyvarlist == NULL) {
    return NULL;
  }
  tyvarlist->tyvar = tyvar;
  tyvarlist->next = next;
  return tyvarlist;
}

void free_tyvarlist(TyVarList *tyvarlist) {
  if (tyvarlist == NULL) {
    return;
  }
  free_tyvar(tyvarlist->tyvar);
  TyVarList *tmp = tyvarlist->next;
  free(tyvarlist);
  if (tmp != NULL) {
    free_tyvarlist(tmp);
  }
}

TyCon *new_tycon(char *value) {
  TyCon *tycon = (TyCon *)malloc(sizeof(TyCon));
  if (tycon == NULL) {
    return NULL;
  }
  tycon->value = value;
  return tycon;
}

void free_tycon(TyCon *tycon) {
  if (tycon == NULL) {
    return;
  }
  free(tycon->value);
  free(tycon);
}

LongTyCon *new_longtycon_nonqualified(TyCon *tycon) {
  LongTyCon *longtycon = (LongTyCon *)malloc(sizeof(LongTyCon));
  if (longtycon == NULL) {
    return NULL;
  }
  longtycon->kind = LONGTYCON_NONQUALIFIED;
  longtycon->u.nonqualified.tycon = tycon;
  return longtycon;
}

LongTyCon *new_longtycon_qualified(StrIdList *stridlist, TyCon *tycon) {
  LongTyCon *longtycon = (LongTyCon *)malloc(sizeof(LongTyCon));
  if (longtycon == NULL) {
    return NULL;
  }
  longtycon->kind = LONGTYCON_QUALIFIED;
  longtycon->u.qualified.stridlist = stridlist;
  longtycon->u.qualified.tycon = tycon;
  return longtycon;
}

void free_longtycon(LongTyCon *longtycon) {
  if (longtycon == NULL) {
    return;
  }
  switch (longtycon->kind) {
  case LONGTYCON_NONQUALIFIED:
    free_tycon(longtycon->u.nonqualified.tycon);
    break;
  case LONGTYCON_QUALIFIED:
    free_stridlist(longtycon->u.qualified.stridlist);
    free_tycon(longtycon->u.qualified.tycon);
    break;
  }
  free(longtycon);
}

Lab *new_lab_alphanumeric(char *value) {
  Lab *lab = (Lab *)malloc(sizeof(Lab));
  if (lab == NULL) {
    return NULL;
  }
  lab->kind = LAB_ALPHANUMERIC;
  lab->u.alphanumeric.value = value;
  return lab;
}

Lab *new_lab_numeric(int value) {
  Lab *lab = (Lab *)malloc(sizeof(Lab));
  if (lab == NULL) {
    return NULL;
  }
  lab->kind = LAB_NUMERIC;
  lab->u.numeric.value = value;
  return lab;
}

void free_lab(Lab *lab) {
  if (lab == NULL) {
    return;
  }
  switch (lab->kind) {
  case LAB_ALPHANUMERIC:
    free(lab->u.alphanumeric.value);
    break;
  case LAB_NUMERIC:
    break;
  }
  free(lab);
}

StrId *new_strid(char *value) {
  StrId *strid = (StrId *)malloc(sizeof(StrId));
  if (strid == NULL) {
    return NULL;
  }
  strid->value = value;
  return strid;
}

void free_strid(StrId *strid) {
  if (strid == NULL) {
    return;
  }
  free(strid->value);
  free(strid);
}

LongStrId *new_longstrid_nonqualified(StrId *strid) {
  LongStrId *longstrid = (LongStrId *)malloc(sizeof(LongStrId));
  if (longstrid == NULL) {
    return NULL;
  }
  longstrid->kind = LONGSTRID_NONQUALIFIED;
  longstrid->u.nonqualified.strid = strid;
  return longstrid;
}

LongStrId *new_longstrid_qualified(StrIdList *stridlist, StrId *strid) {
  LongStrId *longstrid = (LongStrId *)malloc(sizeof(LongStrId));
  if (longstrid == NULL) {
    return NULL;
  }
  longstrid->kind = LONGSTRID_QUALIFIED;
  longstrid->u.qualified.stridlist = stridlist;
  longstrid->u.qualified.strid = strid;
  return longstrid;
}

void free_longstrid(LongStrId *longstrid) {
  if (longstrid == NULL) {
    return;
  }
  switch (longstrid->kind) {
  case LONGSTRID_NONQUALIFIED:
    free_strid(longstrid->u.nonqualified.strid);
    break;
  case LONGSTRID_QUALIFIED:
    free_stridlist(longstrid->u.qualified.stridlist);
    free_strid(longstrid->u.qualified.strid);
    break;
  }
  free(longstrid);
}

LongStrIdList *new_longstridlist(LongStrId *longstrid, LongStrIdList *next) {
  LongStrIdList *longstridlist = (LongStrIdList *)malloc(sizeof(LongStrIdList));
  if (longstridlist == NULL) {
    return NULL;
  }
  longstridlist->longstrid = longstrid;
  longstridlist->next = next;
  return longstridlist;
}

void free_longstridlist(LongStrIdList *longstridlist) {
  if (longstridlist == NULL) {
    return;
  }
  free_longstrid(longstridlist->longstrid);
  LongStrIdList *tmp = longstridlist->next;
  free(longstridlist);
  if (tmp != NULL) {
    free_longstridlist(tmp);
  }
}

Constant *new_constant_integer(int value) {
  Constant *constant = (Constant *)malloc(sizeof(Constant));
  if (constant == NULL) {
    return NULL;
  }
  constant->kind = CONSTANT_INTEGER;
  constant->u.integer.value = value;
  return constant;
}

void free_constant(Constant *constant) {
  if (constant == NULL) {
    return;
  }
  switch (constant->kind) {
  case CONSTANT_INTEGER:
    break;
  }
  free(constant);
}

AtPat *new_atpat_wildcard(void) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = ATPAT_WILDCARD;
  return atpat;
}

AtPat *new_atpat_special_constant(Constant *scon) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = ATPAT_SPECIAL_CONSTANT;
  atpat->u.special_constant.scon = scon;
  return atpat;
}

AtPat *new_atpat_value_identifier(bool op_prefixed, LongVId *longvid) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = ATPAT_VALUE_IDENTIFIER;
  atpat->u.value_identifier.op_prefixed = op_prefixed;
  atpat->u.value_identifier.longvid = longvid;
  return atpat;
}

AtPat *new_atpat_record(PatRow *patrow) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = ATPAT_RECORD;
  atpat->u.record.patrow = patrow;
  return atpat;
}

AtPat *new_atpat_parened_pat(Pat *pat) {
  AtPat *atpat = (AtPat *)malloc(sizeof(AtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = ATPAT_PARENED_PAT;
  atpat->u.parened_pat.pat = pat;
  return atpat;
}

void free_atpat(AtPat *atpat) {
  if (atpat == NULL) {
    return;
  }
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
  if (patrow == NULL) {
    return NULL;
  }
  patrow->kind = PATROW_WILDCARD;
  return patrow;
}

PatRow *new_patrow_pattern_row(Lab *lab, Pat *pat, PatRow *next) {
  PatRow *patrow = (PatRow *)malloc(sizeof(PatRow));
  if (patrow == NULL) {
    return NULL;
  }
  patrow->kind = PATROW_PATTERN_ROW;
  patrow->u.pattern_row.lab = lab;
  patrow->u.pattern_row.pat = pat;
  patrow->u.pattern_row.next = next;
  return patrow;
}

void free_patrow(PatRow *patrow) {
  if (patrow == NULL) {
    return;
  }
  PatRow *tmp = NULL;
  switch (patrow->kind) {
  case PATROW_PATTERN_ROW:
    free_lab(patrow->u.pattern_row.lab);
    free_pat(patrow->u.pattern_row.pat);
    tmp = patrow->u.pattern_row.next;
    break;
  case PATROW_WILDCARD:
    break;
  }
  free(patrow);
  if (tmp != NULL) {
    free_patrow(tmp);
  }
}

Pat *new_pat_atomic(AtPat *atpat) {
  Pat *pat = (Pat *)malloc(sizeof(Pat));
  if (pat == NULL) {
    return NULL;
  }
  pat->kind = PAT_ATOMIC;
  pat->u.atomic.atpat = atpat;
  return pat;
}

Pat *new_pat_constructed_pattern(bool op_prefixed, LongVId *longvid,
                                 AtPat *atpat) {
  Pat *constructed = (Pat *)malloc(sizeof(Pat));
  if (constructed == NULL) {
    return NULL;
  }
  constructed->kind = PAT_CONSTRUCTED_PATTERN;
  constructed->u.constructed_pattern.op_prefixed = op_prefixed;
  constructed->u.constructed_pattern.longvid = longvid;
  constructed->u.constructed_pattern.atpat = atpat;
  return constructed;
}

Pat *new_pat_infixed_value_construction(Pat *pat1, VId *vid, Pat *pat2) {
  Pat *infixed = (Pat *)malloc(sizeof(Pat));
  if (infixed == NULL) {
    return NULL;
  }
  infixed->kind = PAT_INFIXED_VALUE_CONSTRUCTION;
  infixed->u.infixed_value_construction.pat1 = pat1;
  infixed->u.infixed_value_construction.vid = vid;
  infixed->u.infixed_value_construction.pat2 = pat2;
  return infixed;
}

Pat *new_pat_typed(Pat *pat, Ty *ty) {
  Pat *typed = (Pat *)malloc(sizeof(Pat));
  if (typed == NULL) {
    return NULL;
  }
  typed->kind = PAT_TYPED;
  typed->u.typed.pat = pat;
  typed->u.typed.ty = ty;
  return typed;
}

Pat *new_pat_layered(bool op_prefixed, VId *vid, Ty *ty, Pat *pat) {
  Pat *layered = (Pat *)malloc(sizeof(Pat));
  if (layered == NULL) {
    return NULL;
  }
  layered->kind = PAT_LAYERED;
  layered->u.layered.op_prefixed = op_prefixed;
  layered->u.layered.vid = vid;
  layered->u.layered.ty = ty;
  layered->u.layered.pat = pat;
  return layered;
}

void free_pat(Pat *pat) {
  if (pat == NULL) {
    return;
  }
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
    if (pat->u.layered.ty != NULL) {
      free_ty(pat->u.layered.ty);
    }
    free_pat(pat->u.layered.pat);
    break;
  }
  free(pat);
}

Ty *new_ty_type_variable(TyVar *tyvar) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = TY_TYPE_VARIABLE;
  ty->u.type_variable.tyvar = tyvar;
  return ty;
}

Ty *new_ty_record_type_expression(TyRow *tyrow) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = TY_RECORD_TYPE_EXPRESSION;
  ty->u.record_type_expression.tyrow = tyrow;
  return ty;
}

Ty *new_ty_type_construction(TyList *tylist, LongTyCon *longtycon) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = TY_TYPE_CONSTRUCTION;
  ty->u.type_construction.tylist = tylist;
  ty->u.type_construction.longtycon = longtycon;
  return ty;
}

Ty *new_ty_function_type_expression(Ty *arg_ty, Ty *res_ty) {
  Ty *ty = (Ty *)malloc(sizeof(Ty));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = TY_FUNCTION_TYPE_EXPRESSION;
  ty->u.function_type_expression.arg_ty = arg_ty;
  ty->u.function_type_expression.res_ty = res_ty;
  return ty;
}

Ty *new_ty_parened_ty(Ty *ty) {
  Ty *parened = (Ty *)malloc(sizeof(Ty));
  if (parened == NULL) {
    return NULL;
  }
  parened->kind = TY_PARENED_TY;
  parened->u.parened_ty.ty = ty;
  return parened;
}

void free_ty(Ty *ty) {
  if (ty == NULL) {
    return;
  }
  switch (ty->kind) {
  case TY_TYPE_VARIABLE:
    free_tyvar(ty->u.type_variable.tyvar);
    break;
  case TY_RECORD_TYPE_EXPRESSION:
    free_tyrow(ty->u.record_type_expression.tyrow);
    break;
  case TY_TYPE_CONSTRUCTION:
    free_tylist(ty->u.type_construction.tylist);
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

TyList *new_tylist(Ty *ty, TyList *next) {
  TyList *tylist = (TyList *)malloc(sizeof(TyList));
  tylist->ty = ty;
  tylist->next = next;
  return tylist;
}

void free_tylist(TyList *tylist) {
  if (tylist == NULL) {
    return;
  }
  free_ty(tylist->ty);
  TyList *tmp = tylist->next;
  free(tylist);
  if (tmp != NULL) {
    free_tylist(tmp);
  }
}

TyRow *new_tyrow(Lab *lab, Ty *ty, TyRow *next) {
  TyRow *tyrow = (TyRow *)malloc(sizeof(TyRow));
  if (tyrow == NULL) {
    return NULL;
  }
  tyrow->lab = lab;
  tyrow->ty = ty;
  tyrow->next = next;
  return tyrow;
}

void free_tyrow(TyRow *tyrow) {
  if (tyrow == NULL) {
    return;
  }
  free_lab(tyrow->lab);
  free_ty(tyrow->ty);
  TyRow *tmp = tyrow->next;
  free(tyrow);
  if (tmp != NULL) {
    free_tyrow(tmp);
  }
}

AtExp *new_atexp_special_constant(Constant *scon) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = ATEXP_SPECIAL_CONSTANT;
  atexp->u.special_constant.scon = scon;
  return atexp;
}

AtExp *new_atexp_value_identifier(bool op_prefixed, LongVId *longvid) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = ATEXP_VALUE_IDENTIFIER;
  atexp->u.value_identifier.op_prefixed = op_prefixed;
  atexp->u.value_identifier.longvid = longvid;
  return atexp;
}

AtExp *new_atexp_record(ExpRow *exprow) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = ATEXP_RECORD;
  atexp->u.record.exprow = exprow;
  return atexp;
}

AtExp *new_atexp_local_declaration(Dec *dec, Exp *exp) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = ATEXP_LOCAL_DECLARATION;
  atexp->u.local_declaration.dec = dec;
  atexp->u.local_declaration.exp = exp;
  return atexp;
}

AtExp *new_atexp_parened_exp(Exp *exp) {
  AtExp *atexp = (AtExp *)malloc(sizeof(AtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = ATEXP_PARENED_EXP;
  atexp->u.parened_exp.exp = exp;
  return atexp;
}

void free_atexp(AtExp *atexp) {
  if (atexp == NULL) {
    return;
  }
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
  if (exprow == NULL) {
    return NULL;
  }
  exprow->lab = lab;
  exprow->exp = exp;
  exprow->next = next;
  return exprow;
}

void free_exprow(ExpRow *exprow) {
  if (exprow == NULL) {
    return;
  }
  free_lab(exprow->lab);
  free_exp(exprow->exp);
  ExpRow *tmp = exprow->next;
  free(exprow);
  if (tmp != NULL) {
    free_exprow(tmp);
  }
}

Exp *new_exp_atomic(AtExp *atexp) {
  Exp *atomic = (Exp *)malloc(sizeof(Exp));
  if (atomic == NULL) {
    return NULL;
  }
  atomic->kind = EXP_ATOMIC;
  atomic->u.atomic.atexp = atexp;
  return atomic;
}

Exp *new_exp_application(Exp *exp, AtExp *atexp) {
  Exp *application = (Exp *)malloc(sizeof(Exp));
  if (application == NULL) {
    return NULL;
  }
  application->kind = EXP_APPLICATION;
  application->u.application.exp = exp;
  application->u.application.atexp = atexp;
  return application;
}

Exp *new_exp_infixed_application(Exp *exp1, VId *vid, Exp *exp2) {
  Exp *infixed = (Exp *)malloc(sizeof(Exp));
  if (infixed == NULL) {
    return NULL;
  }
  infixed->kind = EXP_INFIXED_APPLICATION;
  infixed->u.infixed_application.exp1 = exp1;
  infixed->u.infixed_application.vid = vid;
  infixed->u.infixed_application.exp2 = exp2;
  return infixed;
}

Exp *new_exp_typed(Exp *exp, Ty *ty) {
  Exp *typed = (Exp *)malloc(sizeof(Exp));
  if (typed == NULL) {
    return NULL;
  }
  typed->kind = EXP_TYPED;
  typed->u.typed.exp = exp;
  typed->u.typed.ty = ty;
  return typed;
}

Exp *new_exp_handle_exception(Exp *exp, Match *match) {
  Exp *handle = (Exp *)malloc(sizeof(Exp));
  if (handle == NULL) {
    return NULL;
  }
  handle->kind = EXP_HANDLE_EXCEPTION;
  handle->u.handle_exception.exp = exp;
  handle->u.handle_exception.match = match;
  return handle;
}

Exp *new_exp_raise_exception(Exp *exp) {
  Exp *raise = (Exp *)malloc(sizeof(Exp));
  if (raise == NULL) {
    return NULL;
  }
  raise->kind = EXP_RAISE_EXCEPTION;
  raise->u.raise_exception.exp = exp;
  return raise;
}

Exp *new_exp_function(Match *match) {
  Exp *function = (Exp *)malloc(sizeof(Exp));
  if (function == NULL) {
    return NULL;
  }
  function->kind = EXP_FUNCTION;
  function->u.function.match = match;
  return function;
}

void free_exp(Exp *exp) {
  if (exp == NULL) {
    return;
  }
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
  if (match == NULL) {
    return NULL;
  }
  match->mrule = mrule;
  match->next = next;
  return match;
}

void free_match(Match *match) {
  if (match == NULL) {
    return;
  }
  free_mrule(match->mrule);
  Match *tmp = match->next;
  free(match);
  if (tmp != NULL) {
    free_match(tmp);
  }
}

Mrule *new_mrule(Pat *pat, Exp *exp) {
  Mrule *mrule = (Mrule *)malloc(sizeof(Mrule));
  if (mrule == NULL) {
    return NULL;
  }
  mrule->pat = pat;
  mrule->exp = exp;
  return mrule;
}

void free_mrule(Mrule *mrule) {
  if (mrule == NULL) {
    return;
  }
  free_pat(mrule->pat);
  free_exp(mrule->exp);
  free(mrule);
}

Dec *new_dec_value_declaration(TyVarList *tyvarlist, ValBind *valbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = DEC_VALUE_DECLARATION;
  dec->u.value_declaration.tyvarlist = tyvarlist;
  dec->u.value_declaration.valbind = valbind;
  return dec;
}

Dec *new_dec_type_declaration(TypBind *typbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = DEC_TYPE_DECLARATION;
  dec->u.type_declaration.typbind = typbind;
  return dec;
}

Dec *new_dec_datatype_declaration(DatBind *datbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = DEC_DATATYPE_DECLARATION;
  dec->u.datatype_declaration.datbind = datbind;
  return dec;
}

Dec *new_dec_datatype_replication(TyCon *tycon, LongTyCon *longtycon) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = DEC_DATATYPE_REPLICATION;
  dec->u.datatype_replication.tycon = tycon;
  dec->u.datatype_replication.longtycon = longtycon;
  return dec;
}

Dec *new_dec_abstype_declaration(DatBind *datbind, Dec *dec) {
  Dec *abstype = (Dec *)malloc(sizeof(Dec));
  if (abstype == NULL) {
    return NULL;
  }
  abstype->kind = DEC_ABSTYPE_DECLARATION;
  abstype->u.abstype_declaration.datbind = datbind;
  abstype->u.abstype_declaration.dec = dec;
  return abstype;
}

Dec *new_dec_exception_declaration(ExBind *exbind) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = DEC_EXCEPTION_DECLARATION;
  dec->u.exception_declaration.exbind = exbind;
  return dec;
}

Dec *new_dec_local_declaration(Dec *dec1, Dec *dec2) {
  Dec *local = (Dec *)malloc(sizeof(Dec));
  if (local == NULL) {
    return NULL;
  }
  local->kind = DEC_LOCAL_DECLARATION;
  local->u.local_declaration.dec1 = dec1;
  local->u.local_declaration.dec2 = dec2;
  return local;
}

Dec *new_dec_open_declaration(LongStrIdList *longstridlist) {
  Dec *dec = (Dec *)malloc(sizeof(Dec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = DEC_OPEN_DECLARATION;
  dec->u.open_declaration.longstridlist = longstridlist;
  return dec;
}

Dec *new_dec_sequential_declaration(Dec *dec1, Dec *dec2) {
  Dec *sequential = (Dec *)malloc(sizeof(Dec));
  if (sequential == NULL) {
    return NULL;
  }
  sequential->kind = DEC_SEQUENTIAL_DECLARATION;
  sequential->u.sequential_declaration.dec1 = dec1;
  sequential->u.sequential_declaration.dec2 = dec2;
  return sequential;
}

Dec *new_dec_infix_l_directive(char *d, VIdList *vidlist) {
  Dec *infixl = (Dec *)malloc(sizeof(Dec));
  if (infixl == NULL) {
    return NULL;
  }
  infixl->kind = DEC_INFIX_L_DIRECTIVE;
  infixl->u.infix_l_directive.d = d;
  infixl->u.infix_l_directive.vidlist = vidlist;
  return infixl;
}

Dec *new_dec_infix_r_directive(char *d, VIdList *vidlist) {
  Dec *infixr = (Dec *)malloc(sizeof(Dec));
  if (infixr == NULL) {
    return NULL;
  }
  infixr->kind = DEC_INFIX_R_DIRECTIVE;
  infixr->u.infix_r_directive.d = d;
  infixr->u.infix_r_directive.vidlist = vidlist;
  return infixr;
}

Dec *new_dec_nonfix_directive(VIdList *vidlist) {
  Dec *nonfix = (Dec *)malloc(sizeof(Dec));
  if (nonfix == NULL) {
    return NULL;
  }
  nonfix->kind = DEC_NONFIX_DIRECTIVE;
  nonfix->u.nonfix_directive.vidlist = vidlist;
  return nonfix;
}

void free_dec(Dec *dec) {
  if (dec == NULL) {
    return;
  }
  switch (dec->kind) {
  case DEC_VALUE_DECLARATION:
    free_tyvarlist(dec->u.value_declaration.tyvarlist);
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
  if (bind == NULL) {
    return NULL;
  }
  bind->kind = VALBIND_BIND;
  bind->u.bind.pat = pat;
  bind->u.bind.exp = exp;
  bind->u.bind.next = next;
  return bind;
}

ValBind *new_valbind_rec(ValBind *valbind) {
  ValBind *rec = (ValBind *)malloc(sizeof(ValBind));
  if (rec == NULL) {
    return NULL;
  }
  rec->kind = VALBIND_REC;
  rec->u.rec.valbind = valbind;
  return rec;
}

void free_valbind(ValBind *valbind) {
  if (valbind == NULL) {
    return;
  }
  ValBind *tmp = NULL;
  switch (valbind->kind) {
  case VALBIND_BIND:
    free_pat(valbind->u.bind.pat);
    free_exp(valbind->u.bind.exp);
    tmp = valbind->u.bind.next;
    break;
  case VALBIND_REC:
    free_valbind(valbind->u.rec.valbind);
    break;
  }
  free(valbind);
  if (tmp != NULL) {
    free_valbind(tmp);
  }
}

TypBind *new_typbind(TyVarList *tyvarlist, TyCon *tycon, Ty *ty,
                     TypBind *next) {
  TypBind *typbind = (TypBind *)malloc(sizeof(TypBind));
  if (typbind == NULL) {
    return NULL;
  }
  typbind->tyvarlist = tyvarlist;
  typbind->tycon = tycon;
  typbind->ty = ty;
  typbind->next = next;
  return typbind;
}

void free_typbind(TypBind *typbind) {
  if (typbind == NULL) {
    return;
  }
  free_tyvarlist(typbind->tyvarlist);
  free_tycon(typbind->tycon);
  free_ty(typbind->ty);
  TypBind *tmp = typbind->next;
  free(typbind);
  if (tmp != NULL) {
    free_typbind(tmp);
  }
}

DatBind *new_datbind(TyVarList *tyvarlist, TyCon *tycon, ConBind *conbind,
                     DatBind *next) {
  DatBind *datbind = (DatBind *)malloc(sizeof(DatBind));
  if (datbind == NULL) {
    return NULL;
  }
  datbind->tyvarlist = tyvarlist;
  datbind->tycon = tycon;
  datbind->conbind = conbind;
  datbind->next = next;
  return datbind;
}

void free_datbind(DatBind *datbind) {
  if (datbind == NULL) {
    return;
  }
  free_tyvarlist(datbind->tyvarlist);
  free_tycon(datbind->tycon);
  free_conbind(datbind->conbind);
  DatBind *tmp = datbind->next;
  free(datbind);
  if (tmp != NULL) {
    free_datbind(tmp);
  }
}

ConBind *new_conbind(bool op_prefixed, VId *vid, Ty *ty, ConBind *next) {
  ConBind *conbind = (ConBind *)malloc(sizeof(ConBind));
  if (conbind == NULL) {
    return NULL;
  }
  conbind->op_prefixed = op_prefixed;
  conbind->vid = vid;
  conbind->ty = ty;
  conbind->next = next;
  return conbind;
}

void free_conbind(ConBind *conbind) {
  if (conbind == NULL) {
    return;
  }
  free_vid(conbind->vid);
  if (conbind->ty != NULL) {
    free_ty(conbind->ty);
  }
  ConBind *tmp = conbind->next;
  free(conbind);
  if (tmp != NULL) {
    free_conbind(tmp);
  }
}

ExBind *new_exbind_declaration(bool op_prefixed, VId *vid, Ty *ty,
                               ExBind *next) {
  ExBind *exbind = (ExBind *)malloc(sizeof(ExBind));
  if (exbind == NULL) {
    return NULL;
  }
  exbind->kind = EXBIND_DECLARATION;
  exbind->u.declaration.op_prefixed = op_prefixed;
  exbind->u.declaration.vid = vid;
  exbind->u.declaration.ty = ty;
  exbind->next = next;
  return exbind;
}

ExBind *new_exbind_replication(bool op_prefixed_vid, VId *vid,
                               bool op_prefixed_longvid, LongVId *longvid,
                               ExBind *next) {
  ExBind *exbind = (ExBind *)malloc(sizeof(ExBind));
  if (exbind == NULL) {
    return NULL;
  }
  exbind->kind = EXBIND_REPLICATION;
  exbind->u.replication.op_prefixed_vid = op_prefixed_vid;
  exbind->u.replication.vid = vid;
  exbind->u.replication.op_prefixed_longvid = op_prefixed_longvid;
  exbind->u.replication.longvid = longvid;
  exbind->next = next;
  return exbind;
}

void free_exbind(ExBind *exbind) {
  if (exbind == NULL) {
    return;
  }
  switch (exbind->kind) {
  case EXBIND_DECLARATION:
    free_vid(exbind->u.declaration.vid);
    if (exbind->u.declaration.ty != NULL) {
      free_ty(exbind->u.declaration.ty);
    }
    break;
  case EXBIND_REPLICATION:
    free_vid(exbind->u.replication.vid);
    free_longvid(exbind->u.replication.longvid);
    break;
  }
  ExBind *tmp = exbind->next;
  free(exbind);
  if (tmp != NULL) {
    free_exbind(tmp);
  }
}
