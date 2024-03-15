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
				ft_list_size.s
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
	      	-z noexecstack -fsanitize=address -no-pie \
	      	$(TESTM) $(OBJS) -o $(TEST)
	      ./$(TEST)
	      /bin/rm -f $(TEST)

clean:
				/bin/rm -f $(OBJS)

fclean: clean
	      /bin/rm -f $(LIB)

re:     fclean all
