/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/17 18:12:38 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"

/* enums */

typedef enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	ESCAPED,
	DEFAULT,
	S_UNKNOWN,
}	t_state;

typedef enum e_token_type
{
	SQUOTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	VAR = '$',
	PIPE = '|',
	RD_IN = '<',
	RD_OUT = '>',
	F_IN,
	F_OUT,
	F_APPEND,
	F_HEREDOC,
	WORD = -1,
	HEREDOC = -2,
	RD_AOUT = -3,
	NEW_LINE = '\n',
	WSPACE = ' ',
	UNKNOWN,
}	t_token_type;

/* Lexer */

typedef struct s_token
{
	int				len;
	char			*content;
	t_token_type	type;
	t_state			state;
}	t_token;

typedef struct s_lexer
{
	struct s_lexer		*prev;
	t_token				*token;
	struct s_lexer		*next;
}	t_lexer;

t_lexer			*lexer(char *input);
t_token			*new_token(char *content, int len, \
		t_token_type type, t_state state);
int				add_token(t_lexer **lexer, t_token *token);
void			free_lexer(t_lexer *lexer);
int				is_space(char c);
int				is_token(char c);
t_token_type	get_token_type(char *str);
int				is_redirection(char *str);
int				get_token_length(char *str);
int				get_token(char *input, t_lexer **lexer, int i, t_state state);
int				get_var(t_lexer **lexer, char *input, t_state state);
int				get_word(t_lexer **lexer, char *input, t_state state);
void			print_lexer(t_lexer *lexer);
void			change_state(char c, t_state *state);
int				valid_syntax(t_lexer *lexer);
t_lexer			*get_last_node(t_lexer *tokens);

/* Minishell */

typedef struct s_rd
{
	char				*file;
	t_token_type		type;
	struct s_rd			*next;
}	t_rd;

typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
	t_rd	*redir;
	char	**full_cmd;
}	t_command;

typedef struct s_shell
{
	t_lexer		*lexer;
	t_command	**cmds;
	char		**files;
	int			cmds_count;
	char		**full_cmd;
	char		*prompt;
	char		*path;
	char		**env;
	t_list		*exp;
	char		**path_list;
	int			exit;
	int			status_code;
}	t_shell;

/* Parser */

t_command		**parse(t_shell **shell);
char			**init_args(char **command);
int				args_len(t_lexer *tokens);
int				cmds_len(t_lexer *tokens);
t_command		**parse(t_shell **shell);
char			*parse_quotes(t_lexer **tokens, t_shell **shell);
void			handle_word(char **command, int *i, t_lexer **tokens, \
	t_shell **shell);
void			handle_quote(char **command, int *i, t_lexer **tokens, \
	t_shell **shell);
t_command		*init_cmd(char **command, t_rd *rd);
char			**parse_cmds(t_lexer **tokens, t_shell **shell, t_rd **rd);
t_rd			*new_rd(char *file, t_token_type type);
void			rd_addfront(t_rd **rd, t_rd *new);
void			free_rd(t_rd **rd);
void			handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell);
void			print_redir(t_rd *rd);
int				is_word(t_lexer *tokens);
int				is_quote(t_lexer *tokens);
int				is_redir(t_lexer *tokens);

/* Execution */

int				is_cmd_exist(t_command **command, t_shell **shell);
int				ft_exec(t_shell **shell);
void			ft_exec_builtin(t_shell **shell);
void			free_exec(t_shell **shell);
void			ft_pwd(t_shell **shell);
void			ft_echo(t_shell **shell);
void			ft_env(t_shell **shell);
int				ft_cd(t_shell **shell);
int				ft_unset(t_shell **shell);
int				ft_export(t_shell **shell);
int				ft_setenv(char *name, char *value, t_shell **shell);
int				ft_setenv_help(char *name, char *value, t_shell **shell, int i);
char			*ft_getenv(t_shell **shell, const char *name);
void			export_env(t_shell **shell);
void			ft_setexport(t_list **export, char *name);
int				ft_is_var_exist(char **env, char *key);

/* Helpers */

char			*init_prompt(void);
void			sig_handler(int sig);
void			free_split(char **array);
void			free_shell(t_shell **shell);

int				args_count(char **args);
char			**dup_list(char **list);
char			*redir_type(int type);

/* Errors */

void			not_found(char *cmd);
void			throw_err(int err_code, t_shell **shell);
void			console(int status, char *cmd, char *err);
#endif