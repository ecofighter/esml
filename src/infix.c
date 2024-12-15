#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_INITIAL_CAPACITY 32

typedef enum Direction {
  Leftfix,
  Rightfix,
  Nonfix,
} Direction;

typedef struct Fixity {
  int prec;
  Direction direction;
} Fixity;

typedef struct Entry Entry;
struct Entry {
  const char *key;
  Fixity fixity;
  Entry *next;
};

typedef struct OpTable OpTable;
struct OpTable {
  Entry **buckets;
  size_t capacity;
  size_t size;
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

static Entry *entry_create(const char *key, int prec, Direction direction) {
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
  entry->fixity.direction = direction;
  entry->next = NULL;
  return entry;
}

OpTable *optable_create(void) {
  OpTable *table = (OpTable *)malloc(sizeof(OpTable));
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

void optable_free(OpTable *table) {
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

static int optable_resize(OpTable *table, size_t new_capacity) {
  Entry **new_buckets = calloc(new_capacity, sizeof(Entry *));
  if (new_buckets == NULL) {
    return 0;
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
  return 1;
}

const Fixity *optable_get(OpTable *table, const char *key) {
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

int optable_set(OpTable *table, const char *key, int prec,
                Direction direction) {
  if (table == NULL || key == NULL) {
    return 0;
  }

  if (table->size >= table->capacity * 0.75) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity ||
        !optable_resize(table, new_capacity)) {
      return 0;
    }
  }

  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

  Entry *current = table->buckets[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      current->fixity.prec = prec;
      current->fixity.direction = direction;
      return 1;
    }
    current = current->next;
  }

  Entry *new_entry = entry_create(key, prec, direction);
  if (new_entry == NULL) {
    return 0;
  }

  new_entry->next = table->buckets[index];
  table->buckets[index] = new_entry;
  table->size++;

  return 1;
}

int optable_delete(OpTable *table, const char *key) {
  if (table == NULL || key == NULL) {
    return 0;
  }

  int deleted = 0;
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
      deleted = 1;
    }
    prev = current;
    current = current->next;
  }

  return deleted;
}
