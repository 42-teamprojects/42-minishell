/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:21:19 by htalhaou          #+#    #+#             */
/*   Updated: 2023/03/30 13:14:58 by htalhaou         ###   ########.fr       */
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
int		unset_help(t_shell *shell);
void	ft_export(t_shell *shell);

#endif
