/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:06 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/26 11:26:01 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*escape_special_chars(const char *str)
{
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(strlen(str) * 2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '$')
		{
			result[j++] = '\\';
		}
		result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	check_var(char *var)
{
	int	i;

	i = 0;
	if (var == NULL || ft_strchr(var, '$') != NULL \
		|| (!ft_isalpha(var[0]) && var[0] != '_'))
	{
		var = ft_concat(2, "export: ", var);
		console(1, var, "not a valid identifier");
		(g_shell)->status_code = 1;
		free(var);
		return (1);
	}
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			var = ft_concat(2, "export", var);
			console(1, var, "not a valid identifier");
			(g_shell)->status_code = 1;
			free(var);
			return (1);
		}
	}
	return (0);
}

void	export_env(void)
{
	int		i;
	char	**var;
	char	*value;
	char	*escaped_value;
	t_list	*exp;

	i = 0;
	while ((g_shell)->env[i])
	{
		value = ft_strchr((g_shell)->env[i], '=') + 1;
		if (!value)
			exit(1);
		var = ft_split((g_shell)->env[i], "=");
		escaped_value = escape_special_chars(value);
		printf("declare -x %s=\"%s\"\n", var[0], escaped_value);
		free(escaped_value);
		free_array(var);
		i++;
	}
	exp = (g_shell)->exp;
	while (exp)
	{
		printf("declare -x %s\n", (char *)exp->content);
		exp = exp->next;
	}
}

int	validate_export(int idx, int i)
{
	if (ft_strchr((g_shell)->cmds[idx]->args[i], '=') == NULL || \
			(g_shell)->cmds[idx]->args[i][0] == '=')
	{
		if (!check_var((g_shell)->cmds[idx]->args[i]) && \
			!ft_is_var_exist((g_shell)->env, (g_shell)->cmds[idx]->args[i]))
			ft_setexport(&(g_shell)->exp, \
			ft_strdup((g_shell)->cmds[idx]->args[i]));
		return (0);
	}
	return (1);
}

int	ft_export(int idx)
{
	char	**var;
	char	*value;
	int		i;

	if (!(g_shell)->cmds[idx]->args)
		return (export_env(), 1);
	i = -1;
	while ((g_shell)->cmds[idx]->args[++i])
	{
		if (!validate_export(idx, i))
			continue ;
		value = ft_strchr((g_shell)->cmds[idx]->args[i], '=') + 1;
		if (!value)
			return (1);
		var = ft_split((g_shell)->cmds[idx]->args[i], "=");
		if (!var)
			return (1);
		if (!check_var(var[0]) && value)
		{
			remove_node(&(g_shell)->exp, var[0], free);
			ft_setenv(var[0], value);
		}
		free_array(var);
	}
	return ((g_shell)->status_code);
}
