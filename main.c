/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/20 22:06:34 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_shell **shell)
{
	char		*input;

	input = ft_strtrim(readline(BGREEN"minishell $> "CX), "\t ");
	if (!input || !ft_strcmp(input, "exit"))
		return (free(input), stop(1, shell));
	if (!ft_strlen(input))
		return (free(input), stop(-3, shell));
	add_history(input);
	(*shell)->lexer = lexer(input);
	input = NULL;
	if (valid_syntax((*shell)->lexer))
	{
		(*shell)->cmds = parse(shell);
		if (!(*shell)->cmds || !(*shell)->cmds[0])
			return (stop(-3, shell));
		// print_commands((*shell)->cmds);
		return ;
	}
	stop(-3, shell);
}
// print_lexer((*shell)->lexer);

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	init_shell(&shell, env);
	while (shell->exit != 1)
	{
		shell->exit = 0;
		read_input(&shell);
		if (shell->exit != 0)
			continue ;
		if (shell->cmds[0]->path != NULL)
		{
			if (shell->cmds[0]->redir != NULL)
				redirect(&shell);
			if (!ft_strcmp(shell->cmds[0]->path, "builtin"))
				ft_exec_builtin(&shell);
			else if (ft_strcmp(shell->cmds[0]->path, "redir") != 0)
				ft_exec(&shell);
			if (shell->cmds[0]->redir != NULL)
				rollback_fd(&shell);
		}
		free_shell(shell, BASIC);
	}
	free_shell(shell, FULL);
}
