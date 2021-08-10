#ifndef PARSE_H
#define PARSE_H

enum Associativity {
  LEFT,
  RIGHT
};

struct Operator {
  char name;
  int presedence;
  enum Associativity associativity;
};

struct Token *arrange(struct Token *, size_t length);

#endif
