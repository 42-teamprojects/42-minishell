/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:18:39 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/04 13:41:22 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*check_quotes(t_lexer **tokens, t_shell **shell)
{
	t_token_type	type;

	type = (*tokens)->token->type;
	while (*tokens)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->token->type == type)
			break ;
	}
	if (!*tokens)
	{
		(*shell)->status_code = 2;
		console(1, "unexpected EOF while looking for matching", "");
	}
	return (*tokens);
}

int	check_pipe(t_lexer *tokens, t_shell **shell)
{
	t_lexer	*before_pipe;
	t_lexer	*after_pipe;

	before_pipe = tokens->prev;
	after_pipe = tokens->next;
	while (after_pipe && after_pipe->token->type == WSPACE)
		after_pipe = after_pipe->next;
	while (before_pipe && before_pipe->token->type == WSPACE)
		before_pipe = before_pipe->prev;
	if ((!before_pipe || !after_pipe) || (before_pipe->token->type != WORD
			&& after_pipe->token->type != WORD && !is_redir(after_pipe)))
		return (((*shell)->status_code = 2), \
			console(1, "syntax error near unexpected token", \
			"|"), 1);
	return (0);
}

int	check_redir(t_lexer *tokens, t_shell **shell)
{
	t_lexer			*after_rd;
	t_token_type	type;

	after_rd = tokens->next;
	type = tokens->token->type;
	while (after_rd && after_rd->token->type == WSPACE)
		after_rd = after_rd->next;
	if (!after_rd || (after_rd->token->type != WORD \
		&& after_rd->token->type != VAR && \
		after_rd->token->type != SQUOTE && after_rd->token->type != DQUOTE))
		return (((*shell)->status_code = 2), \
			console(1, "syntax error near unexpected token", \
						redir_type(type)), 1);
	return (0);
}

int	valid_syntax(t_shell **shell)
{
	t_lexer	*tmp;

	tmp = (*shell)->lexer;
	while (tmp)
	{
		if (is_quote(tmp) && !check_quotes(&tmp, shell))
			return (0);
		else if (is_redir(tmp) && check_redir(tmp, shell))
			return (0);
		else if (tmp->token->type == PIPE && check_pipe(tmp, shell))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
