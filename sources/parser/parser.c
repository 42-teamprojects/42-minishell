/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 13:34:35 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_redirects(t_command *cmd, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], ">", 2) == 0)
		{
			if (args[i + 1])
				cmd->output_redirect = ft_strdup(args[i + 1]);
			else
				return ;
			args[i] = 0;
			args[i + 1] = 0;
		}
		else if (ft_strncmp(args[i], ">>", 2) == 0)
		{
			if (args[i + 1])
				cmd->output_redirect = ft_strjoin(args[i + 1], ">>");
			else
				return ;
			args[i] = 0;
			args[i + 1] = 0;
		}
		else if (ft_strncmp(args[i], "<", 2) == 0)
		{
			if (args[i + 1])
				cmd->input_redirect = ft_strdup(args[i + 1]);
			else
				return ;
			args[i] = 0;
			args[i + 1] = 0;
		}
		else if (ft_strncmp(args[i], "<<", 2) == 0)
		{
			if (args[i + 1])
				cmd->input_redirect = ft_strjoin(args[i + 1], "<<");
			else
				return ;
			args[i] = 0;
			args[i + 1] = 0;
		}
		i++;
	}
}


t_command	init_cmd(char *input)
{
	char		**command;
	t_command	cmd;

	command = ft_split(input, ' ');
	cmd.name = command[0];
	cmd.argc = args_count(command) - 1;
	cmd.args = init_args(command);
	cmd.input_redirect = 0;
	cmd.output_redirect = 0;
	free_split(command);
	return (cmd);
}
