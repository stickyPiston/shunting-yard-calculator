#ifndef VECTOR_H
#define VECTOR_H

#include <lex.h>

#include <stdlib.h>

struct Vector {
  size_t size;
  struct Token *tokens;
};

void pushToQueue(struct Vector *queue, struct Token token);
void pushToStack(struct Vector *stack, struct Token token);
struct Token popFromStack(struct Vector *stack);
struct Token *first(struct Vector *v);
struct Vector initVector();

#endif
