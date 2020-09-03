/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:20:12 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/01 02:32:18 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *bytes;

	bytes = malloc(count * size);
	if (bytes == NULL)
		return (bytes);
	ft_bzero(bytes, size * count);
	return (bytes);
}
