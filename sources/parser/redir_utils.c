/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:49:50 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 12:56:38 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ambiguous_cases(t_lexer **tokens, char **command, int *i)
{
	char	*expanded;
	char	**split;

	expanded = ft_getenv((*tokens)->token->content + 1);
	if (is_only_whitespace(expanded))
		return (free(expanded), all_space_ambiguous(tokens));
	else if ((*expanded == ' ' && command[*i - 1] && \
	(!is_token_type((*tokens)->prev, WSPACE, DEFAULT)) && \
	!is_redir((*tokens)->prev)) && ((is_quote((*tokens)->prev) \
	&& ft_strlen(command[*i - 1]) > 0 && is_only_whitespace(command[*i - 1])) \
	|| (ft_strlen(command[*i - 1]) > 0 && \
	!is_only_whitespace(command[*i - 1]))))
		return (free(expanded), 1);
	else if (expanded[ft_strlen(expanded) - 1] == ' ' && (*tokens)->next \
		&& space_right_ambiguous(tokens))
		return (free(expanded), 1);
	split = ft_split(expanded, " \t");
	if (args_count(split) == 0 || args_count(split) > 1 || !ft_strlen(split[0]))
		return (free_array(split), free(expanded), 1);
	return (free_array(split), free(expanded), -2);
}

int	check_ambiguous(t_lexer **tokens, char **command, int *i)
{
	char	*expanded;

	if ((*tokens)->token->content && ((*tokens)->token->content[1] == '@' || \
	(*tokens)->token->content[1] == '*' || \
	ft_isdigit((*tokens)->token->content[1])) && (*tokens)->token->len == 2)
		return (-1);
	else
	{
		expanded = ft_getenv((*tokens)->token->content + 1);
		if (!expanded && is_var_alone(*tokens))
			return (free(expanded), 1);
		else if ((!expanded && !is_var_alone(*tokens)) \
			|| (expanded && !ft_strlen(expanded) && !is_var_alone(*tokens)))
			return (free(expanded), -1);
		return (free(expanded), ambiguous_cases(tokens, command, i));
	}
}

int	handle_word_redir(char **command, int *i, t_lexer **tokens)
{
	char	*tmp;
	char	*expanded;

	expanded = NULL;
	if ((*tokens)->token->type == VAR)
	{
		if (check_ambiguous(tokens, command, i) == 1)
			return (1);
		else if (check_ambiguous(tokens, command, i) == 0)
			return (0);
		else if (check_ambiguous(tokens, command, i) == -1)
			expanded = ft_strdup("");
		else
		{
			tmp = ft_getenv((*tokens)->token->content + 1);
			expanded = ft_strtrim(tmp, " ");
			free(tmp);
		}
	}
	else
		expanded = ft_strdup((*tokens)->token->content);
	update_command(tokens, command, i, expanded);
	return (0);
}
