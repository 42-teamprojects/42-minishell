/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/01 20:35:26 by yelaissa         ###   ########.fr       */
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
	free(input);
	input = NULL;
	if (valid_syntax((*shell)->lexer))
	{
		(*shell)->path_list = ft_split(ft_getenv(shell, "PATH"), ':');
		(*shell)->cmds = parse(shell);
		if (!(*shell)->cmds || !(*shell)->cmds[0])
			return (stop(-3, shell));
		print_lexer((*shell)->lexer);
		print_commands((*shell)->cmds);
		return ;
	}
	free_lexer((*shell)->lexer);
	stop(-3, shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;

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
			ft_exec(&shell);
		free_shell(shell, BASIC);
	}
	free_shell(shell, FULL);
}
