/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/09 00:09:33 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = (t_shell *) malloc(sizeof(t_shell));
	(*shell)->exit_status = 1;
	(*shell)->env = env;
	(*shell)->path = NULL;
	(*shell)->path_list = ft_split(getenv("PATH"), ':');
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}

void	read_input(t_shell **shell)
{
	char		*input;
	t_command	**commands;

	input = ft_strtrim(readline((*shell)->prompt), "\t ");
	if (!input || !ft_strcmp(input, "exit"))
		return (free(input), throw_err(0, shell));
	if (!ft_strlen(input))
		return (free(input));
	(*shell)->lexer = lexer(input);
	add_history(ft_strdup(input));
	free(input);
	input = NULL;
	if (valid_syntax((*shell)->lexer))
	{
		commands = parse(shell);
		if (!is_cmd_exist(commands, shell))
			(*shell)->exit_status = -1;
		else if ((*shell)->path == NULL)
			(*shell)->cmds = commands;
	}
	free_lexer((*shell)->lexer);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	init_shell(&shell, env);
	while (shell->exit_status)
	{
		shell->exit_status = 1;
		shell->prompt = init_prompt();
		read_input(&shell);
		if (shell->exit_status != 1)
			continue ;
		if (shell->path != NULL)
		{
			ft_exec(&shell);
			free_exec(&shell);
		}
		else if (shell->cmds[0]->name != NULL)
		{
			ft_exec_builtin(&shell);
			free(shell->cmds[0]->name);
			shell->cmds[0]->name = NULL;
		}
		free(shell->prompt);
	}
	free_shell(&shell);
}
