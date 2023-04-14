/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:27:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/14 22:07:47 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(t_dll **tokens)
{
	return (((*tokens)->token->type == WORD || \
		(*tokens)->token->type == VAR) \
		&& (*tokens)->token->state == DEFAULT);
}

int	is_quote(t_dll **tokens)
{
	return ((*tokens)->token->type == DQUOTE \
		|| (*tokens)->token->type == SQUOTE);
}

int	is_redir(t_dll **tokens)
{
	return ((*tokens)->token->type == RD_OUT \
		|| (*tokens)->token->type == RD_IN \
		|| (*tokens)->token->type == RD_AOUT \
		|| (*tokens)->token->type == HEREDOC);
}

void	handle_word(char **command, int *i, t_dll **tokens, t_shell **shell)
{
	char	*expanded;

	expanded = (*tokens)->token->content;
	if ((*tokens)->token->type == VAR && (*tokens)->token->len > 1)
	{
		expanded = ft_getenv(shell, (*tokens)->token->content + 1);
		if (!expanded)
			expanded = ft_strdup("");
	}
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			expanded);
	else
		command[(*i)++] = ft_strdup(expanded);
}

void	handle_quote(char **command, int *i, t_dll **tokens, \
	t_shell **shell)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			parse_quotes(tokens, shell));
	else
		command[(*i)++] = parse_quotes(tokens, shell);
}

char	*parse_quotes(t_dll **tokens, t_shell **shell)
{
	t_token_type	type;
	char			*str_in_quotes;
	char			*expanded;

	type = (*tokens)->token->type;
	(*tokens) = (*tokens)->next;
	str_in_quotes = ft_strdup("");
	while ((*tokens) && (*tokens)->token->type != type)
	{
		expanded = (*tokens)->token->content;
		if ((*tokens)->token->type == VAR && (*tokens)->token->len > 1 \
			&& (*tokens)->token->state == IN_DQUOTE)
		{
			expanded = ft_getenv(shell, (*tokens)->token->content + 1);
			if (!expanded)
				expanded = ft_strdup("");
		}
		str_in_quotes = ft_strjoin_gnl(str_in_quotes, \
			expanded);
		(*tokens) = (*tokens)->next;
	}
	return (str_in_quotes);
}
