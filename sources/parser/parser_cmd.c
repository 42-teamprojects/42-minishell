/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:27:23 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/08 17:44:59 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_word(t_dll **tokens)
{
	return (((*tokens)->token->type == WORD \
		|| (*tokens)->token->type == VAR) \
		&& (*tokens)->token->state == DEFAULT);
}

static int	is_quote(t_dll **tokens)
{
	return ((*tokens)->token->type == DQUOTE \
		|| (*tokens)->token->type == SQUOTE);
}

static void	handle_word(char **command, int *i, t_dll **tokens)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			(*tokens)->token->content);
	else
		command[(*i)++] = ft_strdup((*tokens)->token->content);
}

static void	handle_quote(char **command, int *i, t_dll **tokens)
{
	if ((*tokens)->prev && (*tokens)->prev->token->type != WSPACE)
		command[*i - 1] = ft_strjoin_gnl(command[*i - 1], \
			parse_quotes(tokens));
	else
		command[(*i)++] = parse_quotes(tokens);
}

char	**parse_cmds(t_dll **tokens)
{
	char	**command;
	int		i;

	i = 0;
	command = (char **)malloc(sizeof(char *) * (args_len(*tokens) + 1));
	if (!command)
		return (NULL);
	while ((*tokens))
	{
		if ((*tokens)->token->type == WSPACE)
			(*tokens) = (*tokens)->next;
		if (is_word(tokens))
			handle_word(command, &i, tokens);
		if (is_quote(tokens))
			handle_quote(command, &i, tokens);
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
