/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:51 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 17:34:26 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rd	*new_rd(char *file, t_token_type type)
{
	t_rd	*new_rd;

	new_rd = malloc(sizeof(t_rd));
	if (!new_rd)
		return (NULL);
	open_file(file, type);
	new_rd->file = file;
	new_rd->type = type;
	new_rd->next = NULL;
	return (new_rd);
}

void	rd_addback(t_rd **rd, t_rd *new)
{
	t_rd	*current;

	if (*rd == NULL)
	{
		*rd = new;
		return ;
	}
	current = *rd;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

int	get_redir_args(t_lexer **tokens, char ***args, int *i, int *flag)
{
	if (is_word(*tokens))
	{
		if (handle_word_redir(*args, i, tokens))
		{
			*flag = 1;
			return (1);
		}
	}
	if (is_quote(*tokens))
		handle_quote(*args, i, tokens, 1);
	return (0);
}

char	**get_filename(t_lexer **tokens)
{
	char	**args;
	int		i;
	int		flag;

	i = 0;
	args = (char **)malloc(sizeof(char *) * \
		(args_len(*tokens, WSPACE) + 1));
	if (!args)
		return (NULL);
	flag = 0;
	while ((*tokens))
	{
		if (get_redir_args(tokens, &args, &i, &flag))
			break ;
		if ((*tokens)->token->type == WSPACE || !(*tokens)->next)
			break ;
		(*tokens) = (*tokens)->next;
	}
	args[i] = NULL;
	if (flag)
		return (free_array(args), NULL);
	return (args);
}

int	handle_redir(t_rd **rd, t_lexer **tokens)
{
	char			**args;
	t_token_type	type;
	char			*file;

	(g_shell)->openheredoc = 1;
	type = (*tokens)->token->type;
	while ((*tokens)->token->type != WORD && (*tokens)->token->type != VAR && \
		(*tokens)->token->type != SQUOTE && (*tokens)->token->type != DQUOTE)
		*tokens = (*tokens)->next;
	if (type == HEREDOC)
		file = open_heredoc(tokens);
	else
	{
		args = get_filename(tokens);
		if (!args)
			return (1);
		if (args && !args[0])
			return (free_array(args), 1);
		file = ft_strdup(args[0]);
		free_array(args);
	}	
	rd_addback(rd, new_rd(file, type));
	return (0);
}
