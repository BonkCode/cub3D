#include <mlx.h>
#include "v_types.h"
#include "cub.h"
#include <stdio.h>

void		draw_rect(t_data *img, t_vector2 start, t_vector2 end, int color)
{
	t_vector2	pos;
	t_vector2	min;
	t_vector2	max;

	min.x = start.x < end.x ? start.x : end.x;
	max.x = start.x > end.x ? start.x : end.x;
	min.y = start.y < end.y ? start.y : end.y;
	max.y = start.y > end.y ? start.y : end.y;

	pos.x = min.x;
	pos.y = min.y;
	while (pos.x  < max.x)
	{
		my_mlx_pixel_put(img, pos.x, pos.y, color);
		++pos.x;
	}
	while (pos.y  < max.y)
	{
		my_mlx_pixel_put(img, pos.x, pos.y, color);
		++pos.y;
	}
	while (pos.x  > min.x)
	{
		my_mlx_pixel_put(img, pos.x, pos.y, color);
		--pos.x;
	}
	while (pos.y  > min.y)
	{
		my_mlx_pixel_put(img, pos.x, pos.y, color);
		--pos.y;
	}
}

void	draw_rect_filled(t_data *img, t_vector2 start, t_vector2 end, int color)
{
	t_vector2	pos;
	t_vector2	min;
	t_vector2	max;


	min.x = start.x < end.x ? start.x : end.x;
	max.x = start.x > end.x ? start.x : end.x;
	min.y = start.y < end.y ? start.y : end.y;
	max.y = start.y > end.y ? start.y : end.y;
	pos.y = min.y;
	//printf("min.x:%f min.y:%f - max.x:%f max.y:%f\n", min.x, min.y, max.x, max.y);
	while (pos.y < max.y)
	{
		pos.x = min.x;
		while (pos.x < max.x)
		{
			my_mlx_pixel_put(img, pos.x, pos.y, color);
			++pos.x;
		}
		++pos.y;
	}
}