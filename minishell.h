/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 11:31:34 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/global.h"

typedef struct s_command 
{
	char *name;
	char **args;
}	t_command;

typedef struct s_shell
{
	t_command 	cmd;
	char		*prompt;
	char		**env;
}	t_shell;

/* Helpers */

char	*init_prompt();
void	sig_handler(int sig);

#endif