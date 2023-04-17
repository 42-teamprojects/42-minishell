/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/17 00:03:10 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_shell **shell)
{
	free((*shell)->path);
	(*shell)->path = NULL;
	free_split((*shell)->full_cmd);
	(*shell)->full_cmd = NULL;
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
			return (1);
		free_split(var);
	}
	return (0);
}
