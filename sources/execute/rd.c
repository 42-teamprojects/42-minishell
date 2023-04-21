/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:59:32 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/21 03:06:45 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_file(char *file)
{
    if (access(file, F_OK) == -1)
    {
        perror(file);
        return 1;
    }

    if (access(file, R_OK) == -1)
    {
        console(1, file, "Permission denied");
        return 1;
    }

    if (access(file, X_OK) == 0)
    {
        console(1, file, "Is a directory");
        return 1;
    }

    return 0;
}


int	redirect_input(char *file, t_shell **shell)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (check_file(file));
	(*shell)->old_in = dup(STDIN_FILENO);
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
		return (check_file(file));
	(*shell)->old_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirection(t_rd *rd, t_shell **shell)
{
    int ret;

	(*shell)->orig_stdout = dup(STDOUT_FILENO);
    (*shell)->orig_stdin = dup(STDIN_FILENO);
	ret = 0 ;
    while (rd)
    {
        if (rd->type == RD_OUT || rd->type == RD_AOUT)
        {
            if (redirect_output(rd->file, shell, rd->type))
            {
                ret = 1;
                break ;
            }
        }
        else if (rd->type == RD_IN || rd->type == HEREDOC)
        {
            if (redirect_input(rd->file, shell))
            {
                ret = 1 ;
                break ;
            }
        }
        rd = rd->next;
    }
    if (ret)
        exit (0);
    return (0);
}

