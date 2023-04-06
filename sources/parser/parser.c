/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/06 21:46:53 by yelaissa         ###   ########.fr       */
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
	cmd->args = NULL;
	free_split(command);
	return (cmd);
}

char	*parse_quotes(t_dll **tokens)
{
	t_token_type	type;
	char			*str_in_quotes;

	type = (*tokens)->token->type;
	(*tokens) = (*tokens)->next;
	str_in_quotes = NULL;
	while ((*tokens) && (*tokens)->token->type != type)
	{
		str_in_quotes = ft_strjoin_gnl(str_in_quotes, \
			(*tokens)->token->content);
		(*tokens) = (*tokens)->next;
	}
	return (str_in_quotes);
}

t_command	*parse_cmds(t_dll *tokens)
{
	t_dll		*tmp;
	char		**command;
	int			i;

	i = 0;
	command = (char **) malloc(sizeof(char *) * args_len(tokens) + 1);
	tmp = tokens;
	while (tmp && tmp->token->type != PIPE)
	{
		if (tmp->token->type == WORD && \
			(tmp->token->state != IN_DQUOTE || tmp->token->state != IN_SQUOTE))
		{
			command[i] = ft_strdup(tmp->token->content);
			i++;
		}
		if (tmp->token->type == SPACE)
			tmp = tmp->next;
		if (tmp->token->type == DQUOTE || tmp->token->type == SQUOTE)
		{
			command[i] = parse_quotes(&tmp);
			i++;
		}
		tmp = tmp->next;
	}
	return (init_cmd(command));
}

t_command	**parse(t_shell *shell)
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
		if (!parse_cmds(shell->lexer->head))
			break ;
		commands[i] = parse_cmds(shell->lexer->head);
	}
	commands[i] = NULL;
	return (commands);
}
