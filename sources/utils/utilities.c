/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/10 20:34:46 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**dup_list(char **list)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (args_count(list) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (list[i])
	{
		args[i] = ft_strdup(list[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	delete_content(void *data)
{
	free(data);
}
