/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:26:06 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/21 14:00:42 by yelaissa         ###   ########.fr       */
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
		(*shell)->status_code = 1;
		free(var);
		return (1);
	}
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			var = ft_concat(2, "export", var);
			console(1, var, "not a valid identifier");
			(*shell)->status_code = 1;
			free(var);
			return (1);
		}
	}
	return (0);
}

void	export_env(t_shell **shell)
{
	int		i;
	char	**var;
	char	*value;
	char	*escaped_value;
	t_list	*exp;

	i = 0;
	while ((*shell)->env[i])
	{
		value = ft_strchr((*shell)->env[i], '=') + 1;
		if (!value)
			exit(1);
		var = ft_split((*shell)->env[i], '=');
		escaped_value = escape_special_chars(value);
		printf("declare -x %s=\"%s\"\n", var[0], escaped_value);
		free(escaped_value);
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
		if (!check_var(shell, (*shell)->cmds[idx]->args[i]) && \
			!ft_is_var_exist((*shell)->env, (*shell)->cmds[idx]->args[i]))
			ft_setexport(&(*shell)->exp, \
			ft_strdup((*shell)->cmds[idx]->args[i]));
		return (0);
	}
	return (1);
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
		if (!validate_export(shell, idx, i))
			continue ;
		value = ft_strchr((*shell)->cmds[idx]->args[i], '=') + 1;
		if (!value)
			return (1);
		var = ft_split((*shell)->cmds[idx]->args[i], '=');
		if (!var)
			return (1);
		if (!check_var(shell, var[0]) && value)
		{
			remove_node(&(*shell)->exp, var[0], free);
			ft_setenv(var[0], value, shell);
		}
		free_array(var);
	}
	return ((*shell)->status_code);
}
