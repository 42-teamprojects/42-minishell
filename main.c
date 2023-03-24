/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:48:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/23 23:33:26 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/** 
 * Parse the input
 * Validate
 * Excute 
*/
int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	char	*input;
	char	*user;
	char	cwd[1024];
	char	*line;
	char	*str;
	
	(void) ac;
	(void) av;
	shell.env = env;
	signal(SIGQUIT, &sig_handler);
	signal(SIGINT, &sig_handler);
	while (1)
	{
		user = ft_strjoin(YELLOW, getenv("USER"));
    	getcwd(cwd, 1024);
    	str = strrchr(cwd, '/') + 1;
    	if (str == NULL)
			exit (1);
    	line = ft_strjoin_gnl(user, BRED "@");
    	line = ft_strjoin_gnl(line, str);
    	line = ft_strjoin_gnl(line, " $ " CX);
    	input = readline(line);
    	free(line);
    	if (!input)
    	    exit(0);
	}
}
