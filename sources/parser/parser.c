/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/27 18:07:01 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	init_cmd(char *input)
{
	char		**command;
	t_command	cmd;

	command = ft_split(input, ' ');
	cmd.name = ft_strdup(command[0]);
	cmd.argc = args_count(command) - 1;
	cmd.args = init_args(command);
	free_split(command);
	return (cmd);
}

char	*parse_input(char *input)
{
	t_quote_state	quote_state;

	quote_state = valid_quotes(input);
	if (quote_state == NO_QUOTES || quote_state == UNCLOSED_SINGLE_QUOTE \
		|| quote_state == UNCLOSED_DOUBLE_QUOTE)
		return (input);
	else
	{
		if (quote_state == CLOSED_SINGLE_QUOTES)
			return (trim_single_quotes(input));
		else
			return (trim_double_quotes(input));
	}
}
