/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:21:51 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/08 23:58:46 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	is_redirection(char *str)
{
	if (*str == '>' && *(str + 1) == '>')
		return (RD_AOUT);
	if (*str == '<' && *(str + 1) == '<')
		return (HEREDOC);
	if (*str == '>')
		return (RD_OUT);
	if (*str == '<')
		return (RD_IN);
	return (0);
}

t_token_type	get_token_type(char *str)
{
	if (*str == ' ')
		return (WSPACE);
	else if (*str == '|')
		return (PIPE);
	else if (is_redirection(str))
		return (is_redirection(str));
	else if (*str == '"')
		return (DQUOTE);
	else if (*str == '\'')
		return (SQUOTE);
	else if (*str == '\\')
		return (ESCAPE);
	else if (*str == ' ')
		return (WSPACE);
	return (NEW_LINE);
}

int	get_token_length(char *str)
{
	if ((*str == '>' && *(str + 1) == '>') \
		|| (*str == '<' && *(str + 1) == '<'))
		return (2);
	return (1);
}

int	get_token(char *input, t_lexer *lexer, int i, t_state state)
{
	int	len;

	len = get_token_length(input + i);
	add_token(lexer, new_token(ft_substr(input, i, len), len, \
		get_token_type(input + i), state));
	return (len);
}
