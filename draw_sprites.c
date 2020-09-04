/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:50:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/04 18:02:52 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "v_types.h"
#include <math.h>
#include <stdio.h>

void			draw_sprite(t_data texture, t_game *game, t_vector2 sprite_pos,
					t_ivector2 sprite_dimensions, t_win win)
{
	t_vector2	sprite_offset;
	double		sprite_angle;
	double		sprite_dist;
	t_vector2	pos_diff;
	int			sprite_size;
	int			line_width;
	int			i;
	int			lines_count;

	line_width = (int)round((float)win.x / (float)game->rays_count);;
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
	lines_count = sprite_size / line_width;
	i = -1;
	//printf ("%i %i\n", lines_count, line_width);
	while (++i < lines_count)
	{
		if (sprite_dist < game->depth_buffer[(int)sprite_offset.x / line_width + i])
			file_to_image(texture, &game->img, new_vector2(sprite_offset.x + i * line_width, sprite_offset.y), new_vector2((float)i * (float)line_width / (float)sprite_size * (float)sprite_dimensions.x, 0),
				new_vector2(line_width, sprite_size),
				sprite_dimensions.x, sprite_dimensions.y, 1, win, 1);	
	}
}
