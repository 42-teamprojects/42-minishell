/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:18:39 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/17 17:40:20 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*check_quotes(t_lexer **tokens)
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
		console(1, "syntax error", "unclosed quotes");
	return (*tokens);
}

int	check_redir(t_lexer *tokens)
{
	t_lexer			*next;
	t_token_type	type;

	next = tokens->next;
	type = tokens->token->type;
	while (next && next->token->type == WSPACE)
		next = next->next;
	if (!next || (next->token->type != WORD && next->token->type != VAR && \
		next->token->type != SQUOTE && next->token->type != DQUOTE))
		return (console(1, "syntax error near unexpected token", \
						redir_type(type)), 1);
	return (0);
}

int	valid_syntax(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (is_quote(tmp) && !check_quotes(&tmp))
			return (0);
		else if (is_redir(tmp) && check_redir(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
