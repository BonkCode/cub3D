/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 13:56:28 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/06 17:25:24 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"
#include "cub.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

void			setup_h_rays(t_ray *ray, float *atan, t_player player, int *dof)
{
	ray->rotation = player.rotation;
	if (local_abs(tan(ray->rotation)) > 0.00001)
		*atan = 1 / tan(ray->rotation);
	if (local_abs(cos(ray->rotation)) > 0.99999)
	{
		ray->pos.x = player.pos.x;
		ray->pos.y = player.pos.y;
		*dof = 32;
	}
	else if (ray->rotation < PI)
	{
		ray->pos.y = (int)player.pos.y - (int)player.pos.y % GRID_SIZE;
		ray->pos.x = (player.pos.y - ray->pos.y) * *atan + player.pos.x;
		ray->offset.y = -GRID_SIZE;
		ray->offset.x = -ray->offset.y * *atan;
	}
	else if (ray->rotation > PI)
	{
		ray->pos.y = (int)player.pos.y - (int)player.pos.y %
						GRID_SIZE + GRID_SIZE;
		ray->pos.x = (player.pos.y - ray->pos.y) * *atan + player.pos.x;
		ray->offset.y = GRID_SIZE;
		ray->offset.x = -ray->offset.y * *atan;
	}
}

void			setup_v_rays(t_ray *ray, float *ntan, t_player player, int *dof)
{
	ray->rotation = player.rotation;
	if (!same_value(ray->rotation, PI / 2) &&
		!same_value(ray->rotation, 3 * PI / 2))
		*ntan = tan(ray->rotation);
	else
		stop_casting(ray, player, dof);
	if (*dof == -1)
	{
		if (ray->rotation > PI / 2 && ray->rotation < 3 * PI / 2)
		{
			ray->pos.x = (int)player.pos.x - (int)player.pos.x % GRID_SIZE;
			ray->pos.y = (player.pos.x - ray->pos.x) * *ntan + player.pos.y;
			ray->offset.x = -GRID_SIZE;
			ray->offset.y = -ray->offset.x * *ntan;
		}
		else if (ray->rotation < PI / 2 || ray->rotation > 3 * PI / 2)
		{
			ray->pos.x = (int)player.pos.x - (int)player.pos.x %
				GRID_SIZE + GRID_SIZE;
			ray->pos.y = (player.pos.x - ray->pos.x) * *ntan + player.pos.y;
			ray->offset.x = GRID_SIZE;
			ray->offset.y = -ray->offset.x * *ntan;
		}
	}
}

t_ray			cast_h_rays(t_player player, char **map, t_ivector2 map_size)
{
	t_ray		ray;
	t_vector2	max;
	float		atan;
	int			dof;

	dof = 0;
	setup_h_rays(&ray, &atan, player, &dof);
	while (dof < 32)
	{
		max.x = (int)(ray.pos.x / GRID_SIZE);
		max.y = (int)(ray.pos.y / GRID_SIZE);
		if (max.x < map_size.x && max.y < map_size.y && map[(int)max.y +
			(ray.rotation < PI ? (int)ray.offset.y / GRID_SIZE :
			0)][(int)max.x] == 1)
			dof = 32;
		else if (ray.pos.x < 0 || get_distance(player.pos, ray.pos) > 2000)
			stop_casting(&ray, player, &dof);
		else
		{
			ray.pos.x += ray.offset.x;
			ray.pos.y += ray.offset.y;
		}
		++dof;
	}
	return (ray);
}

t_ray			cast_v_rays(t_player player, char **map, t_ivector2 map_size)
{
	t_ray		ray;
	t_vector2	max;
	float		ntan;
	int			dof;

	dof = -1;
	setup_v_rays(&ray, &ntan, player, &dof);
	while (++dof < 32)
	{
		max.x = (int)(ray.pos.x / GRID_SIZE);
		max.y = (int)(ray.pos.y / GRID_SIZE);
		if (max.x < map_size.x && max.y < map_size.y && max.x >= 0 && max.y >=
			0 && map[(int)max.y][(int)max.x + (ray.rotation > PI / 2 &&
			ray.rotation < 3 * PI / 2 ?
			(int)ray.offset.x / GRID_SIZE : 0)] == 1)
			dof = 32;
		else if (ray.pos.y < 0 || get_distance(player.pos, ray.pos) > 2000)
			stop_casting(&ray, player, &dof);
		else
		{
			ray.pos.x += ray.offset.x;
			ray.pos.y += ray.offset.y;
		}
	}
	return (ray);
}

void			cast_rays(t_player player, int rays_count, t_game *game)
{
	t_ray				shortest_ray;
	t_raycasting_params	rc_params;
	t_display_params	drawing_params;

	init_raycasting(game, &player, &rc_params, rays_count);
	while (++rc_params.current_ray_number < rays_count)
	{
		shortest_ray = get_s_ray(player, game, &rc_params);
		get_texture(rc_params, &drawing_params, player);
		shortest_ray.length = get_distance(player.pos, shortest_ray.pos) *
			cos(rc_params.starting_rotation - shortest_ray.rotation);
		shortest_ray.length = shortest_ray.length < 1 ? 1 : shortest_ray.length;
		rc_params.line_height = (GRID_SIZE * game->config.win.y) /
								shortest_ray.length;
		rc_params.line_offset =
			game->config.win.y / 2 - rc_params.line_height / 2;
		setup_drawing_params(&drawing_params, shortest_ray, rc_params, game);
		file_to_image(drawing_params, &game->img, new_vector2(
			rc_params.current_ray_number * rc_params.line_width,
			rc_params.line_offset));
		game->depth_buffer[rc_params.current_ray_number] =
			shortest_ray.length;
		update_ray_rotation(rays_count, rc_params, &player);
	}
}
