/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:57:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/25 14:55:17 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	throw_err(int err_code, char *variable, t_shell *shell)
{
	printf("\n");
	if (variable)
		free(variable);
	free_shell(shell);
	exit(err_code);
}

void	print404(char *cmd)
{
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
		cmd);
}