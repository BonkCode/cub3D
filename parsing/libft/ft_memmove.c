/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:42:25 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/06 14:17:55 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*s;
	char			*d;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if ((s == NULL || d == NULL) || n == 0)
		return (dst);
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	return (dst);
}
