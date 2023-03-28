/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:42:52 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/28 15:24:24 by htalhaou         ###   ########.fr       */
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

char	*remove_quotes(char *input)
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

char	*trim_backslash(char const *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (strlen(s) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '\"')
			i++;
		new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

char	**parse_input(char *input)
{
	char	**in;
	// char	**in2;
	int 	i;

	if (ft_strchr(input, ' ') == NULL)
	{
		in = malloc(sizeof(char *) * 2);
		in[0] = remove_quotes(input);
		in[1] = NULL;
		return (in);
	}
	in = ft_split_cmd(input, ' ');
	if (in == NULL)
	{
		printf("Error: malloc failed");
		exit(0);
	}
	i = -1;
	while (in[++i])
		printf("%s\n", trim_backslash(in[i]));
	return (in);
}
