# Minishell

## Snippets

``` c
printf("%s \n", shell->cmd->name);
for(int i=0; shell->cmd->args[i]; i++)
	printf("%s \n", shell->cmd->args[i]);
```

## To look at

``` c
char	*ft_charjoin(char c1, char c2)
{
	char	*str;

	str = malloc(3);
	if (!str)
		return (NULL);
	str[0] = c1;
	str[1] = c2;
	str[2] = '\0';
	return (str);
}

char	*expand_env(char *input)
{
	int		i;
	int		j;
	char	*var_name;
	char	*var_value;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			var_name = ft_strdup("");
			j = i + 1;
			while (input[j] && ft_isalnum(input[j]))
			{
				var_name = ft_charjoin(var_name, input[j]);
				j++;
			}
			if (ft_strlen(var_name))
			{
				var_value = getenv(var_name);
				if (!var_value)
					var_value = "";
				result = ft_strjoin_gnl(result, var_value);
				i = j - 1;
				free(var_name);
				continue;
			}
			free(var_name);
		}
		result = ft_charjoin(result, input[i]);
		i++;
	}
	return (result);
}

char	*trim_DQUOTEs(char *input)
{
	char	*trimmed;
	size_t	i;
	size_t	j;

	trimmed = ft_strdup(input);
	i = 0;
	j = 0;
	while (trimmed[i])
	{
		if (trimmed[i] == '\"')
		{
			i++;
			while (trimmed[i] && trimmed[i] != '\"')
			{
				if (trimmed[i] == '$')
				{
					j = expand_env(trimmed);
					i++;
				}
				else
					trimmed[j++] = trimmed[i++];
			}
			if (trimmed[i] == '\"')
				i++;
		}
		else
			trimmed[j++] = trimmed[i++];
	}
	trimmed[j] = '\0';
	return (trimmed);
}

```
