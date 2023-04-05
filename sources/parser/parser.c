/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/05 14:46:37 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*init_cmd(char **command)
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	cmd->name = ft_strdup(command[0]);
	cmd->argc = args_count(command) - 1;
	cmd->args = init_args(command);
	free_split(command);
	return (cmd);
}

t_command	**parse_cmds(t_shell *shell)
{
	t_command	**commands;
	int			commands_len;
	int			i;

	commands_len = cmds_len(shell->lexer->head);
	commands = (t_command **) malloc(sizeof(t_command *) \
		* commands_len);
	i = -1;
	while (++i < commands_len)
	{
		commands[i] = parse_cmds(shell->lexer->head);
	}
	commands[i];
	return (commands);
}
