// Testing read!
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

extern size_t ft_strlen(char const *str);
extern char *ft_strcpy(char *dst, char const *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t ft_read(int fildes, void *buf, size_t nbyte);
extern char *ft_strdup(const char *s1);
extern int ft_atoi_base(char *str, char *base);
extern int ft_list_size(t_list *begin_list);
extern void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
                              void (*free_fct)(void *));
extern void ft_list_push_front(t_list **begin_list, void *data);

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

void test_list_size(void) {
  { assert(0 == ft_list_size(NULL)); }
  {
    t_list head = {0, 0};
    assert(1 == ft_list_size(&head));
  }
  {
    t_list last = {0, 0};
    t_list second = {0, &last};
    t_list first = {0, &second};
    t_list head = {0, &first};

    assert(4 == ft_list_size(&head));
  }
  puts("[ft_list_size] OK!");
}

int test_list_remove_if_compare_always_same(void *d1, void *d2) {
  (void)d1, (void)d2;
  return 0;
}

int test_list_remove_if_compare_always_different(void *d1, void *d2) {
  (void)d1, (void)d2;
  return 1;
}

void test_list_remove_if(void) {
  {
    t_list *lst = NULL;
    ft_list_remove_if(&lst, NULL, NULL, NULL);
  }
  {
    t_list *lst = malloc(sizeof(t_list));
    lst->data = NULL;
    lst->next = NULL;

    ft_list_remove_if(&lst, NULL, test_list_remove_if_compare_always_same,
                      free);
    assert(lst == NULL);
  }
  {
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    second->data = NULL;
    second->next = NULL;
    lst->data = NULL;
    lst->next = second;

    ft_list_remove_if(&lst, NULL, test_list_remove_if_compare_always_same,
                      free);
    assert(lst == NULL);
  }
  {
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    second->data = strdup("Test");
    second->next = NULL;
    lst->data = strdup("Hey");
    lst->next = second;

    ft_list_remove_if(&lst, "Test", test_list_remove_if_compare_always_same,
                      free);
    assert(lst == NULL);
  }
  {
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    second->data = strdup("Test");
    second->next = NULL;
    lst->data = strdup("Hey");
    lst->next = second;

    ft_list_remove_if(&lst, "Test",
                      test_list_remove_if_compare_always_different, free);
    assert(strcmp(lst->data, "Hey") == 0);
    assert(lst->next == second);
    assert(lst->next->data == second->data);
    assert(lst->next->next == second->next);
    free(lst->next->data);
    free(lst->next);
    free(lst->data);
    free(lst);
  }
  {
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    second->data = strdup("Test");
    second->next = NULL;
    lst->data = strdup("Hey");
    lst->next = second;

    ft_list_remove_if(&lst, "Hey", strcmp, free);
    assert(lst != NULL);
    assert(lst->next == NULL);
    assert(strcmp(lst->data, "Test") == 0);
    free(second->data);
    free(second);
  }
  {
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    second->data = strdup("Test");
    second->next = NULL;
    lst->data = strdup("Hey");
    lst->next = second;

    ft_list_remove_if(&lst, "Test", strcmp, free);
    assert(lst != NULL);
    assert(lst->next == NULL);
    assert(strcmp(lst->data, "Hey") == 0);
    free(lst->data);
    free(lst);
  }
  {
    t_list *fourth = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    fourth->data = strdup("World");
    fourth->next = NULL;
    third->data = strdup("Lol");
    third->next = fourth;
    second->data = strdup("Test");
    second->next = third;
    lst->data = strdup("Hey");
    lst->next = second;

    ft_list_remove_if(&lst, NULL, test_list_remove_if_compare_always_same,
                      free);
    assert(lst == NULL);
  }
  {
    t_list *fourth = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *lst = malloc(sizeof(t_list));
    fourth->data = strdup("World");
    fourth->next = NULL;
    third->data = strdup("Lol");
    third->next = fourth;
    second->data = strdup("Test");
    second->next = third;
    lst->data = strdup("Hey");
    lst->next = second;

    ft_list_remove_if(&lst, "Test", strcmp, free);
    assert(lst->next == third);
    assert(third->next == fourth);
    assert(strcmp(third->data, "Lol") == 0);
    free(fourth->data);
    free(fourth);
    free(third->data);
    free(third);
    free(lst->data);
    free(lst);
  }
  puts("[ft_list_remove_if] OK!");
}

void test_list_push_front(void) {
  {
    t_list *new = NULL;

    assert(new == NULL);
  }
  {
    t_list *new = NULL;

    ft_list_push_front(&new, "Test");
    assert(strcmp(new->data, "Test") == 0);
    assert(new->next == NULL);
    free(new);
  }
  {
    t_list *new = NULL;

    ft_list_push_front(&new, "Test");
    ft_list_push_front(&new, "Random");
    assert(strcmp(new->data, "Random") == 0);
    assert(strcmp(new->next->data, "Test") == 0);
    assert(new->next != NULL);
    assert(new->next->next == NULL);
    free(new->next);
    free(new);
  }
  puts("[ft_list_push_front] OK!");
}

int main(void) {
  test_strlen();
  test_strcpy();
  test_strcmp();
  test_write();
  test_read();
  test_strdup();
  test_atoi_base();
  test_list_size();
  test_list_remove_if();
  test_list_push_front();
}
