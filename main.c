/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/19 00:06:11 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = (t_shell *) malloc(sizeof(t_shell));
	(*shell)->exit = 0;
	(*shell)->env = env;
	(*shell)->exp = NULL;
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
		return (free(input), stop(1, shell));
	if (!ft_strlen(input))
		return (free(input), stop(-3, shell));
	add_history(ft_strdup(input));
	(*shell)->lexer = lexer(input);
	print_lexer((*shell)->lexer);
	input = NULL;
	if (valid_syntax((*shell)->lexer))
	{
		commands = parse(shell);
		print_redir(commands[0]->redir);
		if (!commands || !commands[0])
			return (stop(-3, shell));
		(*shell)->cmds = commands;
	}
	else
		stop(-3, shell);
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
		if (shell->exit != 0 || shell->cmds[0]->path == NULL)
			continue ;
		if (ft_strcmp(shell->cmds[0]->path, "builtin"))
		{
			if (shell->cmds[0]->redir != NULL)
			{
				if (handle_redirection(shell->cmds[0]->redir))
				{
					console(1, "Failed to redirect output/input", NULL);
					continue ;
				}
			}
			ft_exec(&shell);
			free_exec(&shell);
		}
		else if (!ft_strcmp(shell->cmds[0]->path, "builtin"))
		{
			if (shell->cmds[0]->redir != NULL)
			{
				if (handle_redirection(shell->cmds[0]->redir))
				{
					console(1, "Failed to redirect output/input", NULL);
					continue ;
				}
			}
			ft_exec_builtin(&shell);
			free(shell->cmds[0]->name);
			shell->cmds[0]->name = NULL;
		}
		free(shell->prompt);
	}
	free_shell(&shell);
}