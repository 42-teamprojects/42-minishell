/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/30 11:53:55 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern char	**environ;

void	free_exec(t_shell *shell)
{
	free(shell->path);
	shell->path = NULL;
	free_split(shell->cmd.full_cmd);
	shell->cmd.full_cmd = NULL;
}

int	unset_help(t_shell *shell)
{
	char	**envp;
	char	**next;

	envp = environ;
	while (*envp != NULL)
	{
		if (strncmp(*shell->cmd.full_cmd, *envp,
				strlen(*shell->cmd.full_cmd)) == 0
			&& (*envp)[strlen(*shell->cmd.full_cmd)] == '=')
		{
			next = envp + 1;
			while (*next != NULL)
			{
				*envp = *next;
				envp = next;
				next++;
			}
			*envp = NULL;
			return (0);
		}
		envp++;
	}
	return (0);
}
