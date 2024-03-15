// Testing read!
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

extern size_t ft_strlen(char const *str);
extern char *ft_strcpy(char *dst, char const *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t ft_read(int fildes, void *buf, size_t nbyte);
extern char *ft_strdup(const char *s1);
extern int ft_atoi_base(char *str, char *base);

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
    assert(ft_write(2, "testing in progress...!\n", 24) == 24);
    assert(errno == 0);
  }
  errno = 0;
  puts("[ft_write] OK!");
}

void test_read(void) {
  {
    assert(ft_read(-1, NULL, 0) == -1);
    assert(errno = EBADF);
  }
  errno = 0;
  {
    assert(ft_read(-1, NULL, 10) == -1);
    assert(errno = EBADF);
  }
  errno = 0;
  {
    int fd = open("ft_read.s", O_RDONLY);

    assert(ft_read(fd, NULL, 10) == -1);
    close(fd);
  }
  errno = 0;
  {
    int fd = open("main.c", O_RDONLY);
    char buff[11];
    char buff2[11] = "// Testing\0";

    buff[10] = 0;
    assert(ft_read(fd, buff, 10) == 10);
    assert(strcmp(buff, buff2) == 0);
    close(fd);
  }
  errno = 0;
  puts("[ft_read] OK!");
}

void test_strdup(void) {
  {
    char *src = "This is a simple strdup attempt.";
    char *dst;

    dst = ft_strdup(src);
    assert(strlen(dst) == strlen(src));
    assert(strcmp(dst, src) == 0);
    free(dst);
  }
  {
    char *src = "";
    char *dst;

    dst = ft_strdup(src);
    assert(strlen(dst) == strlen(src));
    assert(strcmp(dst, src) == 0);
    free(dst);
  }
  puts("[ft_strdup] OK!");
}

void test_atoi_base(void) {
  { assert(0 == ft_atoi_base("", "")); }
  { assert(0 == ft_atoi_base("", "0123456789")); }
  { assert(0 == ft_atoi_base("100", "")); }
  { assert(0 == ft_atoi_base("100", "012345-6789")); }
  { assert(0 == ft_atoi_base("100", "012345+6789")); }
  { assert(100 == ft_atoi_base("100", "0123456789")); }
  { assert(100 == ft_atoi_base("100abc10000", "0123456789")); }
  { assert(-100 == ft_atoi_base("-100", "0123456789")); }
  { assert(1 == ft_atoi_base("          1", "0132456789")); }
  { assert(-1 == ft_atoi_base("        -1", "0132456789")); }
  { assert(-1 == ft_atoi_base("      ---1", "0132456789")); }
  { assert(-100 == ft_atoi_base("  ---100", "0132456789")); }
  { assert(-100 == ft_atoi_base("  ---100", "0132456789")); }
  { assert(100 == ft_atoi_base("   +++100", "0132456789")); }
  { assert(-100 == ft_atoi_base("   +-+100", "0132456789")); }
  { assert(-171 == ft_atoi_base("-ab", "0132456789abcdef")); }
  { assert(-171 == ft_atoi_base("-ab", "0132456789abcdef")); }
  { assert(-0xfabada == ft_atoi_base("-fabada", "0132456789abcdef")); }
  puts("[ft_atoi_base] OK!");
}

int main(void) {
  test_strlen();
  test_strcpy();
  test_strcmp();
  test_write();
  test_read();
  test_strdup();
  test_atoi_base();
}
