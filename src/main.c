#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include <lex.h>
#include <parse.h>
#include <evaluate.h>

const char *source = NULL;

int main(int argc, const char *argv[]) {
  if (argc == 2) {
    source = argv[1];
    size_t length = 0;
    struct Token *tokens = lex(source, &length);
    struct Token *arrangedTokens = arrange(tokens, &length);
    printTokens(arrangedTokens, length);
    printf("Result of %s: %d\n", source, evaluate(arrangedTokens, length));

    freeTokens(tokens, length);
  } else {
    puts("This script requires an argument.");
  }
}
