/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:58:50 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 12:50:31 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*current;
	t_token	*token;

	while (lexer != NULL)
	{
		current = lexer;
		lexer = lexer->next;
		token = current->token;
		if (token != NULL)
		{
			if (token->content != NULL)
				free(token->content);
			free(token);
		}	
		free(current);
	}
}

void	free_rd(t_rd *rd)
{
	t_rd	*current;

	while (rd != NULL)
	{
		current = rd;
		rd = rd->next;
		if (current->file != NULL)
		{
			free(current->file);
			current->file = NULL;
		}
		free(current);
		current = NULL;
	}
}

void	free_command(t_command *cmd)
{
	if (cmd != NULL)
	{
		if (cmd->name != NULL)
			free(cmd->name);
		if (cmd->args != NULL)
			free_array(cmd->args);
		if (cmd->redir != NULL)
			free_rd(cmd->redir);
		if (cmd->path != NULL)
			free(cmd->path);
		if (cmd->full_cmd != NULL)
			free_array(cmd->full_cmd);
		free(cmd);
	}
}

void	free_shell(t_shell *shell, int option)
{
	int	i;

	if (shell != NULL)
	{
		if (option == BASIC)
		{
			if (shell->cmds != NULL)
			{
				i = -1;
				while (++i < shell->cmds_count)
					free_command(shell->cmds[i]);
				free(shell->cmds);
			}
		}
		if (option == FULL)
		{
			free_array(shell->env);
			ft_lstclear(&shell->exp, free);
			free(shell);
		}
	}
}
