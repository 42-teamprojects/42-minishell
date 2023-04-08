/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:30 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/08 23:25:57 by htalhaou         ###   ########.fr       */
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
		chdir(ft_getenv(shell, "OLDPWD"));
		ft_setenv("OLDPWD", s, shell);
	}
	else if ((*shell)->cmds[0]->args[0] == NULL)
		chdir(ft_strjoin("/Users/", getenv("USER")));
	else if (chdir((*shell)->cmds[0]->args[0]) != 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	return (0);
}
