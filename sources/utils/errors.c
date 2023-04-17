/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:57:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/16 23:56:09 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_err(int err_code, t_shell **shell)
{
	if (err_code == 1)
	{
		(*shell)->exit_status = 1;
		printf("\n");
	}
	if (err_code)
		(*shell)->exit_status = err_code;
}

void	console(int status, char *cmd, char *err)
{
	if (status == 0)
		printf(BGREEN"→  "CX "minishell: %s: %s\n"CX, cmd, err);
	else
		printf(BRED"→  "CX "minishell: %s: %s\n"CX, cmd, err);
}

void	not_found(char *cmd)
{
	printf(BRED"→  "CX "minishell: command not found: " BRED"%s\n"CX, \
		cmd);
}

t_dll	*check_quotes(t_dll **tokens, t_token_type type)
{
	while (*tokens)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->token->type == type)
			break ;
	}
	if (!*tokens)
		console(1, "syntax error", "unclosed quotes");
	return (*tokens);
}

int	check_redir(t_dll *tokens)
{
	t_dll			*next;
	t_token_type	type;

	next = tokens->next;
	type = tokens->token->type;
	while (next && next->token->type == WSPACE)
		next = next->next;
	if (!next || (next->token->type != WORD && next->token->type != VAR && \
		next->token->type != SQUOTE && next->token->type != DQUOTE))
		return (console(1, "syntax error near unexpected token", \
						redir_type(type)), 1);
	return (0);
}

int	valid_syntax(t_lexer *lexer)
{
	t_dll	*tmp;

	tmp = lexer->head;
	while (tmp)
	{
		if (is_quote(&tmp))
		{
			if (!check_quotes(&tmp, tmp->token->type))
				return (0);
		}
		else if (is_redir(&tmp))
		{
			if (check_redir(tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
