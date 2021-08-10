#ifndef LEX_H
#define LEX_H

#include <stdlib.h>

enum TokenType {
  NUMBER,
  OPERATOR,
  NONE
};

struct Token {
  char *value;
  enum TokenType type;
};

void printTokens(struct Token *, size_t);
void freeTokens(struct Token *, size_t);
struct Token *lex(const char *, int *);

#endif
