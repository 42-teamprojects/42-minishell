/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/25 14:57:55 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	read_input(t_shell *shell)
{
	char	*input;

	input = ft_strtrim(readline(shell->prompt), "\t ");
	if (!input || !ft_strncmp(input, "exit", 4))
		throw_err(0, input, shell);
	if (!ft_strlen(input))
		return (free(input));
	add_history(input);
	if (!verify_input(shell, input))
		return (free(input));
	shell->cmd = init_cmd(input);
	free(input);
	input = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void) ac;
	(void) av;
	shell.env = env;
	shell.path = getenv("PATH");
	shell.prompt = init_prompt();
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	while (1)
	{
		read_input(&shell);
	}
	free_shell(&shell);
}
