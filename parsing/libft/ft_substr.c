/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 02:30:09 by rvernius          #+#    #+#             */
/*   Updated: 2020/05/06 15:40:06 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cache;
	size_t	i;

	i = 0;
	if (!s || !(cache = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	while (i < len && s[i] != '\0')
	{
		cache[i] = s[i + start];
		i += 1;
	}
	cache[i] = '\0';
	return (cache);
}
