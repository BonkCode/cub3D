/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:16:09 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/07 15:14:31 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

double			local_abs(double x)
{
	return (x > 0 ? x : -x);
}

int				same_value(double x, double y)
{
	if (local_abs(x - y) < 0.0001)
		return (1);
	return (0);
}

