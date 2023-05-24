/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:04:45 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 15:16:54 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\v' \
	|| c == '\n' || c == '\r' || c == '\f');
}

int	has_spaces_on_sides(char const *s)
{
	size_t	len;

	len = strlen(s);
	if (isspace(s[0]))
		return (1);
	if (len > 0 && isspace(s[len - 1]))
		return (1);
	return (0);
}
