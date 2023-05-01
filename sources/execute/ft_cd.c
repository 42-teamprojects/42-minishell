/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/01 19:25:45 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell **shell, int idx)
{
	char	s[PATH_MAX];
	char	*oldpwd;
	char	*user;
	char	*path;

	getcwd(s, sizeof(s));
	user = ft_getenv(shell, "USER");
	path = ft_strjoin("/Users/", user);
	if ((*shell)->cmds[idx]->args[0] && \
		!ft_strcmp((*shell)->cmds[idx]->args[0], "-"))
	{
		oldpwd = ft_getenv(shell, "OLDPWD");
		if (oldpwd == NULL)
			return (console(1, "cd", "OLDPWD not set"), 0);
		return (free(oldpwd), chdir(oldpwd), console(1, "cd", oldpwd), \
			ft_setenv("OLDPWD", s, shell), 0);
	}
	if ((*shell)->cmds[idx]->args[0] == NULL || \
		*((*shell)->cmds[idx]->args[0]) == '~')
		return (ft_setenv("OLDPWD", s, shell), \
			chdir(path), free(user), free(path), 0);
	ft_setenv("OLDPWD", s, shell);
	if (chdir((*shell)->cmds[idx]->args[0]) != 0)
		return (console(1, (*shell)->cmds[idx]->args[0], strerror(errno)), 1);
	return (ft_setenv("PWD", getcwd(s, sizeof(s)), shell), 0);
}
