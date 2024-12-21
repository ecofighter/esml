#ifndef UTILS_H
#define UTILS_H

#if ((defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L) ||               \
     __STDC_VERSION__ >= 202311L)
#include <string.h>
#define esml_strdup strdup
#else
#include <stdlib.h>
#include <string.h>
static inline char *esml_strdup(const char *str) {
  if (str == NULL) {
    return NULL;
  }

  size_t len = strlen(str) + 1;
  char *new_str = (char *)malloc(len);
  if (new_str == NULL) {
    return NULL;
  }
  memcpy(new_str, str, len);

  return new_str;
}
#endif

#endif // UTILS_H
