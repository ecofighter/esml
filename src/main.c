#include <stdio.h>

#include "pp.h"
#include "syntax.h"

#include "parse_state.h"

extern int parse_stdin(ParseState *state);

int main(int argc, char *argv[]) {
  printf("SML Parser started. Enter your code (Ctrl+D to end on Unix, Ctrl+Z "
         "on Windows):\n");

  ParseState *state = parse_state_create("stdin");
  int result = parse_stdin(state);

  if (result == 0) {
    printf("\nParsing completed successfully.\n");
    // print_ast(stdout, parse_state_get_result(state));
    parse_state_free(state);
    return 0;
  } else {
    printf("\nParsing failed.\n");
    parse_state_print_errors(state, stderr);
    parse_state_free(state);
    return 1;
  }
}
