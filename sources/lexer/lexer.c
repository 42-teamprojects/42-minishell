/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:25:39 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/20 22:17:49 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *input, t_lexer **lexer, int i, t_state *state)
{
	if (is_token(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"' || input[i] == '\\')
			change_state(input[i], state);
		if (input[i] == '$')
		{
			if (is_token(input[i + 1]) || input[i + 1] == '=')
			{
				add_token(lexer, new_token(ft_strdup("$"), 1, WORD, *state));
				i++;
			}
			else
				i += get_var(lexer, input + i, *state);
		}
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
	t_lexer		*lexer;

	i = 0;
	state = DEFAULT;
	lexer = NULL;
	while (input[i])
	{
		i = tokenize(input, &lexer, i, &state);
	}
	return (lexer);
}
