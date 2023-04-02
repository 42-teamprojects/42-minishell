/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:49:37 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/02 16:54:49 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Function to create a new token
t_data	*new_token(char *content, int len, t_token type, t_status status)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (0);
	new->content = content;
	new->len = len;
	new->type = type;
	new->status = status;
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
int	add_token(t_lexer *lexer, t_data *data)
{
	t_lst	*new_node;
	t_lst	*last_node;

	new_node = (t_lst *) malloc(sizeof(t_lst));
	if (!new_node)
		return (0);
	new_node->data = *data;
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
	return (1);
}

// Function to free the lexer
void	free_lexer(t_lexer *lexer)
{
	t_lst	*node;
	t_lst	*temp;

	node = lexer->head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp->data.content);
		free(temp);
	}
	free(lexer);
}
