/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:06:44 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/07 18:30:40 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_export(t_shell *shell)
{
	int		result;
	char	**var_name;

	if (shell->cmd.args[0] == NULL)
		return (-1);
	var_name = ft_split(shell->cmd.args[0], '=');
	if (var_name[1])
	{
		result = ft_setenv(var_name[0], var_name[1], shell);
		if (result == 0)
			printf("Exported %s=%s\n", var_name[0], var_name[1]);
		else
			printf("Failed to export %s=%s\n", var_name[0], var_name[1]);
	}
	return (0);
}

int	ft_unset(t_shell *shell)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	while (shell->env[i])
		i++;
	new_environ = malloc((i + 1) * sizeof(char *));
	if (!new_environ)
		return (-1);
	if (shell->cmd.args[0] == NULL)
		return (-1);
	i = -1;
	j = 0;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], shell->cmd.args[0],
				ft_strlen(shell->cmd.args[0])) == 0
			&& shell->env[i][ft_strlen(shell->cmd.args[0])] == '=')
			continue ;
		new_environ[j++] = ft_strdup(shell->env[i]);
	}
	new_environ[j] = NULL;
	shell->env = new_environ;
	return (0);
}
