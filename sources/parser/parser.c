/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/17 17:40:36 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_logic(char ***command, int *i, t_lexer **tokens, t_shell **shell)
{
	if (is_word(*tokens))
		handle_word(*command, i, tokens, shell);
	if (is_quote(*tokens))
		handle_quote(*command, i, tokens, shell);
}

char	**parse_cmds(t_lexer **tokens, t_shell **shell, t_rd **rd)
{
	char	**command;
	int		i;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (args_len(*tokens) + 1));
	if (!command)
		return (NULL);
	while ((*tokens) && (*shell)->exit == 0)
	{
		if ((*tokens)->token->type == WSPACE)
			(*tokens) = (*tokens)->next;
		parse_logic(&command, &i, tokens, shell);
		if (is_redir(*tokens))
			handle_redir(rd, tokens, shell);
		if ((*tokens)->token->type == PIPE)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		(*tokens) = (*tokens)->next;
	}
	command[i] = NULL;
	return (command);
}

t_command	**parse(t_shell **shell)
{
	int			i;
	char		**cmd;
	t_lexer		*tokens;
	t_command	**commands;
	t_rd		*rd;

	(*shell)->cmds_count = cmds_len((*shell)->lexer);
	commands = (t_command **)malloc(sizeof(t_command *) \
		* ((*shell)->cmds_count + 1));
	if (!commands)
		return (NULL);
	i = -1;
	tokens = (*shell)->lexer;
	while (++i < (*shell)->cmds_count)
	{
		rd = NULL;
		cmd = parse_cmds(&tokens, shell, &rd);
		if (!cmd || (*shell)->exit != 0)
			break ;
		commands[i] = init_cmd(cmd, rd);
	}
	commands[i] = NULL;
	return (commands);
}
