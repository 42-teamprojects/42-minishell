/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:05:59 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/22 18:45:58 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_type(t_lexer *tokens, t_token_type type, t_state state)
{
	if (!tokens)
		return (0);
	if (state == S_UNKNOWN)
		return (tokens && tokens->token->type == type);
	return (tokens && tokens->token->type == type \
		&& tokens->token->state == state);
}

int	is_word(t_lexer *tokens)
{
	return (tokens && ((tokens->token->type == WORD \
			|| tokens->token->type == VAR) \
			&& tokens->token->state == DEFAULT));
}

int	is_quote(t_lexer *tokens)
{
	return (tokens && (tokens->token->type == DQUOTE \
		|| tokens->token->type == SQUOTE));
}

int	is_redir(t_lexer *tokens)
{
	return (tokens && (tokens->token->type == RD_OUT || \
		tokens->token->type == RD_IN || \
		tokens->token->type == RD_AOUT || \
		tokens->token->type == HEREDOC));
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
		if (cmd->argc >= 1)
			cmd->args = init_args(command);
		else
			cmd->args = NULL;
		cmd->full_cmd = command;
	}
	cmd->redir = rd;
	cmd->path = path;
	return (cmd);
}
