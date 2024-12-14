#ifndef PARSE_STATE_H
#define PARSE_STATE_H

#include <stdio.h>

#include "syntax.h"

struct ParseState;
typedef struct ParseState ParseState;

ParseState *parse_state_create(const char *filename);
void parse_state_free(ParseState *state);
void *parse_state_register_node(ParseState *state, void *ptr);
void parse_state_register_error(ParseState *state, const char *message,
                                int line, int column);
void parse_state_cleanup_partial(ParseState *state);
void parse_state_set_result(ParseState *state, Dec *result);
Dec *parse_state_get_result(ParseState *state);
void parse_state_print_errors(ParseState *state, FILE *stream);

#endif // PARSE_STATE_H
