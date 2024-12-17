#ifndef INFIX_H
#define INFIX_H

#include <stdbool.h>

typedef enum Assoc {
  Left,
  Right,
} Assoc;

typedef struct Fixity {
  int prec;
  Assoc assoc;
} Fixity;

typedef struct InfixTable InfixTable;
typedef struct InfixTableList InfixTableList;

InfixTable *infixtable_create(void);
void infixtable_free(InfixTable *table);
InfixTable *infixtable_clone(const InfixTable *table);
const Fixity *infixtable_get(InfixTable *table, const char *key);
bool infixtable_set(InfixTable *table, const char *key, int prec, Assoc assoc);
bool infixtable_delete(InfixTable *table, const char *key);
InfixTableList *infixtablelist_create(void);
void infixtablelist_free(InfixTableList *list);
bool infixtablelist_push(InfixTableList *list, const InfixTable *table);
InfixTable *infixtablelist_pop(InfixTableList *list);
InfixTable *infixtablelist_clone_top(InfixTableList *list);

#endif // INFIX_H
