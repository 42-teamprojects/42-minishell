/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 17:51:40 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"

t_shell	*g_shell;

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

t_command		**parse(void);
char			**init_args(char **command);
int				args_len(t_lexer *tokens, t_token_type test_type);
int				cmds_len(t_lexer *tokens);
char			*parse_quotes(t_lexer **tokens, int expand);
void			handle_word(char **command, int *i, \
				t_lexer **tokens, int expand);
int				handle_word_redir(char **command, int *i, t_lexer **tokens);
void			handle_quote(char **command, int *i, \
				t_lexer **tokens, int expand);
char			*open_heredoc(t_lexer **tokens);
t_command		*init_cmd(char **command, char *path, t_rd *rd);
char			**parse_cmds(t_lexer **tokens, t_rd **rd, int *err);
t_rd			*new_rd(char *file, t_token_type type);
void			rd_addback(t_rd **rd, t_rd *new);
int				handle_redir(t_rd **rd, t_lexer **tokens);
int				is_word(t_lexer *tokens);
int				is_quote(t_lexer *tokens);
int				is_redir(t_lexer *tokens);
void			update_command(t_lexer **tokens, char **command, \
				int *i, char *expanded);
int				check_near_quotes(t_lexer **tokens);
int				all_space_ambiguous(t_lexer **tokens);
int				space_right_quotes_ambiguous(t_lexer **tokens);
int				space_right_ambiguous(t_lexer **tokens);
void			write_heredoc(int fd, char *line, char *delimiter, int flag);
void			open_file(char *file, t_token_type type);
char			**allocate_command(t_lexer **tokens);
void			parse_logic(char ***command, int *i, t_lexer **tokens);
char			*expand_variables_in_line(char *line);
char			**get_args(t_lexer **tokens, int *i, int *flag);
void			handler(int sig);
char			*tokens_to_str(t_lexer **tokens);
/* EXECUTION */

char			*check_cmd(char **cmd);
int				ft_exec(void);
int				ft_exec_builtin(int idx);
int				ft_pwd(int idx);
int				ft_echo(int idx);
int				ft_env(int idx);
int				ft_exit(int idx);
int				ft_cd(int idx);
int				ft_unset(int idx);
int				ft_export(int idx);
int				ft_setenv(char *name, char *value);
int				ft_setenv_help(char *name, char *value, int i);
char			*ft_getenv(const char *name);
void			export_env(void);
void			ft_setexport(t_list **export, char *name);
int				ft_is_var_exist(char **env, char *key);
int				handle_redirection(t_rd *rd);
int				redirect_output(char *file, t_token_type type);
int				redirect_input(char *file);
int				create_pipe(void);
void			close_pipes(void);
void			redirect_pipe(int i);
int				is_cmd_parent(char *cmd);
int				is_var_alone(t_lexer *tokens);
int				check_args_for_unset(int idx);
char			**create_new_environ(int env_count);
int				check_var_for_unset(char *var);

/* HELPERS */

void			sig_handler(int sig);
int				args_count(char **args);
char			**dup_list(char **list);
char			*redir_type(t_token_type type);
char			*remove_slashes(char *path);
void			init_shell(t_shell **shell, char **env);
void			rollback_fd(t_shell **shell);
int				is_token_type(t_lexer *tokens, \
				t_token_type type, t_state state);

/* ERRORS */

void			stop(int err_code);
void			console(int status, char *cmd, char *err);

/* FREE */

void			free_array(char **array);
void			free_lexer(t_lexer *lexer);
void			free_rd(t_rd *rd);
void			free_command(t_command *cmd);
void			free_shell(t_shell *shell, int option);

void			rl_replace_line(const char *str, int i);

#endif