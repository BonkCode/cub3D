/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:46:21 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/04 18:02:16 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"
#include "cub.h"
#include <stdio.h>

void		my_mlx_pixel_put(t_data *data, t_ivector2 pos, int color, t_win win)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x >= win.x || pos.y >= win.y)
		return ;
	dst = data->addr + (pos.y * data->line_length +
				pos.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
