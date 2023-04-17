/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/17 22:22:20 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = (t_shell *) malloc(sizeof(t_shell));
	(*shell)->exit = 0;
	(*shell)->env = env;
	(*shell)->exp = NULL;
	(*shell)->path = NULL;
	(*shell)->path_list = ft_split(getenv("PATH"), ':');
	// (*shell)->files[0] = "test.txt";
	// (*shell)->files[1] = "test1.txt";
	// (*shell)->files[2] = "\0";
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}

void	read_input(t_shell **shell)
{
	char		*input;
	t_command	**commands;

	input = ft_strtrim(readline((*shell)->prompt), "\t ");
	if (!input || !ft_strcmp(input, "exit"))
		return (free(input), throw_err(1, shell));
	if (!ft_strlen(input))
		return (free(input), throw_err(-3, shell));
	add_history(ft_strdup(input));
	(*shell)->lexer = lexer(input);
	print_lexer((*shell)->lexer);
	input = NULL;
	if (valid_syntax((*shell)->lexer))
	{
		commands = parse(shell);
		if (!commands || !commands[0])
			return (throw_err(-3, shell));
		print_redir(commands[0]->redir);
		if (!is_cmd_exist(commands, shell))
			(*shell)->exit = -1;
		else if ((*shell)->path == NULL)
			(*shell)->cmds = commands;
	}
	else
		throw_err(-3, shell);
	free_lexer((*shell)->lexer);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	init_shell(&shell, env);
	while (shell->exit != 1)
	{
		shell->exit = 0;
		shell->prompt = init_prompt();
		read_input(&shell);
		if (shell->exit != 0)
			continue ;
		if (shell->path != NULL)
		{
			// if (shell->cmds[0]->redir->output)
			// 	rediterct_output(&shell);
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