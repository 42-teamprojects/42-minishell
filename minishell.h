/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/23 22:13:38 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BRED "\e[1;31m"
# define RED "\033[0;31m"
# define YELLOW "\033[1;33m"
# define CX "\033[0m"
# define BLACK "\e[0;30m"
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
typedef struct s_command 
{
	char *name;
	char **args;
}	t_command;

typedef struct s_shell
{
	t_command 	cmd;
	char		**env;
}	t_shell;

#endif