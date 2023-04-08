/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:21:19 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/08 17:42:01 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	ft_pwd(t_shell **shell);
void	ft_echo(t_shell **shell);
void	ft_env(t_shell **shell);
int		ft_cd(t_shell **shell);
int		ft_unset(t_shell **shell);
int		ft_export(t_shell **shell);
int		ft_setenv(char *name, char *value, t_shell **shell);
int		ft_setenv_help(char *name, char *value, t_shell **shell, int i);
char	*ft_getenv(t_shell **shell, const char *name);

#endif