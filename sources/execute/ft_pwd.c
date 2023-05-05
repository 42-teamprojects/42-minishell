/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:23:58 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/05 15:50:58 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell **shell, int idx)
{
	char	s[PATH_MAX];

	(void)shell;
	(void)idx;
	printf("%s\n", getcwd(s, sizeof(s)));
	return (0);
}
