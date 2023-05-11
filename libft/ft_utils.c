/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:04:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/07 00:05:06 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_isspace(int c)
{
	return c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' || c == '\f';
}

int has_spaces_on_sides(char const *s)
{
	if (isspace(s[0]))
		return 1;
	size_t len = strlen(s);
	if (len > 0 && isspace(s[len - 1]))
		return 1;
	return 0;
}
