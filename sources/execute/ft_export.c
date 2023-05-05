/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:06 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/05 15:52:21 by htalhaou         ###   ########.fr       */
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
		console(1, var, "not a valid identifier");
		free(var);
		return (0);
	}
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			var = ft_concat(2, "export", var);
			console(1, var, "not a valid identifier");
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
			exit(0);
		var = ft_split((*shell)->env[i], '=');
		printf("declare -x %s=\"%s\"\n", var[0], value);
		free_array(var);
		i++;
	}
	exp = (*shell)->exp;
	while (exp)
	{
		printf("declare -x %s\n", (char *)exp->content);
		exp = exp->next;
	}
}

int	validate_export(t_shell **shell, int idx, int i)
{
	if (ft_strchr((*shell)->cmds[idx]->args[i], '=') == NULL || \
			(*shell)->cmds[idx]->args[i][0] == '=')
	{
		if (check_var(shell, (*shell)->cmds[idx]->args[i]) && \
			!ft_is_var_exist((*shell)->env, (*shell)->cmds[idx]->args[i]))
			ft_setexport(&(*shell)->exp, \
			ft_strdup((*shell)->cmds[idx]->args[i]));
		return (1);
	}
	return (0);
}

int	ft_export(t_shell **shell, int idx)
{
	char	**var;
	char	*value;
	int		i;

	if ((*shell)->cmds[idx]->args[0] == NULL)
		return (export_env(shell), 1);
	i = -1;
	while ((*shell)->cmds[idx]->args[++i])
	{
		if (validate_export(shell, idx, i))
			continue ;
		value = ft_strchr((*shell)->cmds[idx]->args[i], '=') + 1;
		if (!value)
			return (1);
		var = ft_split((*shell)->cmds[idx]->args[i], '=');
		if (!var)
			return (1);
		if (check_var(shell, var[0]) && value)
		{
			remove_node(&(*shell)->exp, var[0], free);
			return (ft_setenv(var[0], value, shell), free_array(var), 0);
		}
		free_array(var);
	}
	return (1);
}
