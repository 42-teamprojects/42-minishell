/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/22 18:53:06 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char *user, char *home, char *path)
{
	free(user);
	free(home);
	free(path);
}

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
	if ((*shell)->cmds[idx]->argc > 0 && \
		chdir((*shell)->cmds[idx]->args[0]) != 0)
		return (free_mem(user, home, path),
			console(1, (*shell)->cmds[idx]->args[0], strerror(errno)), 1);
	else if ((*shell)->cmds[idx]->argc == 0 && chdir(home) != 0)
		return (free_mem(user, home, path), \
			console(1, "cd", "HOME not set"), 1);
	else if ((*shell)->cmds[idx]->args && \
		(*shell)->cmds[idx]->args[0] && \
		*((*shell)->cmds[idx]->args[0]) == '~')
		chdir(path);
	ft_setenv("OLDPWD", s, shell);
	getcwd(s, sizeof(s));
	ft_setenv("PWD", s, shell);
	return (free_mem(user, home, path), 0);
}
