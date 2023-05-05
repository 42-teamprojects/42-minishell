/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:27:15 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/05 15:52:52 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_for_unset(t_shell **shell, char *var)
{
	int	i;

	i = 0;
	(void) shell;
	if (ft_strchr(var, '=') != NULL \
		|| (!ft_isalpha(var[0]) && var[0] != '_'))
	{
		var = ft_concat(3, "unset: '", var, "': not a valid identifier");
		console(1, var, "");
		free(var);
		return (0);
	}
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			var = ft_concat(3, "unset: '", var, "': not a valid identifier");
			console(1, var, "");
			free(var);
			return (0);
		}
	}
	return (1);
}
int	ft_unset(t_shell **shell, int idx)
{
	int		i;
	int		j;
	int		k;
	char	**new_environ;
	int		should_copy;

	i = 0;
	while ((*shell)->cmds[idx]->args[i])
	{
		if (!check_var_for_unset(shell, (*shell)->cmds[idx]->args[i]))
			return (1);
		i++;
	}
	i = 0;
	while ((*shell)->env[i])
		i++;
	new_environ = malloc((i + 1) * sizeof(char *));
	if (!new_environ)
		return (1);
	if ((*shell)->cmds[idx]->args[0] == NULL)
		return (1);
	i = -1;
	k = 0;
	while ((*shell)->env[++i])
	{
		should_copy = 1;
		j = -1;
		while ((*shell)->cmds[idx]->args[++j])
		{
			if (ft_strncmp((*shell)->env[i], (*shell)->cmds[idx]->args[j],
					ft_strlen((*shell)->cmds[idx]->args[j])) == 0 \
			&& (*shell)->env[i][ft_strlen((*shell)->cmds[idx]->args[j])] == '=')
			{
				should_copy = 0;
				break ;
			}
		}
		if (should_copy)
		{
			new_environ[k] = ft_strdup((*shell)->env[i]);
			k++;
		}
	}
	new_environ[k] = NULL;
	(*shell)->env = new_environ;
	return (0);
}
