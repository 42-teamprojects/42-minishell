/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:49:50 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/11 22:12:43 by yelaissa         ###   ########.fr       */
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

int	handle_word_redir(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	*expanded;

	expanded = ft_strdup((*tokens)->token->content);
	if ((*tokens)->token->type == VAR)
	{
		if ((*tokens)->token->content && \
		((*tokens)->token->content[1] == '@' || \
		(*tokens)->token->content[1] == '*' || \
		ft_isdigit((*tokens)->token->content[1])) \
		&& (*tokens)->token->len == 2)
			expanded = ft_strdup("");
		else if ((*tokens)->token->state == DEFAULT)
		{
			expanded = ft_strtrim_min(ft_getenv(shell, \
				(*tokens)->token->content + 1), " ");
			if (!expanded)
			{
				if (is_var_alone(*tokens))
				{
					return (1);
				}
				else
					expanded = ft_strdup("");
			}
			else if (ft_strlen(expanded) == 0 && !is_var_alone(*tokens))
			{
				t_lexer *tmp = (*tokens)->next;
				while (tmp && is_quote(tmp))
						tmp = tmp->next;
				if (!tmp && (*tokens)->next && is_quote((*tokens)->next))
					expanded = ft_strdup("");
				t_lexer *tmp2 = (*tokens)->next;
				while (tmp2 && ((tmp2->token->type == WSPACE || is_redir(tmp2))  && tmp2->token->state == DEFAULT) && is_quote(tmp2))
						tmp2 = tmp2->prev;
				if (!tmp2 && (*tokens)->next && is_quote((*tokens)->next))
					expanded = ft_strdup("");
			}
			else
			{
				// ((tmp->token->type != WSPACE || !is_redir(tmp))  && tmp->token->state == DEFAULT)
				// || ((tmp->token->type == WSPACE || is_redir(tmp)))
				if (is_only_whitespace(expanded)) //space
				{
					t_lexer *tmp = (*tokens)->next;
					while (tmp && is_quote(tmp))
							tmp = tmp->next;
					if ((!tmp) && (*tokens)->next && is_quote((*tokens)->next))
						return (1);
					t_lexer *tmp2 = (*tokens)->prev;
					while (tmp2 && tmp2->token->type != WSPACE && is_quote(tmp2))
							tmp2 = tmp2->prev;
					if (tmp2 && tmp2->token->type == WSPACE && (*tokens)->prev && is_quote((*tokens)->prev) && !(*tokens)->next)
						return (1);
					// Check if the previous token is a quote and the next token is not whitespace or NULL
					if ((*tokens)->prev && is_quote((*tokens)->prev) && ((*tokens)->next == NULL || ((*tokens)->next->token->type != WSPACE && (*tokens)->next->token->state != DEFAULT)))
					{
						return (0);
					}

					// Check if the next token is a quote and the previous token is not whitespace or NULL
					if ((*tokens)->next && is_quote((*tokens)->next) && ((*tokens)->prev == NULL || ((*tokens)->prev->token->type != WSPACE && (*tokens)->prev->token->state != DEFAULT)))
					{
						
						return (0);
					}

					if ((*tokens)->prev && ((*tokens)->prev->token->type == SQUOTE || (*tokens)->prev->token->type == DQUOTE) && ((*tokens)->prev->prev && ((*tokens)->prev->prev->token->type == (*tokens)->prev->token->type)))
					{
						return (1);
					}

					if ((*tokens)->prev && ((*tokens)->next == NULL || ((*tokens)->next->token->type == WSPACE && (*tokens)->next->token->state == DEFAULT)))
						return (0);
					if (!(*tokens)->next && !(*tokens)->prev)
					{
						return (1);
					}
					if ((*tokens)->prev && ((*tokens)->prev->token->type == SQUOTE || (*tokens)->prev->token->type == DQUOTE) \
					&& ((*tokens)->prev->prev && ((*tokens)->prev->prev->token->type == (*tokens)->prev->token->type)))
					{
						return (1);
					}
					if ((*tokens)->prev && ((*tokens)->next == NULL || ((*tokens)->next->token->type == WSPACE && (*tokens)->next->token->state == DEFAULT)))
						return (0);
				}
				else if (*expanded == ' ' && ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && !is_redir((*tokens)->prev))) //space left
				{
					if (((*tokens)->prev->token->type == SQUOTE || (*tokens)->prev->token->type == DQUOTE) \
						&& command[*i - 1] && ft_strlen(command[*i - 1]) > 0 && is_only_whitespace(command[*i - 1]))
					{
						return (1);
					}
					else if ((command[*i - 1] && ft_strlen(command[*i - 1]) > 0 && !is_only_whitespace(command[*i - 1])))
					{
						return (1);
					}
				}
				else if (expanded[ft_strlen(expanded) - 1] == ' ' && (*tokens)->next) //space right
				{
					if (is_quote((*tokens)->next))
					{
						t_lexer *tmp = (*tokens)->next;
						while (tmp && is_quote(tmp))
							tmp = tmp->next;
						if (tmp && tmp->token->type == WORD)
							return (1);
						if (tmp && tmp->prev && is_quote(tmp->prev))
						{
							tmp = tmp->prev;
							char *str = parse_quotes(&tmp, shell, 1);
							if (tmp->next != NULL || (tmp->next && (tmp->next->token->type == WSPACE && tmp->next->token->state == DEFAULT)))
								return (1);
							if (str && ft_strlen(str) > 0)
								return (1);
							free(str);
						}
					}
					else if ((*tokens)->next->token->type == VAR)
					{
						char *str = ft_getenv(shell, (*tokens)->next->token->content + 1);
						if (str && ft_strlen(str) > 0 && !is_only_whitespace(str))
						{
							return (1);
						}
					}
				}
				else
				{
					char **split = ft_split(expanded, ' ');
					if (args_count(split) == 0 || args_count(split) > 1 || !split[0] || !ft_strlen(split[0]))
					{
						return (1);
					}
				}
			}
			expanded = ft_strtrim(expanded, " ");
		}
	}
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
		!is_redir((*tokens)->prev) && \
			(*tokens)->prev->token->type != PIPE)
		{
			if (command[*i - 1])
				command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
					expanded);
			else
				command[(*i)++] = expanded;
		}
	else
		command[(*i)++] = expanded;
	return (0);
}

int	handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell)
{
	char			**args;
	int				i;
	t_token_type	type;
	char			*file;

	type = (*tokens)->token->type;
	while ((*tokens)->token->type != WORD && (*tokens)->token->type != VAR &&
		   (*tokens)->token->type != SQUOTE && (*tokens)->token->type != DQUOTE)
		*tokens = (*tokens)->next;
	if (type == HEREDOC)
		file = open_heredoc(tokens, shell);
	else
	{
		i = 0;
		args = (char **)malloc(sizeof(char *) * (args_len(*tokens, shell, WSPACE) + 1));
		if (!args)
			return (1);
		while ((*tokens))
		{
			if (is_word(*tokens))
			{
				if (handle_word_redir(args, &i, tokens, shell))
					return (1);
			}
			
			if (is_quote(*tokens))
				handle_quote(args, &i, tokens, shell, 1);
			if ((*tokens)->token->type == WSPACE || !(*tokens)->next)
				break ;
			(*tokens) = (*tokens)->next;
		}
		args[i] = NULL;
		if (!args[0])
			return (1);
		file = ft_strdup(args[0]);
	}	
	rd_addback(rd, new_rd(file, type));
	return (0);
}
