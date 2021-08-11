#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include <lex.h>
#include <parse.h>
#include <split.h>
#include <vector.h>
#include <evaluate.h>

const char *source = NULL;

int main(int argc, const char *argv[]) {
  if (argc == 2) {
    source = argv[1];
    size_t length = 0;
    struct Token *tokens = lex(source, &length);
    struct Vector *expressions = split(tokens, &length);
    for (size_t i = 0; i < length; i++) {
      struct Vector expression = expressions[i];
      struct Token *arrangedTokens = arrange(expression.tokens, &expression.size);
      printf("%d\n", evaluate(arrangedTokens, expression.size));
    }

    freeTokens(tokens, length);
  } else {
    puts("This script requires an argument.");
  }
}
