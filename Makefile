NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADERS = includes/global.h includes/minishell.h

LIBFT	= libft/libft.a

SRCS = main.c \
	sources/utils/helpers.c \
	sources/utils/errors.c \
	sources/utils/utilities.c \
	sources/execute/validation.c \
	sources/execute/execution.c \
	sources/execute/utils.c \
	sources/parser/parser.c \
	sources/parser/parser_utils.c \
	sources/execute/function.c \
	sources/lexer/lexer_init.c \
	sources/lexer/lexer_utils.c \
	sources/lexer/tokenizer.c \
	sources/lexer/lexer.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
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