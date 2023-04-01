/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/01 20:04:06 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_exec(t_shell *shell)
{
	free(shell->path);
	shell->path = NULL;
	free_split(shell->cmd.full_cmd);
	shell->cmd.full_cmd = NULL;
}

int	unset_help(t_shell *shell)
{
	int		i = 0;
	char	**next;

	if (shell == NULL || shell->env == NULL || shell->cmd.full_cmd == NULL
		|| shell->cmd.full_cmd[1] == NULL)
		return (-1);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->cmd.full_cmd[0], shell->env[i],
				ft_strlen(*shell->cmd.full_cmd)) == 0
			&& (shell->env[i])[ft_strlen(shell->cmd.full_cmd[0])] == '=')
		{
			next = &shell->env[i] + 1;
			while (*next != NULL)
			{
				shell->env[i] = *next;
				shell->env[i] = *next;
				next++;
			}
			shell->env[i] = NULL;
			return (0);
		}
		shell->env[i]++;
	}
	return (0);
}

// int	unset_help(t_shell *shell)
// {
//     int i = 0;
//     char **next;

//     while (shell->env[i])
//     {
//         if (ft_strncmp(shell->cmd.full_cmd[0], shell->env[i],
//                 ft_strlen(shell->cmd.full_cmd[0])) == 0
//             && shell->env[i][ft_strlen(shell->cmd.full_cmd[0])] == '=')
//         {
//             next = &shell->env[i];
//             while (*next != NULL)
//             {
//                 *next = *(next + 1);
//                 next++;
//             }
//             return (0);
//         }
//         i++;
//     }
//     return (0);
// }


int	ft_setenv_help(const char *name, const char *value, t_shell *shell, int i)
{
	char	*new_entry;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, shell->env, i * sizeof(char *));
	new_entry = ft_strjoin(name, "=");
	if (new_entry == NULL)
	{
		free(new_environ);
		return (-1);
	}
	new_entry = ft_strjoin(new_entry, value);
	if (new_entry == NULL)
	{
		free(new_environ);
		free(new_entry);
		return (-1);
	}
	new_environ[i] = new_entry;
	new_environ[i + 1] = NULL;
	shell->env = new_environ;
	return (0);
}

int	ft_setenv(const char *name, const char *value,
		int overwrite, t_shell *shell)
{
	int		i;
	int		len;
	char	*new_entry;

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
			new_entry = ft_strjoin(name, "=");
			if (new_entry == NULL)
				return (-1);
			new_entry = ft_strjoin(new_entry, value);
			if (new_entry == NULL)
			{
				free(new_entry);
				return (-1);
			}
			free(shell->env[i]);
			shell->env[i] = new_entry;
			return (0);
		}
		i++;
	}
	ft_setenv_help(name, value, shell, i);
	return (0);
}
