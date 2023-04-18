/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:28:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/18 18:27:42 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		str = ft_strdup("minishell");
	line = ft_concat(4, user, " " BRED, str, YELLOW " $ " CX);
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
			array[i] = NULL;
			i++;
		}
	}
}

void	free_shell(t_shell **shell)
{
	free_split((*shell)->path_list);
}
