NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT	= libft/libft.a

SRCS = main.c sources/utils/helpers.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) minishell.h
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o  $@ $(LIBFT)

$(LIBFT):
		make all -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f minishell libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re libft

# To be deleted
run: all
	@./minishell