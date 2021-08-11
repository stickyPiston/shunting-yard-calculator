#include <lex.h>
#include <parse.h>
#include <vector.h>
#include <error.h>

#include <stdlib.h>
#include <stdio.h>

// Operator helper methods

struct Operator operators[] = {
  {'=', 1, RIGHT},
  {'+', 2, LEFT},
  {'-', 2, LEFT},
  {'/', 3, LEFT},
  {'*', 3, LEFT},
  {'^', 4, RIGHT}
};
size_t operatorsSize = sizeof(operators) / sizeof(operators[0]);

struct Operator getopt(char name) {
  for (size_t i = 0; i < operatorsSize; i++) {
    if (name == operators[i].name) return operators[i];
  }
  return (struct Operator){ ' ', 0, LEFT };
}

// Public methods

struct Token *arrange(struct Token *tokens, size_t *length) {
  struct Vector queue = initVector();
  struct Vector stack = initVector();

  size_t index = 0;
  while (index < *length) {
    struct Token token = tokens[index];
    switch (token.type) {
      case IDENTIFIER:
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

      case BRACKET: {
        if (token.value[0] == '(') {
          pushToStack(&stack, token);
        } else {
          while (1) {
            struct Token t = popFromStack(&stack);
            if (t.type == NONE) reportError("Mismatched bracket", token.index);
            if (t.value[0] == '(') break;
            else pushToQueue(&queue, t);
          }
        }
      } break;

      default: break;
    }
    index++;
  }

  while (stack.size > 1) {
    struct Token t = popFromStack(&stack);
    if (t.value[0] == '(' || t.value[0] == ')') reportError("Mismatched bracket", t.index);
    pushToQueue(&queue, t);
  }

  *length = queue.size - 1;
  return queue.tokens;
}
