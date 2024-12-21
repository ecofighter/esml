#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_state.h"
#include "utils.h"

#define INITIAL_CAPACITY 16

typedef struct MemoryTracker MemoryTracker;
struct MemoryTracker {
  void **ptrs;
  size_t count;
  size_t capacity;
};

static MemoryTracker *memory_tracker_create(void);
static void memory_tracker_free(MemoryTracker *tracker);
static void track_malloc(MemoryTracker *tracker, void *ptr);
static void cleanup_memory(MemoryTracker *tracker);

typedef struct ParseError ParseError;
struct ParseError {
  char *message;
  int line;
  int column;
};

typedef struct ErrorList ErrorList;
struct ErrorList {
  ParseError *errors;
  size_t count;
  size_t capacity;
};

static ErrorList *error_list_create(void);
static void error_list_free(ErrorList *list);
static void error_list_add(ErrorList *list, const char *message, int line,
                           int column);
static void error_list_print(const ErrorList *list, FILE *stream);

static MemoryTracker *memory_tracker_create(void) {
  MemoryTracker *tracker = (MemoryTracker *)malloc(sizeof(MemoryTracker));
  tracker->ptrs = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
  tracker->count = 0;
  tracker->capacity = INITIAL_CAPACITY;
  return tracker;
}

static void memory_tracker_free(MemoryTracker *tracker) {
  cleanup_memory(tracker);
  free(tracker);
}

static void track_malloc(MemoryTracker *tracker, void *ptr) {
  if (tracker->count >= tracker->capacity) {
    tracker->capacity *= 2;
    tracker->ptrs =
        (void **)realloc(tracker->ptrs, tracker->capacity * sizeof(void *));
  }

  tracker->ptrs[tracker->count++] = ptr;
}

static void cleanup_memory(MemoryTracker *tracker) {
  for (size_t i = 0; i < tracker->count; i++) {
    free(tracker->ptrs[i]);
  }
  free(tracker->ptrs);
}

static ErrorList *error_list_create(void) {
  ErrorList *list = (ErrorList *)malloc(sizeof(ErrorList));
  list->errors = (ParseError *)malloc(INITIAL_CAPACITY * sizeof(ParseError));
  list->count = 0;
  list->capacity = INITIAL_CAPACITY;
  return list;
}

static void error_list_add(ErrorList *list, const char *message, int line,
                           int column) {
  if (list->count >= list->capacity) {
    list->capacity *= 2;
    list->errors = (ParseError *)realloc(list->errors,
                                         list->capacity * sizeof(ParseError));
  }

  ParseError *error = &list->errors[list->count++];
  error->message = esml_strdup(message);
  if (error->message == NULL) {
    fprintf(stderr, "failed to add an error.\n");
  }
  error->line = line;
  error->column = column;
}

static void error_list_free(ErrorList *list) {
  for (size_t i = 0; i < list->count; i++) {
    free(list->errors[i].message);
  }
  free(list->errors);
  free(list);
}

static void error_list_print(const ErrorList *list, FILE *stream) {
  for (size_t i = 0; i < list->count; i++) {
    ParseError *error = &list->errors[i];
    fprintf(stream, "%d:%d: error: %s\n", error->line, error->column,
            error->message);
  }
}

struct ParseState {
  const char *filename;
  MemoryTracker *tracker;
  ErrorList *error_list;
  CDec *result;
};

ParseState *parse_state_create(const char *filename) {
  ParseState *state = (ParseState *)malloc(sizeof(ParseState));
  if (state == NULL) {
    return NULL;
  }

  state->filename = (const char *)esml_strdup(filename);
  if (state->filename == NULL) {
    free(state);
    return NULL;
  }

  state->tracker = memory_tracker_create();
  if (state->tracker == NULL) {
    free((char *)state->filename);
    free(state);
    return NULL;
  }

  state->error_list = error_list_create();
  if (state->error_list == NULL) {
    free((char *)state->filename);
    memory_tracker_free(state->tracker);
    free(state);
    return NULL;
  }
  state->result = NULL;
  return state;
}

void parse_state_free(ParseState *state) {
  free((char *)state->filename);
  memory_tracker_free(state->tracker);
  error_list_free(state->error_list);
  free(state);
}

void *parse_state_register_node(ParseState *state, void *ptr) {
  track_malloc(state->tracker, ptr);
  return ptr;
}

void parse_state_register_error(ParseState *state, const char *message,
                                int line, int column) {
  error_list_add(state->error_list, message, line, column);
}

void parse_state_cleanup_partial(ParseState *state) {
  memory_tracker_free(state->tracker);
  state->tracker = memory_tracker_create();
  state->result = NULL;
}

void parse_state_set_result(ParseState *state, CDec *result) {
  state->result = result;
}

CDec *parse_state_get_result(ParseState *state) { return state->result; }

void parse_state_print_errors(ParseState *state, FILE *stream) {
  fprintf(stream, "Errors in file %s:\n", state->filename);
  error_list_print(state->error_list, stream);
}
