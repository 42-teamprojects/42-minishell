/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:49:37 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/21 00:51:49 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *content, int len, t_token_type type, t_state state)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = content;
	new->len = len;
	new->type = type;
	new->state = state;
	return (new);
}

int	add_token(t_lexer **lexer, t_token *token)
{
	t_lexer		*new_node;
	t_lexer		*last_node;

	if (!lexer || !token)
		return (0);
	new_node = (t_lexer *) malloc(sizeof(t_lexer));
	if (!new_node)
		return (0);
	new_node->token = token;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!*lexer)
	{
		*lexer = new_node;
		return (1);
	}
	last_node = *lexer;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
	new_node->prev = last_node;
	return (1);
}

t_lexer	*get_last_node(t_lexer *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}
