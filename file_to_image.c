/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 18:17:10 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/04 19:51:01 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "v_types.h"
#include "mlx.h"
#include <math.h>

static t_ivector2	setup_closest_neighboor(t_display_params params,
											t_vector2 pos, t_vector2 scale)
{
	t_ivector2	closest_neighboor;

	closest_neighboor = new_ivector2(params.const_x == 0 ?
		(int)round(pos.x / scale.x) : 0, (int)round(pos.y / scale.y));
	closest_neighboor.x = closest_neighboor.x >= params.source.size.x ?
		params.source.size.x - 1 : closest_neighboor.x;
	closest_neighboor.y = closest_neighboor.y >= params.source.size.y ?
		params.source.size.y - 1 : closest_neighboor.y;
	return (closest_neighboor);
}

static int			not_black(int color)
{
	if (get_r(color) > 0 || get_g(color) > 0 || get_b(color) > 0)
		return (1);
	return (0);
}

static void			draw_pic(t_display_params params, t_vector2 coords,
						t_vector2 scale, t_data *image)
{
	t_ivector2	closest_neighboor;
	char		*dst;
	t_vector2	pos;
	int			color;

	pos = new_vector2(-1, -1);
	pos.y = pos.y + coords.y < -scale.y ? -scale.y - coords.y : pos.y;
	while (++pos.y < params.size.y)
	{
		if (pos.y + coords.y > params.win.y)
			break ;
		pos.x = -1;
		while (++pos.x < params.size.x)
		{
			closest_neighboor = setup_closest_neighboor(params, pos, scale);
			dst = params.source.addr + ((closest_neighboor.y +
				(int)params.offset.y) * params.source.line_length +
				(closest_neighboor.x + (int)params.offset.x) *
				(params.source.bits_per_pixel / 8));
			color = *(unsigned int*)dst;
			if (not_black(color) || params.transparent == 0)
				my_mlx_pixel_put(image, new_ivector2((int)pos.x +
				(int)coords.x, (int)pos.y + (int)coords.y), color, params.win);
		}
	}
}

void				file_to_image(t_display_params params, t_data *image,
							t_vector2 coordinates)
{
	t_vector2	scale;

	params.source.addr = mlx_get_data_addr(params.source.img,
		&params.source.bits_per_pixel, &params.source.line_length,
		&params.source.endian);
	if (params.source.size.x == 0 || params.source.size.y == 0)
		return ;
	while (params.offset.x > params.source.size.x)
		params.offset.x -= params.source.size.x;
	while (params.offset.y > params.source.size.y)
		params.offset.y -= params.source.size.y;
	scale = new_vector2(params.size.x / params.source.size.x,
		params.size.y / params.source.size.y);
	draw_pic(params, coordinates, scale, image);
}
