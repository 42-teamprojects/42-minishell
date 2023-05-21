/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:49:50 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/21 20:24:16 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_near_quotes(t_lexer **tokens)
{
	t_lexer			*tmp;
	t_token_type	quote_type;

	quote_type = UNKNOWN;
	tmp = (*tokens)->next;
	if (tmp && is_quote(tmp))
		quote_type = tmp->token->type;
	while (tmp && is_quote(tmp) && is_token_type(tmp, quote_type, S_UNKNOWN))
			tmp = tmp->next;
	if ((!tmp) && (*tokens)->next && is_quote((*tokens)->next))
		return (1);
	tmp = (*tokens)->prev;
	if (tmp && is_quote(tmp))
		quote_type = tmp->token->type;
	while (tmp && !is_token_type(tmp, WSPACE, DEFAULT) && !is_redir(tmp) \
		&& is_quote(tmp) && is_token_type(tmp, quote_type, S_UNKNOWN))
			tmp = tmp->prev;
	if (tmp && (is_token_type(tmp, WSPACE, DEFAULT) || is_redir(tmp)) \
		&& is_quote((*tokens)->prev) && !(*tokens)->next)
		return (1);
	return (0);
}

int	all_space_ambiguous(t_lexer **tokens)
{
	if (check_near_quotes(tokens))
		return (1);
	if ((is_quote((*tokens)->prev) && \
		((*tokens)->next == NULL || !is_token_type((*tokens)->next, WSPACE, DEFAULT)))
		|| (is_quote((*tokens)->next) && \
		((*tokens)->prev == NULL || !is_token_type((*tokens)->prev, WSPACE, DEFAULT)))
		|| ((*tokens)->prev && \
		((*tokens)->next == NULL || is_token_type((*tokens)->next, WSPACE, DEFAULT))))
		return (0);
	return (-2);
}

int	space_right_quotes_ambiguous(t_lexer **tokens, t_shell **shell)
{
	t_lexer			*tmp;
	char			*str;
	t_token_type	quote_type;

	quote_type = UNKNOWN;
	tmp = (*tokens)->next;
	if (tmp && is_quote(tmp))
		quote_type = tmp->token->type;
	while (tmp && is_quote(tmp) && is_token_type(tmp, quote_type, S_UNKNOWN))
			tmp = tmp->next;
	if (tmp && tmp->token->type == WORD)
		return (1);
	if (tmp && is_quote(tmp->prev))
	{
		tmp = tmp->prev;
		str = parse_quotes(&tmp, shell, 1);
		if (str && ft_strlen(str) > 0)
			return (free(str), 1);
		free(str);
	}
	return (0);
}
int	space_right_ambiguous(t_lexer **tokens, t_shell **shell)
{
	char	*str;

	if (is_quote((*tokens)->next) && \
		space_right_quotes_ambiguous(tokens, shell))
			return (1);
	else if ((*tokens)->next->token->type == VAR)
	{
		str = ft_getenv(shell, (*tokens)->next->token->content + 1);
		if (str && ft_strlen(str) > 0 && !is_only_whitespace(str))
			return (free(str), 1);
		free(str);
	}
	return (0);
}

int	ambiguous_cases(t_lexer **tokens, t_shell **shell, char **command, int *i)
{
	char	*expanded;
	char	**split;

	expanded = ft_getenv(shell, (*tokens)->token->content + 1);
	if (is_only_whitespace(expanded))
		return (free(expanded), all_space_ambiguous(tokens));
	else if ((*expanded == ' ' && command[*i - 1] && \
	(!is_token_type((*tokens)->prev, WSPACE, DEFAULT)) && !is_redir((*tokens)->prev)) && \
	((is_quote((*tokens)->prev) \
	&& ft_strlen(command[*i - 1]) > 0 && is_only_whitespace(command[*i - 1]))
	|| (ft_strlen(command[*i - 1]) > 0 && !is_only_whitespace(command[*i - 1]))))
		return (free(expanded), 1);
	else if (expanded[ft_strlen(expanded) - 1] == ' ' && (*tokens)->next \
		&& space_right_ambiguous(tokens, shell))
		return (free(expanded), 1);
	split = ft_split(expanded, ' ');
	if (args_count(split) == 0 || args_count(split) > 1 || !ft_strlen(split[0]))
		return (free_array(split), 1);
	return (free_array(split), free(expanded), -2);
}

int	check_ambiguous(t_lexer **tokens, t_shell **shell, char **command, int *i)
{
	char	*expanded;

	if ((*tokens)->token->content && ((*tokens)->token->content[1] == '@' || \
	(*tokens)->token->content[1] == '*' || \
	ft_isdigit((*tokens)->token->content[1])) && (*tokens)->token->len == 2)
		return (-1);
	else
	{
		expanded = ft_getenv(shell, (*tokens)->token->content + 1);
		if (!expanded && is_var_alone(*tokens))
			return (free(expanded), 1);
		else if ((!expanded && !is_var_alone(*tokens)) \
			|| (expanded && !ft_strlen(expanded) && !is_var_alone(*tokens)))
			return (free(expanded), -1);
		return (free(expanded), ambiguous_cases(tokens, shell, command, i));
	}
}

int	handle_word_redir(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	*tmp;
	char	*expanded;

	expanded = NULL;
	if ((*tokens)->token->type == VAR)
	{
		if (check_ambiguous(tokens, shell, command, i) == 1)
			return (1);
		else if (check_ambiguous(tokens, shell, command, i) == 0)
			return (0);
		else if (check_ambiguous(tokens, shell, command, i) == -1)
			expanded = ft_strdup("");
		else
		{
			tmp = ft_getenv(shell, (*tokens)->token->content + 1);
			expanded = ft_strtrim(tmp, " ");
			free(tmp);
		}
	}
	else
		expanded = ft_strdup((*tokens)->token->content);
	update_command(tokens, command, i, expanded);
	return (0);
}
