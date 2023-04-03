/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:57:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/03 19:36:03 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	throw_err(int err_code, t_shell *shell)
{
	printf("\n");
	if (err_code == 0)
		shell->exit_status = 0;
}

void	print404(char *cmd)
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
		printf("minishell: unclosed quotes detected.\n");
	return (*tokens);
}

int	valid_syntax(t_lexer *lexer)
{
	t_dll	*tmp;

	tmp = lexer->head;
	while (tmp)
	{
		if (tmp->token->type == DQUOTE || tmp->token->type == SQOUTE)
		{
			if (!check_quotes(&tmp, tmp->token->type))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
