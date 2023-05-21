/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:31:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/21 21:39:36 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_near_quotes(t_lexer **tokens)
{
	t_lexer			*tmp;
	t_token_type	quote_type;

	quote_type = UNKNOWN;
	tmp = (*tokens)->next;
	if (tmp && is_quote(tmp))
		quote_type = tmp->token->type;
	while (tmp && is_quote(tmp) && is_token_type(tmp, quote_type, S_UNKNOWN))
			tmp = tmp->next;
	if ((!tmp) && (*tokens)->next && is_quote((*tokens)->next))
		return (1);
	tmp = (*tokens)->prev;
	if (tmp && is_quote(tmp))
		quote_type = tmp->token->type;
	while (tmp && !is_token_type(tmp, WSPACE, DEFAULT) && !is_redir(tmp) \
		&& is_quote(tmp) && is_token_type(tmp, quote_type, S_UNKNOWN))
			tmp = tmp->prev;
	if (tmp && (is_token_type(tmp, WSPACE, DEFAULT) || is_redir(tmp)) \
		&& is_quote((*tokens)->prev) && !(*tokens)->next)
		return (1);
	return (0);
}

int	all_space_ambiguous(t_lexer **tokens)
{
	if (check_near_quotes(tokens))
		return (1);
	if ((is_quote((*tokens)->prev) && \
		((*tokens)->next == NULL || \
		!is_token_type((*tokens)->next, WSPACE, DEFAULT)))
		|| (is_quote((*tokens)->next) && \
		((*tokens)->prev == NULL || \
		!is_token_type((*tokens)->prev, WSPACE, DEFAULT)))
		|| ((*tokens)->prev && \
		((*tokens)->next == NULL || \
		is_token_type((*tokens)->next, WSPACE, DEFAULT))))
		return (0);
	return (-2);
}

int	space_right_quotes_ambiguous(t_lexer **tokens, t_shell **shell)
{
	t_lexer			*tmp;
	char			*str;
	t_token_type	quote_type;

	quote_type = UNKNOWN;
	tmp = (*tokens)->next;
	if (tmp && is_quote(tmp))
		quote_type = tmp->token->type;
	while (tmp && is_quote(tmp) && is_token_type(tmp, quote_type, S_UNKNOWN))
			tmp = tmp->next;
	if (tmp && tmp->token->type == WORD)
		return (1);
	if (tmp && is_quote(tmp->prev))
	{
		tmp = tmp->prev;
		str = parse_quotes(&tmp, shell, 1);
		if (str && ft_strlen(str) > 0)
			return (free(str), 1);
		free(str);
	}
	return (0);
}

int	space_right_ambiguous(t_lexer **tokens, t_shell **shell)
{
	char	*str;

	if (is_quote((*tokens)->next) && \
		space_right_quotes_ambiguous(tokens, shell))
		return (1);
	else if ((*tokens)->next->token->type == VAR)
	{
		str = ft_getenv(shell, (*tokens)->next->token->content + 1);
		if (str && ft_strlen(str) > 0 && !is_only_whitespace(str))
			return (free(str), 1);
		free(str);
	}
	return (0);
}
