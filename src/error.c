#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern const char *source;

void reportError(const char *reason, size_t index) {
  int row = 1, col = 1;
  size_t sourceLength = strlen(source);
  char line[512] = { 0 };
  size_t i = 0;
  for ( ; i <= index && i < sourceLength; i++) {
    if (source[i] == '\n') {
      row++; col = 1;
      memset(line, 0, 512);
    } else {
      line[col - 1] = source[i];
      col++;
    }
  }

  char *arrow = calloc(col + 2, 1);
  int offset = 3;
  if (i == sourceLength - 1) offset = 1;
  memset(arrow, '~', col - offset);
  arrow[col - offset] = '^';

  fprintf(stderr, "[ FAIL ]: %s at line %d:%d\n", reason, row, col);
  fprintf(stderr, "%d: %s\n", row, line);
  fprintf(stderr, "   %s\n", arrow);
  abort();
}
