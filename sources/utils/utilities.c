/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:32:55 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/18 18:57:11 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**dup_list(char **list)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (args_count(list) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (list[i])
	{
		args[i] = ft_strdup(list[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	*redir_type(t_token_type type)
{
	if (type == RD_OUT)
		return (">");
	if (type == RD_AOUT)
		return (">>");
	if (type == RD_IN)
		return ("<");
	if (type == HEREDOC)
		return ("<<");
	return (NULL);
}

char	*remove_slashes(char *path)
{
	char	**parts;
	char	*joined;
	int		i;

	parts = ft_split(path, '/');
	if (!parts)
		return (NULL);
	joined = ft_strdup("");
	if (!joined)
	{
		free_split(parts);
		return (NULL);
	}
	i = 0;
	while (parts[i])
	{
		if (ft_strlen(parts[i]) > 0)
		{
			joined = ft_strjoin_gnl(joined, "/");
			joined = ft_strjoin_gnl(joined, parts[i]);
		}
		i++;
	}
	free_split(parts);
	return (joined);
}
