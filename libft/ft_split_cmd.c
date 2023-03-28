#include "libft.h"

static int	ft_countwords(char const *str, char c);
static int	ft_wordlen(char const *str, char c, int i);
static int	ft_skipdelimiter(char const *str, char c, int i);
static char	*ft_getquoted(char const *str, int *i);

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
		if (s[i] == '\'' || s[i] == '\"')
			splited[j] = ft_getquoted(s, &i);
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
