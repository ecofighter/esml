#include <stdio.h>

#include "concrete_syntax.h"
#include "pp.h"

static void print_indent(FILE *fp, int indent) {
  for (int i = 0; i < indent; i++) {
    fprintf(fp, "  ");
  }
}

void print_c_vid(FILE *fp, CVId *vid, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CVId: value=%s\n", vid->value);
}

void print_c_vidlist(FILE *fp, CVIdList *vidlist, int indent) {
  if (!vidlist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CVIdList:\n");
  print_c_vid(fp, vidlist->vid, indent + 1);
  print_c_vidlist(fp, vidlist->next, indent + 1);
}

void print_c_qualified_vid(FILE *fp, CQualifiedVId *qvid, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CQualifiedVId: value=%s\n", qvid->value);
}

void print_c_longvid(FILE *fp, CLongVId *longvid, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CLongVId: kind=%s\n",
          longvid->kind == CLONGVID_NONQUALIFIED ? "nonqualified"
                                                 : "qualified");
  if (longvid->kind == CLONGVID_NONQUALIFIED) {
    print_c_vid(fp, longvid->u.nonqualified.vid, indent + 1);
  } else {
    print_c_qualified_vid(fp, longvid->u.qualified.qualified_vid, indent + 1);
  }
}

void print_c_tyvar(FILE *fp, CTyVar *tyvar, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CTyVar: value=%s\n", tyvar->value);
}

void print_c_tyvarlist(FILE *fp, CTyVarList *tyvarlist, int indent) {
  if (!tyvarlist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CTyVarList:\n");
  print_c_tyvar(fp, tyvarlist->tyvar, indent + 1);
  print_c_tyvarlist(fp, tyvarlist->next, indent + 1);
}

void print_c_tycon(FILE *fp, CTyCon *tycon, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CTyCon: value=%s\n", tycon->value);
}

void print_c_qualified_tycon(FILE *fp, CQualifiedTyCon *qtycon, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CQualifiedTyCon: value=%s\n", qtycon->value);
}

void print_c_longtycon(FILE *fp, CLongTyCon *longtycon, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CLongTyCon: kind=%s\n",
          longtycon->kind == CLONGTYCON_NONQUALIFIED ? "nonqualified"
                                                     : "qualified");
  if (longtycon->kind == CLONGTYCON_NONQUALIFIED) {
    print_c_tycon(fp, longtycon->u.nonqualified.tycon, indent + 1);
  } else {
    print_c_qualified_tycon(fp, longtycon->u.qualified.qualified_tycon,
                            indent + 1);
  }
}

void print_c_lab(FILE *fp, CLab *lab, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CLab: kind=%s value=%s\n",
          lab->kind == CLAB_ALPHANUMERIC ? "alphanumeric" : "numeric",
          lab->value);
}

void print_c_strid(FILE *fp, CStrId *strid, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CStrId: value=%s\n", strid->value);
}

void print_c_qualified_strid(FILE *fp, CQualifiedStrId *qstrid, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CQualifiedStrId: value=%s\n", qstrid->value);
}

void print_c_longstrid(FILE *fp, CLongStrId *longstrid, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CLongStrId: kind=%s\n",
          longstrid->kind == CLONGSTRID_NONQUALIFIED ? "nonqualified"
                                                     : "qualified");
  if (longstrid->kind == CLONGSTRID_NONQUALIFIED) {
    print_c_strid(fp, longstrid->u.nonqualified.strid, indent + 1);
  } else {
    print_c_qualified_strid(fp, longstrid->u.qualified.qualified_strid,
                            indent + 1);
  }
}

void print_c_longstridlist(FILE *fp, CLongStrIdList *longstridlist,
                           int indent) {
  if (!longstridlist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CLongStrIdList:\n");
  print_c_longstrid(fp, longstridlist->longstrid, indent + 1);
  print_c_longstridlist(fp, longstridlist->next, indent + 1);
}

void print_c_constant(FILE *fp, CConstant *constant, int indent) {
  print_indent(fp, indent);
  fprintf(fp, "CConstant: kind=integer value=%s\n", constant->u.value);
}

void print_c_atpat(FILE *fp, CAtPat *atpat, int indent) {
  if (!atpat)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CAtPat: kind=");
  switch (atpat->kind) {
  case CATPAT_WILDCARD:
    fprintf(fp, "wildcard\n");
    break;
  case CATPAT_SPECIAL_CONSTANT:
    fprintf(fp, "special_constant\n");
    print_c_constant(fp, atpat->u.special_constant.scon, indent + 1);
    break;
  case CATPAT_VALUE_IDENTIFIER:
    fprintf(fp, "value_identifier op_prefixed=%d\n",
            atpat->u.value_identifier.op_prefixed);
    print_c_longvid(fp, atpat->u.value_identifier.longvid, indent + 1);
    break;
  case CATPAT_RECORD:
    fprintf(fp, "record\n");
    print_c_patrow(fp, atpat->u.record.patrow, indent + 1);
    break;
  case CATPAT_ZERO_TUPLE:
    fprintf(fp, "zero_tuple\n");
    break;
  case CATPAT_N_TUPLE:
    fprintf(fp, "n_tuple\n");
    print_c_patlist(fp, atpat->u.n_tuple.patlist, indent + 1);
    break;
  case CATPAT_LIST:
    fprintf(fp, "list\n");
    print_c_patlist(fp, atpat->u.list.patlist, indent + 1);
    break;
  case CATPAT_PARENED_PAT:
    fprintf(fp, "parened_pat\n");
    print_c_pat(fp, atpat->u.parened_pat.pat, indent + 1);
    break;
  }
}

void print_c_atpatlist(FILE *fp, CAtPatList *atpatlist, int indent) {
  if (!atpatlist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CAtPatList:\n");
  print_c_atpat(fp, atpatlist->atpat, indent + 1);
  print_c_atpatlist(fp, atpatlist->next, indent + 1);
}

void print_c_patrow(FILE *fp, CPatRow *patrow, int indent) {
  if (!patrow)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CPatRow: kind=");
  switch (patrow->kind) {
  case CPATROW_WILDCARD:
    fprintf(fp, "wildcard\n");
    break;
  case CPATROW_PATTERN_ROW:
    fprintf(fp, "pattern_row\n");
    print_c_lab(fp, patrow->u.pattern_row.lab, indent + 1);
    print_c_pat(fp, patrow->u.pattern_row.pat, indent + 1);
    print_c_patrow(fp, patrow->u.pattern_row.next, indent + 1);
    break;
  case CPATROW_LABEL_AS_VARIABLE:
    fprintf(fp, "label_as_variable\n");
    print_c_vid(fp, patrow->u.label_as_variable.vid, indent + 1);
    if (patrow->u.label_as_variable.ty) {
      print_c_ty(fp, patrow->u.label_as_variable.ty, indent + 1);
    }
    print_c_pat(fp, patrow->u.label_as_variable.pat, indent + 1);
    print_c_patrow(fp, patrow->u.label_as_variable.next, indent + 1);
    break;
  }
}

void print_c_pat(FILE *fp, CPat *pat, int indent) {
  if (!pat)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CPat: kind=");
  switch (pat->kind) {
  case CPAT_ATOMIC:
    fprintf(fp, "atomic\n");
    print_c_atpat(fp, pat->u.atomic.atpat, indent + 1);
    break;
  case CPAT_ATPATLIST:
    fprintf(fp, "atpatlist\n");
    print_c_atpatlist(fp, pat->u.atpatlist.atpatlist, indent + 1);
    break;
  case CPAT_TYPED:
    fprintf(fp, "typed\n");
    print_c_pat(fp, pat->u.typed.pat, indent + 1);
    print_c_ty(fp, pat->u.typed.ty, indent + 1);
    break;
  case CPAT_LAYERED:
    fprintf(fp, "layered op_prefixed=%d\n", pat->u.layered.op_prefixed);
    print_c_vid(fp, pat->u.layered.vid, indent + 1);
    if (pat->u.layered.ty) {
      print_c_ty(fp, pat->u.layered.ty, indent + 1);
    }
    print_c_pat(fp, pat->u.layered.pat, indent + 1);
    break;
  }
}

void print_c_patlist(FILE *fp, CPatList *patlist, int indent) {
  if (!patlist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CPatList:\n");
  print_c_pat(fp, patlist->pat, indent + 1);
  print_c_patlist(fp, patlist->next, indent + 1);
}

void print_c_ty(FILE *fp, CTy *ty, int indent) {
  if (!ty)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CTy: kind=");
  switch (ty->kind) {
  case CTY_TYPE_VARIABLE:
    fprintf(fp, "type_variable\n");
    print_c_tyvar(fp, ty->u.type_variable.tyvar, indent + 1);
    break;
  case CTY_RECORD_TYPE_EXPRESSION:
    fprintf(fp, "record_type_expression\n");
    print_c_tyrow(fp, ty->u.record_type_expression.tyrow, indent + 1);
    break;
  case CTY_TYPE_CONSTRUCTION:
    fprintf(fp, "type_construction\n");
    print_c_tylist(fp, ty->u.type_construction.tylist, indent + 1);
    print_c_longtycon(fp, ty->u.type_construction.longtycon, indent + 1);
    break;
  case CTY_TUPLE_TYPE:
    fprintf(fp, "tuple_type\n");
    print_c_tylist(fp, ty->u.tuple_type.tylist, indent + 1);
    break;
  case CTY_FUNCTION_TYPE_EXPRESSION:
    fprintf(fp, "function_type_expression\n");
    print_c_ty(fp, ty->u.function_type_expression.arg_ty, indent + 1);
    print_c_ty(fp, ty->u.function_type_expression.res_ty, indent + 1);
    break;
  case CTY_PARENED_TY:
    fprintf(fp, "parened_ty\n");
    print_c_ty(fp, ty->u.parened_ty.ty, indent + 1);
    break;
  }
}

void print_c_tylist(FILE *fp, CTyList *tylist, int indent) {
  if (!tylist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CTyList:\n");
  print_c_ty(fp, tylist->ty, indent + 1);
  print_c_tylist(fp, tylist->next, indent + 1);
}

void print_c_tyrow(FILE *fp, CTyRow *tyrow, int indent) {
  if (!tyrow)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CTyRow:\n");
  print_c_lab(fp, tyrow->lab, indent + 1);
  print_c_ty(fp, tyrow->ty, indent + 1);
  print_c_tyrow(fp, tyrow->next, indent + 1);
}

// Expression-related printing functions
void print_c_atexp(FILE *fp, CAtExp *atexp, int indent) {
  if (!atexp)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CAtExp: kind=");
  switch (atexp->kind) {
  case CATEXP_SPECIAL_CONSTANT:
    fprintf(fp, "special_constant\n");
    print_c_constant(fp, atexp->u.special_constant.scon, indent + 1);
    break;
  case CATEXP_VALUE_IDENTIFIER:
    fprintf(fp, "value_identifier op_prefixed=%d\n",
            atexp->u.value_identifier.op_prefixed);
    print_c_longvid(fp, atexp->u.value_identifier.longvid, indent + 1);
    break;
  case CATEXP_RECORD:
    fprintf(fp, "record\n");
    print_c_exprow(fp, atexp->u.record.exprow, indent + 1);
    break;
  case CATEXP_RECORD_SELECTOR:
    fprintf(fp, "record_selector\n");
    print_c_lab(fp, atexp->u.record_selector.lab, indent + 1);
    break;
  case CATEXP_ZERO_TUPLE:
    fprintf(fp, "zero_tuple\n");
    break;
  case CATEXP_N_TUPLE:
    fprintf(fp, "n_tuple\n");
    print_c_explist(fp, atexp->u.n_tuple.explist, indent + 1);
    break;
  case CATEXP_LIST:
    fprintf(fp, "list\n");
    print_c_explist(fp, atexp->u.list.explist, indent + 1);
    break;
  case CATEXP_SEQUENCE:
    fprintf(fp, "sequence\n");
    print_c_explist(fp, atexp->u.sequence.explist, indent + 1);
    break;
  case CATEXP_LOCAL_DECLARATION:
    fprintf(fp, "local_declaration\n");
    print_c_dec(fp, atexp->u.local_declaration.dec, indent + 1);
    print_c_exp(fp, atexp->u.local_declaration.exp, indent + 1);
    break;
  case CATEXP_PARENED_EXP:
    fprintf(fp, "parened_exp\n");
    print_c_exp(fp, atexp->u.parened_exp.exp, indent + 1);
    break;
  }
}

void print_c_atexplist(FILE *fp, CAtExpList *atexplist, int indent) {
  if (!atexplist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CAtExpList:\n");
  print_c_atexp(fp, atexplist->atexp, indent + 1);
  print_c_atexplist(fp, atexplist->next, indent + 1);
}

void print_c_exprow(FILE *fp, CExpRow *exprow, int indent) {
  if (!exprow)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CExpRow:\n");
  print_c_lab(fp, exprow->lab, indent + 1);
  print_c_exp(fp, exprow->exp, indent + 1);
  print_c_exprow(fp, exprow->next, indent + 1);
}

void print_c_exp(FILE *fp, CExp *exp, int indent) {
  if (!exp)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CExp: kind=");
  switch (exp->kind) {
  case CEXP_ATOMIC:
    fprintf(fp, "atomic\n");
    print_c_atexp(fp, exp->u.atomic.atexp, indent + 1);
    break;
  case CEXP_ATEXPLIST:
    fprintf(fp, "atexplist\n");
    print_c_atexplist(fp, exp->u.atexplist.atexplist, indent + 1);
    break;
  case CEXP_TYPED:
    fprintf(fp, "typed\n");
    print_c_exp(fp, exp->u.typed.exp, indent + 1);
    print_c_ty(fp, exp->u.typed.ty, indent + 1);
    break;
  case CEXP_CONJUNCTION:
    fprintf(fp, "conjunction\n");
    print_c_exp(fp, exp->u.conjunction.exp1, indent + 1);
    print_c_exp(fp, exp->u.conjunction.exp2, indent + 1);
    break;
  case CEXP_DISJUNCTION:
    fprintf(fp, "disjunction\n");
    print_c_exp(fp, exp->u.disjunction.exp1, indent + 1);
    print_c_exp(fp, exp->u.disjunction.exp2, indent + 1);
    break;
  case CEXP_HANDLE_EXCEPTION:
    fprintf(fp, "handle_exception\n");
    print_c_exp(fp, exp->u.handle_exception.exp, indent + 1);
    print_c_match(fp, exp->u.handle_exception.match, indent + 1);
    break;
  case CEXP_RAISE_EXCEPTION:
    fprintf(fp, "raise_exception\n");
    print_c_exp(fp, exp->u.raise_exception.exp, indent + 1);
    break;
  case CEXP_CONDITIONAL:
    fprintf(fp, "conditional\n");
    print_c_exp(fp, exp->u.conditional.exp1, indent + 1);
    print_c_exp(fp, exp->u.conditional.exp2, indent + 1);
    print_c_exp(fp, exp->u.conditional.exp2, indent + 1);
    break;
  case CEXP_ITERATION:
    fprintf(fp, "iteration\n");
    print_c_exp(fp, exp->u.iteration.exp1, indent + 1);
    print_c_exp(fp, exp->u.iteration.exp2, indent + 1);
    break;
  case CEXP_CASE_ANALYSIS:
    fprintf(fp, "case_analysis\n");
    print_c_exp(fp, exp->u.case_analysis.exp, indent + 1);
    print_c_match(fp, exp->u.case_analysis.match, indent + 1);
    break;
  case CEXP_FUNCTION:
    fprintf(fp, "function\n");
    print_c_match(fp, exp->u.function.match, indent + 1);
    break;
  }
}

void print_c_explist(FILE *fp, CExpList *explist, int indent) {
  if (!explist)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CExpList:\n");
  print_c_exp(fp, explist->exp, indent + 1);
  print_c_explist(fp, explist->next, indent + 1);
}

void print_c_match(FILE *fp, CMatch *match, int indent) {
  if (!match)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CMatch:\n");
  print_c_mrule(fp, match->mrule, indent + 1);
  print_c_match(fp, match->next, indent + 1);
}

void print_c_mrule(FILE *fp, CMrule *mrule, int indent) {
  if (!mrule)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CMrule:\n");
  print_c_pat(fp, mrule->pat, indent + 1);
  print_c_exp(fp, mrule->exp, indent + 1);
}

void print_c_dec(FILE *fp, CDec *dec, int indent) {
  if (!dec)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CDec: kind=");
  switch (dec->kind) {
  case CDEC_VALUE_DECLARATION:
    fprintf(fp, "value_declaration\n");
    if (dec->u.value_declaration.tyvarseq) {
      print_c_tyvarlist(fp, dec->u.value_declaration.tyvarseq, indent + 1);
    }
    print_c_valbind(fp, dec->u.value_declaration.valbind, indent + 1);
    break;
  case CDEC_FUNCTION_DECLARATION:
    fprintf(fp, "function_declaration\n");
    if (dec->u.function_declaration.tyvarseq) {
      print_c_tyvarlist(fp, dec->u.function_declaration.tyvarseq, indent + 1);
    }
    print_c_fvalbind(fp, dec->u.function_declaration.fvalbind, indent + 1);
    break;
  case CDEC_TYPE_DECLARATION:
    fprintf(fp, "type_declaration\n");
    print_c_typbind(fp, dec->u.type_declaration.typbind, indent + 1);
    break;
  case CDEC_DATATYPE_DECLARATION:
    fprintf(fp, "datatype_declaration\n");
    print_c_datbind(fp, dec->u.datatype_declaration.datbind, indent + 1);
    if (dec->u.datatype_declaration.typbind) {
      print_c_typbind(fp, dec->u.datatype_declaration.typbind, indent + 1);
    }
    break;
  case CDEC_DATATYPE_REPLICATION:
    fprintf(fp, "datatype_replication\n");
    print_c_tycon(fp, dec->u.datatype_replication.tycon, indent + 1);
    print_c_longtycon(fp, dec->u.datatype_replication.longtycon, indent + 1);
    break;
  case CDEC_ABSTYPE_DECLARATION:
    fprintf(fp, "abstype_declaration\n");
    print_c_datbind(fp, dec->u.abstype_declaration.datbind, indent + 1);
    if (dec->u.abstype_declaration.typbind) {
      print_c_typbind(fp, dec->u.abstype_declaration.typbind, indent + 1);
    }
    print_c_dec(fp, dec->u.abstype_declaration.dec, indent + 1);
    break;
  case CDEC_EXCEPTION_DECLARATION:
    fprintf(fp, "exception_declaration\n");
    print_c_exbind(fp, dec->u.exception_declaration.exbind, indent + 1);
    break;
  case CDEC_LOCAL_DECLARATION:
    fprintf(fp, "local_declaration\n");
    print_c_dec(fp, dec->u.local_declaration.dec1, indent + 1);
    print_c_dec(fp, dec->u.local_declaration.dec2, indent + 1);
    break;
  case CDEC_OPEN_DECLARATION:
    fprintf(fp, "open_declaration\n");
    print_c_longstridlist(fp, dec->u.open_declaration.longstridlist,
                          indent + 1);
    break;
  case CDEC_EMPTY_DECLARATION:
    fprintf(fp, "empty_declaration\n");
    break;
  case CDEC_SEQUENTIAL_DECLARATION:
    fprintf(fp, "sequential_declaration\n");
    print_c_dec(fp, dec->u.sequential_declaration.dec1, indent + 1);
    print_c_dec(fp, dec->u.sequential_declaration.dec2, indent + 1);
    break;
  case CDEC_INFIX_L_DIRECTIVE:
    fprintf(fp, "infix_l_directive\n");
    if (dec->u.infix_l_directive.d) {
      print_indent(fp, indent + 1);
      fprintf(fp, "precedence=%s\n", dec->u.infix_l_directive.d);
    }
    print_c_vidlist(fp, dec->u.infix_l_directive.vidlist, indent + 1);
    break;
  case CDEC_INFIX_R_DIRECTIVE:
    fprintf(fp, "infix_r_directive\n");
    if (dec->u.infix_r_directive.d) {
      print_indent(fp, indent + 1);
      fprintf(fp, "precedence=%s\n", dec->u.infix_r_directive.d);
    }
    print_c_vidlist(fp, dec->u.infix_r_directive.vidlist, indent + 1);
    break;
  case CDEC_NONFIX_DIRECTIVE:
    fprintf(fp, "nonfix_directive\n");
    print_c_vidlist(fp, dec->u.nonfix_directive.vidlist, indent + 1);
    break;
  }
}

void print_c_valbind(FILE *fp, CValBind *valbind, int indent) {
  if (!valbind)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CValBind: kind=");
  switch (valbind->kind) {
  case CVALBIND_BIND:
    fprintf(fp, "bind\n");
    print_c_pat(fp, valbind->u.bind.pat, indent + 1);
    print_c_exp(fp, valbind->u.bind.exp, indent + 1);
    break;
  case CVALBIND_REC:
    fprintf(fp, "rec\n");
    print_c_valbind(fp, valbind->u.rec.valbind, indent + 1);
    break;
  }
}

void print_c_fvalbind(FILE *fp, CFValBind *fvalbind, int indent) {
  if (!fvalbind)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CFValBind:\n");
  print_c_fmatch(fp, fvalbind->fmatch, indent + 1);
  if (fvalbind->next) {
    print_c_fvalbind(fp, fvalbind->next, indent + 1);
  }
}

void print_c_fmatch(FILE *fp, CFMatch *fmatch, int indent) {
  if (!fmatch)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CFMatch:\n");
  print_c_fmrule(fp, fmatch->fmrule, indent + 1);
  if (fmatch->next) {
    print_c_fmatch(fp, fmatch->next, indent + 1);
  }
}

void print_c_fmrule(FILE *fp, CFMrule *fmrule, int indent) {
  if (!fmrule)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CFMrule:\n");
  print_c_atpatlist(fp, fmrule->atpatlist, indent + 1);
  if (fmrule->ty) {
    print_c_ty(fp, fmrule->ty, indent + 1);
  }
  print_c_exp(fp, fmrule->exp, indent + 1);
}

void print_c_typbind(FILE *fp, CTypBind *typbind, int indent) {
  if (!typbind)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CTypBind:\n");
  if (typbind->tyvarseq) {
    print_c_tyvarlist(fp, typbind->tyvarseq, indent + 1);
  }
  print_c_tycon(fp, typbind->tycon, indent + 1);
  print_c_ty(fp, typbind->ty, indent + 1);
  if (typbind->next) {
    print_c_typbind(fp, typbind->next, indent + 1);
  }
}

void print_c_datbind(FILE *fp, CDatBind *datbind, int indent) {
  if (!datbind)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CDatBind:\n");
  if (datbind->tyvarseq) {
    print_c_tyvarlist(fp, datbind->tyvarseq, indent + 1);
  }
  print_c_tycon(fp, datbind->tycon, indent + 1);
  print_c_conbind(fp, datbind->conbind, indent + 1);
  if (datbind->next) {
    print_c_datbind(fp, datbind->next, indent + 1);
  }
}

void print_c_conbind(FILE *fp, CConBind *conbind, int indent) {
  if (!conbind)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CConBind:\n");
  if (conbind->op_prefixed) {
    print_indent(fp, indent + 1);
    fprintf(fp, "op_prefixed\n");
  }
  print_c_vid(fp, conbind->vid, indent + 1);
  print_c_ty(fp, conbind->ty, indent + 1);
  if (conbind->next) {
    print_c_conbind(fp, conbind->next, indent + 1);
  }
}

void print_c_exbind(FILE *fp, CExBind *exbind, int indent) {
  if (!exbind)
    return;
  print_indent(fp, indent);
  fprintf(fp, "CExBind: kind=");
  switch (exbind->kind) {
  case CEXBIND_DECLARATION:
    fprintf(fp, "declaration\n");
    if (exbind->u.declaration.op_prefixed) {
      print_indent(fp, indent + 1);
      fprintf(fp, "op_prefixed\n");
    }
    print_c_vid(fp, exbind->u.declaration.vid, indent + 1);
    print_c_ty(fp, exbind->u.declaration.ty, indent + 1);
    break;
  case CEXBIND_REPLICATION:
    fprintf(fp, "replication\n");
    if (exbind->u.replication.op_prefixed_vid) {
      print_indent(fp, indent + 1);
      fprintf(fp, "op_prefixed\n");
    }
    print_c_vid(fp, exbind->u.replication.vid, indent + 1);
    if (exbind->u.replication.op_prefixed_longvid) {
      print_indent(fp, indent + 1);
      fprintf(fp, "op_prefixed\n");
    }
    print_c_longvid(fp, exbind->u.replication.longvid, indent + 1);
    break;
  }
  if (exbind->next) {
    print_c_exbind(fp, exbind->next, indent + 1);
  }
}
