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

int		draw_line(t_data *img, t_vector2 start, t_vector2 end, int thickness, int color)
{
	t_vector2	pos;
	t_vector2	prev_pos;
	double		k;
	double		b;
	int			i;

	if (thickness < 0)
		return (-1);
	i = -thickness;	
	if (start.x > end.x)
		swap_v2(&start, &end);
	if ((int)end.x - (int)start.x == 0)
	{
		pos.y = start.y;
		b = start.y < end.y ? 1 : -1;
		while ((int)pos.y != (int)end.y)
		{
			my_mlx_pixel_put(img, (int)start.x, (int)pos.y, color);
			pos.y += b;
		}
		return (0);
	}
	k = (end.y - start.y) / (end.x - start.x);
	b = start.y - k * start.x;
	pos.x = start.x;
	pos.y = k * pos.x + b;
	my_mlx_pixel_put(img, (int)pos.x, (int)pos.y, color);
	while (++pos.x <= end.x)
	{
		prev_pos = new_vector2(pos.x - 1, pos.y);
		pos.y = k * pos.x + b;
		my_mlx_pixel_put(img, (int)pos.x, (int)pos.y, color);
		while (local_abs((int)prev_pos.y - (int)pos.y) > 1)
		{
			my_mlx_pixel_put(img, (int)pos.x, (int)prev_pos.y, color);
			prev_pos.y += pos.y > prev_pos.y ? 1 : -1;
		}
		//++pos.x;
	}
	++i;
	return (0);
}