/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:29:47 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/27 20:46:39 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static int	ft_wordlen(char const *str, char c, int i)
{
	int	len;

	len = 0;
	while (str[i] != c && str[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
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
		while (s[i] == c)
			i++;
		wordlen = ft_wordlen(s, c, i);
		splited[j] = ft_substr(s, i, wordlen);
		i += wordlen;
		j++;
	}
	splited[j] = 0;
	return (splited);
}

char	**ft_split_quotes(char const *s, char c)
{
	int		i;
	int		j;
	int		wordlen;
	int		countwords;
	char	**splited;
	int		start;

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
		while (s[i] == c)
			i++;
		if (s[i] == '"' || s[i] == '\'')
		{
			start = i++;
			while (s[i] && s[i] != s[start])
				i++;
			splited[j] = ft_substr(s, start + 1, i - start - 1);
			i++;
		}
		else
		{
			wordlen = ft_wordlen(s, c, i);
			splited[j] = ft_substr(s, i, wordlen);
			i += wordlen;
		}
		j++;
	}
	splited[j] = 0;
	return (splited);
}
