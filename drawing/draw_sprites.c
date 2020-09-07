/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:50:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/07 16:21:50 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "v_types.h"
#include <math.h>
#include <stdio.h>

static void		setup_sprite_angle(double *sprite_angle,
								t_game game, t_sprite sprite)
{
	*sprite_angle = atan2(game.player.pos.y - sprite.pos.y,
						sprite.pos.x - game.player.pos.x);
	while (*sprite_angle - game.player.rotation > PI)
		*sprite_angle -= 2 * PI;
	while (*sprite_angle - game.player.rotation < -PI)
		*sprite_angle += 2 * PI;
	*sprite_angle = (game.player.rotation - *sprite_angle + PI / 6) / (PI / 3);
}

static int		get_line_width(t_game game)
{
	return ((int)round((float)game.config.win.x / (float)game.rays_count));
}

void			draw_sprite(t_display_params params, t_game *game,
							t_sprite sprite)
{
	t_vector2			sprite_offset;
	double				sprite_angle;
	int					sprite_size;
	int					line_width;
	t_ivector2			counter;

	line_width = get_line_width(*game);
	setup_sprite_angle(&sprite_angle, *game, sprite);
	sprite_size = (GRID_SIZE * game->config.win.y) / sprite.distance;
	sprite_offset.x = game->config.win.x * sprite_angle - sprite_size / 2;
	sprite_offset.y = game->config.win.y / 2 - sprite_size / 2;
	counter = new_ivector2(-1, sprite_size / line_width);
	params.transparent = 1;
	params.const_x = 1;
	params.win = game->config.win;
	params.size = new_vector2(line_width, sprite_size);
	while (++counter.x < counter.y)
	{
		params.offset = new_vector2((float)counter.x * (float)line_width /
				(float)sprite_size * (float)params.source.size.x, 0);
		if (sprite.distance <
			game->depth_buffer[(int)sprite_offset.x / line_width + counter.x])
			file_to_image(params, &game->img, new_vector2(sprite_offset.x +
				counter.x * line_width, sprite_offset.y));
	}
}
