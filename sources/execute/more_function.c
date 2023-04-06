/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:06:44 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/06 22:49:23 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_shell *shell)
{
	if (unset_help(shell))
	{
		perror("unset");
		return (0);
	}
	printf("Environment variable '%s' has been unset.\n",
		shell->cmd.full_cmd[0]);
	return (1);
}

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
