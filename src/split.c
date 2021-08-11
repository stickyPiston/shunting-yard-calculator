#include <vector.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <split.h>
#include <lex.h>

struct Vector *split(struct Token *tokens, size_t *length) {
  size_t expressionCount = 0;
  struct Vector *expressions = NULL;
  struct Vector currentVector = initVector();

  size_t index = 0;
  while (index < *length) {
    struct Token token = tokens[index];
    if (token.value[0] == ';') {
      if (expressions == NULL) {
        expressions = malloc(++expressionCount * sizeof(struct Vector));
      } else {
        expressions = realloc(expressions, ++expressionCount * sizeof(struct Vector));
      }
      memcpy(expressions + (expressionCount - 1), &currentVector, sizeof(struct Vector));
      currentVector = initVector();
    } else {
      pushToQueue(&currentVector, token);
    }

    index++;
  }

  *length = expressionCount;
  return expressions;
}
