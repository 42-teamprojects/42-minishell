/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:49:37 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/08 16:51:33 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to create a new token
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

// Function to initialize a new lexer
t_lexer	*init_lexer(void)
{
	t_lexer	*lexer;

	lexer = (t_lexer *) malloc(sizeof(t_lexer));
	if (!lexer)
		return (0);
	lexer->head = NULL;
	lexer->size = 0;
	return (lexer);
}

// Function to add a new token to the end of the lexer
int	add_token(t_lexer *lexer, t_token *token)
{
	t_dll		*new_node;
	t_dll		*last_node;
	static int	i;

	new_node = (t_dll *) malloc(sizeof(t_dll));
	if (!new_node)
		return (0);
	new_node->token = token;
	new_node->idx = i;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (lexer->head == NULL)
	{
		lexer->head = new_node;
		lexer->size++;
		return (1);
	}
	last_node = lexer->head;
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
	new_node->prev = last_node;
	lexer->size++;
	i++;
	return (1);
}

// Function to free the lexer
void	free_lexer(t_lexer *lexer)
{
	t_dll	*node;
	t_dll	*temp;

	node = lexer->head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp->token->content);
		free(temp);
	}
	free(lexer);
}
