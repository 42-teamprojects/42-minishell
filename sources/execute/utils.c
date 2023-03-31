/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/31 23:14:33 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// extern char	**environ;

void	free_exec(t_shell *shell)
{
	free(shell->path);
	shell->path = NULL;
	free_split(shell->cmd.full_cmd);
	shell->cmd.full_cmd = NULL;
}

// int	unset_help(t_shell *shell)
// {
// 	char	**envp;
// 	char	**next;

// 	envp = environ;
// 	while (*envp != NULL)
// 	{
// 		if (ft_strncmp(*shell->cmd.full_cmd, *envp,
// 				ft_strlen(*shell->cmd.full_cmd)) == 0
// 			&& (*envp)[ft_strlen(*shell->cmd.full_cmd)] == '=')
// 		{
// 			next = envp + 1;
// 			while (*next != NULL)
// 			{
// 				*envp = *next;
// 				envp = next;
// 				next++;
// 			}
// 			*envp = NULL;
// 			return (0);
// 		}
// 		envp++;
// 	}
// 	return (0);
// }

int	ft_setenv(const char *name, const char *value,
	int overwrite, t_shell *shell)
{
	int		i;
	int		len;
	char	*new_entry;
	char	**new_environ;

	i = 0;
	if (name == NULL || value == NULL)
		return (-1);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			if (!overwrite)
				return (0);
			new_entry = malloc(len);
			if (new_entry == NULL)
				return (-1);
			strcpy(new_entry, name);
			strcat(new_entry, "=");
			strcat(new_entry, value);
			free(shell->env[i]);
			shell->env[i] = new_entry;
			return (0);
		}
		i++;
	}
	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	memcpy(new_environ, shell->env, i * sizeof(char *));
	new_entry = malloc(len);
	if (new_entry == NULL)
	{
		free(new_environ);
		return (-1);
	}
	strcpy(new_entry, name);
	strcat(new_entry, "=");
	strcat(new_entry, value);
	new_environ[i] = new_entry;
	new_environ[i + 1] = NULL;
	shell->env = new_environ;
	return (0);
}
