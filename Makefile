TEST  = libasm_test
LIB   = libasm.a

TESTM = main.c
SRCS  = ft_read.s \
				ft_strcmp.s \
				ft_strcpy.s \
				ft_strdup.s \
				ft_strlen.s \
				ft_write.s \
				ft_atoi_base.s \
				ft_list_size.s \
				ft_list_remove_if.s \
				ft_list_push_front.s \
				ft_list_sort.s
OBJS  = $(SRCS:.s=.o)
OBJM  = $(TESTM:.c=.o)

%.o:    %.s
				/usr/bin/nasm -f elf64 $<

$(LIB): $(OBJS)
				/usr/bin/ar rc $(LIB) $(OBJS)
				/usr/bin/ranlib $(LIB)

all:    $(LIB)

test:   $(LIB)
	      /usr/bin/cc -Wall -Werror -Wextra -Wpedantic \
	      	-z noexecstack -fsanitize=address \
	        $(TESTM) -L. -lasm -o $(TEST)
	      ./$(TEST)

clean:
				/bin/rm -f $(OBJS)

fclean: clean
	      /bin/rm -f $(LIB)

re:     fclean all
