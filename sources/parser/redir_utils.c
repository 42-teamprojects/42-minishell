/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:13:56 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/10 22:54:32 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_redir(char **command, int *i, t_lexer **tokens, \
	t_shell **shell)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && \
			!is_redir((*tokens)->prev) && \
			(*tokens)->prev->token->type != PIPE)
	{
		char *tmp = parse_quotes(tokens, shell, 1);
		if (ft_strlen(tmp) > 0)
			command[*i - 1] = ft_strjoin_gnl(command[*i - 1], tmp);
	}
	else
		command[(*i)++] = parse_quotes(tokens, shell, 1);
}

int	handle_word_redir(char **command, int *i, t_lexer **tokens, t_shell **shell)
{
	char	*expanded;

	expanded = ft_strdup((*tokens)->token->content);
	if ((*tokens)->token->type == VAR)
	{
		//  && is_var_alone(*tokens)
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
				// printf("here 1\n");
				return (1);
			}
			else
			{
				if (ft_strlen(ft_strtrim(expanded, " ")) == 0) //space
				{
					if (!(*tokens)->next && !(*tokens)->prev)
						return (1);
					if ((*tokens)->prev && ((*tokens)->prev->token->type == SQUOTE || (*tokens)->prev->token->type == DQUOTE) \
					&& ((*tokens)->prev->prev && ((*tokens)->prev->prev->token->type == (*tokens)->prev->token->type)))
						return (1);
					if ((*tokens)->next && ((*tokens)->next->token->type == SQUOTE || (*tokens)->next->token->type == DQUOTE) \
					&& ((*tokens)->next->next && ((*tokens)->next->next->token->type == (*tokens)->next->token->type)))
						return (1);
					if ((*tokens)->prev && ((*tokens)->next == NULL || ((*tokens)->next->token->type == WSPACE && (*tokens)->next->token->state == DEFAULT)))
						return (0);
				}
				else if (*expanded == ' ') //space left
				{
					if (((*tokens)->prev->token->type == SQUOTE || (*tokens)->prev->token->type == DQUOTE) \
					&& ((*tokens)->prev->prev && ((*tokens)->prev->prev->token->type == (*tokens)->prev->token->type)))
					{
						// printf("hna\n");
						return (0);
					}
					if ((*tokens)->prev && ((*tokens)->prev->token->type != WSPACE && (*tokens)->prev->token->state == DEFAULT))
					{
						// printf("hna2\n");
						return (1);
					}
				}
				else if (expanded[ft_strlen(expanded) - 1] == ' ' && (*tokens)->next) //space right
				{
					// printf("dlkha\n");
					// if ((*tokens)->next->next && ((*tokens)->next->next->token->type == WSPACE && (*tokens)->next->next->token->state == DEFAULT))
						return (1);
				}
				else if ((!expanded || ft_strlen(expanded) == 0)  && (!(*tokens)->next || !(*tokens)->prev))
				{
					// printf("here 6\n");
					return (1);
				}
				else
				{
					// printf("%s\n", expanded);
					char **split = ft_split(expanded, ' ');
					if (args_count(split) == 0 || args_count(split) > 1 || !split[0] || !ft_strlen(split[0]))
					{
						// printf("here 7\n");
						return (1);
					}
				}
			}
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
	t_lexer			*tmp;

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
		tmp = *tokens;
		while ((*tokens))
		{
			if (is_word(*tokens))
			{
				if (handle_word_redir(args, &i, tokens, shell))
					return (1);
			}
			
			if (is_quote(*tokens))
				handle_quote_redir(args, &i, tokens, shell);
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