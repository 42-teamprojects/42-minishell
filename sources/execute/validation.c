/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/25 15:23:20 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(t_shell *shell, char *str)
{
	char	**command;
	char	*path;
	char	**first_cmd;
	int		i;

	command = ft_split(shell->path, ':');
	first_cmd = ft_split(str, ' ');
	i = 0;
	while (command[i])
	{
		path = ft_strjoin(command[i], "/");
		path = ft_strjoin_gnl(path, first_cmd[0]);
		if (access(path, F_OK) == 0 || !ft_strcmp(path, "export") \
			|| !ft_strcmp(path, "unset"))
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
		first_cmd[0]);
	return (free_split(first_cmd), free_split(command), 0);
}
