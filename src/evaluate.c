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

int evaluate(struct Token *tokens, size_t length) {
  struct Vector stack = initVector();

  size_t index = 0;
  while (index < length) {
    struct Token token = tokens[index];

    if (token.type == NUMBER) {
      pushToStack(&stack, token);
    } else if (token.type == OPERATOR) {
      struct Token lhsToken = popFromStack(&stack);
      struct Token rhsToken = popFromStack(&stack);
      int lhs = strtoi(lhsToken.value);
      int rhs = strtoi(rhsToken.value);

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
      pushToStack(&stack, (struct Token){ itostr(result), NUMBER });
    }

    index++;
  }

  return strtoi(popFromStack(&stack).value);
}
