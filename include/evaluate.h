#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdlib.h>
#include <lex.h>

struct Variable {
  char *name;
  int value;
};

struct VariableMap {
  struct Variable *variables;
  size_t variablesCount;
  size_t capacity;
};

int evaluate(struct Token *, size_t);

#endif
