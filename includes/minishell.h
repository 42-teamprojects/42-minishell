/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/02 16:54:12 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "global.h"

/* enums */

typedef enum e_status
{
	IN_DQUOTE,
	IN_SQUOTE,
	ESCAPE,
	DEFAULT,
}	t_status;

typedef enum e_token
{
	SPACE = ' ',
	NEW_LINE = '\n',
	SQOUTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	VAR = '$',
	PIPE = '|',
	RIN = '<',
	ROUT = '>',
	WORD = -1,
	HEREDOC = -2,
	AROUT = -3,
}	t_token;

/* Structs */

typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
	char	*input_redirect;
	char	*output_redirect;
	char	out_mode;
	char	**full_cmd;
}	t_command;

typedef struct s_shell
{
	t_command	cmd;
	char		*prompt;
	char		*path;
	char		**env;
	char		**path_list;
	int			exit_status;
}	t_shell;

/* Parser */

t_command	init_cmd(char **command);
char		**parse_input(char *input);

/* Execution */

int			verify_input(char **command, t_shell *shell);
int			ft_exec(t_shell *shell);
void		ft_exec_builtin(t_shell *shell);
void		free_exec(t_shell *shell);

/* Helpers */

char		*init_prompt(void);
void		sig_handler(int sig);
void		free_split(char **array);
void		free_shell(t_shell *shell);

int			args_count(char **args);
char		**dup_list(char **list);

/* Errors */

void		print404(char *cmd);
void		throw_err(int err_code, t_shell *shell);

#endif