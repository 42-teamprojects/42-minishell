/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:26:32 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/19 00:23:49 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("/tmp/.ms_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 0);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	return (ft_strdup("/tmp/.ms_heredoc"));
}

void	handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell)
{
	t_token_type	type;
	char			*file;

	type = (*tokens)->token->type;
	while ((*tokens)->token->type != WORD && (*tokens)->token->type != VAR \
		&& (*tokens)->token->type != SQUOTE && (*tokens)->token->type != DQUOTE)
		*tokens = (*tokens)->next;
	if ((*tokens)->token->type == VAR && type != HEREDOC)
	{
		file = ft_strtrim(ft_getenv(shell, (*tokens)->token->content + 1), \
				" \t\r\v\f");
		if (!file || ft_strlen(file) == 0)
			return (console(1, (*tokens)->token->content, "ambiguous redirect"),
				free_rd(rd), stop(-3, shell));
	}
	else if (is_quote(*tokens))
		file = parse_quotes(tokens, shell);
	else
		file = ft_strdup((*tokens)->token->content);
	if (type == HEREDOC)
		file = open_heredoc(file);
	rd_addfront(rd, new_rd(file, type));
}

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
