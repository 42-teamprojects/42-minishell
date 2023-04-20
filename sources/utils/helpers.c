/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:28:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/20 22:16:43 by yelaissa         ###   ########.fr       */
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
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = (t_shell *) malloc(sizeof(t_shell));
	(*shell)->exit = 0;
	(*shell)->status_code = 0;
	(*shell)->env = dup_list(env);
	(*shell)->exp = NULL;
	(*shell)->old_out = -1;
	(*shell)->old_in = -1;
	(*shell)->path_list = ft_split(getenv("PATH"), ':');
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}

void	rollback_fd(t_shell **shell)
{
	if ((*shell)->old_in >= 0)
	{
		dup2((*shell)->old_in, STDIN_FILENO);
		(*shell)->old_in = -1;
	}
	if ((*shell)->old_out >= 0)
	{
		dup2((*shell)->old_out, STDOUT_FILENO);
		(*shell)->old_out = -1;
	}
	if ((*shell)->orig_stdout >= 0)
	{
		dup2((*shell)->orig_stdout, STDOUT_FILENO);
		close((*shell)->orig_stdout);
	}
	if ((*shell)->orig_stdin >= 0)
	{
		dup2((*shell)->orig_stdin, STDIN_FILENO);
		close((*shell)->orig_stdin);
	}
}

void	redirect(t_shell **shell)
{
	if (handle_redirection((*shell)->cmds[0]->redir, shell))
		console(1, "Failed to redirect output/input", NULL);
}