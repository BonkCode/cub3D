/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:37:25 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/06 14:26:57 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*list;

	if (!dest)
		return (NULL);
	list = (unsigned char*)dest;
	while (n-- > 0)
		*(list++) = (unsigned char)c;
	return (dest);
}
