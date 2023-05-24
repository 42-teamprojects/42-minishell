/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 16:38:37 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char	**values;
	char	*value;
	int		name_len;
	int		i;

	value = NULL;
	values = NULL;
	name_len = ft_strlen(name);
	if (name_len == 1 && name[0] == '?')
		return (ft_itoa((g_shell)->status_code));
	i = 0;
	while ((g_shell)->env[i])
	{
		if (ft_strncmp((g_shell)->env[i], name, name_len) == 0
			&& (g_shell)->env[i][name_len] == '=')
		{
			values = ft_split((g_shell)->env[i], '=');
			value = ft_strdup(values[1]);
			free_array(values);
			break ;
		}
		i++;
	}
	return (value);
}

void	ft_setexport(t_list **export, char *name)
{
	if (!*export)
	{
		ft_lstadd_front(export, ft_lstnew(name));
		return ;
	}
	remove_node(export, name, free);
	ft_lstadd_front(export, ft_lstnew(name));
}

int	ft_is_var_exist(char **env, char *key)
{
	int		i;
	char	**var;

	i = -1;
	while (env[++i])
	{
		var = ft_split(env[i], '=');
		if (!var)
			return (1);
		if (!ft_strcmp(key, var[0]))
		{
			free_array(var);
			return (1);
		}
		free_array(var);
	}
	return (0);
}

int	is_cmd_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "/usr/bin/cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
