/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:05:59 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/20 16:12:30 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(t_lexer *tokens)
{
	return ((tokens->token->type == WORD ||
			 tokens->token->type == VAR) &&
			tokens->token->state == DEFAULT);
}

int	is_quote(t_lexer *tokens)
{
	return (tokens->token->type == DQUOTE \
		|| tokens->token->type == SQUOTE);
}

int	is_redir(t_lexer *tokens)
{
	return (tokens->token->type == RD_OUT || \
		tokens->token->type == RD_IN || \
		tokens->token->type == RD_AOUT || \
		tokens->token->type == HEREDOC);
}

t_command	*init_cmd(char **command, char *path, t_rd *rd)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (command && command[0])
	{
		cmd->name = ft_strdup(command[0]);
		cmd->argc = args_count(command) - 1;
		cmd->args = init_args(command);
		cmd->full_cmd = command;
	}
	if (rd)
		cmd->redir = rd;
	cmd->path = path;
	return (cmd);
}
