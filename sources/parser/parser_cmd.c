/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:27:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/21 00:01:39 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_var_alone(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	**split;
	char	*expanded;

	expanded = ft_getenv(shell, (*tokens)->token->content + 1);
	if (expanded)
	{
		split = ft_split(expanded, ' ');
		while (split && *split)
			command[(*i)++] = ft_strdup(*split++);
		free_array(split);
		free(expanded);
	}
	return (NULL);
}

char	*handle_expanding(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	*expanded;

	if (((*tokens)->token->type == VAR && (*tokens)->token->content) \
		&& ((*tokens)->token->content[1] == '@' \
		|| (*tokens)->token->content[1] == '*' || \
		ft_isdigit((*tokens)->token->content[1])) \
		&& (*tokens)->token->len == 2)
		return (ft_strdup(""));
	if ((*tokens)->token->type == VAR && (*tokens)->token->state == DEFAULT
		&& is_var_alone(*tokens))
		return (handle_var_alone(command, i, tokens, shell));
	if ((*tokens)->token->type == VAR && (*tokens)->token->len > 1)
	{
		expanded = ft_strtrim_min(ft_getenv(shell, \
			(*tokens)->token->content + 1), " ");
		if (!expanded || ft_strlen(expanded) == 0)
			return (ft_strdup(""));
		return (expanded);
	}
	return (ft_strdup(""));
}

void	handle_word(char **command, int *i, t_lexer **tokens, t_shell **shell, int expand)
{
	char	*expanded;

	expanded = ft_strdup((*tokens)->token->content);
	if (expand && (*tokens)->token->type == VAR)
	{
		expanded = handle_expanding(command, i, tokens, shell);
		if (!expanded)
			return ;
	}
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			!is_redir((*tokens)->prev) && \
			(*tokens)->prev->token->type != PIPE)
		{
			command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			expanded);
			free(expanded);
		}
	else
		command[(*i)++] = expanded;
}

void	handle_quote(char **command, int *i, t_lexer **tokens, \
	t_shell **shell, int expand)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			!is_redir((*tokens)->prev) && \
			(*tokens)->prev->token->type != PIPE)
	{
			command[*i - 1] = ft_strjoin_gnl(command[*i - 1], 
				parse_quotes(tokens, shell, expand));
	}
	else
		command[(*i)++] = parse_quotes(tokens, shell, expand);
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
