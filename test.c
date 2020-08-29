#include "v_types.h"
#include "cub.h"
#include <stdio.h>

t_ray	cast_h_rays(t_player player, int map[24][24])
{
	t_ray		ray;
	t_vector2	max;
	float		atan;
	int			dof;

	ray.rotation = player.rotation;
	dof = 0;
	if (ray.rotation != 0 && ray.rotation != PI)//local_abs(tan(ray.rotation)) > 0.00001)
		atan = 1 / tan(ray.rotation);
	if (ray.rotation == 0 || ray.rotation == PI)//local_abs(cos(ray.rotation)) > 0.99999)
	{
		ray.pos.x = player.pos.x;
		ray.pos.y = player.pos.y;
		dof = 32;
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
	while (dof < 32)
	{
		max.x = (int)(ray.pos.x / GRID_SIZE);
		max.y = (int)(ray.pos.y / GRID_SIZE);
		if (max.x < 24 && max.y < 24 && map[(int)max.y + (ray.rotation < PI ? (int)ray.offset.y / GRID_SIZE : 0)][(int)max.x] > 0)
			dof = 32;
		else if (ray.pos.x < 0 || ray.pos.x > SCREEN_WIDTH)
			{
			dof = 32;
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
		}
		else
		{
			ray.pos.x += ray.offset.x;
			ray.pos.y += ray.offset.y;
		}
		++dof;
	}
	return (ray);
}

int main(void)
{
	t_game	game;

	game.map_active = 0;
	game.player.pos = new_vector2(100, 100);
	game.img.img = NULL;
	game.player.rotation = 3.5203;
	
	while (game)
	return (0);
}