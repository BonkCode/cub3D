#include "v_types.h"
#include "cub.h"
#include <stdio.h>

void	swap_v2(t_vector2 *a, t_vector2 *b)
{
	t_vector2	buffer;

	buffer.x = a->x;
	buffer.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = buffer.x;
	b->y = buffer.y;

}

double	local_abs(double x)
{
	return (x > 0 ? x : -x);
}

void	draw_line(t_data *img, t_vector2 start, t_vector2 end, int thickness, int color)
{
	t_vector2	pos;
	double			k;
	double			b;
	int			i;
	double			current_b;

	if (thickness < 0)
		return ;
	i = -thickness;	
	if (start.x > end.x)
		swap_v2(&start, &end);
	k = (end.y - start.y) / (end.x - start.x);
	b = start.y - k * start.x;
	while (i < thickness)
	{
		pos.x = start.x;
		current_b = b;
		while (pos.x < end.x)
		{
			pos.y = k * pos.x + current_b;
			if (local_abs(pos.x - (int)pos.x) + local_abs(pos.y - (int)pos.y) > LINE_THRESHOLD)
			{
				my_mlx_pixel_put(img, (int)(pos.x + 1), (int)pos.y, color);
				my_mlx_pixel_put(img, (int)(pos.x - 1), (int)pos.y, color);
			}
			my_mlx_pixel_put(img, (int)pos.x, (int)pos.y, color);
			++pos.x;
		}
		++i;
	}
}