/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:46:36 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/01 16:47:00 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"

t_vector2	new_vector2(double x, double y)
{
	t_vector2 new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}

t_ivector2	new_ivector2(int x, int y)
{
	t_ivector2 new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}
