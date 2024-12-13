#include <stdio.h>

#include "pp.h"
#include "syntax.h"

#include "parser.h"

// これらはlex/yaccが生成する関数
extern int yyparse(void);
extern FILE *yyin;
extern void yyrestart(FILE *input_file);
extern int yylex_destroy(void);
extern Dec *parse_result;

// エラーハンドリング用の関数
void yyerror(const char *msg) { fprintf(stderr, "Error: %s\n", msg); }

int main(int argc, char *argv[]) {
  // 標準入力からパース
  yyin = stdin;

  printf("SML Parser started. Enter your code (Ctrl+D to end on Unix, Ctrl+Z "
         "on Windows):\n");

  // パース実行
  int result = yyparse();

  if (result == 0) {
    printf("\nParsing completed successfully.\n");
    print_ast(stdout, parse_result);
    yylex_destroy();
    free_dec(parse_result);
    return 0;
  } else {
    printf("\nParsing failed.\n");
    yylex_destroy();
    return 1;
  }
}
