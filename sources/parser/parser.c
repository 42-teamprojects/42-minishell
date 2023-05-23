/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/23 16:41:16 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int			i;
	char		**cmd;
	char		*path;
	t_lexer		*tokens;
	t_command	**commands;
	t_rd		*rd;
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
	int		err;

	i = 0;
	command = (char **)malloc(sizeof(char *) * \
		(args_len(*tokens, shell, PIPE) + 1));
	if (!command)
		return (NULL);
	err = 0;
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
	t_vars		v;

	v.commands = init_commands(shell);
	if (!v.commands)
		return (NULL);
	v.i = -1;
	v.tokens = (*shell)->lexer;
	while (++v.i < (*shell)->cmds_count)
	{
		v.rd = NULL;
		v.path = NULL;
		v.cmd = parse_cmds(&v.tokens, shell, &v.rd);
		if (!v.cmd || (*shell)->exit != 0)
			break ;
		if (v.cmd[0] == NULL && v.rd != NULL)
			v.path = ft_strdup("redir");
		else
			v.path = check_cmd(v.cmd, shell);
		v.commands[v.i] = init_cmd(v.cmd, v.path, v.rd);
	}
	v.commands[v.i] = NULL;
	return (v.commands);
}
