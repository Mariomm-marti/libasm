<div align='center'>

# libasm
#### _Dive into x86_64 ASM by creating a simple standalone library covering elemental functionality_

[Purpose](#purpose) ~
[Available prototypes](#available-prototypes) ~
[How to install it](#how-to-install-it)

</div>

## Purpose
This library was done with the single objective of diving into ASM x86_64,
without going too much in depth into the different instructions of the
CISC (Complex Instruction Set Computer) architecture.

## Available prototypes
Here is a list of available functions with their prototype and usage:

| Function name        | Prototype                                                                                              | Description                                                                                                                                                                                                                                                                          |
| :------------------: | :----------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| `ft_read`            | `ssize_t ft_read(int fildes, void *buf, size_t nbyte);`                                                | Similar to `read(2)`                                                                                                                                                                                                                                                                 |
| `ft_strcmp`          | `int ft_strcmp(const char *s1, const char *s2);`                                                       | Similar to `strcmp(3)`                                                                                                                                                                                                                                                               |
| `ft_strcpy`          | `char *ft_strcpy(char *dst, char const *src);`                                                         | Similar to `strcpy(3)`                                                                                                                                                                                                                                                               |
| `ft_strdup`          | `char *ft_strdup(const char *s1);`                                                                     | Similar to `strdup(3)`                                                                                                                                                                                                                                                               |
| `ft_strlen`          | `size_t ft_strlen(char const *str);`                                                                   | Similar to `strlen(3)`                                                                                                                                                                                                                                                               |
| `ft_write`           | `ssize_t ft_write(int fildes, const void *buf, size_t nbyte);`                                         | Similar to `write(2)`                                                                                                                                                                                                                                                                |
| `ft_atoi_base`       | `int ft_atoi_base(char *str, char *base);`                                                             | In the following order: takes an arbitrary number of `isspace(3)`, an arbitrary number of + / - signs (converting the final number to + or -), and an arbitrary number of characters expected to be in the base `base` and converts them to base 10. The + and - invalidate the base |
| `ft_list_size`       | `int ft_list_size(t_list *begin_list);`                                                                | Find the size (number of elements) of a `t_list`                                                                                                                                                                                                                                     |
| `ft_list_remove_if`  | `void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));` | Applies the function `cmp` to all nodes using both each node's data and the `data_ref`. If the result of `cmp` is 0, the node content will be free using `free_fct` and the node using `free`. All nodes will be relinked.                                                           |
| `ft_list_push_front` | `void ft_list_push_front(t_list **begin_list, void *data);`                                            | Created a `t_list` node with content `data` and attaches it at the beginning of the linked list using `begin_list`'s node pointer                                                                                                                                                    |
| `ft_list_sort`       | `void ft_list_sort(t_list **begin_list, int (*cmp)(void *d1, void *d2));`                              | Sorts a list `begin_list` using the `cmp` function in ascending order. The `cmp` function understands a negative result as "smaller" `d1`, and a positive or equal value as "larger or equal" `d1` (when compared to `d2`)                                                           |

The definition of a `t_list` is:
```c
typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;
```

## How to install it
A simple `make` in any `x86_64` Linux based architecture should be enough!

Additionally, you can test the software by doing `make test`.
