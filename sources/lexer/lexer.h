/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:12:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/02 16:54:16 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../includes/minishell.h"

typedef struct s_data
{
	int				len;
	char			*content;
	t_token			type;
	t_status		status;
}	t_data;

typedef struct s_lst
{
	t_lst			*next;
	t_data			data;	
	t_lst			*prev;
}	t_lst;

typedef struct s_lexer
{
	t_lst	*head;
	int		size;
}	t_lexer;

#endif