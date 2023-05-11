/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:13:56 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/11 11:36:18 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_only_whitespace(char *str)
{
    while (*str)
    {
        if (!isspace(*str))
            return 0;
        str++;
    }
    return 1;
}

int is_valid_delimiter(t_token *token) {
    return token && (token->type == WSPACE || token->type == SQUOTE || token->type == DQUOTE || token->type == PIPE);
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
			if (!expanded && is_var_alone(*tokens))
			{
				return (1);
			}
			else
			{
				if (is_only_whitespace(expanded)) //space
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
				else if (*expanded == ' ' && ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE && !is_redir((*tokens)->prev))) //space left
				{
					if ((command[*i - 1] && ft_strlen(command[*i - 1]) > 0 && !is_only_whitespace(command[*i - 1])) && ((*tokens)->prev->token->state == DEFAULT))
					{
						return (1);
					}
				}
				else if (expanded[ft_strlen(expanded) - 1] == ' ' && (*tokens)->next) //space right
				{
					if (is_quote((*tokens)->next))
					{
						t_lexer *tmp = (*tokens)->next;
						char *str = parse_quotes(&tmp, shell, 1);
						if (str && ft_strlen(str) > 0)
							return (1);
						free(str);
					}
					else if ((*tokens)->next->token->type == VAR)
					{
						char *str = ft_getenv(shell, (*tokens)->next->token->content + 1);
						if (str && ft_strlen(str) > 0 && !is_only_whitespace(str))
							return (1);
					}
				}
				else if ((!expanded || ft_strlen(expanded) == 0)  && (!(*tokens)->next || !(*tokens)->prev))
				{
					return (1);
				}
				else
				{
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
