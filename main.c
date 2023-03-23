/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:48:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/23 21:15:45 by yelaissa         ###   ########.fr       */
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
	(void) 	ac;
	(void) 	av;
	t_shell	shell;
	char	*input;

	shell.env = env;
	signal(SIGQUIT, &sig_handler);
	signal(SIGINT, &sig_handler);
	while (1)
	{
		input = readline(BRED"minishell $ "CX);
		if(!input)
			exit(0);
	}
}
