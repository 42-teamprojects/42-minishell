/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:53:46 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 12:13:27 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global.h"

char	*init_prompt()
{
	char	*user;
	char	cwd[1024];
	char	*line;
	char	*str;

	user = ft_strjoin(GREEN "→  " CYAN, getenv("USER"));
	getcwd(cwd, 1024);
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
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
