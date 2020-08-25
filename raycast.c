#include "v_types.h"
#include "cub.h"
#include <mlx.h>
#include <math.h>
#include <stdio.h>

static double	local_abs(double x)
{
	return (x > 0 ? x : -x);
}

t_ray	cast_h_rays(t_player player, int map[24][24])
{
	int			i;
	t_ray		ray;
	t_vector2	max;
	float		atan;
	int			dof;

	ray.rotation = player.rotation;
	i = -1;
	while (++i < 1)
	{
		dof = 0;
		if (local_abs(tan(ray.rotation)) > 0.00001)
			atan = 1 / tan(ray.rotation);
		else
			atan = 0;
		if (local_abs(cos(ray.rotation)) > 0.99999)
		{
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
			dof = 16;
		}
		else if (ray.rotation < PI)
		{
			ray.pos.y = (int)player.pos.y - (int)player.pos.y % GRID_SIZE;
			ray.pos.x = (player.pos.y - ray.pos.y) * atan + player.pos.x;
			ray.offset.y = -GRID_SIZE;
			ray.offset.x = -ray.offset.y * atan;
		}
		else if (ray.rotation > PI)
		{
			ray.pos.y = (int)player.pos.y - (int)player.pos.y % GRID_SIZE + GRID_SIZE;
			ray.pos.x = (player.pos.y - ray.pos.y) * atan + player.pos.x;
			ray.offset.y = GRID_SIZE;
			ray.offset.x = -ray.offset.y * atan;
		}
		while (dof < 16)
		{
			max.x = (int)ray.pos.x / GRID_SIZE;
			max.y = (int)ray.pos.y / GRID_SIZE;
			if (max.x < 24 && max.y < 24 && map[(int)max.y + (ray.rotation < PI ? (int)ray.offset.y / GRID_SIZE : 0)][(int)max.x] > 0)
				dof = 16;
			else
			{
				ray.pos.x += ray.offset.x;
				ray.pos.y += ray.offset.y;
			}
			++dof;
		}
	}
	return (ray);
}

t_ray	cast_v_rays(t_player player, int map[24][24])
{
	int			i;
	t_ray		ray;
	t_vector2	max;
	float		ntan;
	int			dof;

	ray.rotation = player.rotation;
	i = -1;
	while (++i < 1)
	{
		printf("%f %f\n", local_abs(ray.rotation - PI / 2), local_abs(ray.rotation - 3 * PI / 2));
		dof = 0;
		if (local_abs(ray.rotation - PI / 2) >= 0.199 && local_abs(ray.rotation - 3 * PI / 2) >= 0.199)
			ntan = tan(ray.rotation);
		else
		{
			ntan = 4;
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
			dof = 16;
		}
		ntan = ntan > 4 ? 4 : ntan;
		if (dof == 0)
		{
			if (ray.rotation > PI / 2 && ray.rotation < 3 * PI / 2)
			{
				ray.pos.x = (int)player.pos.x - (int)player.pos.x % GRID_SIZE;
				ray.pos.y = (player.pos.x - ray.pos.x) * ntan + player.pos.y;
				ray.offset.x = -GRID_SIZE;
				ray.offset.y = -ray.offset.x * ntan;
			}
			else if (ray.rotation < PI / 2 || ray.rotation > 3 * PI / 2)
			{
				ray.pos.x = (int)player.pos.x - (int)player.pos.x % GRID_SIZE + GRID_SIZE;
				ray.pos.y = (player.pos.x - ray.pos.x) * ntan + player.pos.y;
				ray.offset.x = GRID_SIZE;
				ray.offset.y = -ray.offset.x * ntan;
			}
		}
		while (dof < 16)
		{
			max.x = (int)ray.pos.x / GRID_SIZE;
			max.y = (int)ray.pos.y / GRID_SIZE;
			if (max.x < 24 && max.y < 24 && map[(int)max.y][(int)max.x + (ray.rotation > PI / 2 && ray.rotation < 3 * PI / 2 ? (int)ray.offset.x / GRID_SIZE : 0)] > 0)
				dof = 16;
			else
			{
				ray.pos.x += ray.offset.x;
				ray.pos.y += ray.offset.y;
			}
			++dof;
		}
	}
	return (ray);
}

void	cast_rays(t_player player, int map[24][24], t_data *img)
{
	t_ray	h_ray;
	t_ray	v_ray;
	t_ray	shortest_ray;

	h_ray = cast_h_rays(player, map);
	v_ray = cast_v_rays(player, map);
	if (get_distance(player.pos, h_ray.pos) == 0)
		shortest_ray = v_ray;
	else if (get_distance(player.pos, v_ray.pos) == 0)
		shortest_ray = h_ray;
	else
		shortest_ray = get_distance(player.pos, h_ray.pos) < get_distance(player.pos, v_ray.pos) ? h_ray : v_ray;
	draw_line(img, player.pos, shortest_ray.pos, 1, 0x00FF0000);
	draw_rect_filled(img, shortest_ray.pos, new_vector2(shortest_ray.pos.x + 10, shortest_ray.pos.y + 10), 0x00FFFF00);
}