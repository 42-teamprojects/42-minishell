/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:06 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/10 22:17:24 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(char *var)
{
	int	i;

	i = 0;
	if (var == NULL || ft_strchr(var, '$') != NULL \
		|| (!ft_isalpha(var[0]) && var[0] != '_'))
	{
		var = ft_concat(2, "export: ", var);
		console(0, var, "not a valid identifier");
		free(var);
		return (0);
	}
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			var = ft_concat(2, "export: ", var);
			console(0, var, "not a valid identifier");
			free(var);
			return (0);
		}
	}
	return (1);
}

void	export_env(t_shell **shell)
{
	int		i;
	char	**var;
	char	*value;
	t_list	*exp;

	i = 0;
	while ((*shell)->env[i])
	{
		value = ft_strchr((*shell)->env[i], '=') + 1;
		if (!value)
			exit (0);
		var = ft_split((*shell)->env[i], '=');
		printf("declare -x %s=\"%s\"\n", var[0], value);
		free_split(var);
		i++;
	}
	exp = (*shell)->exp;
	while (exp)
	{
		printf("declare -x %s\n", exp->content);
		free_split(var);
		exp = exp->next;
	}
}

int	ft_setenv_help(char *name, char *value, t_shell **shell, int i)
{
	char	*input;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, (*shell)->env, i * sizeof(char *));
	input = ft_concat(3, name, "=", value);
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

int	ft_export(t_shell **shell)
{
	int		result;
	char	**var;
	char	*value;

	if ((*shell)->cmds[0]->args[0] == NULL)
		return (export_env(shell), 1);
	if (ft_strchr((*shell)->cmds[0]->args[0], '=') == NULL)
	{
		if (!ft_is_var_exist((*shell)->env, (*shell)->cmds[0]->args[0]))
			return (ft_setexport(&(*shell)->exp, \
				(*shell)->cmds[0]->args[0]), 1);
		return (1);
	}
	value = ft_strchr((*shell)->cmds[0]->args[0], '=') + 1;
	if (!value)
		return (1);
	var = ft_split((*shell)->cmds[0]->args[0], '=');
	if (!var)
		return (1);
	if (check_var(var[0]) && value)
	{
		remove_node(&(*shell)->exp, var[0], free);
		result = ft_setenv(var[0], value, shell);
	}
	return (free_split(var), 0);
}
