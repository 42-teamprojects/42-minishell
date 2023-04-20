/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:03:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/20 15:57:07 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	args_len(t_lexer *tokens)
{
	int				i;
	t_lexer			*tmp;
	t_token_type	type;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->token->type != PIPE)
	{
		if (tmp->token->type == WORD || tmp->token->type == VAR)
			i++;
		else if (tmp->token->type == DQUOTE || tmp->token->type == SQUOTE)
		{
			type = tmp->token->type;
			i++;
			tmp = tmp->next;
			while (tmp && tmp->token->type != type)
				tmp = tmp->next;
			if (tmp->next && tmp->next->token->type == WORD)
				i--;
		}
		tmp = tmp->next;
	}
	return (i);
}

int	cmds_len(t_lexer *tokens)
{
	int		i;
	t_lexer	*tmp;

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
