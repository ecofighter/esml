#ifndef PP_H
#define PP_H

#include "concrete_syntax.h"
#include <stdio.h>

void print_c_vid(FILE *fp, CVId *vid, int indent);
void print_c_vidlist(FILE *fp, CVIdList *vidlist, int indent);
void print_c_qualified_vid(FILE *fp, CQualifiedVId *qvid, int indent);
void print_c_longvid(FILE *fp, CLongVId *longvid, int indent);
void print_c_tyvar(FILE *fp, CTyVar *tyvar, int indent);
void print_c_tyvarlist(FILE *fp, CTyVarList *tyvarlist, int indent);
void print_c_tycon(FILE *fp, CTyCon *tycon, int indent);
void print_c_qualified_tycon(FILE *fp, CQualifiedTyCon *qtycon, int indent);
void print_c_longtycon(FILE *fp, CLongTyCon *longtycon, int indent);
void print_c_lab(FILE *fp, CLab *lab, int indent);
void print_c_strid(FILE *fp, CStrId *strid, int indent);
void print_c_qualified_strid(FILE *fp, CQualifiedStrId *qstrid, int indent);
void print_c_longstrid(FILE *fp, CLongStrId *longstrid, int indent);
void print_c_longstridlist(FILE *fp, CLongStrIdList *longstridlist, int indent);
void print_c_constant(FILE *fp, CConstant *constant, int indent);

void print_c_atpat(FILE *fp, CAtPat *atpat, int ident);
void print_c_atpatlist(FILE *fp, CAtPatList *atpatlist, int ident);
void print_c_patrow(FILE *fp, CPatRow *patrow, int ident);
void print_c_pat(FILE *fp, CPat *pat, int indent);
void print_c_patlist(FILE *fp, CPatList *patlist, int indent);
void print_c_ty(FILE *fp, CTy *ty, int indent);
void print_c_tylist(FILE *fp, CTyList *tylist, int indent);
void print_c_tyrow(FILE *fp, CTyRow *tyrow, int indent);
void print_c_atexp(FILE *fp, CAtExp *atexp, int indent);
void print_c_atexplist(FILE *fp, CAtExpList *atexplist, int indent);
void print_c_exprow(FILE *fp, CExpRow *exprow, int indent);
void print_c_exp(FILE *fp, CExp *exp, int indent);
void print_c_explist(FILE *fp, CExpList *explist, int indent);
void print_c_match(FILE *fp, CMatch *match, int indent);
void print_c_mrule(FILE *fp, CMrule *mrule, int indent);
void print_c_dec(FILE *fp, CDec *dec, int indent);
void print_c_valbind(FILE *fp, CValBind *valbind, int indent);
void print_c_fvalbind(FILE *fp, CFValBind *fvalbind, int indent);
void print_c_fmatch(FILE *fp, CFMatch *fmatch, int indent);
void print_c_fmrule(FILE *fp, CFMrule *fmrule, int indent);
void print_c_typbind(FILE *fp, CTypBind *typbind, int indent);
void print_c_datbind(FILE *fp, CDatBind *datbind, int indent);
void print_c_conbind(FILE *fp, CConBind *conbind, int indent);
void print_c_exbind(FILE *fp, CExBind *exbind, int indent);

#endif // PP_H
