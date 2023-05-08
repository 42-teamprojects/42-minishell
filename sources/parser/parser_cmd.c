/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:27:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/08 20:06:20 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_word(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	*expanded;
	int		has_var;

	has_var = 0;
	expanded = ft_strdup((*tokens)->token->content);
	if (((*tokens)->token->type == VAR && (*tokens)->token->content) \
		&& ((*tokens)->token->content[1] == '@' \
		|| (*tokens)->token->content[1] == '*' || \
		ft_isdigit((*tokens)->token->content[1])) \
		&& (*tokens)->token->len == 2)
	{
		has_var = 1;
		expanded = ft_strdup("");
	}
	else if ((*tokens)->token->type == VAR && (*tokens)->token->state == DEFAULT
		&& is_var_alone(*tokens))
	{
		has_var = 1;
		expanded = ft_getenv(shell, (*tokens)->token->content + 1);
		if (expanded)
		{
			char **split = ft_split(expanded, ' ');
			while (split && *split)
				command[(*i)++] = *split++;
			free(expanded);
		}
		return (has_var);
	}
	else if ((*tokens)->token->type == VAR && (*tokens)->token->len > 1)
	{
		has_var = 1;
		expanded = ft_strtrim_min(ft_getenv(shell, \
			(*tokens)->token->content + 1), " ");
		if (!expanded || ft_strlen(expanded) == 0)
			return (has_var);
	}
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			(*tokens)->prev->token->type != PIPE)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			expanded);
	else
		command[(*i)++] = expanded;
	return (has_var);
}

void	handle_quote(char **command, int *i, t_lexer **tokens, \
	t_shell **shell)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			(*tokens)->prev->token->type != PIPE)
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
