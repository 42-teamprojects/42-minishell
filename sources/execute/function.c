/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:32:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/28 19:32:52 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_pwd(t_shell *shell)
{
	shell->env = malloc(1000);
	printf("%s\n", getcwd(*shell->env, sizeof(shell->env)));
}

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd.argc)
	{
		printf("%s\n", shell->cmd.args[i]);
		i++;
	}
}

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

int	ft_cd(t_shell *shell)
{
	if (shell->cmd.args[0] == NULL)
	{
		chdir(ft_strjoin("/Users/", getenv("USER")));
	}
	else if (chdir(shell->cmd.args[0]) != 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	return (0);
}
