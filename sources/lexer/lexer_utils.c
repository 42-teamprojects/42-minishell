/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 09:49:08 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/14 23:43:03 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_isdigit(input[i]) || input[i] == '?')
		i++;
	else
	{
		while (!is_token(input[i]) && (ft_isalnum(input[i]) || input[i] == '_'))
			i++;
	}
	var = ft_substr(input, 0, i);
	add_token(lexer, new_token(var, i, VAR, state));
	return (i);
}

int	get_word(t_lexer *lexer, char *input, t_state state)
{
	size_t			i;
	char			*word;
	// t_dll			*last_token;
	// t_token_type	type;

	// last_token = get_last_node(lexer->head);
	i = 0;
	while (!is_token(input[i]))
	{
		// if (last_token && last_token->token->type == WSPACE)
		// {
		// 	last_token = last_token->prev;
		// 	continue ;
		// }
		i++;
	}
	word = ft_substr(input, 0, i);
	// type = last_token->token->type;
	// if (last_token && type == RD_OUT)
	// 	add_token(lexer, new_token(word, i, FILE_OUT, state));
	// else if (last_token && type == RD_IN)
	// 	add_token(lexer, new_token(word, i, FILE_IN, state));
	// else if (last_token && type == RD_AOUT)
	// 	add_token(lexer, new_token(word, i, FILE_APPEND, state));
	// else if (last_token && type == HEREDOC)
	// 	add_token(lexer, new_token(word, i, HEREDOC, state));
	// else
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
	       node->type == WSPACE ? "WSPACE" :
	       node->type == FILE_IN ? "FILE_IN" :
	       node->type == FILE_OUT ? "FILE_OUT" :
	       node->type == FILE_APPEND ? "FILE_APPEND" :
	       node->type == FILE_HEREDOC ? "FILE_HEREDOC" :
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