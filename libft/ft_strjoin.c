/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:48:13 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/23 23:35:06 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	dstlen;
	int	j;

	j = 0;
	dstlen = ft_strlen(dest);
	while (src[j])
	{
		dest[dstlen + j] = src[j];
		j++;
	}
	dest[dstlen + j] = 0;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!(str))
		return (NULL);
	*str = 0;
	ft_strcat(str, (char *)s1);
	ft_strcat(str, (char *)s2);
	str[ft_strlen(str)] = '\0';
	return (str);
}
