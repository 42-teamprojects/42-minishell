/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/07 23:15:35 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->exit_status = 1;
	shell->env = env;
	shell->path = NULL;
	shell->path_list = ft_split(getenv("PATH"), ':');
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}

void	read_input(t_shell *shell)
{
	char		*input;
	t_command	**commands;

	input = ft_strtrim(readline(shell->prompt), "\t ");
	if (!input || !ft_strcmp(input, "exit"))
		return (free(input), throw_err(0, shell));
	if (!ft_strlen(input))
		return (free(input));
	shell->lexer = lexer(input);
	add_history(input);
	if (valid_syntax(shell->lexer))
	{
		print_lexer(shell->lexer);
		commands = parse(shell);
		for (int i = 0; commands[i]; i++)
		{
			printf("commands[%d] = %s\n", i, commands[i]->name);
			for (int j = 0; commands[i]->args[j]; j++)
				printf("commands[%d]->args[%d] = %s\n", i, j, commands[i]->args[j]);
		}
		free_lexer(shell->lexer);
		// if (!verify_input(command, shell))
			// return (free(input));
		// else if (shell->path == NULL)
		// 	shell->cmd = init_cmd(command);
		// input = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void) ac;
	(void) av;
	init_shell(&shell, env);
	while (shell.exit_status)
	{
		shell.prompt = init_prompt();
		read_input(&shell);
		// if (shell.path != NULL)
		// {
		// 	ft_exec(&shell);
		// 	free_exec(&shell);
		// }
		// else if (shell.cmd->name != NULL)
		// {
		// 	ft_exec_builtin(&shell);
		// 	free(shell.cmd->name);
		// 	shell.cmd->name = NULL;
		// }
		// free(shell.prompt);
	}
	free_shell(&shell);
}
