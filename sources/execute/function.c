/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:32:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/31 21:18:26 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern char	**environ;

void	ft_pwd(t_shell *shell)
{
	shell->env = malloc(1000);
	printf("%s\n", getcwd(*shell->env, sizeof(shell->env)));
}

void	ft_echo(t_shell *shell)
{
	int				i;
	char			*dollar_sign;
	char			*var_name;
	char			*var_value;

	i = 0;
	int state = 3;
	dollar_sign = strchr(*shell->cmd.args, '$');
	if (state == DOUBLE_QUOTE && dollar_sign)
	{
		var_name = dollar_sign + 1;
		var_value = getenv(var_name);
		if (var_value)
			printf("%s\n", var_value);
		else
			printf("Variable not found: %s\n", var_name);
	}
	else if (state == SINGLE_QUOTE && dollar_sign)
	{
		var_name = dollar_sign + 1;
		printf("%s\n", shell->cmd.args[0]);
	}
	else
		printf("%s\n", shell->cmd.args[0]);
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

// int	ft_unset(t_shell *shell)
// {
// 	if (unsetenv(shell->cmd.args[0]))
// 	{
// 		perror("unsetenv");
// 		return (0);
// 	}
// 	printf("Environment variable '%s' has been unset.\n", shell->cmd.args[0]);
// 	return (1);
// }

void	ft_export(t_shell *shell)
{
	int		result;
	char	**var_name;

	var_name = ft_split(shell->cmd.args[0], '=');
	if (var_name[1] != NULL)
	{
		result = ft_setenv(var_name[0], var_name[1], 0, shell);
		if (result == 0)
			printf("Exported %s=%s\n", var_name[0], var_name[1]);
		else
			printf("Failed to export %s=%s\n", var_name[0], var_name[1]);
	}
}
