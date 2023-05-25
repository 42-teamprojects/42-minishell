/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:32:18 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/25 16:46:10 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args_for_unset(int idx)
{
	int	i;

	i = 0;
	while ((g_shell)->cmds[idx]->args[i])
	{
		if (!check_var_for_unset((g_shell)->cmds[idx]->args[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**create_new_environ(int env_count)
{
	char	**new_environ;

	new_environ = malloc((env_count + 1) * sizeof(char *));
	if (!new_environ)
		return (NULL);
	return (new_environ);
}
