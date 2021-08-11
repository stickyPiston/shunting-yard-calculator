#include <vector.h>
#include <stdio.h>

void pushToQueue(struct Vector *queue, struct Token token) {
  queue->tokens = realloc(queue->tokens, ++queue->size * sizeof(struct Token));
  queue->tokens[queue->size - 2] = token;
}

void pushToStack(struct Vector *stack, struct Token token) {
  pushToQueue(stack, token);
}

struct Token popFromStack(struct Vector *stack) {
  if (stack->size > 1) {
    struct Token token = stack->tokens[stack->size - 2];
    stack->tokens = realloc(stack->tokens, --stack->size * sizeof(struct Token));
    return token;
  } else {
    return (struct Token){ NULL, 0, NONE };
  }
}

struct Token *first(struct Vector *v) {
  if (v->size > 1)
    return v->tokens + (v->size - 2);
  else
    return NULL;
}

void printVector(struct Vector *v) {
  for (size_t i = 0; i < v->size - 1; i++) {
    printf("%zu: %s\n", i, v->tokens[i].value);
  }
}

struct Vector initVector() {
  return (struct Vector){ 1, malloc(sizeof(struct Token)) };
}
