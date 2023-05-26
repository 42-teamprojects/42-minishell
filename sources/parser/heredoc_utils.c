/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:48:51 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 17:50:22 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handler(int sig)
{
	int	fd;

	fd = 0;
	if (sig == SIGINT)
	{
		fd = open("/tmp/.ms_heredoc", O_WRONLY | O_TRUNC, 0644);
		close(fd);
		write(1, "\n", 1);
		(g_shell)->status_code = 1;
		(g_shell)->openheredoc = 0;
		if (g_shell->pid != 0)
			kill(g_shell->pid, SIGKILL);
	}
}
