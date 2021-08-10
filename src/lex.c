#include <lex.h>

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void addToken(struct Token **tokens, size_t *size, char *value, enum TokenType type) {
  *tokens = realloc(*tokens, (*size + 1) * sizeof(struct Token));
  (*tokens)[*size - 1] = (struct Token){value, type};
  *size += 1;
}

void printTokens(struct Token *tokens, size_t length) {
  for (size_t i = 0; i < length; i++)
    printf("%zu: %s", i, tokens[i].value);
}

void freeTokens(struct Token *tokens, size_t count) {
  for (size_t i = 0; i < count; i++) {
    free(tokens[i].value);
  }
  free(tokens);
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

struct Token *lex(const char *source, int *length) {
  struct Token *tokens = malloc(sizeof(struct Token));
  size_t tokenCount = 1;

  size_t lexindex = 0;
  size_t sourceLength = strlen(source);
  while (lexindex < sourceLength) {
    while (isspace(source[lexindex])) lexindex++;

    char c = source[lexindex];
    if (isdigit(c)) { // number
      char *num = calloc(11, 1); int index = 0; // 32-bit number is max. 10 digits
      while (isdigit(source[lexindex])) {
        num[index++] = source[lexindex++];
      }
      num[index] = '\0';
      addToken(&tokens, &tokenCount, num, NUMBER);
    } else if (isOperator(c)) { // operator
      char *operatorString = calloc(2, 1);
      operatorString[0] = c;
      addToken(&tokens, &tokenCount, operatorString, OPERATOR);
      lexindex++;
    }
  }

  *length = tokenCount - 1;
  return tokens;
}
