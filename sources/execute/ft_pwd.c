/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:23:58 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/01 19:26:32 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell **shell, int idx)
{
	char	s[PATH_MAX];

	(void)shell;
	(void)idx;
	printf("%s\n", getcwd(s, sizeof(s)));
}
