/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:56:19 by yelaissa          #+#    #+#             */
/*   Updated: 2023/04/10 22:18:58 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

void	remove_node(t_list **head, void *key, void (*del)(void*))
{
	t_list	*curr;
	t_list	*prev;

	curr = *head;
	prev = NULL;
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->content, key) \
			|| ft_memcmp(curr->content, key, sizeof(key)) == 0)
		{
			if (prev == NULL)
				*head = curr->next;
			else
				prev->next = curr->next;
			del(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
