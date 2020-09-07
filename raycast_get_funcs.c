/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_get_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:17:11 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/06 17:29:07 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "v_types.h"
#include <math.h>

void			init_textures(t_game *game, t_texture_v4 *textures)
{
	textures->n.img = mlx_xpm_file_to_image(game->vars.mlx,
		game->config.textures.n_path, &textures->n.size.x,
		&textures->n.size.y);
	textures->s.img = mlx_xpm_file_to_image(game->vars.mlx,
		game->config.textures.s_path, &textures->s.size.x,
		&textures->s.size.y);
	textures->w.img = mlx_xpm_file_to_image(game->vars.mlx,
		game->config.textures.w_path, &textures->w.size.x,
		&textures->w.size.y);
	textures->e.img = mlx_xpm_file_to_image(game->vars.mlx,
		game->config.textures.e_path, &textures->e.size.x,
		&textures->e.size.y);
}

void			update_ray_rotation(int rays_count,
		t_raycasting_params rc_params, t_player *player)
{
	player->rotation -= DR / (rays_count / rc_params.fov);
	if (player->rotation > 2 * PI)
		player->rotation -= 2 * PI;
	else if (player->rotation < 0)
		player->rotation += 2 * PI;
}

void			init_raycasting(t_game *game, t_player *player,
				t_raycasting_params *params, int rays_count)
{
	params->fov = game->config.win.x < 60 ? game->config.win.x : 60;
	if (!(game->depth_buffer = malloc(sizeof(int) * rays_count)))
		return ;
	params->starting_rotation = game->player.rotation;
	player->rotation += params->fov / 2 * DR;
	if (player->rotation > 2 * PI)
		player->rotation -= 2 * PI;
	else if (player->rotation < 0)
		player->rotation += 2 * PI;
	params->current_ray_number = -1;
	params->line_width = (int)round(
		(float)game->config.win.x / (float)rays_count);
	init_textures(game, &params->textures);
}

t_ray			get_s_ray(t_player player, t_game *game,
				t_raycasting_params *raycasting_params)
{
	t_ray	h_ray;
	t_ray	v_ray;

	h_ray = cast_h_rays(player, game->config.map.map,
		new_ivector2(game->config.map.m, game->config.map.rows));
	v_ray = cast_v_rays(player, game->config.map.map,
		new_ivector2(game->config.map.m, game->config.map.rows));
	if ((int)(get_distance(player.pos, h_ray.pos)) < 1)
	{
		raycasting_params->color = 0x000000FF;
		return (v_ray);
	}
	else if ((int)(get_distance(player.pos, v_ray.pos)) < 1)
	{
		raycasting_params->color = 0x0000FF00;
		return (h_ray);
	}
	else
	{
		raycasting_params->color = get_distance(player.pos, h_ray.pos) <
			get_distance(player.pos, v_ray.pos) ? 0x0000FF00 : 0x000000FF;
		return (get_distance(player.pos, h_ray.pos) <
			get_distance(player.pos, v_ray.pos) ? h_ray : v_ray);
	}
}
