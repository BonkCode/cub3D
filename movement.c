/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:06:31 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/04 19:51:29 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include "cub.h"
#include "v_types.h"
#include "keys.h"
#include <stdio.h>

t_vector2	get_new_pos(int key, t_player player)
{
	t_vector2	new_pos;

	new_pos = new_vector2(0, 0);
	if (key == KEY_W)
		new_pos = new_vector2(
			player.pos.x + PLAYER_SPEED * cos(player.rotation),
			player.pos.y - PLAYER_SPEED * sin(player.rotation));
	else if (key == KEY_S)
		new_pos = new_vector2(
			player.pos.x - PLAYER_SPEED * cos(player.rotation),
			player.pos.y + PLAYER_SPEED * sin(player.rotation));
	else if (key == KEY_A)
		new_pos = new_vector2(
			player.pos.x + PLAYER_SPEED * cos(player.rotation + PI / 2),
			player.pos.y - PLAYER_SPEED * sin(player.rotation + PI / 2));
	else
		new_pos = new_vector2(
			player.pos.x - PLAYER_SPEED * cos(player.rotation + PI / 2),
			player.pos.y + PLAYER_SPEED * sin(player.rotation + PI / 2));
	return (new_pos);
}

double		get_new_rotation(int key, t_player player)
{
	double	new_rotation;

	if (key == KEY_Q || key == KEY_LEFT)
		new_rotation = player.rotation + .1;
	else
		new_rotation = player.rotation - .1;
	return (new_rotation);
}

int			no_potential_collosion(char **map, t_vector2 new_pos)
{
	if ((map[(int)(new_pos.y / GRID_SIZE)]
			[(int)((new_pos.x - 1) / GRID_SIZE)] != 1) &&
		(map[(int)((new_pos.y - 1) / GRID_SIZE)]
			[(int)(new_pos.x / GRID_SIZE)] != 1) &&
		(map[(int)((new_pos.y + 1) / GRID_SIZE)]
			[(int)(new_pos.x / GRID_SIZE)] != 1) &&
		(map[(int)(new_pos.y / GRID_SIZE)]
			[(int)((new_pos.x + 1) / GRID_SIZE)] != 1))
		return (1);
	return (0);
}

int			move_player(int key, t_game *game)
{
	t_vector2	new_pos;

	new_pos = new_vector2(game->player.pos.x, game->player.pos.y);
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		new_pos = get_new_pos(key, game->player);
	else if (key == KEY_Q || key == KEY_E ||
			key == KEY_LEFT || key == KEY_RIGHT)
		game->player.rotation = get_new_rotation(key, game->player);
	else if (key == KEY_M)
		game->map_active = game->map_active == 0 ? 1 : 0;
	else if (key == KEY_ESC)
		exit(0);
	else
	{
		draw_frame(game);
		return (0);
	}
	if (game->player.rotation > 2 * PI)
		game->player.rotation -= 2 * PI;
	else if (game->player.rotation < 0)
		game->player.rotation += 2 * PI;
	if (no_potential_collosion(game->config.map.map, new_pos))
		game->player.pos = new_pos;
	return (0);
}
