/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:50:33 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/26 16:15:59 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	char	*path;
	char	*full_path;
	char	**path_list;
	int		i;
}				t_vars;

int	is_valid_cmd(char *str)
{
	char	*s;

	s = ft_tolowercase(str);
	if (ft_strcmp(s, "cd") == 0 || \
		ft_strcmp(s, "pwd") == 0 || \
		ft_strcmp(s, "env") == 0 || \
		ft_strcmp(s, "echo") == 0 || \
		ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(s, "/usr/bin/cd") == 0 || \
		ft_strcmp(s, "/bin/pwd") == 0 || \
		ft_strcmp(s, "/usr/bin/env") == 0 || \
		ft_strcmp(s, "/bin/echo") == 0 || \
		ft_strcmp(str, "export") == 0 || \
		ft_strcmp(str, "unset") == 0 || \
		ft_strcmp(str, "exit") == 0)
	{
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

void	transform_path(char *path)
{
	char	*ptr;

	ptr = ft_strnstr(path, "::", ft_strlen(path));
	while (ptr != NULL)
	{
		ft_memmove(ptr + 3, ptr + 2, \
		ft_strlen(ptr + 2) + 1);
		ft_memcpy(ptr, ":.:", 3);
		ptr = ft_strnstr(ptr + 3, "::", ft_strlen(ptr + 3));
	}
}

char	**get_path_list(char *full_path)
{
	char	**path_list;

	transform_path(full_path);
	path_list = ft_split(full_path, ":");
	return (free(full_path), path_list);
}

char	*check_cmd(char **cmd)
{
	t_vars	v;

	if (!cmd[0] || !args_count(cmd))
		return (NULL);
	if (cmd && cmd[0] && !*cmd[0])
		return (console(1, cmd[0], "command not found"), NULL);
	if (is_valid_cmd(cmd[0]))
		return (ft_strdup("builtin"));
	if (*cmd[0] == '/' || *cmd[0] == '.')
		return (ft_strdup(cmd[0]));
	v.full_path = ft_getenv("PATH");
	if (!v.full_path)
		return (console(1, cmd[0], "No such file or directory"), NULL);
	v.path_list = get_path_list(v.full_path);
	v.path = cmd[0];
	v.i = -1;
	while (v.path_list[++v.i])
	{
		v.path = ft_concat(3, v.path_list[v.i], "/", cmd[0]);
		if (access(v.path, F_OK) == 0)
			return (free_array(v.path_list), v.path);
		free(v.path);
	}
	return (free_array(v.path_list), \
		console(1, cmd[0], "command not found"), NULL);
}
