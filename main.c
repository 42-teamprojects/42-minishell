/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/19 00:33:39 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = (t_shell *) malloc(sizeof(t_shell));
	(*shell)->exit = 0;
	(*shell)->env = env;
	(*shell)->exp = NULL;
	(*shell)->old_out = -1;
	(*shell)->old_in = -1;
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
	input = NULL;
	if (valid_syntax((*shell)->lexer))
	{
		commands = parse(shell);
		if (!commands || !commands[0])
			return (stop(-3, shell));
		(*shell)->cmds = commands;
		print_lexer((*shell)->lexer);
		print_commands(commands);
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
				if (handle_redirection(shell->cmds[0]->redir, &shell))
				{
					console(1, "Failed to redirect output/input", NULL);
					continue ;
				}
			}
			ft_exec(&shell);
			free_exec(&shell);
			if ((shell)->old_in >= 0)
			{
				dup2((shell)->old_in, STDIN_FILENO);  // restore the old stdin
        		(shell)->old_in = -1;
    		}
    		if ((shell)->old_out >= 0)
    		{
        		dup2((shell)->old_out, STDOUT_FILENO);  // restore the old stdout
        		(shell)->old_out = -1;
    		}
		}
		else if (!ft_strcmp(shell->cmds[0]->path, "builtin"))
		{
			if (shell->cmds[0]->redir != NULL)
			{
				if (handle_redirection(shell->cmds[0]->redir, &shell))
				{
					console(1, "Failed to redirect output/input", NULL);
					continue ;
				}
			}
			ft_exec_builtin(&shell);
			free(shell->cmds[0]->name);
			shell->cmds[0]->name = NULL;
			if ((shell)->old_in >= 0)
			{
				dup2((shell)->old_in, STDIN_FILENO);  // restore the old stdin
        		(shell)->old_in = -1;
    		}
    		if ((shell)->old_out >= 0)
    		{
        		dup2((shell)->old_out, STDOUT_FILENO);  // restore the old stdout
        		(shell)->old_out = -1;
    		}
		}
		free(shell->prompt);
	}
	free_shell(&shell);
}
