/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 09:22:08 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_shell **shell)
{
	char		*prompt;
	char		*input;

	prompt = readline(BGREEN"minishell $> "CX);
	input = ft_strtrim(prompt, " ");
	if (!prompt)
	{
		free(prompt);
		free_array((*shell)->env);
		exit((*shell)->status_code);
	}
	free(prompt);
	return (input);
}

void	read_input(t_shell **shell)
{
	char		*input;

	input = ft_prompt(shell);
	if (!ft_strlen(input))
		return (free(input), stop(-1, shell));
	add_history(input);
	(*shell)->lexer = lexer(input);
	free(input);
	if (!valid_syntax(shell))
		return (free_lexer((*shell)->lexer), stop(-1, shell));
	(*shell)->cmds = parse(shell);
	free_lexer((*shell)->lexer);
	if (!(*shell)->cmds)
		return (stop(-1, shell));
	// system("leaks minishell -q");
	// return (free_shell(*shell, BASIC), stop(-1, shell));
	// print_lexer((*shell)->lexer);
	// return (stop(-1, shell));
	// print_commands((*shell)->cmds);
}

void	execute_inparent(t_shell **shell)
{
	t_rd	*rd;

	rd = (*shell)->cmds[0]->redir;
	if (rd && handle_redirection(rd, shell))
		return ;
	(*shell)->status_code = ft_exec_builtin(shell, 0);
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
