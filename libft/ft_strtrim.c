/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:20:42 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/24 15:15:33 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	char	*str;

	str = NULL;
	if (s1 != 0 && set != 0)
	{
		front = 0;
		back = ft_strlen(s1);
		while (s1[front] && ft_strchr(set, s1[front]))
			front++;
		while (s1[back - 1] && ft_strchr(set, s1[back - 1]) && back > front)
			back--;
		str = (char *)malloc(sizeof(char) * (back - front + 1));
		if (!str)
			return (NULL);
		ft_strlcpy(str, &s1[front], back - front + 1);
	}
	return (str);
}

char	*ft_strtrim_min(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	char	*str;

	str = NULL;
	if (s1 != 0 && set != 0)
	{
		front = 0;
		back = ft_strlen(s1);
		while (s1[front] && ft_strchr(set, s1[front]))
			front++;
		while (s1[back - 1] && ft_strchr(set, s1[back - 1]) && back > front)
			back--;
		if (front > 0 && s1[front - 1] == ' ')
			front--;
		if (back < ft_strlen(s1) && s1[back] == ' ')
			back++;
		str = (char *)malloc(sizeof(char) * (back - front + 1));
		if (!str)
			return (NULL);
		ft_strlcpy(str, &s1[front], back - front + 1);
		free((char *)s1);
	}
	return (str);
}
