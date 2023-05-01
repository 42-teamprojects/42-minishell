/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:05 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/01 19:25:16 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell **shell, int idx)
{
	int	i;

	i = 0;
	(void)idx;
	while ((*shell)->env[i])
	{
		printf("%s\n", (*shell)->env[i]);
		i++;
	}
}
