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

typedef struct s_vars
{
	int		fd;
	int		i;
	int		flag;
	char	*line;
	char	**args;
	int		pid;
	int		status;
}				t_vars;

char	*tokens_to_str(t_lexer **tokens)
{
	char	*str;
	char	*tmp;
	t_lexer	*current;

	str = ft_strdup("");
	current = *tokens;
	while (current)
	{
		if (current->token->type == VAR)
			tmp = ft_getenv(current->token->content + 1);
		else
			tmp = ft_strdup(current->token->content);
		str = ft_strjoin_gnl(str, tmp);
		free(tmp);
		current = current->next;
	}
	return (str);
}

char	*expand_variables_in_line(char *line)
{
	char	*expanded_line;
	t_lexer	*tokens;

	tokens = lexer(line);
	expanded_line = tokens_to_str(&tokens);
	free_lexer(tokens);
	return (expanded_line);
}

char	**get_args(t_lexer **tokens, int *i, int *flag)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * \
		(args_len(*tokens, WSPACE) + 1));
	if (!args)
		return (NULL);
	while ((*tokens))
	{
		if (is_word(*tokens))
			handle_word(args, i, tokens, 0);
		if (is_quote(*tokens))
		{
			*flag = 1;
			handle_quote(args, i, tokens, 0);
		}
		if ((*tokens)->token->type == WSPACE || !(*tokens)->next)
			break ;
		(*tokens) = (*tokens)->next;
	}
	args[*i] = NULL;
	return (args);
}

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

char	*open_heredoc(t_lexer **tokens)
{
	t_vars	v;

	v.i = 0;
	v.flag = 0;
	v.args = get_args(tokens, &v.i, &v.flag);
	v.line = NULL;
	if (!v.args[0])
		return (NULL);
	v.fd = open("/tmp/.ms_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (v.fd < 0)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	v.pid = fork();
	if (v.pid == -1)
		return (free_array(v.args), console(1, "", strerror(errno)), NULL);
	else if (v.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		write_heredoc(v.fd, v.line, v.args[0], v.flag);
		exit(1);
	}
	else
		waitpid(v.pid, &v.status, 0);
	free_array(v.args);
	close(v.fd);
	signal(SIGINT, &sig_handler);
	return (ft_strdup("/tmp/.ms_heredoc"));
}
