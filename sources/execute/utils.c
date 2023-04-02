/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/02 22:22:31 by htalhaou         ###   ########.fr       */
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
	int		i;
	char	**next;

	i = 0;
	if (shell == NULL || shell->env == NULL || shell->cmd.full_cmd == NULL)
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
				next++;
			}
			shell->env[i] = NULL;
			return (0);
		}
		shell->env[i]++;
	}
	return (0);
}

int	ft_setenv_help(const char *name, const char *value, t_shell *shell, int i)
{
	char	*input;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, shell->env, i * sizeof(char *));
	input = ft_strjoin(name, "=");
	input = ft_strjoin(input, value);
	new_environ[i] = input;
	new_environ[i + 1] = NULL;
	shell->env = new_environ;
	return (0);
}

int	ft_setenv(const char *name, const char *value, t_shell *shell)
{
	int		i;
	int		len;
	char	*input;

	i = -1;
	if (name == NULL || value == NULL)
		return (-1);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
				shell->overwrite = 1;
		else
				shell->overwrite = 0;
		if (shell->overwrite == 1)
		{
			input = ft_strjoin(name, "=");
			input = ft_strjoin(input, value);
			shell->env[i] = input;
			return (0);
		}
	}
	ft_setenv_help(name, value, shell, i);
	return (0);
}
