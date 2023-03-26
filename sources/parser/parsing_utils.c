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
	char	*result;
	int		i;
	int		j;

	result = ft_strdup(input);
	i = 0;
	j = 0;
	while (result[i])
	{
		if (result[i] == '\'')
			i++;
		else
			result[j++] = result[i++];
	}
	result[j] = '\0';
	return (result);
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
