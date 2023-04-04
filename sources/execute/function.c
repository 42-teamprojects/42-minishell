/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:32:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/04 22:00:10 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_pwd(t_shell *shell)
{
	char	s[PATH_MAX];

	(void)shell;
	printf("%s\n", getcwd(s, sizeof(s)));
}

void	ft_echo(t_shell *shell)
{
	int				i;
	char			*dollar_sign;
	char			*var_name;
	char			*var_value;
	int				state;

	i = 0;
	state = 3;
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
		chdir(ft_strjoin("/Users/", getenv("USER")));
	else if (chdir(shell->cmd.args[0]) != 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	return (0);
}
