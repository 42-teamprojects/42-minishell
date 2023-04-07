/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:29:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/07 18:30:33 by htalhaou         ###   ########.fr       */
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

int	ft_setenv_help(char *name, char *value, t_shell *shell, int i)
{
	char	*input;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, shell->env, i * sizeof(char *));
	input = ft_strjoin(name, "=");
	input = ft_strjoin_gnl(input, value);
	new_environ[i] = input;
	new_environ[i + 1] = NULL;
	shell->env = new_environ;
	return (0);
}

int	ft_setenv(char *name, char *value, t_shell *shell)
{
	int		i;
	int		len;
	char	*input;
	int		overwrite;

	i = -1;
	if (name == NULL || value == NULL)
		return (-1);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	overwrite = 0;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			overwrite = 1;
			break ;
		}
	}
	if (overwrite == 1)
	{
		input = ft_strjoin(name, "=");
		input = ft_strjoin_gnl(input, value);
		shell->env[i] = input;
	}
	else
		ft_setenv_help(name, value, shell, i);
	return (0);
}

// int	check_overwrite(char *name, t_shell *shell)
// {
// 	int	i;
// 	int	overwrite;

// 	overwrite = 0;
// 	i = -1;
// 	while (shell->env[++i])
// 	{
// 		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
// 			&& shell->env[i][ft_strlen(name)] == '=')
// 		{
// 			overwrite = 1;
// 			break ;
// 		}
// 	}
// 	return (overwrite);
// }

// void    ft_export_new(t_shell *shell, char *variable)
// {
// 	int        i;
// 	char    **var;
// 	char    **new_env;	
// 	var = ft_split(variable,'=');
// 	i = 0;
// 	while (shell->env[i])
// 	{
// 	    if(!ft_strncmp(shell->env[i],var[0],ft_strlen(var[0])) && shell->env[i][ft_strlen(var[0]) + 1] == '=')
// 	    {
// 	        free(shell->env[i]);
// 	        shell->env[i] = ft_strdup(variable);
// 	        return ;
// 	    }
// 	    i++;
// 	}
// 	new_env = malloc(sizeof(char) * i + 2);
// 	i = 0;
// 	while (shell->env[i])
// 	{
// 	    new_env[i] = ft_strdup(shell->env[i]);
// 	    free(shell->env[i]);
// 	    i++;
// 	}
// 	new_env[i] = ft_strdup(variable);
// 	i++;
// 	new_env[i] = NULL;
// }