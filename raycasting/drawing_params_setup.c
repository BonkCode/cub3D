/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_params_setup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:27:11 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/06 17:28:11 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"
#include "cub.h"

void			setup_drawing_params(t_display_params *drawing_params,
		t_ray shortest_ray, t_raycasting_params rc_params, t_game *game)
{
	get_drawing_params_offset(rc_params, drawing_params, shortest_ray);
	drawing_params->transparent = 0;
	drawing_params->const_x = 1;
	drawing_params->win = game->config.win;
	drawing_params->size = new_vector2(rc_params.line_width,
									rc_params.line_height);
}

void			get_texture_params(t_display_params *drawing_params,
								t_data texture)
{
	drawing_params->source = texture;
	drawing_params->source.size.x = texture.size.x;
	drawing_params->source.size.y = texture.size.y;
}

void			get_texture(t_raycasting_params rc_params,
			t_display_params *drawing_params, t_player player)
{
	if (rc_params.color == 0x0000FF00 && (player.rotation <= PI &&
											player.rotation >= 0))
		get_texture_params(drawing_params, rc_params.textures.s);
	else if (rc_params.color == 0x0000FF00)
		get_texture_params(drawing_params, rc_params.textures.n);
	else if (player.rotation >= PI / 2 & player.rotation <= 3 * PI / 2)
		get_texture_params(drawing_params, rc_params.textures.e);
	else
		get_texture_params(drawing_params, rc_params.textures.w);
}

void			get_drawing_params_offset(t_raycasting_params rc_params,
				t_display_params *drawing_params, t_ray shortest_ray)
{
	if (rc_params.color == 0x0000FF00)
		drawing_params->offset = new_vector2(
			((shortest_ray.pos.x - shortest_ray.pos.x / (float)GRID_SIZE) /
			(float)GRID_SIZE * drawing_params->source.size.x), 0);
	else
		drawing_params->offset = new_vector2(
			((shortest_ray.pos.y - shortest_ray.pos.y / (float)GRID_SIZE) /
			(float)GRID_SIZE * drawing_params->source.size.y), 0);
	drawing_params->transparent = 0;
}
