/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:22:00 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 16:26:55 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv_help(char *name, char *value, int i)
{
	char	*input;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, (g_shell)->env, i * sizeof(char *));
	input = ft_concat(3, name, "=", value);
	new_environ[i] = ft_strdup(input);
	new_environ[i + 1] = NULL;
	free((g_shell)->env);
	(g_shell)->env = new_environ;
	free(input);
	return (0);
}

int	ft_setenv(char *name, char *value)
{
	int		i;
	char	*input;
	int		overwrite;

	i = -1;
	if (name == NULL || value == NULL)
		return (-1);
	overwrite = 0;
	while ((g_shell)->env[++i])
	{
		if (ft_strncmp((g_shell)->env[i], name, ft_strlen(name)) == 0
			&& (g_shell)->env[i][ft_strlen(name)] == '=')
		{
			overwrite = 1;
			break ;
		}
	}
	if (overwrite == 1)
	{
		input = ft_concat(3, name, "=", value);
		free((g_shell)->env[i]);
		(g_shell)->env[i] = input;
	}
	else
		ft_setenv_help(name, value, i);
	return (0);
}
