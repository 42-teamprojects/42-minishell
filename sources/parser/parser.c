/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/08 11:53:04 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

char	*parse_quotes(t_dll **tokens)
{
	t_token_type	type;
	char			*str_in_quotes;

	type = (*tokens)->token->type;
	(*tokens) = (*tokens)->next;
	str_in_quotes = ft_strdup("");
	while ((*tokens) && (*tokens)->token->type != type)
	{
		str_in_quotes = ft_strjoin_gnl(str_in_quotes, \
			(*tokens)->token->content);
		(*tokens) = (*tokens)->next;
	}
	return (str_in_quotes);
}

t_command	**parse(t_shell *shell)
{
	int			i;
	char		**cmd;
	t_dll		*tokens;
	t_command	**commands;
	int			commands_len;

	commands_len = cmds_len(shell->lexer->head);
	commands = (t_command **)malloc(sizeof(t_command *) \
		* (commands_len + 1));
	if (!commands)
		return (NULL);
	i = -1;
	tokens = shell->lexer->head;
	while (++i < commands_len)
	{
		cmd = parse_cmds(&tokens);
		if (!cmd)
			break ;
		commands[i] = init_cmd(cmd);
	}
	commands[i] = NULL;
	return (commands);
}
