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

void	start_heredoc(t_vars v)
{
	signal(SIGQUIT, SIG_DFL);
	write_heredoc(v.fd, v.line, v.args[0], v.flag);
	exit(0);
}

int	fork_hand(t_vars *v)
{
	v->pid = fork();
	if (v->pid == -1)
		return (free_array(v->args), console(1, "", strerror(errno)), 1);
	else if (v->pid == 0)
		start_heredoc(*v);
	else
	{
		g_shell->pid = v->pid;
		waitpid(v->pid, &v->status, 0);
		(g_shell)->status_code = WEXITSTATUS(v->status);
	}
	if (g_shell->openheredoc == 0)
		(g_shell)->status_code = 1;
	return (0);
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
	signal(SIGINT, &handler);
	if (fork_hand(&v))
		return (NULL);
	free_array(v.args);
	close(v.fd);
	signal(SIGINT, &sig_handler);
	return (ft_strdup("/tmp/.ms_heredoc"));
}
