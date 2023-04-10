/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:40:41 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/10 21:11:12 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skipdelimiter(char const *str, char c, int i)
{
	while (str[i] == c)
		i++;
	return (i);
}

static char	*ft_getquoted(char const *str, int *i)
{
	int		start;
	int		end;
	char	*quoted;

	start = ++(*i);
	end = start;
	while (str[end] && str[end] != str[start - 1])
		end++;
	if (!str[end])
	{
		*i = -1;
		return (NULL);
	}
	quoted = ft_substr(str, start, end - start);
	*i = end + 1;
	return (quoted);
}

static int	ft_countwords(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		i = ft_skipdelimiter(str, c, i);
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
		if (str[i] == '\'' || str[i] == '\"')
		{
			ft_getquoted(str, &i);
			if (i == -1)
				return (-1);
		}
		len++;
		i++;
	}
	return (len);
}

static int	ft_quoted_wordlen(char const *s, int start)
{
	int		i;
	char	quote;

	i = start + 1;
	quote = s[start];
	while (s[i] != '\0')
	{
		if (s[i] == quote)
			return (i - start + 1);
		else if (s[i] == '\\' && quote != '\'')
			i += 2;
		else
			i++;
	}
	return (-1);
}

static char	*ft_escape_quotes(char const *word)
{
	char	*escaped;
	int		i;
	int		j;

	escaped = (char *)malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!escaped)
		return (NULL);
	ft_bzero(escaped, ft_strlen(word) + 1);
	i = 0;
	j = 0;
	while (word[i])
	{
		escaped[j++] = word[i++];
	}
	return (escaped);
}

char	**ft_split_cmd(char const *s, char c)
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
		i = ft_skipdelimiter(s, c, i);
		if (s[i] == '\"' || s[i] == '\'')
		{
			wordlen = ft_quoted_wordlen(s, i);
			if (wordlen == -1)
			{
				free(splited);
				return (NULL);
			}
			splited[j] = ft_escape_quotes(ft_substr(s, i, wordlen));
			i += wordlen;
		}
		else
		{
			wordlen = ft_wordlen(s, c, i);
			if (wordlen == -1)
			{
				free(splited);
				return (NULL);
			}
			splited[j] = ft_substr(s, i, wordlen);
			i += wordlen;
		}
		j++;
	}
	splited[j] = NULL;
	return (splited);
}
