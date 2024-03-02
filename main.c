#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

extern size_t ft_strlen(char const *str);
extern char *ft_strcpy(char *dst, char const *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fildes, const void *buf, size_t nbyte);

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

void test_strcmp(void) {
  {
    char a[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char b[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    assert(ft_strcmp(a, b) == 0);
  }
  {
    char a[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char b[6] = {'H', 'E', 'l', 'l', 'o', '\0'};
    assert(ft_strcmp(a, b) == 32);
  }
  { assert(ft_strcmp("", "") == 0); }
  {
    char a[6] = {'H', 'E', 'l', 'l', 'o', '\0'};
    char b[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    assert(ft_strcmp(a, b) == -32);
  }
  {
    char a[6] = {'H', '\x69', 'l', 'l', 'o', '\0'};
    char b[6] = {'H', '\x69', 'l', 'l', 'o', '\0'};
    assert(ft_strcmp(a, b) == 0);
  }
  { assert(ft_strcmp("\x00\x00\x00", "") == 0); }
  puts("[ft_strcmp] OK!");
}

void test_write(void) {
  {
    assert(ft_write(-1, "Hey!\n", 5) == -1);
    assert(errno == EBADF);
  }
  errno = 0;
  {
    assert(ft_write(2, "STDERR works!\n", 14) == 14);
    assert(errno == 0);
  }
  puts("[ft_write] OK!");
}

int main(void) {
  test_strlen();
  test_strcpy();
  test_strcmp();
  test_write();
}
