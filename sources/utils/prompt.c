/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:53:46 by yelaissa          #+#    #+#             */
/*   Updated: 2023/03/24 11:00:36 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/global.h"

char	*init_prompt(void)
{
	char	*user;
	char	cwd[1024];
	char	*line;
	char	*str;

	user = ft_strjoin(GREEN "→  " CYAN, getenv("USER"));
	getcwd(cwd, 1024);
	str = ft_strrchr(cwd, '/') + 1;
	if (str == 0)
		exit (1);
	line = ft_strjoin_gnl(user, " " BRED);
	line = ft_strjoin_gnl(line, str);
	line = ft_strjoin_gnl(line, YELLOW " $ " CX);
	return (line);
}