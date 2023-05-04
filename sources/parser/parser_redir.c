/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:26:32 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/04 22:49:03 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_heredoc(t_lexer **tokens, t_shell **shell)
{
	int		fd;
	int		flag;
	char	*line;
	char	*delimiter;

	flag = 0;
	if (is_quote(*tokens))
	{
		flag = 1;
		delimiter = parse_quotes(tokens, shell, 0);
	}
	else
		delimiter = ft_strdup((*tokens)->token->content);
	fd = open("/tmp/.ms_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 0);
		line = get_next_line(0);
		if (!line)
			break ;
		line = ft_strtrim(line, "\n");
		if (*line == '$' && !flag && ft_strcmp(line, delimiter) != 0)
			line = ft_getenv(shell, line + 1);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (ft_strdup("/tmp/.ms_heredoc"));
}

int	handle_redir(t_rd **rd, t_lexer **tokens, t_shell **shell)
{
	t_token_type	type;
	char			*file;
	int				quote_flag;

	quote_flag = 0;
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
				free_rd(*rd), stop(-3, shell), 1);
	}
	else if (is_quote(*tokens) && type != HEREDOC)
		file = parse_quotes(tokens, shell, 1);
	else if (type != HEREDOC)
		file = ft_strdup((*tokens)->token->content);
	else
		file = open_heredoc(tokens, shell);
	rd_addback(rd, new_rd(file, type));
	return (0);
}

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
