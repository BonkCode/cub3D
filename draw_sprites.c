/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:50:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/03 17:10:39 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "v_types.h"
#include <math.h>
#include <stdio.h>

static double	local_abs(double x)
{
	return (x > 0 ? x : -x);
}

void			draw_sprite(t_data texture, t_game *game, t_vector2 sprite_pos,
					t_ivector2 sprite_dimensions, t_win win)
{
	t_vector2	sprite_offset;
	double		sprite_angle;
	double		sprite_dist;
	t_vector2	pos_diff;
	int			sprite_size;

	sprite_angle = atan2(game->player.pos.y - sprite_pos.y,
						sprite_pos.x - game->player.pos.x);
	sprite_angle = sprite_angle < 0 ? sprite_angle + 2 * PI : sprite_angle;
	sprite_angle = sprite_angle > 2 * PI ? sprite_angle - 2 * PI : sprite_angle;
	while (sprite_angle - game->player.rotation > PI)
		sprite_angle -= 2 * PI;
	while (sprite_angle - game->player.rotation < -PI)
		sprite_angle += 2 * PI;
	pos_diff = new_vector2(sprite_pos.x - game->player.pos.x,
							sprite_pos.y - game->player.pos.y);
	sprite_dist = sqrt(pos_diff.x * pos_diff.x + pos_diff.y * pos_diff.y);
	sprite_size = (GRID_SIZE * win.y) / sprite_dist;
	sprite_angle = (game->player.rotation - sprite_angle + PI / 6) / (PI / 3);
	sprite_offset.x = game->config.win.x * sprite_angle - sprite_size / 2;
	sprite_offset.y = game->config.win.y / 2 - sprite_size / 2;
	file_to_image(texture, &game->img, sprite_offset, new_vector2(0, 0),
		new_vector2(sprite_size, sprite_size),
		sprite_dimensions.x, sprite_dimensions.y, 1, win, 0);
}
