/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:03:26 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/07 22:15:00 by yelaissa         ###   ########.fr       */
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

int	is_var_alone(t_lexer *tokens)
{
	return (tokens->token->type == VAR && \
		((tokens->next && (tokens->next->token->type == WSPACE)) \
		|| (tokens->prev && (tokens->prev->token->type == WSPACE))));
}

int	args_len(t_lexer *tokens, t_shell **shell, t_token_type test_type)
{
	int				i;
	t_lexer			*tmp;
	t_token_type	type;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->token->type != test_type)
	{
		if (tmp->token->type == VAR && !tmp->prev)
			i++;
		else if (tmp->token->type == WORD && !is_var_alone(tmp))
			i++;
		else if (tmp->token->type == VAR && is_var_alone(tmp))
		{
			char *expanded = ft_getenv(shell, tmp->token->content + 1);
			if (expanded)
			{
				char **split = ft_split(expanded, ' ');
				i += args_count(split);
				free(expanded);
				free(split);
			}
			else
				i++;
		}
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
		if (tmp->token->type == PIPE && (tmp->token->state == DEFAULT))
			i++;
		tmp = tmp->next;
	}
	return (i);
}
