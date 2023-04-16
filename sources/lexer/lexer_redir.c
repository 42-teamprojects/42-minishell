/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:35:31 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/16 13:50:39 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir(t_lexer *lexer, char *input, t_state state)
{
	size_t	i;
	char	*redir;

	i = 1;
	if (input[i] == '>' || input[i] == '<')
		i++;
	redir = ft_substr(input, 0, i);
	add_token(lexer, new_token(redir, i, F_OUT, state));
	return (i);
}

t_token_type	get_redir_type(t_lexer *lexer)
{
	t_token_type	type;
	t_dll			*last_token;

	last_token = NULL;
	type = WORD;
	if (lexer->head)
	{
		last_token = get_last_node(lexer->head);
		type = last_token->token->type;
	}
	while (last_token && type == WSPACE)
	{
		last_token = last_token->prev;
		type = last_token->token->type;
	}
	if (last_token && type == RD_OUT)
		return (F_OUT);
	else if (last_token && type == RD_IN)
		return (F_IN);
	else if (last_token && type == RD_AOUT)
		return (F_APPEND);
	else if (last_token && type == HEREDOC)
		return (F_HEREDOC);
	else
		return (WORD);
}
