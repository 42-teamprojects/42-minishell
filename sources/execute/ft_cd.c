/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/21 03:52:53 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell **shell)
{
	char	s[PATH_MAX];

	getcwd(s, sizeof(s));
	if ((*shell)->cmds[0]->args[0] && \
		!ft_strcmp((*shell)->cmds[0]->args[0], "-"))
	{
		if (ft_getenv(shell, "OLDPWD") == NULL)
			return (console(1, "cd", "OLDPWD not set"), 0);
		return (chdir(ft_getenv(shell, "OLDPWD")), \
			console(1, "cd", ft_getenv(shell, "OLDPWD")), \
			ft_setenv("OLDPWD", s, shell), 0);
	}
	if ((*shell)->cmds[0]->args[0] == NULL || \
		*((*shell)->cmds[0]->args[0]) == '~')
		return (ft_setenv("OLDPWD", s, shell), \
			chdir(ft_strjoin("/Users/", ft_getenv(shell, "USER"))), 0);
	ft_setenv("OLDPWD", s, shell);
	if (chdir((*shell)->cmds[0]->args[0]) != 0)
		return (console(1, (*shell)->cmds[0]->args[0], strerror(errno)), 1);
	return (ft_setenv("PWD", getcwd(s, sizeof(s)), shell), 0);
}
