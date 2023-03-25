/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/25 20:10:11 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(t_shell *shell, char *str)
{
	char	**command;
	char	*path;
	char	**first_cmd;
	int		status;
	pid_t	pid;
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
			pid = fork();
			if (pid == -1)
			{
			  printf("%s\n", strerror(errno));
			  return (-1);
			}
			if (pid == 0)
			{
				if (execve(path, first_cmd, NULL) == -1)
				{
					printf("%s\n", strerror(errno));
					return (-1);
				}
			}
			else
			{
				waitpid(pid, &status, 0);
				return (0);
			}
		}
		free(path);
		i++;
	}
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
	first_cmd[0]);
	return (free_split(first_cmd), free_split(command), 0);
}
