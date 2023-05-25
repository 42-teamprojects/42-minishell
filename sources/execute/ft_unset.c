/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:27:15 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/25 16:43:47 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_var
{
	int	i;
	int	k;
	int	should_copy;
	int	j;
}	t_var;

int	check_var_for_unset(char *var)
{
	int	i;

	i = 0;
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

int	copy_env_and_unset(int idx, char **new_environ)
{
	t_var	v;

	v.k = 0;
	v.i = -1;
	while ((g_shell)->env[++v.i])
	{
		v.should_copy = 1;
		v.j = -1;
		while ((g_shell)->cmds[idx]->args[++v.j])
		{
			if (ft_strncmp((g_shell)->env[v.i], (g_shell)->cmds[idx]->args[v.j],
					ft_strlen((g_shell)->cmds[idx]->args[v.j])) == 0 \
			&& (g_shell)->env[v.i] \
			[ft_strlen((g_shell)->cmds[idx]->args[v.j])] == '=')
			{
				v.should_copy = 0;
				break ;
			}
		}
		if (v.should_copy)
			new_environ[v.k++] = ft_strdup((g_shell)->env[v.i]);
	}
	new_environ[v.k] = NULL;
	return (0);
}

int	ft_unset(int idx)
{
	int		env_count;
	char	**new_environ;

	if (check_args_for_unset(idx))
		return (1);
	env_count = 0;
	while ((g_shell)->env[env_count])
		env_count++;
	new_environ = create_new_environ(env_count);
	if (!new_environ)
		return (1);
	if ((g_shell)->cmds[idx]->args[0] == NULL)
		return (1);
	copy_env_and_unset(idx, new_environ);
	free_array((g_shell)->env);
	(g_shell)->env = new_environ;
	return (0);
}
