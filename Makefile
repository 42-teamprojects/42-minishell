NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT	= libft/libft.a

DEPS = includes/global.h includes/minishell.h sources/parser/parser.h

SRCS = main.c sources/utils/helpers.c \
	sources/utils/errors.c \
	sources/execute/validation.c \
	sources/parser/parser.c \
	sources/parser/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(DEPS)
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