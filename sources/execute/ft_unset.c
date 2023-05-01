/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:27:15 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/01 19:25:45 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell **shell, int idx)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	while ((*shell)->env[i])
		i++;
	new_environ = malloc((i + 1) * sizeof(char *));
	if (!new_environ)
		return (-1);
	if ((*shell)->cmds[idx]->args[0] == NULL)
		return (-1);
	i = -1;
	j = 0;
	while ((*shell)->env[++i])
	{
		if (ft_strncmp((*shell)->env[i], (*shell)->cmds[idx]->args[0],
				ft_strlen((*shell)->cmds[idx]->args[0])) == 0
			&& (*shell)->env[i][ft_strlen((*shell)->cmds[idx]->args[0])] == '=')
			continue ;
		new_environ[j++] = ft_strdup((*shell)->env[i]);
	}
	new_environ[j] = NULL;
	(*shell)->env = new_environ;
	return (0);
}
