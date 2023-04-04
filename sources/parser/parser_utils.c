/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:03:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/04 16:44:34 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**init_args(char **command)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (args_count(command)));
	if (!args)
		return (NULL);
	i = 1;
	while (command[i])
	{
		args[i - 1] = ft_strdup(command[i]);
		i++;
	}
	args[i - 1] = NULL;
	return (args);
}

int	args_len(t_dll *tokens)
{
	int		i;
	t_dll	*tmp;
	t_dll	*tmp2;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->token->type != PIPE)
	{
		if (tmp->token->type == WORD || tmp->token->type == ENV)
			i++;
		else if (tmp->token->type == DQUOTE || tmp->token->type == SQUOTE)
		{
			tmp2 = tmp2->next;
			while (tmp2 && tmp2->type != type)
				tmp2 = tmp2->next;
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

int	cmds_len(t_dll *tokens)
{
	int		i;
	t_dll	*tmp;

	i = 1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->token->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
