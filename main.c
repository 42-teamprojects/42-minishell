/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/26 17:37:46 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	read_input(t_shell *shell)
{
	char	*input;

	input = ft_strtrim(readline(shell->prompt), "\t ");
	if (!input || !ft_strcmp(input, "exit"))
		throw_err(0, input, shell);
	if (!ft_strlen(input))
		return (free(input));
	add_history(input);
	input = parse_input(input);
	if (!verify_input(shell, input))
		return (free(input));
	else if (shell->path == NULL)
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
	shell.prompt = init_prompt();
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	ft_bzero(&shell.cmd, sizeof(t_command));
	while (1)
	{
		read_input(&shell);
		if (shell.path != NULL)
		{
			ft_exec(&shell);
			shell.path = NULL;
			shell.cmd.full_cmd = NULL;
		}
		else if (shell.cmd.name != NULL)
		{
			ft_exec_builtin(&shell);
			shell.cmd.name = NULL;
		}
	}
	free_shell(&shell);
}
