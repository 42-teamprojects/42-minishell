/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/05 16:41:02 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"

/* LEXER */

t_lexer			*lexer(char *input);
t_token			*new_token(char *content, int len, \
		t_token_type type, t_state state);
int				add_token(t_lexer **lexer, t_token *token);
int				is_space(char c);
int				is_token(char c);
t_token_type	get_token_type(char *str);
t_token_type	is_redirection(char *str);
int				get_token_length(char *str);
int				get_token(char *input, t_lexer **lexer, int i, t_state state);
int				get_var(t_lexer **lexer, char *input, t_state state);
int				get_word(t_lexer **lexer, char *input, t_state state);
void			change_state(char c, t_state *state);
int				valid_syntax(t_shell **shell);
t_lexer			*get_last_node(t_lexer *tokens);

/* PARSER */

t_command		**parse(t_shell **shell);
char			**init_args(char **command);
int				args_len(t_lexer *tokens);
int				cmds_len(t_lexer *tokens);
t_command		**parse(t_shell **shell);
char			*parse_quotes(t_lexer **tokens, t_shell **shell, int expand);
void			handle_word(char **command, int *i, t_lexer **tokens, \
	t_shell **shell);
void			handle_quote(char **command, int *i, t_lexer **tokens, \
	t_shell **shell);
t_command		*init_cmd(char **command, char *path, t_rd *rd);
char			**parse_cmds(t_lexer **tokens, t_shell **shell, t_rd **rd);
t_rd			*new_rd(char *file, t_token_type type);
void			rd_addback(t_rd **rd, t_rd *new);
int			handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell);
int				is_word(t_lexer *tokens);
int				is_quote(t_lexer *tokens);
int				is_redir(t_lexer *tokens);

/* EXECUTION */

char			*check_cmd(char **cmd, char **path_list);
int				ft_exec(t_shell **shell);
int				ft_exec_builtin(t_shell **shell, int idx);
int				ft_pwd(t_shell **shell, int idx);
int				ft_echo(t_shell **shell, int idx);
int				ft_env(t_shell **shell, int idx);
int				ft_exit(t_shell **shell, int idx);
int				ft_cd(t_shell **shell, int idx);
int				ft_unset(t_shell **shell, int idx);
int				ft_export(t_shell **shell, int idx);
int				ft_setenv(char *name, char *value, t_shell **shell);
int				ft_setenv_help(char *name, char *value, t_shell **shell, int i);
char			*ft_getenv(t_shell **shell, const char *name);
void			export_env(t_shell **shell);
void			ft_setexport(t_list **export, char *name);
int				ft_is_var_exist(char **env, char *key);
int				handle_redirection(t_rd *rd, t_shell **shell);
int				redirect_output(char *file, t_shell **shell, t_token_type type);
int				redirect_input(char *file, t_shell **shell);
int				create_pipe(t_shell **shell);
void			close_pipes(t_shell **shell);
void			redirect_pipe(t_shell **shell, int i);
int				is_cmd_parent(char *cmd);

/* HELPERS */

void			sig_handler(int sig);
int				args_count(char **args);
char			**dup_list(char **list);
char			*redir_type(t_token_type type);
char			*remove_slashes(char *path);
void			init_shell(t_shell **shell, char **env);
void			rollback_fd(t_shell **shell);

/* ERRORS */

void			stop(int err_code, t_shell **shell);
void			console(int status, char *cmd, char *err);

/* FREE */

void			free_array(char **array);
void			free_lexer(t_lexer *lexer);
void			free_rd(t_rd *rd);
void			free_command(t_command *cmd);
void			free_shell(t_shell *shell, int option);

// TO BE DELETED
void			print_commands(t_command **cmds);
void			print_redir(t_rd *rd);
void			print_lexer(t_lexer *lexer);
#endif