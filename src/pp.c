#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INDENT_WIDTH 2

static void print_vid(FILE *out, VId *vid);
static void print_vidlist(FILE *out, VIdList *vidlist, int indent);
static void print_qualified_vid(FILE *out, QualifiedVId *qualified_vid);
static void print_longvid(FILE *out, LongVId *longvid);
static void print_tyvar(FILE *out, TyVar *tyvar);
static void print_tyvarseq(FILE *out, TyVarSeq *tyvarseq);
static void print_tycon(FILE *out, TyCon *tycon);
static void print_qualified_tycon(FILE *out, QualifiedTyCon *qualified_tycon);
static void print_longtycon(FILE *out, LongTyCon *longtycon);
static void print_lab(FILE *out, Lab *lab);
static void print_strid(FILE *out, StrId *strid);
static void print_qualified_strid(FILE *out, QualifiedStrId *qualified_strid);
static void print_longstrid(FILE *out, LongStrId *longstrid);
static void print_longstridlist(FILE *out, LongStrIdList *longstridlist,
                                int indent);
static void print_constant(FILE *out, Constant *constant);
static void print_atpat(FILE *out, AtPat *atpat, int indent);
static void print_patrow(FILE *out, PatRow *patrow, int indent);
static void print_pat(FILE *out, Pat *pat, int indent);
static void print_ty(FILE *out, Ty *ty, int indent);
static void print_tyseq(FILE *out, TySeq *tyseq, int indent);
static void print_tyrow(FILE *out, TyRow *tyrow, int indent);
static void print_atexp(FILE *out, AtExp *atexp, int indent);
static void print_exprow(FILE *out, ExpRow *exprow, int indent);
static void print_exp(FILE *out, Exp *exp, int indent);
static void print_match(FILE *out, Match *match, int indent);
static void print_mrule(FILE *out, Mrule *mrule, int indent);
static void print_dec(FILE *out, Dec *dec, int indent);
static void print_valbind(FILE *out, ValBind *valbind, int indent);
static void print_typbind(FILE *out, TypBind *typbind, int indent);
static void print_datbind(FILE *out, DatBind *datbind, int indent);
static void print_conbind(FILE *out, ConBind *conbind, int indent);
static void print_exbind(FILE *out, ExBind *exbind, int indent);

static void print_indent(FILE *out, int indent) {
  for (int i = 0; i < indent; i++) {
    fprintf(out, " ");
  }
}

void print_vid(FILE *out, VId *vid) { fprintf(out, "%s", vid->value); }

void print_vidlist(FILE *out, VIdList *vidlist, int indent) {
  if (vidlist == NULL)
    return;
  print_vid(out, vidlist->vid);
  if (vidlist->next) {
    fprintf(out, " ");
    print_vidlist(out, vidlist->next, indent);
  }
}

void print_qualified_vid(FILE *out, QualifiedVId *qualified_vid) {
  fprintf(out, "%s", qualified_vid->value);
}

void print_longvid(FILE *out, LongVId *longvid) {
  switch (longvid->kind) {
  case LONGVID_NONQUALIFIED:
    print_vid(out, longvid->u.nonqualified.vid);
    break;
  case LONGVID_QUALIFIED:
    print_qualified_vid(out, longvid->u.qualified.qualified_vid);
    break;
  }
}

void print_tyvar(FILE *out, TyVar *tyvar) { fprintf(out, "%s", tyvar->value); }

void print_tyvarseq(FILE *out, TyVarSeq *tyvarseq) {
  if (tyvarseq == NULL)
    return;
  print_tyvar(out, tyvarseq->tyvar);
  if (tyvarseq->next) {
    fprintf(out, ", ");
    print_tyvarseq(out, tyvarseq->next);
  }
}

void print_tycon(FILE *out, TyCon *tycon) { fprintf(out, "%s", tycon->value); }

void print_qualified_tycon(FILE *out, QualifiedTyCon *qualified_tycon) {
  fprintf(out, "%s", qualified_tycon->value);
}

void print_longtycon(FILE *out, LongTyCon *longtycon) {
  switch (longtycon->kind) {
  case LONGTYCON_NONQUALIFIED:
    print_tycon(out, longtycon->u.nonqualified.tycon);
    break;
  case LONGTYCON_QUALIFIED:
    print_qualified_tycon(out, longtycon->u.qualified.qualified_tycon);
    break;
  }
}

void print_lab(FILE *out, Lab *lab) { fprintf(out, "%s", lab->value); }

void print_strid(FILE *out, StrId *strid) { fprintf(out, "%s", strid->value); }

void print_qualified_strid(FILE *out, QualifiedStrId *qualified_strid) {
  fprintf(out, "%s", qualified_strid->value);
}

void print_longstrid(FILE *out, LongStrId *longstrid) {
  switch (longstrid->kind) {
  case LONGSTRID_NONQUALIFIED:
    print_strid(out, longstrid->u.nonqualified.strid);
    break;
  case LONGSTRID_QUALIFIED:
    print_qualified_strid(out, longstrid->u.qualified.qualified_strid);
    break;
  }
}

void print_longstridlist(FILE *out, LongStrIdList *longstridlist, int indent) {
  if (longstridlist == NULL)
    return;
  print_longstrid(out, longstridlist->longstrid);
  if (longstridlist->next) {
    fprintf(out, " ");
    print_longstridlist(out, longstridlist->next, indent);
  }
}

void print_constant(FILE *out, Constant *constant) {
  switch (constant->kind) {
  case CONSTANT_INTEGER:
    fprintf(out, "%s", constant->u.value);
    break;
  }
}

void print_atpat(FILE *out, AtPat *atpat, int indent) {
  switch (atpat->kind) {
  case ATPAT_WILDCARD:
    fprintf(out, "_");
    break;
  case ATPAT_SPECIAL_CONSTANT:
    print_constant(out, atpat->u.special_constant.scon);
    break;
  case ATPAT_VALUE_IDENTIFIER:
    if (atpat->u.value_identifier.op_prefixed) {
      fprintf(out, "op ");
    }
    print_longvid(out, atpat->u.value_identifier.longvid);
    break;
  case ATPAT_RECORD:
    fprintf(out, "{");
    if (atpat->u.record.patrow) {
      print_patrow(out, atpat->u.record.patrow, indent + INDENT_WIDTH);
    }
    fprintf(out, "}");
    break;
  case ATPAT_PARENED_PAT:
    fprintf(out, "(");
    print_pat(out, atpat->u.parened_pat.pat, 0);
    fprintf(out, ")");
    break;
  }
}

void print_patrow(FILE *out, PatRow *patrow, int indent) {
  switch (patrow->kind) {
  case PATROW_WILDCARD:
    fprintf(out, "...");
    break;
  case PATROW_PATTERN_ROW:
    print_lab(out, patrow->u.pattern_row.lab);
    fprintf(out, " = ");
    print_pat(out, patrow->u.pattern_row.pat, indent);
    if (patrow->u.pattern_row.next) {
      fprintf(out, ",\n");
      print_indent(out, indent);
      print_patrow(out, patrow->u.pattern_row.next, indent);
    }
    break;
  }
}

void print_pat(FILE *out, Pat *pat, int indent) {
  switch (pat->kind) {
  case PAT_ATOMIC:
    print_atpat(out, pat->u.atomic.atpat, indent);
    break;
  case PAT_CONSTRUCTED_PATTERN:
    if (pat->u.constructed_pattern.op_prefixed) {
      fprintf(out, "op ");
    }
    print_longvid(out, pat->u.constructed_pattern.longvid);
    fprintf(out, " ");
    print_atpat(out, pat->u.constructed_pattern.atpat, indent);
    break;
  case PAT_INFIXED_VALUE_CONSTRUCTION:
    print_pat(out, pat->u.infixed_value_construction.pat1, indent);
    fprintf(out, " ");
    print_vid(out, pat->u.infixed_value_construction.vid);
    fprintf(out, " ");
    print_pat(out, pat->u.infixed_value_construction.pat2, indent);
    break;
  case PAT_TYPED:
    print_pat(out, pat->u.typed.pat, indent);
    fprintf(out, " : ");
    print_ty(out, pat->u.typed.ty, indent);
    break;
  case PAT_LAYERED:
    if (pat->u.layered.op_prefixed) {
      fprintf(out, "op ");
    }
    print_vid(out, pat->u.layered.vid);
    if (pat->u.layered.ty) {
      fprintf(out, " : ");
      print_ty(out, pat->u.layered.ty, indent);
    }
    fprintf(out, " as ");
    print_pat(out, pat->u.layered.pat, indent);
    break;
  }
}

void print_ty(FILE *out, Ty *ty, int indent) {
  switch (ty->kind) {
  case TY_TYPE_VARIABLE:
    print_tyvar(out, ty->u.type_variable.tyvar);
    break;
  case TY_RECORD_TYPE_EXPRESSION:
    fprintf(out, "{");
    if (ty->u.record_type_expression.tyrow) {
      fprintf(out, "\n");
      print_indent(out, indent + INDENT_WIDTH);
      print_tyrow(out, ty->u.record_type_expression.tyrow,
                  indent + INDENT_WIDTH);
      fprintf(out, "\n");
      print_indent(out, indent);
    }
    fprintf(out, "}");
    break;
  case TY_TYPE_CONSTRUCTION:
    if (ty->u.type_construction.tyseq) {
      print_tyseq(out, ty->u.type_construction.tyseq, indent);
      fprintf(out, " ");
    }
    print_longtycon(out, ty->u.type_construction.longtycon);
    break;
  case TY_FUNCTION_TYPE_EXPRESSION:
    print_ty(out, ty->u.function_type_expression.arg_ty, indent);
    fprintf(out, " -> ");
    print_ty(out, ty->u.function_type_expression.res_ty, indent);
    break;
  case TY_PARENED_TY:
    fprintf(out, "(");
    print_ty(out, ty->u.parened_ty.ty, indent);
    fprintf(out, ")");
    break;
  }
}

void print_tyseq(FILE *out, TySeq *tyseq, int indent) {
  if (tyseq == NULL)
    return;
  fprintf(out, "(");
  print_ty(out, tyseq->ty, indent);
  if (tyseq->next) {
    fprintf(out, ", ");
    print_tyseq(out, tyseq->next, indent);
  }
  fprintf(out, ")");
}

void print_tyrow(FILE *out, TyRow *tyrow, int indent) {
  print_lab(out, tyrow->lab);
  fprintf(out, " : ");
  print_ty(out, tyrow->ty, indent);
  if (tyrow->next) {
    fprintf(out, ",\n");
    print_indent(out, indent);
    print_tyrow(out, tyrow->next, indent);
  }
}

void print_atexp(FILE *out, AtExp *atexp, int indent) {
  switch (atexp->kind) {
  case ATEXP_SPECIAL_CONSTANT:
    print_constant(out, atexp->u.special_constant.scon);
    break;
  case ATEXP_VALUE_IDENTIFIER:
    if (atexp->u.value_identifier.op_prefixed) {
      fprintf(out, "op ");
    }
    print_longvid(out, atexp->u.value_identifier.longvid);
    break;
  case ATEXP_RECORD:
    fprintf(out, "{");
    if (atexp->u.record.exprow) {
      print_exprow(out, atexp->u.record.exprow, indent + INDENT_WIDTH);
    }
    fprintf(out, "}");
    break;
  case ATEXP_LOCAL_DECLARATION:
    fprintf(out, "let\n");
    print_indent(out, indent + INDENT_WIDTH);
    print_dec(out, atexp->u.local_declaration.dec, indent + INDENT_WIDTH);
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "in\n");
    print_indent(out, indent + INDENT_WIDTH);
    print_exp(out, atexp->u.local_declaration.exp, indent + INDENT_WIDTH);
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "end");
    break;
  case ATEXP_PARENED_EXP:
    fprintf(out, "(");
    print_exp(out, atexp->u.parened_exp.exp, indent);
    fprintf(out, ")");
    break;
  }
}

void print_exprow(FILE *out, ExpRow *exprow, int indent) {
  print_lab(out, exprow->lab);
  fprintf(out, " = ");
  print_exp(out, exprow->exp, indent);
  if (exprow->next) {
    fprintf(out, ",\n");
    print_indent(out, indent);
    print_exprow(out, exprow->next, indent);
  }
}

void print_exp(FILE *out, Exp *exp, int indent) {
  switch (exp->kind) {
  case EXP_ATOMIC:
    print_atexp(out, exp->u.atomic.atexp, indent);
    break;
  case EXP_APPLICATION:
    print_exp(out, exp->u.application.exp, indent);
    fprintf(out, " ");
    print_atexp(out, exp->u.application.atexp, indent);
    break;
  case EXP_INFIXED_APPLICATION:
    print_exp(out, exp->u.infixed_application.exp1, indent);
    fprintf(out, " ");
    print_vid(out, exp->u.infixed_application.vid);
    fprintf(out, " ");
    print_exp(out, exp->u.infixed_application.exp2, indent);
    break;
  case EXP_TYPED:
    print_exp(out, exp->u.typed.exp, indent);
    fprintf(out, " : ");
    print_ty(out, exp->u.typed.ty, indent);
    break;
  case EXP_HANDLE_EXCEPTION:
    print_exp(out, exp->u.handle_exception.exp, indent);
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "handle\n");
    print_indent(out, indent + INDENT_WIDTH);
    print_match(out, exp->u.handle_exception.match, indent + INDENT_WIDTH);
    break;
  case EXP_RAISE_EXCEPTION:
    fprintf(out, "raise ");
    print_exp(out, exp->u.raise_exception.exp, indent);
    break;
  case EXP_FUNCTION:
    fprintf(out, "fn ");
    print_match(out, exp->u.function.match, indent + INDENT_WIDTH);
    break;
  }
}

void print_match(FILE *out, Match *match, int indent) {
  print_mrule(out, match->mrule, indent);
  if (match->next) {
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "| ");
    print_match(out, match->next, indent);
  }
}

void print_mrule(FILE *out, Mrule *mrule, int indent) {
  print_pat(out, mrule->pat, indent);
  fprintf(out, " => ");
  print_exp(out, mrule->exp, indent);
}

void print_dec(FILE *out, Dec *dec, int indent) {
  if (dec == NULL)
    return;

  print_indent(out, indent);

  switch (dec->kind) {
  case DEC_VALUE_DECLARATION:
    fprintf(out, "val ");
    if (dec->u.value_declaration.tyvarseq) {
      print_tyvarseq(out, dec->u.value_declaration.tyvarseq);
      fprintf(out, " ");
    }
    print_valbind(out, dec->u.value_declaration.valbind, indent + INDENT_WIDTH);
    break;

  case DEC_TYPE_DECLARATION:
    fprintf(out, "type ");
    print_typbind(out, dec->u.type_declaration.typbind, indent + INDENT_WIDTH);
    break;

  case DEC_DATATYPE_DECLARATION:
    fprintf(out, "datatype ");
    print_datbind(out, dec->u.datatype_declaration.datbind,
                  indent + INDENT_WIDTH);
    break;

  case DEC_DATATYPE_REPLICATION:
    fprintf(out, "datatype ");
    print_tycon(out, dec->u.datatype_replication.tycon);
    fprintf(out, " = ");
    print_longtycon(out, dec->u.datatype_replication.longtycon);
    break;

  case DEC_ABSTYPE_DECLARATION:
    fprintf(out, "abstype");
    print_datbind(out, dec->u.abstype_declaration.datbind,
                  indent + INDENT_WIDTH);
    fprintf(out, " with\n");
    print_indent(out, indent + INDENT_WIDTH);
    print_dec(out, dec->u.abstype_declaration.dec, indent + INDENT_WIDTH);
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "end");
    break;

  case DEC_EXCEPTION_DECLARATION:
    fprintf(out, "exception ");
    print_exbind(out, dec->u.exception_declaration.exbind,
                 indent + INDENT_WIDTH);
    break;

  case DEC_LOCAL_DECLARATION:
    fprintf(out, "local\n");
    print_indent(out, indent + INDENT_WIDTH);
    print_dec(out, dec->u.local_declaration.dec1, indent + INDENT_WIDTH);
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "in\n");
    print_indent(out, indent + INDENT_WIDTH);
    print_dec(out, dec->u.local_declaration.dec2, indent + INDENT_WIDTH);
    fprintf(out, "\n");
    print_indent(out, indent);
    fprintf(out, "end");
    break;

  case DEC_OPEN_DECLARATION:
    fprintf(out, "open ");
    print_longstridlist(out, dec->u.open_declaration.longstridlist, indent);
    break;

  case DEC_SEQUENTIAL_DECLARATION:
    print_dec(out, dec->u.sequential_declaration.dec1, indent);
    fprintf(out, "\n");
    print_dec(out, dec->u.sequential_declaration.dec2, indent);
    break;

  case DEC_EMPTY_DECLARATION:
    fprintf(out, "(* empty declaration *)");
    break;

  case DEC_INFIX_L_DIRECTIVE:
    fprintf(out, "infix ");
    if (dec->u.infix_l_directive.d) {
      fprintf(out, "%s ", dec->u.infix_l_directive.d);
    }
    print_vidlist(out, dec->u.infix_l_directive.vidlist, indent);
    break;

  case DEC_INFIX_R_DIRECTIVE:
    fprintf(out, "infixr ");
    if (dec->u.infix_r_directive.d) {
      fprintf(out, "%s ", dec->u.infix_r_directive.d);
    }
    print_vidlist(out, dec->u.infix_r_directive.vidlist, indent);
    break;

  case DEC_NONFIX_DIRECTIVE:
    fprintf(out, "nonfix ");
    print_vidlist(out, dec->u.nonfix_directive.vidlist, indent);
    break;
  }
}

void print_valbind(FILE *out, ValBind *valbind, int indent) {
  switch (valbind->kind) {
  case VALBIND_BIND:
    print_pat(out, valbind->u.bind.pat, indent);
    fprintf(out, " = ");
    print_exp(out, valbind->u.bind.exp, indent);
    break;
  case VALBIND_REC:
    fprintf(out, "rec ");
    print_valbind(out, valbind->u.rec.valbind, indent);
    break;
  }
}

void print_typbind(FILE *out, TypBind *typbind, int indent) {
  if (typbind->tyvarseq) {
    fprintf(out, "(");
    print_tyvarseq(out, typbind->tyvarseq);
    fprintf(out, ") ");
  }
  print_tycon(out, typbind->tycon);
  fprintf(out, " = ");
  print_ty(out, typbind->ty, indent);
  if (typbind->next) {
    fprintf(out, "\n");
    print_indent(out, indent);
    print_typbind(out, typbind->next, indent);
  }
}

void print_datbind(FILE *out, DatBind *datbind, int indent) {
  if (datbind->tyvarseq) {
    fprintf(out, "(");
    print_tyvarseq(out, datbind->tyvarseq);
    fprintf(out, ") ");
  }
  print_tycon(out, datbind->tycon);
  fprintf(out, " = ");
  print_conbind(out, datbind->conbind, indent);
  if (datbind->next) {
    fprintf(out, "\n");
    print_indent(out, indent);
    print_datbind(out, datbind->next, indent);
  }
}

void print_conbind(FILE *out, ConBind *conbind, int indent) {
  if (conbind->op_prefixed) {
    fprintf(out, "op ");
  }
  print_vid(out, conbind->vid);
  if (conbind->ty) {
    fprintf(out, " : ");
    print_ty(out, conbind->ty, indent);
  }
  if (conbind->next) {
    fprintf(out, " | ");
    print_conbind(out, conbind->next, indent);
  }
}

void print_exbind(FILE *out, ExBind *exbind, int indent) {
  switch (exbind->kind) {
  case EXBIND_DECLARATION:
    if (exbind->u.declaration.op_prefixed) {
      fprintf(out, "op ");
    }
    print_vid(out, exbind->u.declaration.vid);
    if (exbind->u.declaration.ty != NULL) {
      fprintf(out, " of ");
      print_ty(out, exbind->u.declaration.ty, indent);
    }
    break;
  case EXBIND_REPLICATION:
    print_vid(out, exbind->u.replication.vid);
    fprintf(out, " = ");
    print_longvid(out, exbind->u.replication.longvid);
    break;
  }
}

void print_ast(FILE *out, Dec *root) {
  print_dec(out, root, 0);
  fprintf(out, "\n");
}
