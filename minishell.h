/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 13:24:08 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/global.h"

typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
	char	*input_redirect;
	char	*output_redirect;
	char	out_mode;
}	t_command;

typedef struct s_shell
{
	t_command	cmd;
	char		*prompt;
	char		**env;
}	t_shell;

/* Parser */
t_command	init_cmd(char *input);

/* Helpers */

char		*init_prompt(void);
void		sig_handler(int sig);
void		free_split(char **array);

#endif