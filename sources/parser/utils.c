/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:05:59 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/17 17:32:08 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(t_lexer *tokens)
{
	return ((tokens->token->type == WORD || \
		tokens->token->type == VAR) \
		&& tokens->token->state == DEFAULT);
}

int	is_quote(t_lexer *tokens)
{
	return (tokens->token->type == DQUOTE \
		|| tokens->token->type == SQUOTE);
}

int	is_redir(t_lexer *tokens)
{
	return (tokens->token->type == RD_OUT \
		|| tokens->token->type == RD_IN \
		|| tokens->token->type == RD_AOUT \
		|| tokens->token->type == HEREDOC);
}

t_command	*init_cmd(char **command, t_rd *rd)
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(command[0]);
	cmd->argc = args_count(command) - 1;
	cmd->args = init_args(command);
	cmd->redir = rd;
	return (cmd);
}
