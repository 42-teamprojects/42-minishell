/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:25:39 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 12:07:12 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tilde(char *input, int i)
{
	if (input[i] == '~' && (!input[i + 1] \
	|| (input[i + 1] && (input[i + 1] == ' ' || input[i + 1] == '/'))) \
	&& (!input[i - 1] || (input[i - 1] && (input[i - 1] == ' '))))
		return (1);
	return (0);
}

void	get_tilde(t_lexer **lexer, t_state *state)
{
	char	*user;
	char	*result;

	user = ft_getenv("USER");
	result = ft_strjoin("/Users/", user);
	add_token(lexer, new_token(result, 1, WORD, *state));
	return (free(user));
}

int	tokenize(char *input, t_lexer **lexer, int i, t_state *state)
{
	if (is_tilde(input, i))
		return (get_tilde(lexer, state), (i + 1));
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
