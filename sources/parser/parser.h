/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:02:11 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/25 14:55:17 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../includes/minishell.h"

typedef enum e_quote_state
{
	NO_QUOTES,
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	UNCLOSED_SINGLE_QUOTE,
	UNCLOSED_DOUBLE_QUOTE,
	CLOSED_SINGLE_QUOTES,
	CLOSED_DOUBLE_QUOTES
}	t_quote_state;

char			**init_args(char **command);
t_quote_state	valid_quotes(char *input);
char			*trim_single_quotes(char *input);
char			*trim_double_quotes(char *input);
#endif