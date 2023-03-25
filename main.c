/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:48:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/25 09:59:12 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_shell *shell)
{
	char	*input;

	input = readline(shell->prompt);
	if (!input || !ft_strncmp(input, "exit", 4))
		throw_err(0);
	add_history(input);
	if (!verify_input(input))
	{
		return (free(input));
	}
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
