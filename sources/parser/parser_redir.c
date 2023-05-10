/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:51 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/10 15:15:43 by htalhaou         ###   ########.fr       */
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
