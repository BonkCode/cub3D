/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:28:43 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/03 15:20:21 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "v_types.h"
#include "cub.h"

void	draw_rect(t_data *img, t_vector2 start, t_vector2 end, int color, t_win win)
{
	t_vector2	pos;
	t_vector2	min;
	t_vector2	max;

	min.x = start.x < end.x ? start.x : end.x;
	max.x = start.x > end.x ? start.x : end.x;
	min.y = start.y < end.y ? start.y : end.y;
	max.y = start.y > end.y ? start.y : end.y;
	pos = new_vector2(min.x, min.y);
	while (pos.x < max.x)
		my_mlx_pixel_put(img, pos.x++, pos.y, color, win);
	while (pos.y < max.y)
		my_mlx_pixel_put(img, pos.x, pos.y++, color, win);
	while (pos.x > min.x)
		my_mlx_pixel_put(img, pos.x--, pos.y, color, win);
	while (pos.y > min.y)
		my_mlx_pixel_put(img, pos.x, pos.y--, color, win);
}

void	draw_rect_filled(t_data *img, t_vector2 start, t_vector2 end, int color, t_win win)
{
	t_vector2	pos;
	t_vector2	min;
	t_vector2	max;

	min.x = start.x < end.x ? start.x : end.x;
	max.x = start.x > end.x ? start.x : end.x;
	min.y = start.y < end.y ? start.y : end.y;
	max.y = start.y > end.y ? start.y : end.y;
	pos.y = min.y;
	while (pos.y < max.y)
	{
		pos.x = min.x;
		while (pos.x < max.x)
		{
			my_mlx_pixel_put(img, pos.x, pos.y, color, win);
			++pos.x;
		}
		++pos.y;
	}
}
