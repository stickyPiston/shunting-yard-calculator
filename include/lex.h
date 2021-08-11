#ifndef LEX_H
#define LEX_H

#include <stdlib.h>

enum TokenType {
  NUMBER,
  IDENTIFIER,
  OPERATOR,
  BRACKET,
  NONE
};

struct Token {
  char *value;
  size_t index;
  enum TokenType type;
};

void printTokens(struct Token *, size_t);
void freeTokens(struct Token *, size_t);
struct Token *lex(const char *, size_t *);

#endif
