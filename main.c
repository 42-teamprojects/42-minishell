/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/30 14:37:59 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->exit_status = 1;
	shell->env = env;
	shell->prompt = init_prompt();
	shell->path = NULL;
	shell->path_list = ft_split(getenv("PATH"), ':');
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	ft_bzero(&shell->cmd, sizeof(t_command));
}

void	read_input(t_shell *shell)
{
	char	*input;
	char	**command;

	input = ft_strtrim(readline(shell->prompt), "\t ");
	if (!input || !ft_strcmp(input, "exit"))
		return (free(input), throw_err(0, shell));
	if (!ft_strlen(input))
		return (free(input));
	add_history(input);
	command = parse_input(input);
	if (!verify_input(command, shell))
		return (free(input));
	else if (shell->path == NULL)
		shell->cmd = init_cmd(command);
	free(input);
	input = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void) ac;
	(void) av;
	init_shell(&shell, env);
	while (shell.exit_status)
	{
		read_input(&shell);
		if (shell.path != NULL)
		{
			ft_exec(&shell);
			free_exec(&shell);
		}
		else if (shell.cmd.name != NULL)
		{
			ft_exec_builtin(&shell);
			free(shell.cmd.name);
			shell.cmd.name = NULL;
		}
	}
	free_shell(&shell);
}
