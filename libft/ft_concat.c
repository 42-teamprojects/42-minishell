/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:26:57 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/23 20:16:22 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat(int num_args, ...)
{
	va_list	args;
	char	*concatenated_str;
	char	*arg;
	int		i;

	va_start(args, num_args);
	concatenated_str = ft_strdup(va_arg(args, char *));
	i = 1;
	while (i < num_args)
	{
		arg = va_arg(args, char *);
		if (!arg)
			break ;
		concatenated_str = ft_strjoin_gnl(concatenated_str, arg);
		i++;
	}
	va_end(args);
	return (concatenated_str);
}
