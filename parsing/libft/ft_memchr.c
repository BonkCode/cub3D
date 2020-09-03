/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:26:46 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/06 14:16:28 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cache;
	size_t			i;

	if (s == NULL)
		return (NULL);
	cache = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cache[i] == (unsigned char)c)
			return (cache + i);
		i++;
	}
	return (0);
}
