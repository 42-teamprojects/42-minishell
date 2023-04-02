/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:28:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/02 16:28:29 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_prompt(void)
{
	char	*user;
	char	cwd[PATH_MAX];
	char	*line;
	char	*str;

	user = ft_strjoin(BGREEN "→  " CYAN, getenv("USER"));
	getcwd(cwd, PATH_MAX);
	str = ft_strrchr(cwd, '/') + 1;
	if (str == 0)
		exit (1);
	line = ft_strjoin_gnl(user, " " BRED);
	line = ft_strjoin_gnl(line, str);
	line = ft_strjoin_gnl(line, YELLOW " $ " CX);
	return (line);
}

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

void	free_split(char **array)
{
	int	i;

	if (array[0])
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_shell(t_shell *shell)
{
	free(shell->prompt);
	if (shell->path != NULL)
		free(shell->path);
	free_split(shell->path_list);
}
