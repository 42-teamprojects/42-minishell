/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:05 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/08 23:25:20 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_pipe(t_command *cmd, int i, int cmds_count)
{
    cmd->fd = (t_fd *)malloc(sizeof(t_fd) * cmds_count);
    if (!cmd->fd)
        return (-1);
    if (pipe(&cmd->fd[i].old_in) < 0)
        return (-1);
    if (pipe(&cmd->fd[i].old_out) < 0)
        return (-1);
    cmd->fd[i].orig_stdin = dup(STDIN_FILENO);
    cmd->fd[i].orig_stdout = dup(STDOUT_FILENO);
    return (0);
}

// int execute_pipeline(t_command *cmds, int cmd_count)
// {
// 	int		i;
//     int     j;
// 	pid_t	pid;
    
// 	i = 0;
// 	while (i < cmd_count)
// 	{
// 		if (create_pipe(&cmds[i], i, cmd_count))
//         {
//             perror("create_pipe");
//             return -1;
//         }
// 		i++;
// 	}
// 	i = 0;
// 	while (i < cmd_count)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			return (-1);
// 		}
// 		else if (pid == 0)
// 		{
// 			if (i == 0)
//                 dup2(cmds[i].fd->old_out[1], STDOUT_FILENO);
//             else if (i == cmd_count - 1)
//                 dup2(cmds[i-1].fd->old_in[0], STDIN_FILENO);
//             else
//             {
//                 dup2(cmds[i-1].fd->old_in[0], STDIN_FILENO);
//                 dup2(cmds[i].fd->old_out[1], STDOUT_FILENO);
//             }
//             j = 0;
//             while (j < cmd_count)
//             {
//                 if (j != i)
//                 {
//                     close(cmds[j].fd->old_in[0]);
//                     close(cmds[j].fd->old_in[1]);
//                     close(cmds[j].fd->old_out[0]);
//                     close(cmds[j].fd->old_out[1]);
//                 }
//                 j++;
//             }
//             if (execvp(cmds[i].args[0], cmds[i].args) < 0) {
//                 perror("execvp");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         i++;
//     }    
//     i = 0;
//     while (i < cmd_count)
//     {
//         close(cmds[i].fd->old_in[0]);
//         close(cmds[i].fd->old_in[1]);
//         close(cmds[i].fd->old_out[0]);
//         close(cmds[i].fd->old_out[1]);
//         i++;
//     }   
//     i = 0;
//     while (i < cmd_count)
//     {
//         wait(NULL);
//         i++;
//     }
//     return (0);
// }

