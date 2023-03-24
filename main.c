/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:48:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 21:51:59 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_shell *shell)
{
	char	*input;

	input = readline(shell->prompt);
	if (!input || !ft_strncmp(input, "exit", 4))
		exit(0);
	add_history(input);
	verify_input(input);
	shell->cmd = init_cmd(input);
	free(input);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void) ac;
	(void) av;
	shell.env = env;
	shell.path = getenv("PATH");
	shell.prompt = init_prompt();
	signal(SIGQUIT, &sig_handler);
	signal(SIGINT, &sig_handler);
	while (1)
	{
		read_input(&shell);
	}
	free(shell.prompt);
}
