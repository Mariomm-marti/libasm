#include <assert.h>
#include <stdio.h>
#include <string.h>

extern size_t ft_strlen(char const *str);
extern char *ft_strcpy(char *dst, char const *src);

void test_strlen(void) {
  assert(ft_strlen(NULL) == 0);
  assert(ft_strlen("") == 0);
  assert(ft_strlen("abc\0def") == 3);
  assert(ft_strlen("a") == 1);
  assert(ft_strlen("01234567890123456789\x19\x23\x01\x0a") == 24);
  puts("[ft_strlen] OK!");
}

void test_strcpy(void) {
  {
    char dest[14];
    char *src = "Hello World!\n\0";

    assert(dest == ft_strcpy(dest, src));
    assert(!strcmp(dest, src));
  }
  {
    char message[14] = {'H', 'e', 'l', 'l', 'o', ' ',  'W',
                        'o', 'r', 'l', 'd', '!', '\n', '\0'};
    assert(message == ft_strcpy(message, message));
    assert(!strcmp(message, message));
  }
  {
    char message[6] = {'T', 'e', 's', 't', '\0', 'o'};

    assert(message == ft_strcpy(message, message + 1));
    assert(!strcmp(message, "est"));
  }
  puts("[ft_strcpy] OK!");
}

int main(void) {
  test_strlen();
  test_strcpy();
}
