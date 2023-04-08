/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:32:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/08 12:49:39 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_pwd(t_shell **shell)
{
	char	s[PATH_MAX];

	(void)shell;
	printf("%s\n", getcwd(s, sizeof(s)));
}

void	ft_env(t_shell **shell)
{
	int	i;

	i = 0;
	while ((*shell)->env[i])
	{
		printf("%s\n", (*shell)->env[i]);
		i++;
	}
}

int	ft_cd(t_shell **shell)
{
	if ((*shell)->cmds[0]->args[0] == NULL)
		chdir(ft_strjoin("/Users/", getenv("USER")));
	else if (chdir((*shell)->cmds[0]->args[0]) != 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	return (0);
}

char	*ft_getenv(t_shell **shell, const char *name)
{
	char	**values;
	char	*value;
	int		name_len;
	int		i;

	value = NULL;
	values = NULL;
	name_len = ft_strlen(name);
	i = 0;
	while ((*shell)->env[i])
	{
		if (ft_strncmp((*shell)->env[i], name, name_len) == 0
			&& (*shell)->env[i][name_len] == '=')
		{
			values = ft_split((*shell)->env[i], '=');
			value = ft_strdup(values[1]);
			free_split(values);
			break ;
		}
		i++;
	}
	return (value);
}

void	ft_echo(t_shell **shell)
{
	int		i;
	char	*var_name;
	int		state;
	char	*dollar_sign;
	char	*var_value;

	i = 0;
	state = 3;
	while (i < (*shell)->cmds[0]->argc)
	{
		dollar_sign = strchr((*shell)->cmds[0]->args[i], '$');
		if (state == DOUBLE_QUOTE && dollar_sign)
		{
			if (*(dollar_sign + 1) == '\0')
				printf("$ ");
			else
			{
				var_name = dollar_sign + 1;
				var_value = ft_getenv(shell, var_name);
				if (var_value)
					printf("%s ", var_value);
				else
					printf("");
			}
		}
		else if (state == SINGLE_QUOTE && dollar_sign)
		{
			var_name = dollar_sign + 1;
			printf("%s", (*shell)->cmds[0]->args[i]);
		}
		else
			printf("%s ", (*shell)->cmds[0]->args[i]);
		i++;
	}
	printf("\n");
}
