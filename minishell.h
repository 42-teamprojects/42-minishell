/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:38:44 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 00:21:30 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/global.h"
# include "includes/utils.h"

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

#endif