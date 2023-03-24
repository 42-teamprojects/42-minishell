/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:48:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 11:02:34 by yelaissa         ###   ########.fr       */
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
	
	(void) ac;
	(void) av;
	shell.env = env;
	signal(SIGQUIT, &sig_handler);
	signal(SIGINT, &sig_handler);
	shell.prompt = init_prompt();
	while (1)
	{
    	input = readline(shell.prompt);
    	if (!input)
    	    exit(0);
		add_history(input);
		free(input);
	}
	free(shell.prompt);
}
