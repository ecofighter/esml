#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "infix.h"

#define TABLE_INITIAL_CAPACITY 16

typedef struct Entry Entry;
struct Entry {
  const char *key;
  Fixity fixity;
  Entry *next;
};

struct InfixTable {
  Entry **buckets;
  size_t capacity;
  size_t size;
};

struct InfixTableList {
  InfixTable *current;
  InfixTableList *next;
};

static uint64_t hash_key(const char *key) {
  const uint64_t OFFSET = 0x811c9dc5;
  const uint64_t PRIME = 0x01000193;
  uint64_t hash = OFFSET;

  for (const char *p = key; *p != '\0'; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= PRIME;
  }
  return hash;
}

static Entry *entry_create(const char *key, int prec, Assoc assoc) {
  Entry *entry = (Entry *)malloc(sizeof(Entry));
  if (entry == NULL) {
    return NULL;
  }

  size_t keylen = strlen(key);
  char *tmpkey = (char *)malloc(keylen + 1);
  if (tmpkey == NULL) {
    free(entry);
    return NULL;
  }
  memcpy(tmpkey, key, keylen);
  tmpkey[keylen] = '\0';

  entry->key = (const char *)tmpkey;
  entry->fixity.prec = prec;
  entry->fixity.assoc = assoc;
  entry->next = NULL;
  return entry;
}

InfixTable *infixtable_create(void) {
  InfixTable *table = (InfixTable *)malloc(sizeof(InfixTable));
  if (table == NULL) {
    return NULL;
  }

  table->capacity = TABLE_INITIAL_CAPACITY;
  table->size = 0;

  table->buckets = calloc(table->capacity, sizeof(Entry *));
  if (table->buckets == NULL) {
    free(table);
    return NULL;
  }

  return table;
}

void infixtable_free(InfixTable *table) {
  if (table == NULL) {
    return;
  }
  for (size_t i = 0; i < table->capacity; i++) {
    Entry *current = table->buckets[i];
    while (current != NULL) {
      Entry *next = current->next;
      free((char *)current->key);
      free(current);
      current = next;
    }
  }

  free(table->buckets);
  free(table);
}

static bool infixtable_resize(InfixTable *table, size_t new_capacity) {
  Entry **new_buckets = calloc(new_capacity, sizeof(Entry *));
  if (new_buckets == NULL) {
    return false;
  }

  for (size_t i = 0; i < table->capacity; i++) {
    Entry *current = table->buckets[i];
    while (current != NULL) {
      Entry *next = current->next;
      uint64_t hash = hash_key(current->key);
      size_t new_index = (size_t)(hash & (uint64_t)(new_capacity - 1));
      current->next = new_buckets[new_index];
      new_buckets[new_index] = current;
      current = next;
    }
  }

  free(table->buckets);
  table->buckets = new_buckets;
  table->capacity = new_capacity;
  return true;
}

InfixTable *infixtable_clone(const InfixTable *table) {
  if (table == NULL) {
    return NULL;
  }

  InfixTable *new_table = infixtable_create();
  if (new_table == NULL) {
    return NULL;
  }

  if (table->capacity > TABLE_INITIAL_CAPACITY) {
    if (!infixtable_resize(new_table, table->capacity)) {
      infixtable_free(new_table);
      return NULL;
    }
  }

  for (size_t i = 0; i < table->capacity; i++) {
    Entry *current = table->buckets[i];
    Entry *prev = NULL;

    while (current != NULL) {
      Entry *new_entry = entry_create(current->key, current->fixity.prec,
                                      current->fixity.assoc);
      if (new_entry == NULL) {
        infixtable_free(new_table);
        return NULL;
      }

      if (prev == NULL) {
        new_table->buckets[i] = new_entry;
      } else {
        prev->next = new_entry;
      }

      prev = new_entry;
      current = current->next;
    }
  }

  new_table->size = table->size;
  return new_table;
}

const Fixity *infixtable_get(InfixTable *table, const char *key) {
  if (table == NULL || key == NULL) {
    return NULL;
  }

  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

  Entry *current = table->buckets[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return (const Fixity *)&current->fixity;
    }
    current = current->next;
  }

  return NULL;
}

bool infixtable_set(InfixTable *table, const char *key, int prec, Assoc assoc) {
  if (table == NULL || key == NULL) {
    return false;
  }

  if (table->size >= table->capacity * 0.75) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity ||
        !infixtable_resize(table, new_capacity)) {
      return false;
    }
  }

  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

  Entry *current = table->buckets[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      current->fixity.prec = prec;
      current->fixity.assoc = assoc;
      return true;
    }
    current = current->next;
  }

  Entry *new_entry = entry_create(key, prec, assoc);
  if (new_entry == NULL) {
    return false;
  }

  new_entry->next = table->buckets[index];
  table->buckets[index] = new_entry;
  table->size++;

  return true;
}

bool infixtable_delete(InfixTable *table, const char *key) {
  if (table == NULL || key == NULL) {
    return false;
  }

  bool deleted = false;
  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

  Entry *current = table->buckets[index];
  Entry *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) {
        table->buckets[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free((char *)current->key);
      free(current);
      table->size--;
      deleted = true;
      break;
    }
    prev = current;
    current = current->next;
  }

  return deleted;
}

InfixTableList *infixtablelist_create(void) {
  InfixTableList *list = (InfixTableList *)malloc(sizeof(InfixTableList));
  if (list == NULL) {
    return NULL;
  }
  list->current = infixtable_create();
  if (list->current == NULL) {
    free(list);
    return NULL;
  }
  list->next = NULL;
  return list;
}

void infixtablelist_free(InfixTableList *list) {
  if (list == NULL) {
    return;
  }

  InfixTableList *current = list;
  while (current != NULL) {
    InfixTableList *next = current->next;
    infixtable_free(current->current);
    free(current);
    current = next;
  }
}

bool infixtablelist_push(InfixTableList *list, const InfixTable *table) {
  if (list == NULL || table == NULL) {
    return false;
  }
  InfixTableList *next = (InfixTableList *)malloc(sizeof(InfixTableList));
  if (next == NULL) {
    return false;
  }
  next->current = list->current;
  next->next = list->next;
  InfixTable *new_table = infixtable_clone(table);
  if (new_table == NULL) {
    free(next);
    return false;
  }
  list->current = new_table;
  list->next = next;
  return true;
}

InfixTable *infixtablelist_pop(InfixTableList *list) {
  if (list == NULL) {
    return NULL;
  }
  InfixTable *table = list->current;
  InfixTableList *next = list->next;
  list->current = next->current;
  list->next = next->next;
  free(next);
  return table;
}

InfixTable *infixtablelist_clone_top(InfixTableList *list) {
  if (list == NULL) {
    return NULL;
  }
  return infixtable_clone(list->current);
}
