/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:35:29 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/20 16:14:49 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirect_output(char *file, t_shell **shell)
{
    int fd;
    
    fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0)
    {
        check_file(file);
        return (-1);
    }
    (*shell)->old_out = dup(STDOUT_FILENO);  // save the old stdout
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}


int redirect_input(char *file, t_shell **shell)
{
    int fd;
    
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        check_file(file);
        return (-1);
    }
    (*shell)->old_in = dup(STDIN_FILENO);  // save the old stdin
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int	append(char *file)
{
	int	fd;

    fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0)
    {
        check_file(file);
        return (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int	check_file(char *file)
{
    if (access(file, F_OK) == -1)
    {
        console(1, file, ": No such file or directory");
        return (1);
    }
    else if (access(file, R_OK) == -1)
    {
        console(1, file, ": Permission denied");
        return (1);
    }
    else if (access(file, X_OK) == 0)
    {
        console(1, file, ": Is a directory");
        return (1);
    }
    return (0);
}

int handle_redirection(t_rd *rd, t_shell **shell)
{
    (*shell)->orig_stdout = dup(STDOUT_FILENO); // store the original stdout
    (*shell)->orig_stdin = dup(STDIN_FILENO); // store the original stdin

    while (rd)
    {
        if (rd->type == RD_OUT)
        {
            if (redirect_output(rd->file, shell))
            {
                console(1, "Failed to redirect output", NULL);
                dup2((*shell)->orig_stdout, STDOUT_FILENO); // restore the original stdout
                close((*shell)->orig_stdout); // close the original stdout file descriptor
                return (1);
            }
        }
        else if (rd->type == RD_IN || rd->type == HEREDOC)
        {
            if (redirect_input(rd->file, shell))
            {
                console(1, "Failed to redirect input", NULL);
                dup2((*shell)->orig_stdin, STDIN_FILENO); // restore the original stdout
                close((*shell)->orig_stdin); // close the original stdout file descriptor
                return (1);
            }
        }
        else if (rd->type == RD_AOUT)
        {
            if (append(rd->file))
            {
                console(1, "Failed to append to file", NULL);
                dup2((*shell)->orig_stdout, STDOUT_FILENO); // restore the original stdout
                close((*shell)->orig_stdout); // close the original stdout file descriptor
                return (1);
            }
        }
        rd = rd->next;
    }
    return (0);
}
