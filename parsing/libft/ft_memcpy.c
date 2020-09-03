/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:38:54 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/06 14:17:23 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	if (dst == NULL || src == NULL)
		return (dst);
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	while (n--)
		*a++ = *b++;
	return (dst);
}
