/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/05 13:59:36 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"
# include "lexer.h"

/* enums */

typedef enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	ESCAPED,
	DEFAULT,
}	t_state;

typedef enum e_token_type
{
	SQOUTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	VAR = '$',
	PIPE = '|',
	RD_IN = '<',
	RD_OUT = '>',
	WORD = -1,
	HEREDOC = -2,
	RD_AOUT = -3,
	NEW_LINE = '\n',
	SPACE = ' ',
}	t_token_type;

/* Lexer */

typedef struct s_token
{
	int				len;
	char			*content;
	t_token_type	type;
	t_state			state;
}	t_token;

typedef struct s_dll
{
	struct s_dll		*prev;
	int					idx;
	t_token				*token;
	struct s_dll		*next;
}	t_dll;

typedef struct s_lexer
{
	t_dll	*head;
	int		size;
}	t_lexer;

t_lexer			*lexer(char *input);
t_token			*new_token(char *content, int len, \
		t_token_type type, t_state state);
t_lexer			*init_lexer(void);
int				add_token(t_lexer *lexer, t_token *token);
void			free_lexer(t_lexer *lexer);
int				is_space(char c);
int				is_token(char c);
t_token_type	get_token_type(char *str);
int				is_redirection(char *str);
int				get_token_length(char *str);
int				get_token(char *input, t_lexer *lexer, int i, t_state state);
int				get_var(t_lexer *lexer, char *input, t_state state);
int				get_word(t_lexer *lexer, char *input, t_state state);
void			print_lexer(t_lexer *lexer);
void			change_state(t_lexer *lexer, char c, t_state *state);
int				valid_syntax(t_lexer *lexer);

/* Minishell */

typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
	char	**full_cmd;
}	t_command;

typedef struct s_shell
{
	t_lexer		*lexer;
	t_command	*cmd;
	char		*prompt;
	char		*path;
	char		**env;
	char		**path_list;
	int			exit_status;
}	t_shell;

/* Parser */

t_command		*init_cmd(char **command);

/* Execution */

int				verify_input(char **command, t_shell *shell);
int				ft_exec(t_shell *shell);
void			ft_exec_builtin(t_shell *shell);
void			free_exec(t_shell *shell);

/* Helpers */

char			*init_prompt(void);
void			sig_handler(int sig);
void			free_split(char **array);
void			free_shell(t_shell *shell);

int				args_count(char **args);
char			**dup_list(char **list);

/* Errors */

void			print404(char *cmd);
void			throw_err(int err_code, t_shell *shell);
#endif