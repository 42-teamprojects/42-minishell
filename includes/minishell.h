/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/19 00:24:57 by yelaissa         ###   ########.fr       */
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
	HEREDOC,
	RD_AOUT,
	WORD,
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
t_token_type	is_redirection(char *str);
int				get_token_length(char *str);
int				get_token(char *input, t_lexer **lexer, int i, t_state state);
int				get_var(t_lexer **lexer, char *input, t_state state);
int				get_word(t_lexer **lexer, char *input, t_state state);
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
	char	*path;
	char	**full_cmd;
}	t_command;

typedef struct s_shell
{
	t_lexer		*lexer;
	t_command	**cmds;
	char		**files;
	char		*prompt;
	int			cmds_count;
	char		**env;
	t_list		*exp;
	char		**path_list;
	int			old_out;
	int			old_in;
	int			orig_stdout;
	int			fd[2];
	int			red_fd[2];
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
t_command *init_cmd(char **command, char *path, t_rd *rd);
char			**parse_cmds(t_lexer **tokens, t_shell **shell, t_rd **rd);
t_rd			*new_rd(char *file, t_token_type type);
// void			rd_addfront(t_rd **rd, t_rd *new);
void			free_rd(t_rd **rd);
void			handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell);
int				is_word(t_lexer *tokens);
int				is_quote(t_lexer *tokens);
int				is_redir(t_lexer *tokens);

/* Execution */

char			*check_cmd(char **cmd, char **path_list);
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
int				handle_redirection(t_rd *rd, t_shell **shell);
int				redirect_output(char *file, t_shell **shell);
int				redirect_input(char *file, t_shell **shell);
int				check_file(char *file);
int				append(char *file);void rd_addback(t_rd **rd, t_rd *new);

/* Helpers */

char			*init_prompt(void);
void			sig_handler(int sig);
void			free_split(char **array);
void			free_shell(t_shell **shell);

int				args_count(char **args);
char			**dup_list(char **list);
char			*redir_type(t_token_type type);
char			*remove_slashes(char *path);

/* Errors */

void			not_found(char *cmd);
void			stop(int err_code, t_shell **shell);
void			console(int status, char *cmd, char *err);


// to be deleted
void			print_commands(t_command **cmds);
void			print_redir(t_rd *rd);
void			print_lexer(t_lexer *lexer);
#endif