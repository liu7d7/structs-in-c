#include <stdio.h>
#include <stdint.h>
#include "list.h"

typedef struct foo {
  int64_t a;
  int64_t b;
} foo;

int main() {
  list(foo) l = list_new(1, sizeof(foo));
  for (int i = 0; i < 100; i++) {
    foo f = {i, i};
    list_add((void**) &l, &f);
  }
  for (int i = 0; i < list_count(l); i++) {
    printf("%lld %lld\n", l[i].a, l[i].b);
  }
  return 0;
}