/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:57:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 17:03:14 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop(int err_code)
{
	if (err_code == 1)
	{
		(g_shell)->exit = 1;
		printf("\n");
	}
	if (err_code)
		(g_shell)->exit = err_code;
}

// Print errors in stderror status : 1
void	console(int status, char *cmd, char *err)
{
	if (status == 1)
		ft_printf_fd(2, "minishell: %s: %s\n", cmd, err);
	else
		ft_printf_fd(1, "minishell: %s: %s\n", cmd, err);
}

// to be deleted

void	print_redir(t_rd *rd)
{
	t_rd	*node;

	printf("+------------+------------+\n");
	printf("| FILE       | TYPE       |\n");
	printf("+------------+------------+\n");
	node = rd;
	while (node)
	{
		printf("| %-10s | %-10s |\n", node->file,
	       redir_type(node->type));
		node = node->next;
	}
	printf("+------------+------------+\n");
}

void	print_node(t_token *node)
{
	printf("| %-10s | %-10d | %-10s | %-10s |\n", node->content, node->len, 
			node->state == IN_DQUOTE ? "IN_DQOUTE" :
			node->state == IN_SQUOTE ? "IN_SQUOTE" :
			node->state == ESCAPED ? "ESCAPED" :
			node->state == DEFAULT ? "DEFAULT" :
	       "UNKNOWN",
	       node->type == SQUOTE ? "SQUOTE" :
	       node->type == DQUOTE ? "DQUOTE" :
	       node->type == ESCAPE ? "ESCAPE" :
	       node->type == VAR ? "VAR" :
	       node->type == PIPE ? "PIPE" :
	       node->type == RD_IN ? "RD_IN" :
	       node->type == RD_OUT ? "RD_OUT" :
	       node->type == WORD ? "WORD" :
	       node->type == HEREDOC ? "HEREDOC" :
	       node->type == RD_AOUT ? "RD_AOUT" :
	       node->type == NEW_LINE ? "NEW_LINE" :
	       node->type == WSPACE ? "WSPACE" :
	       "UNKNOWN");
}

void	print_lexer(t_lexer *lexer)
{
	t_lexer	*node;

	printf("+------------+------------+------------+------------+\n");
	printf("| CONTENT    | LENGTH     | STATE      | TYPE       |\n");
	printf("+------------+------------+------------+------------+\n");
	node = lexer;
	while (node)
	{
		print_node(node->token);
		node = node->next;
	}
	printf("+------------+------------+------------+------------+\n");
}

void print_cmd(t_command *cmd) {
    int i;
    t_rd *tmp = cmd->redir;

	printf("| %-10s | %-10d | %-10s | %-22s |\n",
		cmd->name, cmd->argc, " ", " ");

    if (cmd->args != NULL) {
        i = 0;
        while (cmd->args[i]) {
            if (i == 0)
                printf("|            |            | "CYAN"ARGS       | %-22s |\n" CX, cmd->args[i]);
            else
                printf("|            |            |      "CYAN"      | %-22s |\n" CX, cmd->args[i]);
            i++;
        }
    }

    if (tmp != NULL) {
        i = 0;
        while (tmp != NULL) {
            if (i == 0)
                printf("|            |            | "BRED"REDIRE     | %-22s |\n" CX, ft_concat(3, tmp->file, " ", redir_type(tmp->type)));
            else
                printf("|            |            |     "BRED"       | %-22s |\n" CX, ft_concat(3, tmp->file, " ", redir_type(tmp->type)));
            tmp = tmp->next;
            i++;
        }
    }
}

void print_commands(t_command **cmds) {
    int i;

    printf("+------------+------------+------------+------------------------+\n");
    printf("| " BGREEN "CMD" CX "        | " BGREEN "ARG COUNT" CX "  |            |                        |\n");
    printf("+------------+------------+------------+------------------------+\n");

    i = 0;
    while (cmds[i]) {
        print_cmd(cmds[i]);
        if (cmds[i + 1])
            printf("+------------+------------+------------+------------------------+\n");
        i++;
    }

    printf("+------------+------------+------------+------------------------+\n");
}
