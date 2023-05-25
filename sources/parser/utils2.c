/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:16:03 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/25 22:47:41 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(int fd, char *line, char *delimiter, int flag)
{
	char	*expanded_line;
	char	*tmp;

	while (1)
	{
		tmp = readline("heredoc> ");
		if (!tmp)
			break ;
		line = ft_strtrim(tmp, "\n");
		free(tmp);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!flag)
		{
			expanded_line = expand_variables_in_line(line);
			free(line);
			line = expanded_line;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
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

void	parse_logic(char ***command, int *i, t_lexer **tokens)
{
	if (is_word(*tokens))
		handle_word(*command, i, tokens, 1);
	if (is_quote(*tokens))
		handle_quote(*command, i, tokens, 1);
}

char	**allocate_command(t_lexer **tokens)
{
	char	**command;

	command = (char **)malloc(sizeof(char *) * (args_len(*tokens, PIPE) + 1));
	if (!command)
		return (NULL);
	return (command);
}

char	**sanitize_cmd(char **cmd)
{
	int		i;
	char	**split;
	char	**new;
	int		count;

	if (!cmd || (cmd && !cmd[0]))
		return (cmd);
	split = ft_split(cmd[0], ' ');
	count = args_count(split);
	if (count == 1)
		return (free_array(split), cmd);
	new = (char **)malloc(sizeof(char *) * (count + args_count(cmd)));
	if (!new)
		return (free_array(split), cmd);
	i = -1;
	while (split[++i])
		new[i] = ft_strdup(split[i]);
	free_array(split);
	i = 0;
	while (cmd[++i])
		new[i + count] = ft_strdup(cmd[i]);
	new[i + count] = NULL;
	// free_array(cmd);
	return (new);
}
