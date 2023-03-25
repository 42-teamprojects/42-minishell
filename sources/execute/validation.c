/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/25 09:44:12 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	verify_input(char *str)
{
	t_shell	shell;
	char	**command;
	char	*path_command;
	char	**first_cmd;
	int		i;

	shell.path = getenv("PATH");
	command = ft_split(shell.path, ':');
	first_cmd = ft_split(str, ' ');
	i = 0;
	while (command[i])
	{
		path_command = ft_strjoin(command[i], "/");
		path_command = ft_strjoin(path_command, first_cmd[0]);
		if (access(path_command, F_OK) == 0)
		{
			free(path_command);
			return (1);
		}
		free(path_command);
		i++;
	}
	return (0);
}
