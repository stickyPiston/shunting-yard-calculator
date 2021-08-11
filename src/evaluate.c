#include <evaluate.h>
#include <error.h>
#include <string.h>
#include <vector.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>

int strtoi(const char *s) {
  long l = strtol(s, NULL, 10);
  if (l < INT_MAX && l > INT_MIN) return l;
  else return 0;
}

char *itostr(int n) {
  char *s = calloc(ceil(log10(n)) + 1, 1);
  sprintf(s, "%d", n);
  return s;
}

void printVariableMap(struct VariableMap *map) {
  for (size_t i = 0; i < map->variablesCount - 1; i++) {
    printf("%s: %d\n", map->variables[i].name, map->variables[i].value);
  }
}

void saveToVariableMap(struct VariableMap *map, struct Variable v) {
  if (map->capacity == map->variablesCount) {
    map->capacity *= 2;
    map->variables = realloc(map->variables, map->capacity * sizeof(struct Variable));
    map->variables[map->variablesCount++] = v;
  } else {
    map->variables[map->variablesCount++] = v;
  }
}

struct Variable *recallFromVariableMap(struct VariableMap *map, char *name) {
  for (size_t i = 0; i < map->variablesCount; i++) {
    if (strcmp(map->variables[i].name, name) == 0) {
      return map->variables + i;
    }
  }
  return NULL;
}

int getValue(struct VariableMap *map, struct Token t) {
  if (t.type == IDENTIFIER) {
    struct Variable *var = recallFromVariableMap(map, t.value);
    if (var == NULL) reportError("Recalling an undefined variable", t.index);
    else return var->value;
  } else if (t.type == NUMBER) {
    return strtoi(t.value);
  } else {
    reportError("Cannot use operator as value", t.index);
  }
  return 0;
}

int evaluate(struct Token *tokens, size_t length) {
  struct Vector stack = initVector();
  struct VariableMap variables = { malloc(sizeof(struct Variable)), 0, 1 };

  size_t index = 0;
  while (index < length) {
    struct Token token = tokens[index];

    if (token.type == NUMBER || token.type == IDENTIFIER) {
      pushToStack(&stack, token);
    } else if (token.type == OPERATOR) {
      if (token.value[0] == '=') {
        int value = getValue(&variables, popFromStack(&stack));
        struct Token identifier = popFromStack(&stack);
        saveToVariableMap(&variables, (struct Variable){ .name = identifier.value, .value = value });
        pushToStack(&stack, (struct Token){ identifier.value, token.index, IDENTIFIER });
        printVariableMap(&variables);
      } else {
        struct Token lhsToken = popFromStack(&stack);
        struct Token rhsToken = popFromStack(&stack);
        int lhs = getValue(&variables, rhsToken);
        int rhs = getValue(&variables, lhsToken);

        int result;
        switch (token.value[0]) {
          case '+': {
            result = lhs + rhs;
          } break;

          case '-': {
            result = lhs - rhs;
          } break;

          case '*': {
            result = lhs * rhs;
          } break;

          case '/': {
            result = lhs / rhs;
          } break;

          case '^': {
            result = pow(lhs, rhs);
          } break;
        }

        // This is not the best method to save the data to a stack, but i didn't want to remake a new stack data structure for just ints if i already have a stack for Tokens
        // If i was working in c++, i would have created generic queue and stack classes, but i don't want to use c++
        pushToStack(&stack, (struct Token){ itostr(result), token.index, NUMBER });
      }
    }

    index++;
  }

  printVariableMap(&variables);
  return getValue(&variables, popFromStack(&stack));
}
