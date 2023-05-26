/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/26 12:15:56 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(int idx)
{
	char	s[PATH_MAX];
	char	*home;

	getcwd(s, sizeof(s));
	home = ft_getenv("HOME");
	if ((g_shell)->cmds[idx]->argc > 0 && \
		chdir((g_shell)->cmds[idx]->args[0]) != 0)
	{
		free(home);
		return (console(1, (g_shell)->cmds[idx]->args[0], strerror(errno)), 1);
	}
	else if ((g_shell)->cmds[idx]->argc == 0 && chdir(home) != 0)
		return (free(home), console(1, "cd", "HOME not set"), 1);
	ft_setenv("OLDPWD", s);
	getcwd(s, sizeof(s));
	ft_setenv("PWD", s);
	return (free(home), 0);
}
