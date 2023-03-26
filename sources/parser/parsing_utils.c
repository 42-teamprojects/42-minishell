/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:02:11 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/26 16:56:18 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*trim_single_quotes(char *input)
{
	char	*trimmed;
	size_t	i;
	size_t	j;

	trimmed = ft_strdup(input);
	i = 0;
	j = 0;
	while (trimmed[i])
	{
		if (trimmed[i] == '\'')
			i++;
		else
			trimmed[j++] = trimmed[i++];
	}
	trimmed[j] = '\0';
	return (trimmed);
}

char	*trim_double_quotes(char *input)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(strlen(input));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '"' && (i == 0 || input[i - 1] != '\\'))
			i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
