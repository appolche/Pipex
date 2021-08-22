NAME = libft.a

INCLUDES = ./

HEADER = libft.h

SRCS = ft_strlen.c ft_strlcpy.c ft_strnstr.c ft_putstr_fd.c\
	   ft_strjoin.c ft_split.c ft_putendl_fd.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	gcc -c -Wall -Wextra -Werror -I $(INCLUDES) -o $@ $<

clean: 
	rm -f $(OBJS)
	:
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flean re