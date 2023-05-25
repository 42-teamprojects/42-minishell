/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/25 22:47:28 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int			i;
	char		**cmd;
	char		*path;
	int			err;
	t_lexer		*tokens;
	t_command	**commands;
	t_rd		*rd;
}	t_vars;

int	check_files(int *err, t_rd *rd)
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
				*err = 1;
				(g_shell)->status_code = 1;
				return (stop(-1), console(1, tmp->file, \
					strerror(errno)), 1);
			}
		}
		tmp = tmp->next;
	}
	if (*err)
	{
		(g_shell)->status_code = 1;
		return (stop(-1), console(1, "", "ambiguous redirect"), 1);
	}
	return (0);
}

int	process_tokens_for_cmds(t_lexer **tokens, char **command, \
	int *err, t_rd **rd)
{
	int	i;

	i = 0;
	while (*tokens && (g_shell)->exit == 0)
	{
		if ((*tokens)->token->type == WSPACE)
			(*tokens) = (*tokens)->next;
		parse_logic(&command, &i, tokens);
		if (is_redir(*tokens))
			*err = handle_redir(rd, tokens);
		if (*err)
			break ;
		if ((*tokens)->token->type == PIPE)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		(*tokens) = (*tokens)->next;
	}
	return (i);
}

char	**parse_cmds(t_lexer **tokens, t_rd **rd, int *err)
{
	char	**command;
	int		i;

	i = 0;
	*err = 0;
	command = allocate_command(tokens);
	if (!command)
		return (NULL);
	i = process_tokens_for_cmds(tokens, command, err, rd);
	command[i] = NULL;
	if (check_files(err, *rd))
		return (free_rd(*rd), free_array(command), NULL);
	return (command);
}

t_command	**init_commands(void)
{
	t_command	**commands;

	(g_shell)->cmds_count = cmds_len((g_shell)->lexer);
	commands = (t_command **)malloc(sizeof(t_command *) \
		* ((g_shell)->cmds_count + 1));
	if (!commands)
		return (NULL);
	return (commands);
}

t_command	**parse(void)
{
	t_vars		v;

	v.commands = init_commands();
	if (!v.commands)
		return (NULL);
	v.i = -1;
	v.tokens = (g_shell)->lexer;
	while (++v.i < (g_shell)->cmds_count)
	{
		v.rd = NULL;
		v.path = NULL;
		v.cmd = parse_cmds(&v.tokens, &v.rd, &v.err);
		if (v.err)
			return (free(v.commands), NULL);
		if (!v.cmd || (g_shell)->exit != 0)
			break ;
		if (v.cmd[0] == NULL && v.rd != NULL)
			v.path = ft_strdup("redir");
		else
			v.path = check_cmd(v.cmd);
		v.commands[v.i] = init_cmd(v.cmd, v.path, v.rd);
	}
	v.commands[v.i] = NULL;
	return (v.commands);
}
