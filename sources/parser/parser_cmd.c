/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:27:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/05 20:51:35 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_word(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	*expanded;

	expanded = ft_strdup((*tokens)->token->content);
	if ((*tokens)->token->type == VAR && (*tokens)->token->len > 1)
	{
		expanded = ft_getenv(shell, (*tokens)->token->content + 1);
	}
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			(*tokens)->prev->token->type != PIPE)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			expanded);
	else
		command[(*i)++] = expanded;
}

void	handle_quote(char **command, int *i, t_lexer **tokens, \
	t_shell **shell)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			(*tokens)->prev->token->type != PIPE \
			&& (*tokens)->prev->token->type != VAR)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			parse_quotes(tokens, shell, 1));
	else
		command[(*i)++] = parse_quotes(tokens, shell, 1);
}

char	*parse_quotes(t_lexer **tokens, t_shell **shell, int expand)
{
	t_token_type	type;
	char			*str_in_quotes;
	char			*expanded;

	type = (*tokens)->token->type;
	(*tokens) = (*tokens)->next;
	str_in_quotes = ft_strdup("");
	while ((*tokens) && (*tokens)->token->type != type)
	{
		expanded = ft_strdup((*tokens)->token->content);
		if ((*tokens)->token->type == VAR && (*tokens)->token->len > 1 \
			&& (*tokens)->token->state == IN_DQUOTE && expand)
		{
			expanded = ft_getenv(shell, (*tokens)->token->content + 1);
			if (!expanded)
				expanded = ft_strdup("");
		}
		str_in_quotes = ft_strjoin_gnl(str_in_quotes, \
			expanded);
		(*tokens) = (*tokens)->next;
		free(expanded);
	}
	return (str_in_quotes);
}
