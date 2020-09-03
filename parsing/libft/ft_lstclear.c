/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 00:46:15 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/06 14:15:24 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *cache;

	if (lst && *lst)
	{
		while (*lst)
		{
			cache = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			(*lst) = cache;
		}
		*lst = NULL;
	}
}
