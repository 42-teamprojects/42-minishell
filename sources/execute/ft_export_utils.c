/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:22:00 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/01 19:28:41 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv_help(char *name, char *value, t_shell **shell, int i)
{
	char	*input;
	char	**new_environ;

	new_environ = malloc((i + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	ft_memcpy(new_environ, (*shell)->env, i * sizeof(char *));
	input = ft_concat(3, name, "=", value);
	new_environ[i] = input;
	new_environ[i + 1] = NULL;
	(*shell)->env = new_environ;
	return (0);
}

int	ft_setenv(char *name, char *value, t_shell **shell)
{
	int		i;
	char	*input;
	int		overwrite;

	i = -1;
	if (name == NULL || value == NULL)
		return (-1);
	overwrite = 0;
	while ((*shell)->env[++i])
	{
		if (ft_strncmp((*shell)->env[i], name, ft_strlen(name)) == 0
			&& (*shell)->env[i][ft_strlen(name)] == '=')
		{
			overwrite = 1;
			break ;
		}
	}
	if (overwrite == 1)
	{
		input = ft_concat(3, name, "=", value);
		(*shell)->env[i] = input;
	}
	else
		ft_setenv_help(name, value, shell, i);
	return (0);
}
