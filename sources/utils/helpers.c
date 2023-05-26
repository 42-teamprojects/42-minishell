/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:28:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 17:28:32 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		(g_shell)->status_code = 1;
	}
}

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = (t_shell *) malloc(sizeof(t_shell));
	(*shell)->exit = 0;
	(*shell)->status_code = 0;
	(*shell)->env = dup_list(env);
	(*shell)->exp = NULL;
	(*shell)->fd.old_out = -1;
	(*shell)->fd.old_in = -1;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	rollback_fd(t_shell **shell)
{
	if ((*shell)->fd.old_in >= 0)
	{
		dup2((*shell)->fd.old_in, STDIN_FILENO);
		(*shell)->fd.old_in = -1;
	}
	if ((*shell)->fd.old_out >= 0)
	{
		dup2((*shell)->fd.old_out, STDOUT_FILENO);
		(*shell)->fd.old_out = -1;
	}
	if ((*shell)->fd.orig_stdout >= 0)
	{
		dup2((*shell)->fd.orig_stdout, STDOUT_FILENO);
		close((*shell)->fd.orig_stdout);
	}
	if ((*shell)->fd.orig_stdin >= 0)
	{
		dup2((*shell)->fd.orig_stdin, STDIN_FILENO);
		close((*shell)->fd.orig_stdin);
	}
}

void	update_command(t_lexer **tokens, char **command, int *i, char *expanded)
{
	if (!is_token_type((*tokens)->prev, WSPACE, DEFAULT) && command[*i - 1]
		&& !is_redir((*tokens)->prev) && (*tokens)->prev->token->type != PIPE)
	{
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			expanded);
		free(expanded);
	}
	else
		command[(*i)++] = expanded;
}
