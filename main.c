#include <assert.h>
#include <stdio.h>

extern size_t ft_strlen(char const *str);

void test_strlen(void) {
  assert(ft_strlen(NULL) == 0);
  assert(ft_strlen("") == 0);
  assert(ft_strlen("abc\0def") == 3);
  assert(ft_strlen("a") == 1);
  assert(ft_strlen("01234567890123456789\x19\x23\x01\x0a") == 24);
  puts("[ft_strlen] OK!\n");
}

int main(void) { test_strlen(); }
