#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

static inline char *esml_strdup(const char *str) {
  if (str == NULL) {
    return NULL;
  }

  size_t len = strlen(str);
  char *new_str = (char *)malloc(len + 1);
  if (new_str == NULL) {
    return NULL;
  }
  memcpy(new_str, str, len + 1);

  return new_str;
}

#endif // UTILS_H
