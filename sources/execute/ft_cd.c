/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/04 17:56:42 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell **shell, int idx)
{
	char	s[PATH_MAX];
	char	*user;
	char	*home;
	char	*path;

	getcwd(s, sizeof(s));
	user = ft_getenv(shell, "USER");
	home = ft_getenv(shell, "HOME");
	path = ft_strjoin("/Users/", user);
	if ((*shell)->cmds[idx]->argc > 0)
	{
		if (chdir((*shell)->cmds[idx]->args[0]) != 0)
			return (console(1, (*shell)->cmds[idx]->args[0], strerror(errno)), 1);
	}
	if ((*shell)->cmds[idx]->args[0] == NULL && home != NULL)
		return (ft_setenv("OLDPWD", s, shell), \
			chdir(path), free(user), free(path), 0);
	else if ((*shell)->cmds[idx]->args[0] == NULL && home == NULL)
	{
		(*shell)->status_code = 1;
		return (console(1, "cd", "HOME not set"), 1);
	}
	if (*((*shell)->cmds[idx]->args[0]) == '~')
		return (ft_setenv("OLDPWD", s, shell), \
			chdir(path), free(user), free(path), 0);
	ft_setenv("OLDPWD", s, shell);
	return (ft_setenv("PWD", getcwd(s, sizeof(s)), shell), 0);
}
