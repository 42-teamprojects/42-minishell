/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   rd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yelaissa <yelaissa@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/21 02:59:32 by yelaissa		  #+#	#+#			 */
/*   Updated: 2023/04/25 08:07:52 by yelaissa		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *file, t_shell **shell)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (console(1, file, strerror(errno)), 1);
	(*shell)->fd.old_in = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_output(char *file, t_shell **shell, t_token_type type)
{
	int	fd;

	if (type == RD_OUT)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (console(1, file, strerror(errno)), 1);
	(*shell)->fd.old_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	dupping(t_shell **shell)
{
	dup2((*shell)->fd.orig_stdout, STDOUT_FILENO);
	dup2((*shell)->fd.orig_stdin, STDIN_FILENO);
}

int	handle_redirection(t_rd *rd, t_shell **shell)
{
	(*shell)->fd.orig_stdout = dup(STDOUT_FILENO);
	(*shell)->fd.orig_stdin = dup(STDIN_FILENO);
	while (rd)
	{
		if (rd->type == RD_OUT || rd->type == RD_AOUT)
		{
			if (redirect_output(rd->file, shell, rd->type))
				return (dupping(shell), 1);
		}
		else if (rd->type == RD_IN || rd->type == HEREDOC)
		{
			if (redirect_input(rd->file, shell))
				return (dupping(shell), 1);
		}
		rd = rd->next;
	}
	return (0);
}
