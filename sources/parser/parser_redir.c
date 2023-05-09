/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:11:51 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/09 22:29:00 by yelaissa         ###   ########.fr       */
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

int validate_file_name(const char *file_name)
{
	if (file_name == NULL || *file_name == '\0')
		return (1);
	const char *invalid_chars = "/\\?%*:|\"<>";
	if (ft_strchr(invalid_chars, *file_name) != NULL || !ft_isprint(*file_name))
		return (1);
	size_t max_file_name_length = 255;
	if (strlen(file_name) > max_file_name_length)
		return (1);
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
		int	has_vars = var_count(*tokens, WSPACE);
		while ((*tokens))
		{
			if (is_word(*tokens))
				handle_word(args, &i, tokens, shell);
			if (is_quote(*tokens))
				handle_quote(args, &i, tokens, shell);
			if ((*tokens)->token->type == WSPACE || !(*tokens)->next)
				break ;
			(*tokens) = (*tokens)->next;
		}
		args[i] = NULL;
		if (!args[0])
		{
			return (1);
		}
		if (has_vars > 0)
		{
			char **split = ft_split(args[0], ' ');
			if ((split && split[0] && args_count(split) > 1) || ft_strchr(args[0], ' ') != NULL)
			{
				return (1);
			}
			free_array(split);
		}
		if (args_count(args) == 0 || args_count(args) > 1 || !args[0] || !ft_strlen(args[0]) || !ft_strcmp(args[0], "") ||
			validate_file_name(args[0]))
		{
			return (1);
		}
		file = ft_strdup(args[0]);
	}	
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
