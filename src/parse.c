#include <lex.h>
#include <parse.h>
#include <vector.h>

#include <stdlib.h>
#include <stdio.h>

// Operator helper methods

static struct Operator operators[5] = {
  {'+', 2, LEFT},
  {'-', 2, LEFT},
  {'/', 3, LEFT},
  {'*', 3, LEFT},
  {'^', 4, RIGHT}
};
static size_t operatorsSize = sizeof(operators) / sizeof(operators[0]);

struct Operator getopt(char name) {
  for (size_t i = 0; i < operatorsSize; i++) {
    if (name == operators[i].name) return operators[i];
  }
  return (struct Operator){ ' ', 0, LEFT };
}

// Public methods

struct Token *arrange(struct Token *tokens, size_t length) {
  struct Vector queue = initVector();
  struct Vector stack = initVector();

  size_t index = 0;
  while (index < length) {
    struct Token token = tokens[index];
    switch (token.type) {
      case NUMBER: {
        pushToQueue(&queue, token);
      } break;

      case OPERATOR: {
        while (1) {
          struct Token *stackFirst = first(&stack);
          if (!stackFirst) break;

          struct Operator o1 = getopt(stackFirst->value[0]);
          struct Operator o2 = getopt(token.value[0]);
          if (o1.presedence > o2.presedence || (o1.associativity == LEFT && o1.presedence == o2.presedence))
            pushToQueue(&queue, popFromStack(&stack));
          else
            break;
        }
        pushToStack(&stack, token);
      } break;

      default: break;
    }
    index++;
  }

  while (stack.size > 1) {
    pushToQueue(&queue, popFromStack(&stack));
  }

  return queue.tokens;
}
