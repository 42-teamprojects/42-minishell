/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:57:53 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/25 18:28:47 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_shell **shell)
{
	char		*prompt;
	char		*input;

	prompt = readline(BGREEN"minishell $> "CX);
	input = ft_strtrim(prompt, " \t");
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
		return (free(input), stop(-1));
	add_history(input);
	(*shell)->lexer = lexer(input);
	free(input);
	if (!valid_syntax(shell))
		return (free_lexer((*shell)->lexer), stop(-1));
	(*shell)->cmds = parse();
	free_lexer((*shell)->lexer);
	if (!(*shell)->cmds)
		return (stop(-1));
}

void	execute_inparent(t_shell **shell)
{
	t_rd	*rd;

	rd = (*shell)->cmds[0]->redir;
	if (rd && handle_redirection(rd))
		return ;
	(*shell)->status_code = ft_exec_builtin(0);
	if (rd)
		rollback_fd(shell);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	init_shell(&g_shell, env);
	while (g_shell->exit != 1)
	{
		g_shell->exit = 0;
		read_input(&g_shell);
		if (g_shell->exit != 0)
			continue ;
		if (g_shell->cmds_count == 1 && \
			is_cmd_parent(g_shell->cmds[0]->name))
			execute_inparent(&g_shell);
		else
			ft_exec();
		free_shell(g_shell, BASIC);
	}
	free_shell(g_shell, FULL);
}
