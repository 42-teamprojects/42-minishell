/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/07 23:14:12 by yelaissa         ###   ########.fr       */
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
	str_in_quotes = NULL;
	while ((*tokens))
	{
		if ((*tokens)->token->type == type)
			break ;
		str_in_quotes = ft_strjoin_gnl(str_in_quotes, \
			(*tokens)->token->content);
		(*tokens) = (*tokens)->next;
	}
	while ((*tokens)->next)
	{
		type = get_quote_type((*tokens)->next->token->state);
		if ((*tokens)->next->token->type == WSPACE && \
			(*tokens)->next->token->state == DEFAULT)
			break ;
		(*tokens) = (*tokens)->next;
		if ((*tokens) && (*tokens)->token->type != type)
			str_in_quotes = ft_strjoin_gnl(str_in_quotes, (*tokens)->token->content);
	}
	return (str_in_quotes);
}

char	**parse_cmds(t_dll **tokens)
{
	char		**command;
	int			i;

	i = 0;
	command = (char **) malloc(sizeof(char *) * (args_len(*tokens) + 1));
	if (!command)
		return (NULL);
	while ((*tokens))
	{
		if ((*tokens)->token->type == WSPACE)
			(*tokens) = (*tokens)->next;
		if ((*tokens)->token->type == WORD && (*tokens)->token->state == DEFAULT)
		{
			command[i] = ft_strdup((*tokens)->token->content);
			i++;
		}
		if ((*tokens)->token->type == DQUOTE || (*tokens)->token->type == SQUOTE)
		{
			if ((*tokens)->prev->token->type == WORD)
				command[i - 1] = ft_strjoin_gnl(command[i - 1], \
					parse_quotes(tokens));
			else
			{
				command[i] = parse_quotes(tokens);
				i++;
			}
		}
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
			break;
		commands[i] = init_cmd(cmd);
	}
	commands[i] = NULL;
	return (commands);
}
