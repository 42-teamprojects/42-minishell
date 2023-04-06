/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:49:08 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/05 16:02:15 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_space(char c)
{
	if (ft_strchr(" \t\v\r\f\n", c) != NULL)
		return (1);
	return (0);
}

int	is_token(char c)
{
	if (is_space(c) || ft_strchr("\'\"<>|$\n\0", c) != NULL)
		return (1);
	return (0);
}

int	get_var(t_lexer *lexer, char *input, t_state state)
{
	size_t	i;
	char	*var;

	i = 1;
	while (!is_token(input[i]))
		i++;
	var = ft_substr(input, 0, i);
	add_token(lexer, new_token(var, i, VAR, state));
	return (i);
}

int	get_word(t_lexer *lexer, char *input, t_state state)
{
	size_t	i;
	char	*word;

	i = 0;
	while (!is_token(input[i]))
		i++;
	word = ft_substr(input, 0, i);
	add_token(lexer, new_token(word, i, WORD, state));
	return (i);
}

void	change_state(t_lexer *lexer, char c, t_state *state)
{
	(void) lexer;
	if (c == '\'')
	{
		if (*state == IN_SQUOTE)
			*state = DEFAULT;
		else if (*state != IN_DQUOTE && *state != ESCAPED)
			*state = IN_SQUOTE;
	}
	else if (c == '\"')
	{
		if (*state == IN_DQUOTE)
			*state = DEFAULT;
		else if (*state != IN_SQUOTE && *state != ESCAPED)
			*state = IN_DQUOTE;
	}
	else if (c == '\\')
	{
		if (*state != IN_SQUOTE && *state != ESCAPED)
			*state = ESCAPED;
		else if (*state == ESCAPED)
			*state = DEFAULT;
	}
}

void	print_node(t_token *node)
{
	printf("| %-10s | %-10d | %-10s | %-10s |\n", node->content, node->len, 
			node->state == IN_DQUOTE ? "IN_DQOUTE" :
			node->state == IN_SQUOTE ? "IN_SQUOTE" :
			node->state == ESCAPED ? "ESCAPED" :
			node->state == DEFAULT ? "DEFAULT" :
	       "UNKNOWN",
	       node->type == SQUOTE ? "SQUOTE" :
	       node->type == DQUOTE ? "DQUOTE" :
	       node->type == ESCAPE ? "ESCAPE" :
	       node->type == VAR ? "VAR" :
	       node->type == PIPE ? "PIPE" :
	       node->type == RD_IN ? "RD_IN" :
	       node->type == RD_OUT ? "RD_OUT" :
	       node->type == WORD ? "WORD" :
	       node->type == HEREDOC ? "HEREDOC" :
	       node->type == RD_AOUT ? "RD_AOUT" :
	       node->type == NEW_LINE ? "NEW_LINE" :
	       node->type == SPACE ? "SPACE" :
	       "UNKNOWN");
}

void	print_lexer(t_lexer *lexer)
{
	t_dll	*node;

	printf("+------------+------------+------------+------------+\n");
	printf("| CONTENT    | LENGTH     | STATE      | TYPE       |\n");
	printf("+------------+------------+------------+------------+\n");
	node = lexer->head;
	while (node)
	{
		print_node(node->token);
		node = node->next;
	}
	printf("+------------+------------+------------+------------+\n");
}