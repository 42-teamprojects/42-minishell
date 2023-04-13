/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/13 21:12:35 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_cmd(char **command)
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(command[0]);
	cmd->argc = args_count(command) - 1;
	cmd->args = init_args(command);
	return (cmd);
}

char	**parse_cmds(t_dll **tokens, t_shell **shell)
{
	char	**command;
	int		i;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (args_len(*tokens) + 1));
	if (!command)
		return (NULL);
	while ((*tokens))
	{
		if ((*tokens)->token->type == WSPACE)
			(*tokens) = (*tokens)->next;
		if (is_word(tokens))
			handle_word(command, &i, tokens, shell);
		if (is_quote(tokens))
			handle_quote(command, &i, tokens, shell);
		if ((*tokens)->token->type == PIPE)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		(*tokens) = (*tokens)->next;
	}
	command[i] = NULL;
	return (command);
}

t_command	**parse(t_shell **shell)
{
	int			i;
	char		**cmd;
	t_dll		*tokens;
	t_command	**commands;

	(*shell)->cmds_count = cmds_len((*shell)->lexer->head);
	commands = (t_command **)malloc(sizeof(t_command *) \
		* ((*shell)->cmds_count + 1));
	if (!commands)
		return (NULL);
	i = -1;
	tokens = (*shell)->lexer->head;
	while (++i < (*shell)->cmds_count)
	{
		cmd = parse_cmds(&tokens, shell);
		if (!cmd)
			break ;
		commands[i] = init_cmd(cmd);
	}
	commands[i] = NULL;
	return (commands);
}
