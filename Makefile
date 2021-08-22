NAME = pipex
SRC = pipex.c show_error.c
OBJS = $(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra -g
LFLAGS = -L $(LDIR) -lft
LDIR = ./libft/
HEADER	= pipex.h libft/libft.h

all: 
			make -C libft
			make ${NAME}

$(NAME): $(OBJS) $(HEADER)
	make -C $(LDIR)
	gcc -c $(FLAGS) $(SRC) -I $(LDIR)
	gcc -o $(NAME) $(OBJS) $(LFLAGS)

clean:
	make clean -C $(LDIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re