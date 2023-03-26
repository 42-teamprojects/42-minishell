/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/26 13:34:34 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
			exec_input(command, first_cmd, path);
			return (0);
		}
		free(path);
		i++;
	}
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
	first_cmd[0]);
	return (free_split(first_cmd), free_split(command), 0);
}

int	exec_input(char **command, char **first_cmd, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(path, first_cmd, NULL) == -1)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		return (free_split(first_cmd), free_split(command), 0);
	}
	return (0);
}
