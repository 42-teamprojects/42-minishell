/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:06 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/09 22:41:20 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(char *var)
{
	int	i;

	if ((*var >= '0' && *var <= '9'))
		return (console(0, var, "not a valid identifier"), 0);
	i = 0;
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '\n' && var[i] != '\0')
			return (console(0, var, "not a valid identifier"), 0);
	}
	return (1);
}

int	ft_export(t_shell **shell)
{
	int		result;
	char	**var;

	if ((*shell)->cmds[0]->args[0] == NULL)
		return (-1);
	var = ft_split((*shell)->cmds[0]->args[0], '=');
	if (!var)
		return (1);
	if (check_var(var[0]) && var[1])
	{
		result = ft_setenv(var[0], var[1], shell);
		if (result == 0)
			printf("Exported %s=%s\n", var[0], var[1]);
		else
			printf("Failed to export %s=%s\n", var[0], var[1]);
	}
	return (0);
}

int	ft_setenv_help(char *name, char *value, t_shell **shell, int i)
{
	char	*input;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, (*shell)->env, i * sizeof(char *));
	input = ft_strjoin(name, "=");
	input = ft_strjoin_gnl(input, value);
	new_environ[i] = input;
	new_environ[i + 1] = NULL;
	(*shell)->env = new_environ;
	return (0);
}

int	ft_setenv(char *name, char *value, t_shell **shell)
{
	int		i;
	char	*input;
	int		overwrite;

	i = -1;
	if (name == NULL || value == NULL)
		return (-1);
	overwrite = 0;
	while ((*shell)->env[++i])
	{
		if (ft_strncmp((*shell)->env[i], name, ft_strlen(name)) == 0
			&& (*shell)->env[i][ft_strlen(name)] == '=')
		{
			overwrite = 1;
			break ;
		}
	}
	if (overwrite == 1)
	{
		input = ft_concat(3, name, "=", value);
		(*shell)->env[i] = input;
	}
	else
		ft_setenv_help(name, value, shell, i);
	return (0);
}
