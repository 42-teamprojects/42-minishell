/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:29:47 by yelaissa          #+#    #+#             */
/*   Updated: 2023/05/26 13:02:24 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *str, char *c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_strchr(c, str[i]) && str[i])
			i++;
		if (!ft_strchr(c, str[i]) && str[i])
		{
			count++;
			while (!ft_strchr(c, str[i]) && str[i])
				i++;
		}
	}
	return (count);
}

static int	ft_wordlen(char const *str, char *c, int i)
{
	int	len;

	len = 0;
	while (!ft_strchr(c, str[i]) && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char *c)
{
	int		i;
	int		j;
	int		wordlen;
	int		countwords;
	char	**splited;

	if (!s)
		return (NULL);
	countwords = ft_countwords(s, c);
	splited = (char **)malloc(sizeof(char *) * (countwords + 1));
	if (!splited)
		return (NULL);
	i = 0;
	j = 0;
	while (j < countwords)
	{
		while (ft_strchr(c, s[i]))
			i++;
		wordlen = ft_wordlen(s, c, i);
		splited[j] = ft_substr(s, i, wordlen);
		i += wordlen;
		j++;
	}
	splited[j] = 0;
	return (splited);
}
