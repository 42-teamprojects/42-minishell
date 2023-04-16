/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:26:32 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/16 22:53:38 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rd	*new_rd(char *file, t_token_type type)
{
	t_rd	*new_rd;

	new_rd = malloc(sizeof(t_rd));
	if (!new_rd)
		return (NULL);
	new_rd->file = file;
	new_rd->type = type;
	new_rd->next = NULL;
	return (new_rd);
}

void	rd_addfront(t_rd **rd, t_rd *new)
{
	new->next = *rd;
	*rd = new;
}

void	free_rd(t_rd **rd)
{
	t_rd	*tmp;

	tmp = *rd;
	while (tmp)
	{
		free(tmp->file);
		free(tmp);
		tmp = tmp->next;
	}
	free(*rd);
}

void	handle_redir(t_rd **rd, t_dll **tokens, t_shell **shell)
{
	t_token_type	type;
	char			*file;

	type = (*tokens)->token->type;
	while ((*tokens)->token->type != WORD && (*tokens)->token->type != VAR \
		&& (*tokens)->token->type != SQUOTE && (*tokens)->token->type != DQUOTE)
		*tokens = (*tokens)->next;
	if ((*tokens)->token->type == VAR && type != HEREDOC)
	{
		file = ft_getenv(shell, (*tokens)->token->content + 1);
		if (!file)
		{
			console(0, (*tokens)->token->content, "ambiguous redirect");
			return ;
		}
	}
	else if (is_quote(tokens))
		file = parse_quotes(tokens, shell);
	else
		file = ft_strdup((*tokens)->token->content);
	// if (type == HEREDOC)
	// 	return (parse_heredoc(rd, file, shell));
	rd_addfront(rd, new_rd(file, type));
}

void	print_rd(char *file, t_token_type type)
{
	printf("| %-10s | %-10s |\n", file,
	       type == RD_IN ? "RD_IN" :
	       type == RD_OUT ? "RD_OUT" :
	       type == HEREDOC ? "HEREDOC" :
	       type == RD_AOUT ? "RD_AOUT" :
	       "UNKNOWN");
}

void	print_redir(t_rd *rd)
{
	t_rd	*node;

	printf("+------------+------------+\n");
	printf("| FILE       | TYPE       |\n");
	printf("+------------+------------+\n");
	node = rd;
	while (node)
	{
		print_rd(node->file, node->type);
		node = node->next;
	}
	printf("+------------+------------+\n");
}