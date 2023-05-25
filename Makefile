NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/ #-fsanitize=address -g

HEADERS = includes/global.h includes/minishell.h

LIBFT	= libft/libft.a

SRCS = main.c \
	sources/utils/helpers.c \
	sources/utils/errors.c \
	sources/utils/utilities.c \
	sources/utils/free.c \
	sources/utils/check_syntax.c \
	sources/execute/validation.c \
	sources/execute/execution.c \
	sources/execute/ft_cd.c \
	sources/execute/ft_env.c \
	sources/execute/ft_echo.c \
	sources/execute/ft_pwd.c \
	sources/execute/ft_export.c \
	sources/execute/ft_exit.c \
	sources/execute/ft_export_utils.c \
	sources/execute/ft_unset.c \
	sources/execute/utils.c \
	sources/execute/utils2.c \
	source/execute/rd.c \
	source/execute/pipe.c \
	sources/parser/utils.c \
	sources/parser/parser.c \
	sources/parser/parser_utils.c \
	sources/parser/parser_cmd.c \
	sources/parser/parser_redir.c \
	sources/parser/redir_utils.c \
	sources/parser/ambiguous.c \
	sources/parser/heredoc.c \
	sources/lexer/lexer_init.c \
	sources/lexer/lexer_utils.c \
	sources/lexer/tokenizer.c \
	sources/lexer/lexer.c \

# create necessary directories
OBJDIR = obj
UTILSDIR = $(OBJDIR)/sources/utils
EXECUTEDIR = $(OBJDIR)/sources/execute
PARSERDIR = $(OBJDIR)/sources/parser
LEXERDIR = $(OBJDIR)/sources/lexer
$(shell mkdir -p $(UTILSDIR) $(EXECUTEDIR) $(PARSERDIR) $(LEXERDIR))

# compile source files
OBJS = main.o \
	$(UTILSDIR)/helpers.o \
	$(UTILSDIR)/errors.o \
	$(UTILSDIR)/utilities.o \
	$(UTILSDIR)/free.o \
	$(UTILSDIR)/check_syntax.o \
	$(EXECUTEDIR)/validation.o \
	$(EXECUTEDIR)/execution.o \
	$(EXECUTEDIR)/ft_cd.o \
	$(EXECUTEDIR)/ft_env.o \
	$(EXECUTEDIR)/ft_echo.o \
	$(EXECUTEDIR)/ft_pwd.o \
	$(EXECUTEDIR)/ft_export.o \
	$(EXECUTEDIR)/ft_export_utils.o \
	$(EXECUTEDIR)/ft_unset.o \
	$(EXECUTEDIR)/rd.o \
	$(EXECUTEDIR)/pipe.o \
	$(EXECUTEDIR)/ft_exit.o \
	$(EXECUTEDIR)/utils.o \
	$(EXECUTEDIR)/utils2.o \
	$(PARSERDIR)/utils.o \
	$(PARSERDIR)/parser.o \
	$(PARSERDIR)/parser_utils.o \
	$(PARSERDIR)/parser_cmd.o \
	$(PARSERDIR)/parser_redir.o \
	$(PARSERDIR)/heredoc.o \
	$(PARSERDIR)/redir_utils.o \
	$(PARSERDIR)/ambiguous.o \
	$(LEXERDIR)/lexer_init.o \
	$(LEXERDIR)/lexer_utils.o \
	$(LEXERDIR)/tokenizer.o \
	$(LEXERDIR)/lexer.o \

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o  $@ $(LIBFT)

$(LIBFT):
	make all -C libft

$(UTILSDIR)/%.o: sources/utils/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTEDIR)/%.o: sources/execute/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PARSERDIR)/%.o: sources/parser/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LEXERDIR)/%.o: sources/lexer/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f minishell $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft

# To be
run: all
	@./minishell