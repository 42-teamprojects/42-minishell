/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:11:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/27 19:56:20 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_quote_state	get_state(t_quote_state state, int no_quotes,
	int closed_single_quotes, int closed_double_quotes)
{
	if (no_quotes)
		return (NO_QUOTES);
	if (state == SINGLE_QUOTE)
		return (UNCLOSED_SINGLE_QUOTE);
	else if (state == DOUBLE_QUOTE)
		return (UNCLOSED_DOUBLE_QUOTE);
	else if (closed_single_quotes)
		return (CLOSED_SINGLE_QUOTES);
	else if (closed_double_quotes)
		return (CLOSED_DOUBLE_QUOTES);
	return (NO_QUOTE);
}

t_quote_state	get_quote_state(char c, t_quote_state current_state,
	int *closed_single_quotes, int *closed_double_quotes)
{
	if (c == '\'' && current_state != DOUBLE_QUOTE)
	{
		if (current_state == SINGLE_QUOTE)
		{
			*closed_single_quotes = 1;
			return (CLOSED_SINGLE_QUOTES);
		}
		*closed_single_quotes = 0;
		return (SINGLE_QUOTE);
	}
	else if (c == '"' && current_state != SINGLE_QUOTE)
	{
		if (current_state == DOUBLE_QUOTE)
		{
			*closed_double_quotes = 1;
			return (CLOSED_DOUBLE_QUOTES);
		}
		*closed_double_quotes = 0;
		return (DOUBLE_QUOTE);
	}
	return (current_state);
}

t_quote_state	valid_quotes(char *input)
{
	t_quote_state	state;
	int				closed_single_quotes;
	int				closed_double_quotes;
	int				no_quotes;

	state = NO_QUOTE;
	closed_single_quotes = 0;
	closed_double_quotes = 0;
	no_quotes = 1;
	while (*input)
	{
		if (*input == '\\' && (state == SINGLE_QUOTE || state == DOUBLE_QUOTE))
			input++;
		else
			state = get_quote_state(*input, state, &closed_single_quotes, \
				&closed_double_quotes);
		if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE)
			no_quotes = 0;
		input++;
	}
	return (get_state(state, no_quotes, \
		closed_single_quotes, closed_double_quotes));
}
