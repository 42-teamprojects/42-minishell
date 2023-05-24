/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/24 16:17:07 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char *user, char *home, char *path)
{
	free(user);
	free(home);
	free(path);
}

int	ft_cd(int idx)
{
	char	s[PATH_MAX];
	char	*user;
	char	*home;
	char	*path;

	getcwd(s, sizeof(s));
	user = ft_getenv(g_shell, "USER");
	home = ft_getenv(g_shell, "HOME");
	path = ft_strjoin("/Users/", user);
	if ((g_shell)->cmds[idx]->argc > 0 && \
		chdir((g_shell)->cmds[idx]->args[0]) != 0)
		return (free_mem(user, home, path),
			console(1, (g_shell)->cmds[idx]->args[0], strerror(errno)), 1);
	else if ((g_shell)->cmds[idx]->argc == 0 && chdir(home) != 0)
		return (free_mem(user, home, path), \
			console(1, "cd", "HOME not set"), 1);
	else if ((g_shell)->cmds[idx]->args && \
		(g_shell)->cmds[idx]->args[0] && \
		*((g_shell)->cmds[idx]->args[0]) == '~')
		chdir(path);
	ft_setenv("OLDPWD", s, g_shell);
	getcwd(s, sizeof(s));
	ft_setenv("PWD", s, g_shell);
	return (free_mem(user, home, path), 0);
}
