/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/20 15:24:06 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int		i;
	char	*path;
}	t_vars;

int	check_files(int err, t_shell **shell, t_rd *rd)
{
	t_rd	*tmp;
	int		fd;

	tmp = rd;
	while (tmp)
	{
		if (tmp->type == RD_IN && tmp->file)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd < 0)
			{
				(*shell)->status_code = 1;
				return (stop(-1, shell), console(1, tmp->file, \
					strerror(errno)), 1);
			}
		}
		tmp = tmp->next;
	}
	if (err)
	{
		(*shell)->status_code = 1;
		return (stop(-1, shell), console(1, "", "ambiguous redirect"), 1);
	}
	return (0);
}

void	parse_logic(char ***command, int *i, t_lexer **tokens, t_shell **shell)
{
	if (is_word(*tokens))
		handle_word(*command, i, tokens, shell, 1);
	if (is_quote(*tokens))
		handle_quote(*command, i, tokens, shell, 1);
}

char	**parse_cmds(t_lexer **tokens, t_shell **shell, t_rd **rd)
{
	char	**command;
	int		i;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (args_len(*tokens, shell, PIPE) + 1));
	if (!command)
		return (NULL);
	int	err = 0;
	while ((*tokens) && (*shell)->exit == 0)
	{
		if ((*tokens)->token->type == WSPACE)
			(*tokens) = (*tokens)->next;
		parse_logic(&command, &i, tokens, shell);
		if (is_redir(*tokens))
			err = handle_redir(rd, tokens, shell);
		if (err)
			break ;
		if ((*tokens)->token->type == PIPE)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		(*tokens) = (*tokens)->next;
	}
	if (check_files(err, shell, *rd))
		return (NULL);
	command[i] = NULL;
	return (command);
}

t_command	**init_commands(t_shell **shell)
{
	t_command	**commands;

	(*shell)->cmds_count = cmds_len((*shell)->lexer);
	commands = (t_command **)malloc(sizeof(t_command *) \
		* ((*shell)->cmds_count + 1));
	if (!commands)
		return (NULL);
	return (commands);
}

t_command	**parse(t_shell **shell)
{
	t_vars		vars;
	char		**cmd;
	t_lexer		*tokens;
	t_command	**commands;
	t_rd		*rd;

	commands = init_commands(shell);
	if (!commands)
		return (NULL);
	vars.i = -1;
	tokens = (*shell)->lexer;
	while (++vars.i < (*shell)->cmds_count)
	{
		rd = NULL;
		vars.path = NULL;
		cmd = parse_cmds(&tokens, shell, &rd);
		if (!cmd || (*shell)->exit != 0)
			break ;
		if (cmd[0] == NULL && rd != NULL)
			vars.path = ft_strdup("redir");
		else
			vars.path = check_cmd(cmd, shell);
		commands[vars.i] = init_cmd(cmd, vars.path, rd);
	}
	commands[vars.i] = NULL;
	return (commands);
}
