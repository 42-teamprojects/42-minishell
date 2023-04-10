NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/

HEADERS = includes/global.h includes/minishell.h

LIBFT	= libft/libft.a

SRCDIR = sources
OBJDIR = obj

SRCS = main.c \
	$(SRCDIR)/utils/helpers.c \
	$(SRCDIR)/utils/errors.c \
	$(SRCDIR)/utils/utilities.c \
	$(SRCDIR)/execute/validation.c \
	$(SRCDIR)/execute/execution.c \
	$(SRCDIR)/execute/ft_cd.c \
	$(SRCDIR)/execute/ft_env.c \
	$(SRCDIR)/execute/ft_echo.c \
	$(SRCDIR)/execute/ft_pwd.c \
	$(SRCDIR)/execute/ft_export.c \
	$(SRCDIR)/execute/ft_unset.c \
	$(SRCDIR)/execute/utils.c \
	$(SRCDIR)/parser/parser.c \
	$(SRCDIR)/parser/parser_utils.c \
	$(SRCDIR)/parser/parser_cmd.c \
	$(SRCDIR)/lexer/lexer_init.c \
	$(SRCDIR)/lexer/lexer_utils.c \
	$(SRCDIR)/lexer/tokenizer.c \
	$(SRCDIR)/lexer/lexer.c

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@ $(LIBFT)

$(LIBFT):
	make all -C libft
	make bonus -C libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re libft

# To be deleted
run: all
	@./$(NAME)
