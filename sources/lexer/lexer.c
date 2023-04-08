/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:25:39 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/08 16:51:15 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *input, t_lexer *lexer, int i, t_state *state)
{
	if (is_token(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"' || input[i] == '\\')
			change_state(lexer, input[i], state);
		if (input[i] == '$')
			i += get_var(lexer, input + i, *state);
		else
			i += get_token(input, lexer, i, *state);
		return (i);
	}
	i += get_word(lexer, input + i, *state);
	return (i);
}

t_lexer	*lexer(char *input)
{
	int			i;
	t_state		state;
	t_lexer		*lex;

	i = 0;
	state = DEFAULT;
	lex = init_lexer();
	if (!lex)
		return (NULL);
	while (input[i])
	{
		i = tokenize(input, lex, i, &state);
	}
	free(input);
	return (lex);
}
