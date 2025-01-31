#include <stdlib.h>
#include <string.h>

#include "concrete_syntax.h"
#include "syntax.h"
#include "utils.h"

static VId *from_c_vid(CVId *c_vid) {
  VId *vid = (VId *)malloc(sizeof(VId));
  if (vid == NULL) {
    return NULL;
  }
  vid->value = esml_strdup(c_vid->value);
  if (vid->value == NULL) {
    free(vid);
    return NULL;
  }
  return vid;
}

static VIdList *from_c_vidlist(CVIdList *c_vidlist) {
  VIdList *vidlist = (VIdList *)malloc(sizeof(VIdList));
  if (vidlist == NULL) {
    return NULL;
  }
  vidlist->vid = from_c_vid(c_vidlist->vid);
  if (vidlist->vid == NULL) {
    free(vidlist);
    return NULL;
  }
  vidlist->next = from_c_vidlist(c_vidlist->next);
  if (vidlist->next == NULL) {
    free(vidlist->vid);
    free(vidlist);
    return NULL;
  }
  return vidlist;
}

static LongVId *from_c_longvid(CLongVId *c_longvid) {
  LongVId *longvid = (LongVId *)malloc(sizeof(LongVId));
  if (longvid == NULL) {
    return NULL;
  }
  switch (c_longvid->kind) {
  case CLONGVID_NONQUALIFIED:
    longvid->kind = LONGVID_NONQUALIFIED;
    longvid->u.nonqualified.vid = from_c_vid(c_longvid->u.nonqualified.vid);
    break;
  case CLONGVID_QUALIFIED:
    longvid->kind = LONGVID_QUALIFIED;
    char *buf = esml_strdup(c_longvid->u.qualified.qualified_vid->value);
    char *tok = strtok(buf, ".");
    char *next_tok = strtok(NULL, ".");
    StrIdList *current = longvid->u.qualified.stridlist =
        new_stridlist(new_strid(esml_strdup(tok)), NULL);
    while (next_tok != NULL) {
      current->next = new_stridlist(new_strid(esml_strdup(tok)), NULL);
      current = current->next;
      tok = next_tok;
      next_tok = strtok(NULL, ".");
    }
    longvid->u.qualified.vid = new_vid(esml_strdup(tok));
    free(buf);
    break;
  }
  return longvid;
}

static TyVar *from_c_tyvar(CTyVar *c_tyvar) {
  TyVar *tyvar = (TyVar *)malloc(sizeof(TyVar));
  if (tyvar == NULL) {
    return NULL;
  }
  tyvar->value = esml_strdup(c_tyvar->value);
  if (tyvar->value == NULL) {
    free(tyvar);
    return NULL;
  }
  return tyvar;
}

static TyVarList *from_c_tyvarlist(CTyVarList *c_tyvarlist) {
  TyVarList *tyvarlist = (TyVarList *)malloc(sizeof(TyVarList));
  if (tyvarlist == NULL) {
    return NULL;
  }
  tyvarlist->tyvar = from_c_tyvar(c_tyvarlist->tyvar);
  if (tyvarlist->tyvar == NULL) {
    free(tyvarlist);
    return NULL;
  }
  if (c_tyvarlist->next != NULL) {
    tyvarlist->next = from_c_tyvarlist(c_tyvarlist->next);
  }
  return tyvarlist;
}

static TyCon *from_c_tycon(CTyCon *c_tycon) {
  TyCon *tycon = (TyCon *)malloc(sizeof(TyCon));
  if (tycon == NULL) {
    return NULL;
  }
  // TODO
}
