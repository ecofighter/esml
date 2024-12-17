#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "concrete_syntax.h"

CVId *new_c_vid(char *value) {
  CVId *vid = (CVId *)malloc(sizeof(CVId));
  if (vid == NULL) {
    return NULL;
  }
  vid->value = value;
  return vid;
}

void free_c_vid(CVId *vid) {
  if (vid == NULL) {
    return;
  }
  free(vid->value);
  free(vid);
}

CVIdList *new_c_vidlist(CVId *vid, CVIdList *next) {
  CVIdList *vidlist = (CVIdList *)malloc(sizeof(CVIdList));
  if (vidlist == NULL) {
    return NULL;
  }
  vidlist->vid = vid;
  vidlist->next = next;
  return vidlist;
}

void free_c_vidlist(CVIdList *vidlist) {
  if (vidlist == NULL) {
    return;
  }
  free_c_vid(vidlist->vid);
  CVIdList *tmp = vidlist->next;
  free(vidlist);
  if (tmp != NULL) {
    free_c_vidlist(tmp);
  }
}

CQualifiedVId *new_c_qualified_vid(char *value) {
  CQualifiedVId *qualified_vid = (CQualifiedVId *)malloc(sizeof(CQualifiedVId));
  if (qualified_vid == NULL) {
    return NULL;
  }
  qualified_vid->value = value;
  return qualified_vid;
}

void free_c_qualified_vid(CQualifiedVId *qualified_vid) {
  if (qualified_vid == NULL) {
    return;
  }
  free(qualified_vid->value);
  free(qualified_vid);
}

CLongVId *new_c_longvid_nonqualified(CVId *vid) {
  CLongVId *longvid = (CLongVId *)malloc(sizeof(CLongVId));
  if (longvid == NULL) {
    return NULL;
  }
  longvid->kind = CLONGVID_NONQUALIFIED;
  longvid->u.nonqualified.vid = vid;
  return longvid;
}

CLongVId *new_c_longvid_qualified(CQualifiedVId *qualified_vid) {
  CLongVId *longvid = (CLongVId *)malloc(sizeof(CLongVId));
  if (longvid == NULL) {
    return NULL;
  }
  longvid->kind = CLONGVID_QUALIFIED;
  longvid->u.qualified.qualified_vid = qualified_vid;
  return longvid;
}

void free_c_longvid(CLongVId *longvid) {
  if (longvid == NULL) {
    return;
  }
  switch (longvid->kind) {
  case CLONGVID_NONQUALIFIED:
    free_c_vid(longvid->u.nonqualified.vid);
    break;
  case CLONGVID_QUALIFIED:
    free_c_qualified_vid(longvid->u.qualified.qualified_vid);
    break;
  }
  free(longvid);
}

CTyVar *new_c_tyvar(char *value) {
  CTyVar *tyvar = (CTyVar *)malloc(sizeof(CTyVar));
  if (tyvar == NULL) {
    return NULL;
  }
  tyvar->value = value;
  return tyvar;
}

void free_c_tyvar(CTyVar *tyvar) {
  if (tyvar == NULL) {
    return;
  }
  free(tyvar->value);
  free(tyvar);
}

CTyVarList *new_c_tyvarlist(CTyVar *tyvar, CTyVarList *next) {
  CTyVarList *tyvarlist = (CTyVarList *)malloc(sizeof(CTyVarList));
  if (tyvarlist == NULL) {
    return NULL;
  }
  tyvarlist->tyvar = tyvar;
  tyvarlist->next = next;
  return tyvarlist;
}

void free_c_tyvarlist(CTyVarList *tyvarlist) {
  if (tyvarlist == NULL) {
    return;
  }
  free_c_tyvar(tyvarlist->tyvar);
  CTyVarList *tmp = tyvarlist->next;
  free(tyvarlist);
  if (tmp != NULL) {
    free_c_tyvarlist(tmp);
  }
}

CTyCon *new_c_tycon(char *value) {
  CTyCon *tycon = (CTyCon *)malloc(sizeof(CTyCon));
  if (tycon == NULL) {
    return NULL;
  }
  tycon->value = value;
  return tycon;
}

void free_c_tycon(CTyCon *tycon) {
  if (tycon == NULL) {
    return;
  }
  free(tycon->value);
  free(tycon);
}

CQualifiedTyCon *new_c_qualified_tycon(char *value) {
  CQualifiedTyCon *qualified_tycon =
      (CQualifiedTyCon *)malloc(sizeof(CQualifiedTyCon));
  if (qualified_tycon == NULL) {
    return NULL;
  }
  qualified_tycon->value = value;
  return qualified_tycon;
}

void free_c_qualified_tycon(CQualifiedTyCon *qualified_tycon) {
  if (qualified_tycon == NULL) {
    return;
  }
  free(qualified_tycon->value);
  free(qualified_tycon);
}

CLongTyCon *new_c_longtycon_nonqualified(CTyCon *tycon) {
  CLongTyCon *longtycon = (CLongTyCon *)malloc(sizeof(CLongTyCon));
  if (longtycon == NULL) {
    return NULL;
  }
  longtycon->kind = CLONGTYCON_NONQUALIFIED;
  longtycon->u.nonqualified.tycon = tycon;
  return longtycon;
}

CLongTyCon *new_c_longtycon_qualified(CQualifiedTyCon *qualified_tycon) {
  CLongTyCon *longtycon = (CLongTyCon *)malloc(sizeof(CLongTyCon));
  if (longtycon == NULL) {
    return NULL;
  }
  longtycon->kind = CLONGTYCON_QUALIFIED;
  longtycon->u.qualified.qualified_tycon = qualified_tycon;
  return longtycon;
}

void free_c_longtycon(CLongTyCon *longtycon) {
  if (longtycon == NULL) {
    return;
  }
  switch (longtycon->kind) {
  case CLONGTYCON_NONQUALIFIED:
    free_c_tycon(longtycon->u.nonqualified.tycon);
    break;
  case CLONGTYCON_QUALIFIED:
    free_c_qualified_tycon(longtycon->u.qualified.qualified_tycon);
    break;
  }
  free(longtycon);
}

CLab *new_c_lab_alphanumeric(char *value) {
  CLab *lab = (CLab *)malloc(sizeof(CLab));
  if (lab == NULL) {
    return NULL;
  }
  lab->kind = CLAB_ALPHANUMERIC;
  lab->value = value;
  return lab;
}

CLab *new_c_lab_numeric(char *value) {
  CLab *lab = (CLab *)malloc(sizeof(CLab));
  if (lab == NULL) {
    return NULL;
  }
  lab->kind = CLAB_NUMERIC;
  lab->value = value;
  return lab;
}

void free_c_lab(CLab *lab) {
  if (lab == NULL) {
    return;
  }
  free(lab->value);
  free(lab);
}

CStrId *new_c_strid(char *value) {
  CStrId *strid = (CStrId *)malloc(sizeof(CStrId));
  if (strid == NULL) {
    return NULL;
  }
  strid->value = value;
  return strid;
}

void free_c_strid(CStrId *strid) {
  if (strid == NULL) {
    return;
  }
  free(strid->value);
  free(strid);
}

CQualifiedStrId *new_c_qualified_strid(char *value) {
  CQualifiedStrId *qualified_strid =
      (CQualifiedStrId *)malloc(sizeof(CQualifiedStrId));
  if (qualified_strid == NULL) {
    return NULL;
  }
  qualified_strid->value = value;
  return qualified_strid;
}

void free_c_qualified_strid(CQualifiedStrId *qualified_strid) {
  if (qualified_strid == NULL) {
    return;
  }
  free(qualified_strid->value);
  free(qualified_strid);
}

CLongStrId *new_c_longstrid_nonqualified(CStrId *strid) {
  CLongStrId *longstrid = (CLongStrId *)malloc(sizeof(CLongStrId));
  if (longstrid == NULL) {
    return NULL;
  }
  longstrid->kind = CLONGSTRID_NONQUALIFIED;
  longstrid->u.nonqualified.strid = strid;
  return longstrid;
}

CLongStrId *new_c_longstrid_qualified(CQualifiedStrId *qualified_strid) {
  CLongStrId *longstrid = (CLongStrId *)malloc(sizeof(CLongStrId));
  if (longstrid == NULL) {
    return NULL;
  }
  longstrid->kind = CLONGSTRID_QUALIFIED;
  longstrid->u.qualified.qualified_strid = qualified_strid;
  return longstrid;
}

void free_c_longstrid(CLongStrId *longstrid) {
  if (longstrid == NULL) {
    return;
  }
  switch (longstrid->kind) {
  case CLONGSTRID_NONQUALIFIED:
    free_c_strid(longstrid->u.nonqualified.strid);
    break;
  case CLONGSTRID_QUALIFIED:
    free_c_qualified_strid(longstrid->u.qualified.qualified_strid);
    break;
  }
  free(longstrid);
}

CLongStrIdList *new_c_longstridlist(CLongStrId *longstrid,
                                    CLongStrIdList *next) {
  CLongStrIdList *longstridlist =
      (CLongStrIdList *)malloc(sizeof(CLongStrIdList));
  if (longstridlist == NULL) {
    return NULL;
  }
  longstridlist->longstrid = longstrid;
  longstridlist->next = next;
  return longstridlist;
}

void free_c_longstridlist(CLongStrIdList *longstridlist) {
  if (longstridlist == NULL) {
    return;
  }
  free_c_longstrid(longstridlist->longstrid);
  CLongStrIdList *tmp = longstridlist->next;
  free(longstridlist);
  if (tmp != NULL) {
    free_c_longstridlist(tmp);
  }
}

CConstant *new_c_constant_integer(char *value) {
  CConstant *constant = (CConstant *)malloc(sizeof(CConstant));
  if (constant == NULL) {
    return NULL;
  }
  constant->kind = CCONSTANT_INTEGER;
  constant->u.value = value;
  return constant;
}

void free_c_constant(CConstant *constant) {
  if (constant == NULL) {
    return;
  }
  free(constant->u.value);
  free(constant);
}

CAtPat *new_c_atpat_wildcard(void) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_WILDCARD;
  return atpat;
}

CAtPat *new_c_atpat_special_constant(CConstant *scon) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_SPECIAL_CONSTANT;
  atpat->u.special_constant.scon = scon;
  return atpat;
}

CAtPat *new_c_atpat_value_identifier(bool op_prefixed, CLongVId *longvid) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_VALUE_IDENTIFIER;
  atpat->u.value_identifier.op_prefixed = op_prefixed;
  atpat->u.value_identifier.longvid = longvid;
  return atpat;
}

CAtPat *new_c_atpat_record(CPatRow *patrow) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_RECORD;
  atpat->u.record.patrow = patrow;
  return atpat;
}

CAtPat *new_c_atpat_zero_tuple(void) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_ZERO_TUPLE;
  return atpat;
}

CAtPat *new_c_atpat_n_tuple(CPatList *patlist) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_N_TUPLE;
  atpat->u.n_tuple.patlist = patlist;
  return atpat;
}

CAtPat *new_c_atpat_list(CPatList *patlist) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_LIST;
  atpat->u.list.patlist = patlist;
  return atpat;
}

CAtPat *new_c_atpat_parened_pat(CPat *pat) {
  CAtPat *atpat = (CAtPat *)malloc(sizeof(CAtPat));
  if (atpat == NULL) {
    return NULL;
  }
  atpat->kind = CATPAT_PARENED_PAT;
  atpat->u.parened_pat.pat = pat;
  return atpat;
}

void free_c_atpat(CAtPat *atpat) {
  if (atpat == NULL) {
    return;
  }
  switch (atpat->kind) {
  case CATPAT_WILDCARD:
    break;
  case CATPAT_SPECIAL_CONSTANT:
    free_c_constant(atpat->u.special_constant.scon);
    break;
  case CATPAT_VALUE_IDENTIFIER:
    free_c_longvid(atpat->u.value_identifier.longvid);
    break;
  case CATPAT_RECORD:
    free_c_patrow(atpat->u.record.patrow);
    break;
  case CATPAT_ZERO_TUPLE:
    break;
  case CATPAT_N_TUPLE:
    free_c_patlist(atpat->u.n_tuple.patlist);
    break;
  case CATPAT_LIST:
    free_c_patlist(atpat->u.list.patlist);
    break;
  case CATPAT_PARENED_PAT:
    free_c_pat(atpat->u.parened_pat.pat);
    break;
  }
  free(atpat);
}

CAtPatList *new_c_atpatlist(CAtPat *atpat, CAtPatList *next) {
  CAtPatList *atpatlist = (CAtPatList *)malloc(sizeof(CAtPatList));
  if (atpatlist == NULL) {
    return NULL;
  }
  atpatlist->atpat = atpat;
  atpatlist->next = next;
  return atpatlist;
}

void free_c_atpatlist(CAtPatList *atpatlist) {
  if (atpatlist == NULL) {
    return;
  }
  free_c_atpat(atpatlist->atpat);
  CAtPatList *tmp = atpatlist->next;
  free(atpatlist);
  if (tmp != NULL) {
    free_c_atpatlist(tmp);
  }
}

CPatRow *new_c_patrow_wildcard(void) {
  CPatRow *patrow = (CPatRow *)malloc(sizeof(CPatRow));
  if (patrow == NULL) {
    return NULL;
  }
  patrow->kind = CPATROW_WILDCARD;
  return patrow;
}

CPatRow *new_c_patrow_pattern_row(CLab *lab, CPat *pat, CPatRow *next) {
  CPatRow *patrow = (CPatRow *)malloc(sizeof(CPatRow));
  if (patrow == NULL) {
    return NULL;
  }
  patrow->kind = CPATROW_PATTERN_ROW;
  patrow->u.pattern_row.lab = lab;
  patrow->u.pattern_row.pat = pat;
  patrow->u.pattern_row.next = next;
  return patrow;
}

CPatRow *new_c_patrow_label_as_variable(CVId *vid, CTy *ty, CPat *pat,
                                        CPatRow *next) {
  CPatRow *patrow = (CPatRow *)malloc(sizeof(CPatRow));
  if (patrow == NULL) {
    return NULL;
  }
  patrow->kind = CPATROW_LABEL_AS_VARIABLE;
  patrow->u.label_as_variable.vid = vid;
  patrow->u.label_as_variable.ty = ty;
  patrow->u.label_as_variable.pat = pat;
  patrow->u.label_as_variable.next = next;
  return patrow;
}

void free_c_patrow(CPatRow *patrow) {
  if (patrow == NULL) {
    return;
  }
  switch (patrow->kind) {
  case CPATROW_WILDCARD:
    break;
  case CPATROW_PATTERN_ROW:
    free_c_lab(patrow->u.pattern_row.lab);
    free_c_pat(patrow->u.pattern_row.pat);
    if (patrow->u.pattern_row.next != NULL) {
      free_c_patrow(patrow->u.pattern_row.next);
    }
    break;
  case CPATROW_LABEL_AS_VARIABLE:
    free_c_vid(patrow->u.label_as_variable.vid);
    if (patrow->u.label_as_variable.ty != NULL) {
      free_c_ty(patrow->u.label_as_variable.ty);
    }
    if (patrow->u.label_as_variable.pat != NULL) {
      free_c_pat(patrow->u.label_as_variable.pat);
    }
    if (patrow->u.label_as_variable.next != NULL) {
      free_c_patrow(patrow->u.label_as_variable.next);
    }
    break;
  }
  free(patrow);
}

CPat *new_c_pat_atomic(CAtPat *atpat) {
  CPat *pat = (CPat *)malloc(sizeof(CPat));
  if (pat == NULL) {
    return NULL;
  }
  pat->kind = CPAT_ATOMIC;
  pat->u.atomic.atpat = atpat;
  return pat;
}

CPat *new_c_pat_atpatlist(CAtPatList *atpatlist) {
  CPat *pat = (CPat *)malloc(sizeof(CPat));
  if (pat == NULL) {
    return NULL;
  }
  pat->kind = CPAT_ATPATLIST;
  pat->u.atpatlist.atpatlist = atpatlist;
  return pat;
}

CPat *new_c_pat_typed(CPat *pat, CTy *ty) {
  CPat *typed = (CPat *)malloc(sizeof(CPat));
  if (typed == NULL) {
    return NULL;
  }
  typed->kind = CPAT_TYPED;
  typed->u.typed.pat = pat;
  typed->u.typed.ty = ty;
  return typed;
}

CPat *new_c_pat_layered(bool op_prefixed, CVId *vid, CTy *ty, CPat *pat) {
  CPat *layered = (CPat *)malloc(sizeof(CPat));
  if (layered == NULL) {
    return NULL;
  }
  layered->kind = CPAT_LAYERED;
  layered->u.layered.op_prefixed = op_prefixed;
  layered->u.layered.vid = vid;
  layered->u.layered.ty = ty;
  layered->u.layered.pat = pat;
  return layered;
}

void free_c_pat(CPat *pat) {
  if (pat == NULL) {
    return;
  }
  switch (pat->kind) {
  case CPAT_ATOMIC:
    free_c_atpat(pat->u.atomic.atpat);
    break;
  case CPAT_ATPATLIST:
    free_c_atpatlist(pat->u.atpatlist.atpatlist);
    break;
  case CPAT_TYPED:
    free_c_pat(pat->u.typed.pat);
    free_c_ty(pat->u.typed.ty);
    break;
  case CPAT_LAYERED:
    free_c_vid(pat->u.layered.vid);
    if (pat->u.layered.ty != NULL) {
      free_c_ty(pat->u.layered.ty);
    }
    if (pat->u.layered.pat != NULL) {
      free_c_pat(pat->u.layered.pat);
    }
    break;
  }
  free(pat);
}

CPatList *new_c_patlist(CPat *pat, CPatList *next) {
  CPatList *patlist = (CPatList *)malloc(sizeof(CPatList));
  if (patlist == NULL) {
    return NULL;
  }
  patlist->pat = pat;
  patlist->next = next;
  return patlist;
}

void free_c_patlist(CPatList *patlist) {
  if (patlist == NULL) {
    return;
  }
  free_c_pat(patlist->pat);
  CPatList *tmp = patlist->next;
  free(patlist);
  if (tmp != NULL) {
    free_c_patlist(tmp);
  }
}

CTy *new_c_ty_type_variable(CTyVar *tyvar) {
  CTy *ty = (CTy *)malloc(sizeof(CTy));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = CTY_TYPE_VARIABLE;
  ty->u.type_variable.tyvar = tyvar;
  return ty;
}

CTy *new_c_ty_record_type_expression(CTyRow *tyrow) {
  CTy *ty = (CTy *)malloc(sizeof(CTy));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = CTY_RECORD_TYPE_EXPRESSION;
  ty->u.record_type_expression.tyrow = tyrow;
  return ty;
}

CTy *new_c_ty_type_construction(CTyList *tylist, CLongTyCon *longtycon) {
  CTy *ty = (CTy *)malloc(sizeof(CTy));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = CTY_TYPE_CONSTRUCTION;
  ty->u.type_construction.tylist = tylist;
  ty->u.type_construction.longtycon = longtycon;
  return ty;
}

CTy *new_c_ty_tuple_type(CTyList *tylist) {
  CTy *ty = (CTy *)malloc(sizeof(CTy));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = CTY_TUPLE_TYPE;
  ty->u.tuple_type.tylist = tylist;
  return ty;
}

CTy *new_c_ty_function_type_expression(CTy *arg_ty, CTy *res_ty) {
  CTy *ty = (CTy *)malloc(sizeof(CTy));
  if (ty == NULL) {
    return NULL;
  }
  ty->kind = CTY_FUNCTION_TYPE_EXPRESSION;
  ty->u.function_type_expression.arg_ty = arg_ty;
  ty->u.function_type_expression.res_ty = res_ty;
  return ty;
}

CTy *new_c_ty_parened_ty(CTy *ty) {
  CTy *parened = (CTy *)malloc(sizeof(CTy));
  if (parened == NULL) {
    return NULL;
  }
  parened->kind = CTY_PARENED_TY;
  parened->u.parened_ty.ty = ty;
  return parened;
}

void free_c_ty(CTy *ty) {
  if (ty == NULL) {
    return;
  }
  switch (ty->kind) {
  case CTY_TYPE_VARIABLE:
    free_c_tyvar(ty->u.type_variable.tyvar);
    break;
  case CTY_RECORD_TYPE_EXPRESSION:
    free_c_tyrow(ty->u.record_type_expression.tyrow);
    break;
  case CTY_TYPE_CONSTRUCTION:
    free_c_tylist(ty->u.type_construction.tylist);
    free_c_longtycon(ty->u.type_construction.longtycon);
    break;
  case CTY_TUPLE_TYPE:
    free_c_tylist(ty->u.tuple_type.tylist);
    break;
  case CTY_FUNCTION_TYPE_EXPRESSION:
    free_c_ty(ty->u.function_type_expression.arg_ty);
    free_c_ty(ty->u.function_type_expression.res_ty);
    break;
  case CTY_PARENED_TY:
    free_c_ty(ty->u.parened_ty.ty);
    break;
  }
  free(ty);
}

CTyList *new_c_tylist(CTy *ty, CTyList *next) {
  CTyList *tylist = (CTyList *)malloc(sizeof(CTyList));
  if (tylist == NULL) {
    return NULL;
  }
  tylist->ty = ty;
  tylist->next = next;
  return tylist;
}

void free_c_tylist(CTyList *tylist) {
  if (tylist == NULL) {
    return;
  }
  free_c_ty(tylist->ty);
  CTyList *tmp = tylist->next;
  free(tylist);
  if (tmp != NULL) {
    free_c_tylist(tmp);
  }
}

CTyRow *new_c_tyrow(CLab *lab, CTy *ty, CTyRow *next) {
  CTyRow *tyrow = (CTyRow *)malloc(sizeof(CTyRow));
  if (tyrow == NULL) {
    return NULL;
  }
  tyrow->lab = lab;
  tyrow->ty = ty;
  tyrow->next = next;
  return tyrow;
}

void free_c_tyrow(CTyRow *tyrow) {
  if (tyrow == NULL) {
    return;
  }
  free_c_lab(tyrow->lab);
  free_c_ty(tyrow->ty);
  CTyRow *tmp = tyrow->next;
  free(tyrow);
  if (tmp != NULL) {
    free_c_tyrow(tmp);
  }
}

CAtExp *new_c_atexp_special_constant(CConstant *scon) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_SPECIAL_CONSTANT;
  atexp->u.special_constant.scon = scon;
  return atexp;
}

CAtExp *new_c_atexp_value_identifier(bool op_prefixed, CLongVId *longvid) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_VALUE_IDENTIFIER;
  atexp->u.value_identifier.op_prefixed = op_prefixed;
  atexp->u.value_identifier.longvid = longvid;
  return atexp;
}

CAtExp *new_c_atexp_record(CExpRow *exprow) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_RECORD;
  atexp->u.record.exprow = exprow;
  return atexp;
}

CAtExp *new_c_atexp_record_selector(CLab *lab) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_RECORD_SELECTOR;
  atexp->u.record_selector.lab = lab;
  return atexp;
}

CAtExp *new_c_atexp_zero_tuple(void) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_ZERO_TUPLE;
  return atexp;
}

CAtExp *new_c_atexp_n_tuple(CExpList *explist) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_N_TUPLE;
  atexp->u.n_tuple.explist = explist;
  return atexp;
}

CAtExp *new_c_atexp_list(CExpList *explist) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_LIST;
  atexp->u.list.explist = explist;
  return atexp;
}

CAtExp *new_c_atexp_sequence(CExpList *explist) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_SEQUENCE;
  atexp->u.sequence.explist = explist;
  return atexp;
}

CAtExp *new_c_atexp_local_declaration(CDec *dec, CExp *exp) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_LOCAL_DECLARATION;
  atexp->u.local_declaration.dec = dec;
  atexp->u.local_declaration.exp = exp;
  return atexp;
}

CAtExp *new_c_atexp_parened_exp(CExp *exp) {
  CAtExp *atexp = (CAtExp *)malloc(sizeof(CAtExp));
  if (atexp == NULL) {
    return NULL;
  }
  atexp->kind = CATEXP_PARENED_EXP;
  atexp->u.parened_exp.exp = exp;
  return atexp;
}

void free_c_atexp(CAtExp *atexp) {
  if (atexp == NULL) {
    return;
  }
  switch (atexp->kind) {
  case CATEXP_SPECIAL_CONSTANT:
    free_c_constant(atexp->u.special_constant.scon);
    break;
  case CATEXP_VALUE_IDENTIFIER:
    free_c_longvid(atexp->u.value_identifier.longvid);
    break;
  case CATEXP_RECORD:
    free_c_exprow(atexp->u.record.exprow);
    break;
  case CATEXP_RECORD_SELECTOR:
    free_c_lab(atexp->u.record_selector.lab);
    break;
  case CATEXP_ZERO_TUPLE:
    break;
  case CATEXP_N_TUPLE:
    free_c_explist(atexp->u.n_tuple.explist);
    break;
  case CATEXP_LIST:
    free_c_explist(atexp->u.list.explist);
    break;
  case CATEXP_SEQUENCE:
    free_c_explist(atexp->u.sequence.explist);
    break;
  case CATEXP_LOCAL_DECLARATION:
    free_c_dec(atexp->u.local_declaration.dec);
    free_c_exp(atexp->u.local_declaration.exp);
    break;
  case CATEXP_PARENED_EXP:
    free_c_exp(atexp->u.parened_exp.exp);
    break;
  }
  free(atexp);
}

CAtExpList *new_c_atexplist(CAtExp *atexp, CAtExpList *next) {
  CAtExpList *atexplist = (CAtExpList *)malloc(sizeof(CAtExpList));
  if (atexplist == NULL) {
    return NULL;
  }
  atexplist->atexp = atexp;
  atexplist->next = next;
  return atexplist;
}

void free_c_atexplist(CAtExpList *atexplist) {
  if (atexplist == NULL) {
    return;
  }
  free_c_atexp(atexplist->atexp);
  CAtExpList *tmp = atexplist->next;
  free(atexplist);
  if (tmp != NULL) {
    free_c_atexplist(tmp);
  }
}

CExpRow *new_c_exprow(CLab *lab, CExp *exp, CExpRow *next) {
  CExpRow *exprow = (CExpRow *)malloc(sizeof(CExpRow));
  if (exprow == NULL) {
    return NULL;
  }
  exprow->lab = lab;
  exprow->exp = exp;
  exprow->next = next;
  return exprow;
}

void free_c_exprow(CExpRow *exprow) {
  if (exprow == NULL) {
    return;
  }
  free_c_lab(exprow->lab);
  free_c_exp(exprow->exp);
  CExpRow *tmp = exprow->next;
  free(exprow);
  if (tmp != NULL) {
    free_c_exprow(tmp);
  }
}

CExp *new_c_exp_atomic(CAtExp *atexp) {
  CExp *atomic = (CExp *)malloc(sizeof(CExp));
  if (atomic == NULL) {
    return NULL;
  }
  atomic->kind = CEXP_ATOMIC;
  atomic->u.atomic.atexp = atexp;
  return atomic;
}

CExp *new_c_exp_atexplist(CAtExpList *atexplist) {
  CExp *infexp = (CExp *)malloc(sizeof(CExp));
  if (infexp == NULL) {
    return NULL;
  }
  infexp->kind = CEXP_ATEXPLIST;
  infexp->u.atexplist.atexplist = atexplist;
  return infexp;
}

CExp *new_c_exp_typed(CExp *exp, CTy *ty) {
  CExp *typed = (CExp *)malloc(sizeof(CExp));
  if (typed == NULL) {
    return NULL;
  }
  typed->kind = CEXP_TYPED;
  typed->u.typed.exp = exp;
  typed->u.typed.ty = ty;
  return typed;
}

CExp *new_c_exp_conjunction(CExp *exp1, CExp *exp2) {
  CExp *conj = (CExp *)malloc(sizeof(CExp));
  if (conj == NULL) {
    return NULL;
  }
  conj->kind = CEXP_CONJUNCTION;
  conj->u.conjuction.exp1 = exp1;
  conj->u.conjuction.exp2 = exp2;
  return conj;
}

CExp *new_c_exp_disjunction(CExp *exp1, CExp *exp2) {
  CExp *disj = (CExp *)malloc(sizeof(CExp));
  if (disj == NULL) {
    return NULL;
  }
  disj->kind = CEXP_DISJUNCTION;
  disj->u.disjuction.exp1 = exp1;
  disj->u.disjuction.exp2 = exp2;
  return disj;
}

CExp *new_c_exp_handle_exception(CExp *exp, CMatch *match) {
  CExp *handle = (CExp *)malloc(sizeof(CExp));
  if (handle == NULL) {
    return NULL;
  }
  handle->kind = CEXP_HANDLE_EXCEPTION;
  handle->u.handle_exception.exp = exp;
  handle->u.handle_exception.match = match;
  return handle;
}

CExp *new_c_exp_raise_exception(CExp *exp) {
  CExp *raise = (CExp *)malloc(sizeof(CExp));
  if (raise == NULL) {
    return NULL;
  }
  raise->kind = CEXP_RAISE_EXCEPTION;
  raise->u.raise_exception.exp = exp;
  return raise;
}

CExp *new_c_exp_conditional(CExp *exp1, CExp *exp2, CExp *exp3) {
  CExp *cond = (CExp *)malloc(sizeof(CExp));
  if (cond == NULL) {
    return NULL;
  }
  cond->kind = CEXP_CONDITIONAL;
  cond->u.conditional.exp1 = exp1;
  cond->u.conditional.exp2 = exp2;
  cond->u.conditional.exp3 = exp3;
  return cond;
}

CExp *new_c_exp_iteration(CExp *exp1, CExp *exp2) {
  CExp *iter = (CExp *)malloc(sizeof(CExp));
  if (iter == NULL) {
    return NULL;
  }
  iter->kind = CEXP_ITERATION;
  iter->u.iteration.exp1 = exp1;
  iter->u.iteration.exp2 = exp2;
  return iter;
}

CExp *new_c_exp_case_analysis(CExp *exp, CMatch *match) {
  CExp *case_exp = (CExp *)malloc(sizeof(CExp));
  if (case_exp == NULL) {
    return NULL;
  }
  case_exp->kind = CEXP_CASE_ANALYSIS;
  case_exp->u.case_analysis.exp = exp;
  case_exp->u.case_analysis.match = match;
  return case_exp;
}

CExp *new_c_exp_function(CMatch *match) {
  CExp *function = (CExp *)malloc(sizeof(CExp));
  if (function == NULL) {
    return NULL;
  }
  function->kind = CEXP_FUNCTION;
  function->u.function.match = match;
  return function;
}

void free_c_exp(CExp *exp) {
  if (exp == NULL) {
    return;
  }
  switch (exp->kind) {
  case CEXP_ATOMIC:
    free_c_atexp(exp->u.atomic.atexp);
    break;
  case CEXP_ATEXPLIST:
    free_c_atexplist(exp->u.atexplist.atexplist);
    break;
  case CEXP_TYPED:
    free_c_exp(exp->u.typed.exp);
    free_c_ty(exp->u.typed.ty);
    break;
  case CEXP_CONJUNCTION:
    free_c_exp(exp->u.conjuction.exp1);
    free_c_exp(exp->u.conjuction.exp2);
    break;
  case CEXP_DISJUNCTION:
    free_c_exp(exp->u.disjuction.exp1);
    free_c_exp(exp->u.disjuction.exp2);
    break;
  case CEXP_HANDLE_EXCEPTION:
    free_c_exp(exp->u.handle_exception.exp);
    free_c_match(exp->u.handle_exception.match);
    break;
  case CEXP_RAISE_EXCEPTION:
    free_c_exp(exp->u.raise_exception.exp);
    break;
  case CEXP_CONDITIONAL:
    free_c_exp(exp->u.conditional.exp1);
    free_c_exp(exp->u.conditional.exp2);
    free_c_exp(exp->u.conditional.exp3);
    break;
  case CEXP_ITERATION:
    free_c_exp(exp->u.iteration.exp1);
    free_c_exp(exp->u.iteration.exp2);
    break;
  case CEXP_CASE_ANALYSIS:
    free_c_exp(exp->u.case_analysis.exp);
    free_c_match(exp->u.case_analysis.match);
    break;
  case CEXP_FUNCTION:
    free_c_match(exp->u.function.match);
    break;
  }
  free(exp);
}

CExpList *new_c_explist(CExp *exp, CExpList *next) {
  CExpList *explist = (CExpList *)malloc(sizeof(CExpList));
  if (explist == NULL) {
    return NULL;
  }
  explist->exp = exp;
  explist->next = next;
  return explist;
}

void free_c_explist(CExpList *explist) {
  if (explist == NULL) {
    return;
  }
  free_c_exp(explist->exp);
  CExpList *tmp = explist->next;
  free(explist);
  if (tmp != NULL) {
    free_c_explist(tmp);
  }
}

CMatch *new_c_match(CMrule *mrule, CMatch *next) {
  CMatch *match = (CMatch *)malloc(sizeof(CMatch));
  if (match == NULL) {
    return NULL;
  }
  match->mrule = mrule;
  match->next = next;
  return match;
}

void free_c_match(CMatch *match) {
  if (match == NULL) {
    return;
  }
  free_c_mrule(match->mrule);
  CMatch *tmp = match->next;
  free(match);
  if (tmp != NULL) {
    free_c_match(tmp);
  }
}

CMrule *new_c_mrule(CPat *pat, CExp *exp) {
  CMrule *mrule = (CMrule *)malloc(sizeof(CMrule));
  if (mrule == NULL) {
    return NULL;
  }
  mrule->pat = pat;
  mrule->exp = exp;
  return mrule;
}

void free_c_mrule(CMrule *mrule) {
  if (mrule == NULL) {
    return;
  }
  free_c_pat(mrule->pat);
  free_c_exp(mrule->exp);
  free(mrule);
}

CDec *new_c_dec_value_declaration(CTyVarList *tyvarseq, CValBind *valbind) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_VALUE_DECLARATION;
  dec->u.value_declaration.tyvarseq = tyvarseq;
  dec->u.value_declaration.valbind = valbind;
  return dec;
}

CDec *new_c_dec_function_declaration(CTyVarList *tyvarseq,
                                     CFValBind *fvalbind) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_FUNCTION_DECLARATION;
  dec->u.function_declaration.tyvarseq = tyvarseq;
  dec->u.function_declaration.fvalbind = fvalbind;
  return dec;
}

CDec *new_c_dec_type_declaration(CTypBind *typbind) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_TYPE_DECLARATION;
  dec->u.type_declaration.typbind = typbind;
  return dec;
}

CDec *new_c_dec_datatype_declaration(CDatBind *datbind, CTypBind *typbind) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_DATATYPE_DECLARATION;
  dec->u.datatype_declaration.datbind = datbind;
  dec->u.datatype_declaration.typbind = typbind;
  return dec;
}

CDec *new_c_dec_datatype_replication(CTyCon *tycon, CLongTyCon *longtycon) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_DATATYPE_REPLICATION;
  dec->u.datatype_replication.tycon = tycon;
  dec->u.datatype_replication.longtycon = longtycon;
  return dec;
}

CDec *new_c_dec_abstype_declaration(CDatBind *datbind, CTypBind *typbind,
                                    CDec *dec) {
  CDec *abstype = (CDec *)malloc(sizeof(CDec));
  if (abstype == NULL) {
    return NULL;
  }
  abstype->kind = CDEC_ABSTYPE_DECLARATION;
  abstype->u.abstype_declaration.datbind = datbind;
  abstype->u.abstype_declaration.typbind = typbind;
  abstype->u.abstype_declaration.dec = dec;
  return abstype;
}

CDec *new_c_dec_exception_declaration(CExBind *exbind) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_EXCEPTION_DECLARATION;
  dec->u.exception_declaration.exbind = exbind;
  return dec;
}

CDec *new_c_dec_local_declaration(CDec *dec1, CDec *dec2) {
  CDec *local = (CDec *)malloc(sizeof(CDec));
  if (local == NULL) {
    return NULL;
  }
  local->kind = CDEC_LOCAL_DECLARATION;
  local->u.local_declaration.dec1 = dec1;
  local->u.local_declaration.dec2 = dec2;
  return local;
}

CDec *new_c_dec_open_declaration(CLongStrIdList *longstridlist) {
  CDec *dec = (CDec *)malloc(sizeof(CDec));
  if (dec == NULL) {
    return NULL;
  }
  dec->kind = CDEC_OPEN_DECLARATION;
  dec->u.open_declaration.longstridlist = longstridlist;
  return dec;
}

CDec *new_c_dec_sequential_declaration(CDec *dec1, CDec *dec2) {
  CDec *sequential = (CDec *)malloc(sizeof(CDec));
  if (sequential == NULL) {
    return NULL;
  }
  sequential->kind = CDEC_SEQUENTIAL_DECLARATION;
  sequential->u.sequential_declaration.dec1 = dec1;
  sequential->u.sequential_declaration.dec2 = dec2;
  return sequential;
}

CDec *new_c_dec_infix_l_directive(char *d, CVIdList *vidlist) {
  CDec *infixl = (CDec *)malloc(sizeof(CDec));
  if (infixl == NULL) {
    return NULL;
  }
  infixl->kind = CDEC_INFIX_L_DIRECTIVE;
  infixl->u.infix_l_directive.d = d;
  infixl->u.infix_l_directive.vidlist = vidlist;
  return infixl;
}

CDec *new_c_dec_infix_r_directive(char *d, CVIdList *vidlist) {
  CDec *infixr = (CDec *)malloc(sizeof(CDec));
  if (infixr == NULL) {
    return NULL;
  }
  infixr->kind = CDEC_INFIX_R_DIRECTIVE;
  infixr->u.infix_r_directive.d = d;
  infixr->u.infix_r_directive.vidlist = vidlist;
  return infixr;
}

CDec *new_c_dec_nonfix_directive(CVIdList *vidlist) {
  CDec *nonfix = (CDec *)malloc(sizeof(CDec));
  if (nonfix == NULL) {
    return NULL;
  }
  nonfix->kind = CDEC_NONFIX_DIRECTIVE;
  nonfix->u.nonfix_directive.vidlist = vidlist;
  return nonfix;
}

void free_c_dec(CDec *dec) {
  if (dec == NULL) {
    return;
  }
  switch (dec->kind) {
  case CDEC_VALUE_DECLARATION:
    free_c_tyvarlist(dec->u.value_declaration.tyvarseq);
    free_c_valbind(dec->u.value_declaration.valbind);
    break;
  case CDEC_FUNCTION_DECLARATION:
    free_c_tyvarlist(dec->u.function_declaration.tyvarseq);
    free_c_fvalbind(dec->u.function_declaration.fvalbind);
    break;
  case CDEC_TYPE_DECLARATION:
    free_c_typbind(dec->u.type_declaration.typbind);
    break;
  case CDEC_DATATYPE_DECLARATION:
    free_c_datbind(dec->u.datatype_declaration.datbind);
    if (dec->u.datatype_declaration.typbind != NULL) {
      free_c_typbind(dec->u.datatype_declaration.typbind);
    }
    break;
  case CDEC_DATATYPE_REPLICATION:
    free_c_tycon(dec->u.datatype_replication.tycon);
    free_c_longtycon(dec->u.datatype_replication.longtycon);
    break;
  case CDEC_ABSTYPE_DECLARATION:
    free_c_datbind(dec->u.abstype_declaration.datbind);
    if (dec->u.abstype_declaration.typbind != NULL) {
      free_c_typbind(dec->u.abstype_declaration.typbind);
    }
    free_c_dec(dec->u.abstype_declaration.dec);
    break;
  case CDEC_EXCEPTION_DECLARATION:
    free_c_exbind(dec->u.exception_declaration.exbind);
    break;
  case CDEC_LOCAL_DECLARATION:
    free_c_dec(dec->u.local_declaration.dec1);
    free_c_dec(dec->u.local_declaration.dec2);
    break;
  case CDEC_OPEN_DECLARATION:
    free_c_longstridlist(dec->u.open_declaration.longstridlist);
    break;
  case CDEC_EMPTY_DECLARATION:
    break;
  case CDEC_SEQUENTIAL_DECLARATION:
    free_c_dec(dec->u.sequential_declaration.dec1);
    free_c_dec(dec->u.sequential_declaration.dec2);
    break;
  case CDEC_INFIX_L_DIRECTIVE:
    free(dec->u.infix_l_directive.d);
    free_c_vidlist(dec->u.infix_l_directive.vidlist);
    break;
  case CDEC_INFIX_R_DIRECTIVE:
    free(dec->u.infix_r_directive.d);
    free_c_vidlist(dec->u.infix_r_directive.vidlist);
    break;
  case CDEC_NONFIX_DIRECTIVE:
    free_c_vidlist(dec->u.nonfix_directive.vidlist);
    break;
  }
  free(dec);
}

CValBind *new_c_valbind_bind(CPat *pat, CExp *exp, CValBind *next) {
  CValBind *bind = (CValBind *)malloc(sizeof(CValBind));
  if (bind == NULL) {
    return NULL;
  }
  bind->kind = CVALBIND_BIND;
  bind->u.bind.pat = pat;
  bind->u.bind.exp = exp;
  bind->u.bind.next = next;
  return bind;
}

CValBind *new_c_valbind_rec(CValBind *valbind) {
  CValBind *rec = (CValBind *)malloc(sizeof(CValBind));
  if (rec == NULL) {
    return NULL;
  }
  rec->kind = CVALBIND_REC;
  rec->u.rec.valbind = valbind;
  return rec;
}

void free_c_valbind(CValBind *valbind) {
  if (valbind == NULL) {
    return;
  }
  switch (valbind->kind) {
  case CVALBIND_BIND:
    free_c_pat(valbind->u.bind.pat);
    free_c_exp(valbind->u.bind.exp);
    if (valbind->u.bind.next != NULL) {
      free_c_valbind(valbind->u.bind.next);
    }
    break;
  case CVALBIND_REC:
    free_c_valbind(valbind->u.rec.valbind);
    break;
  }
  free(valbind);
}

CFMatch *new_c_fmatch(CFMrule *fmrule, CFMatch *next) {
  CFMatch *fmatch = (CFMatch *)malloc(sizeof(CFMatch));
  if (fmatch == NULL) {
    return NULL;
  }
  fmatch->fmrule = fmrule;
  fmatch->next = next;
  return fmatch;
}

void free_c_fmatch(CFMatch *fmatch) {
  if (fmatch == NULL) {
    return;
  }
  free_c_fmrule(fmatch->fmrule);
  CFMatch *tmp = fmatch->next;
  free(fmatch);
  if (tmp != NULL) {
    free_c_fmatch(tmp);
  }
}

CFMrule *new_c_fmrule(CAtPatList *atpatlist, CTy *ty, CExp *exp) {
  CFMrule *fmrule = (CFMrule *)malloc(sizeof(CFMrule));
  if (fmrule == NULL) {
    return NULL;
  }
  fmrule->atpatlist = atpatlist;
  fmrule->ty = ty;
  fmrule->exp = exp;
  return fmrule;
}

void free_c_fmrule(CFMrule *fmrule) {
  if (fmrule == NULL) {
    return;
  }
  free_c_atpatlist(fmrule->atpatlist);
  if (fmrule->ty != NULL) {
    free_c_ty(fmrule->ty);
  }
  free_c_exp(fmrule->exp);
  free(fmrule);
}

CFValBind *new_c_fvalbind(CFMatch *fmatch, CFValBind *next) {
  CFValBind *fvalbind = (CFValBind *)malloc(sizeof(CFValBind));
  if (fvalbind == NULL) {
    return NULL;
  }
  fvalbind->fmatch = fmatch;
  fvalbind->next = next;
  return fvalbind;
}

void free_c_fvalbind(CFValBind *fvalbind) {
  if (fvalbind == NULL) {
    return;
  }
  free_c_fmatch(fvalbind->fmatch);
  CFValBind *tmp = fvalbind->next;
  free(fvalbind);
  if (tmp != NULL) {
    free_c_fvalbind(tmp);
  }
}

CTypBind *new_c_typbind(CTyVarList *tyvarseq, CTyCon *tycon, CTy *ty,
                        CTypBind *next) {
  CTypBind *typbind = (CTypBind *)malloc(sizeof(CTypBind));
  if (typbind == NULL) {
    return NULL;
  }
  typbind->tyvarseq = tyvarseq;
  typbind->tycon = tycon;
  typbind->ty = ty;
  typbind->next = next;
  return typbind;
}

void free_c_typbind(CTypBind *typbind) {
  if (typbind == NULL) {
    return;
  }
  if (typbind->tyvarseq != NULL) {
    free_c_tyvarlist(typbind->tyvarseq);
  }
  free_c_tycon(typbind->tycon);
  free_c_ty(typbind->ty);
  CTypBind *tmp = typbind->next;
  free(typbind);
  if (tmp != NULL) {
    free_c_typbind(tmp);
  }
}

CDatBind *new_c_datbind(CTyVarList *tyvarseq, CTyCon *tycon, CConBind *conbind,
                        CDatBind *next) {
  CDatBind *datbind = (CDatBind *)malloc(sizeof(CDatBind));
  if (datbind == NULL) {
    return NULL;
  }
  datbind->tyvarseq = tyvarseq;
  datbind->tycon = tycon;
  datbind->conbind = conbind;
  datbind->next = next;
  return datbind;
}

void free_c_datbind(CDatBind *datbind) {
  if (datbind == NULL) {
    return;
  }
  if (datbind->tyvarseq != NULL) {
    free_c_tyvarlist(datbind->tyvarseq);
  }
  free_c_tycon(datbind->tycon);
  free_c_conbind(datbind->conbind);
  CDatBind *tmp = datbind->next;
  free(datbind);
  if (tmp != NULL) {
    free_c_datbind(tmp);
  }
}

CConBind *new_c_conbind(bool op_prefixed, CVId *vid, CTy *ty, CConBind *next) {
  CConBind *conbind = (CConBind *)malloc(sizeof(CConBind));
  if (conbind == NULL) {
    return NULL;
  }
  conbind->op_prefixed = op_prefixed;
  conbind->vid = vid;
  conbind->ty = ty;
  conbind->next = next;
  return conbind;
}

void free_c_conbind(CConBind *conbind) {
  if (conbind == NULL) {
    return;
  }
  free_c_vid(conbind->vid);
  if (conbind->ty != NULL) {
    free_c_ty(conbind->ty);
  }
  CConBind *tmp = conbind->next;
  free(conbind);
  if (tmp != NULL) {
    free_c_conbind(tmp);
  }
}

CExBind *new_c_exbind_declaration(bool op_prefixed, CVId *vid, CTy *ty,
                                  CExBind *next) {
  CExBind *exbind = (CExBind *)malloc(sizeof(CExBind));
  if (exbind == NULL) {
    return NULL;
  }
  exbind->kind = CEXBIND_DECLARATION;
  exbind->u.declaration.op_prefixed = op_prefixed;
  exbind->u.declaration.vid = vid;
  exbind->u.declaration.ty = ty;
  exbind->next = next;
  return exbind;
}

CExBind *new_c_exbind_replication(bool op_prefixed_vid, CVId *vid,
                                  bool op_prefixed_longvid, CLongVId *longvid,
                                  CExBind *next) {
  CExBind *exbind = (CExBind *)malloc(sizeof(CExBind));
  if (exbind == NULL) {
    return NULL;
  }
  exbind->kind = CEXBIND_REPLICATION;
  exbind->u.replication.op_prefixed_vid = op_prefixed_vid;
  exbind->u.replication.vid = vid;
  exbind->u.replication.op_prefixed_longvid = op_prefixed_longvid;
  exbind->u.replication.longvid = longvid;
  exbind->next = next;
  return exbind;
}

void free_c_exbind(CExBind *exbind) {
  if (exbind == NULL) {
    return;
  }
  switch (exbind->kind) {
  case CEXBIND_DECLARATION:
    free_c_vid(exbind->u.declaration.vid);
    if (exbind->u.declaration.ty != NULL) {
      free_c_ty(exbind->u.declaration.ty);
    }
    break;
  case CEXBIND_REPLICATION:
    free_c_vid(exbind->u.replication.vid);
    free_c_longvid(exbind->u.replication.longvid);
    break;
  }
  CExBind *tmp = exbind->next;
  free(exbind);
  if (tmp != NULL) {
    free_c_exbind(tmp);
  }
}
