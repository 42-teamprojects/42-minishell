/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/03 22:25:57 by htalhaou         ###   ########.fr       */
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
		{
			(*shell)->status_code = 127;
			return (stop(-3, shell));
		}
		// print_lexer((*shell)->lexer);
		// print_commands((*shell)->cmds);
		return ;
	}
	free_lexer((*shell)->lexer);
	stop(-3, shell);
}

void	execute_inparent(t_shell **shell)
{
	t_rd	*rd;

	rd = (*shell)->cmds[0]->redir;
	if (rd && handle_redirection(rd, shell))
		return ;
	ft_exec_builtin(shell, 0);
	if (rd)
		rollback_fd(shell);
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
		if (shell->cmds_count == 1 && \
			is_cmd_parent(shell->cmds[0]->name))
			execute_inparent(&shell);
		else
			ft_exec(&shell);
		free_shell(shell, BASIC);
	}
	free_shell(shell, FULL);
}
