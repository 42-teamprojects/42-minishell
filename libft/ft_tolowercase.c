/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolowercase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:33:10 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/21 03:53:16 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolowercase(char *str)
{
	char	*lower;
	int		i;

	lower = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		lower[i] = ft_tolower(str[i]);
		i++;
	}
	lower[i] = '\0';
	return (lower);
}
