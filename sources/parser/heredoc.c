/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   heredoc.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yelaissa <yelaissa@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/11 16:37:54 by yelaissa		  #+#	#+#			 */
/*   Updated: 2023/05/11 16:38:05 by yelaissa		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

char	*tokens_to_str(t_shell **shell, t_lexer **tokens)
{
	char	*str;
	char	*tmp;
	t_lexer	*current;

	str = ft_strdup("");
	current = *tokens;
	while (current)
	{
		if (current->token->type == VAR)
			tmp = ft_getenv(shell, current->token->content + 1);
		else
			tmp = ft_strdup(current->token->content);
		str = ft_strjoin_gnl(str, tmp);
		free(tmp);
		current = current->next;
	}
	return (str);
}

char	*expand_variables_in_line(char *line, t_shell **shell)
{
	char	*expanded_line;
	t_lexer	*tokens;

	tokens = lexer(line);
	expanded_line = tokens_to_str(shell, &tokens);
	free_lexer(tokens);
	return (expanded_line);
}

char	**get_args(t_lexer **tokens, t_shell **shell, int *i, int *flag)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * \
		(args_len(*tokens, shell, WSPACE) + 1));
	if (!args)
		return (NULL);
	while ((*tokens))
	{
		if (is_word(*tokens))
			handle_word(args, i, tokens, shell, 0);
		if (is_quote(*tokens))
		{
			*flag = 1;
			handle_quote(args, i, tokens, shell, 0);
		}
		if ((*tokens)->token->type == WSPACE || !(*tokens)->next)
			break ;
		(*tokens) = (*tokens)->next;
	}
	args[*i] = NULL;
	return (args);
}

void	write_heredoc(int fd, char *line, char *delimiter, \
	t_shell **shell, int flag)
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
			expanded_line = expand_variables_in_line(line, shell);
			free(line);
			line = expanded_line;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*open_heredoc(t_lexer **tokens, t_shell **shell)
{
	int		fd;
	int		i;
	int		flag;
	char	*line;
	char	**args;

	i = 0;
	flag = 0;
	args = get_args(tokens, shell, &i, &flag);
	line = NULL;
	if (!args[0])
		return (NULL);
	fd = open("/tmp/.ms_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (NULL);
	write_heredoc(fd, line, args[0], shell, flag);
	free_array(args);
	close(fd);
	return (ft_strdup("/tmp/.ms_heredoc"));
}
