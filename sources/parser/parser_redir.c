/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:51 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 16:33:26 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file(char *file, t_token_type type)
{
	int	fd;

	if (type == RD_OUT)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == RD_AOUT)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_RDONLY);
	close(fd);
}

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

char	**get_filename(t_lexer **tokens, t_shell **shell)
{
	char			**args;
	int				i;

	i = 0;
	args = (char **)malloc(sizeof(char *) * \
		(args_len(*tokens, shell, WSPACE) + 1));
	if (!args)
		return (NULL);
	while ((*tokens))
	{
		if (is_word(*tokens) && handle_word_redir(args, &i, tokens, shell))
			return (free_array(args), NULL);
		if (is_quote(*tokens))
			handle_quote(args, &i, tokens, shell, 1);
		if ((*tokens)->token->type == WSPACE || !(*tokens)->next)
			break ;
		(*tokens) = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}

int	handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell)
{
	char			**args;
	t_token_type	type;
	char			*file;

	type = (*tokens)->token->type;
	while ((*tokens)->token->type != WORD && (*tokens)->token->type != VAR && \
		(*tokens)->token->type != SQUOTE && (*tokens)->token->type != DQUOTE)
		*tokens = (*tokens)->next;
	if (type == HEREDOC)
		file = open_heredoc(tokens, shell);
	else
	{
		args = get_filename(tokens, shell);
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
