/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:28:22 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/08 23:28:49 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
