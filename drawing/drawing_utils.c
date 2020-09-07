/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 17:41:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/04 18:17:04 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_types.h"
#include "cub.h"

void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	buffer;

	buffer.pos.x = a->pos.x;
	buffer.pos.y = a->pos.y;
	buffer.distance = a->distance;
	a->pos.x = b->pos.x;
	a->pos.y = b->pos.y;
	a->distance = b->distance;
	b->pos.x = buffer.pos.x;
	b->pos.y = buffer.pos.y;
	b->distance = buffer.distance;
}

void	setup_sprite_array(char **map, t_game *game, t_ivector2 map_size,
	t_sprite **sprites)
{
	t_ivector2	pos;
	int			i;

	i = -1;
	pos.y = -1;
	while (++pos.y < map_size.y)
	{
		pos.x = -1;
		while (++pos.x < map_size.x)
		{
			if (map[pos.y][pos.x] == 2)
			{
				(*sprites)[++i].pos = new_vector2(
							pos.x * GRID_SIZE + GRID_SIZE / 2,
							pos.y * GRID_SIZE + GRID_SIZE / 2);
				(*sprites)[i].distance = get_distance(game->player.pos,
													(*sprites)[i].pos);
			}
		}
	}
}
