/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:21:19 by htalhaou          #+#    #+#             */
/*   Updated: 2023/04/07 18:27:39 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../includes/minishell.h"
# include "../parser/parser.h"

void	ft_pwd(t_shell *shell);
void	ft_echo(t_shell *shell);
void	ft_env(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_unset(t_shell *shell);
int		ft_export(t_shell *shell);
int		ft_setenv(char *name, char *value, t_shell *shell);
int		ft_setenv_help(char *name, char *value, t_shell *shell, int i);
char	*ft_getenv(t_shell	*shell, const char *name);
void	over_value(t_shell *shell, char *name, int overwrite);
// void	next(int overwrite, char *input, t_shell *shell,
// 			char *name, char *value);
int		check_overwrite(char *name, t_shell *shell);
void    ft_export_new(t_shell *shell, char *variable);

#endif
