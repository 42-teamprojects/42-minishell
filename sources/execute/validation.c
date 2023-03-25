/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/25 14:55:17 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(t_shell *shell, char *str)
{
	char	**command;
	char	*path_command;
	char	**first_cmd;
	int		i;

	command = ft_split(shell->path, ':');
	first_cmd = ft_split(str, ' ');
	i = 0;
	while (command[i])
	{
		path_command = ft_strjoin(command[i], "/");
		path_command = ft_strjoin_gnl(path_command, first_cmd[0]);
		if (access(path_command, F_OK) == 0)
		{
			free(path_command);
			return (1);
		}
		free(path_command);
		i++;
	}
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
		first_cmd[0]);
	return (free_split(first_cmd), free_split(command), 0);
}
