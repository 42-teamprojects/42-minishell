/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:06 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/15 21:19:53 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(t_shell **shell, char *var)
{
	int	i;

	i = 0;
	(void) shell;
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
	int		i;

	if ((*shell)->cmds[0]->args[0] == NULL)
		return (export_env(shell), 1);
	i = -1;
	while ((*shell)->cmds[0]->args[++i])
	{
		if (ft_strchr((*shell)->cmds[0]->args[i], '=') == NULL)
		{
			if (check_var(shell, (*shell)->cmds[0]->args[i]) && \
				!ft_is_var_exist((*shell)->env, (*shell)->cmds[0]->args[i]))
			{
				ft_setexport(&(*shell)->exp, (*shell)->cmds[0]->args[i]);
				continue ;
			}
			continue ;
		}
		value = ft_strchr((*shell)->cmds[0]->args[i], '=') + 1;
		if (!value)
			return (1);
		var = ft_split((*shell)->cmds[0]->args[i], '=');
		if (!var)
			return (1);
		if (check_var(shell, var[0]) && value)
		{
			remove_node(&(*shell)->exp, var[0], free);
			result = ft_setenv(var[0], value, shell);
		}
		free_split(var);
	}
	return (1);
}
