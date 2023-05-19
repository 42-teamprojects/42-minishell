/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:49 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/19 19:32:53 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# define BRED "\e[1;31m"
# define RED "\033[0;31m"
# define YELLOW "\033[1;33m"
# define CX "\033[0m"
# define BLACK "\e[0;30m"
# define GREEN "\e[0;32m"
# define BGREEN "\e[1;32m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>

# define BASIC 0
# define CMD 1
# define FULL 2

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

/* Minishell */

typedef struct s_rd
{
	char				*file;
	int					fd[2];
	t_token_type		type;
	struct s_rd			*next;
}	t_rd;

typedef struct s_fd
{
	int	old_out;
	int	old_in;
	int	orig_stdout;
	int	orig_stdin;
}	t_fd;

typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
	t_rd	*redir;
	int		fd[2];
	char	*path;
	char	**full_cmd;
}	t_command;

typedef struct s_shell
{
	t_lexer		*lexer;
	t_command	**cmds;
	t_list		*exp;
	t_fd		fd;
	char		**env;
	int			cmds_count;
	int			exit;
	int			status_code;
}	t_shell;

#endif