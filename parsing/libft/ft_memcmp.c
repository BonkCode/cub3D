/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:45:37 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/03 21:30:04 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *list1;
	unsigned char *list2;

	if ((s1 == NULL && s2 == NULL) || n == 0)
		return (0);
	list1 = (unsigned char *)s1;
	list2 = (unsigned char *)s2;
	while (n--)
	{
		if (*list1 != *list2)
			return (*list1 - *list2);
		else
		{
			list1++;
			list2++;
		}
	}
	return (0);
}
