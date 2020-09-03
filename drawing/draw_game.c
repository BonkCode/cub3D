/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:04:40 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/03 16:40:42 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include "cub.h"
#include <stdio.h>
#include "v_types.h"

void		draw_player(t_data *img, t_player player, t_win win)
{
	t_vector2	start;
	t_vector2	end;
	t_vector2	view_vector;
	int			player_color;
	int			ray_color;

	start = new_vector2((int)player.pos.x - PLAYER_SIZE / 2,
						(int)player.pos.y - PLAYER_SIZE / 2);
	end = new_vector2((int)player.pos.x + PLAYER_SIZE / 2,
					(int)player.pos.y + PLAYER_SIZE / 2);
	player_color = 0x0000FF00;
	ray_color = 0x00FF0000;
	view_vector = new_vector2(player.pos.x + 20 * cos(player.rotation),
							player.pos.y - 20 * sin(player.rotation));
	draw_rect_filled(img, start, end, player_color, win);
	draw_line(img, player.pos, view_vector, ray_color, win);
}

void		draw_map(char **map, t_data *img, int map_active, t_vars vars, t_win win, t_ivector2 map_size)
{
	t_ivector2	pos;
	t_vector2	start;
	t_vector2	end;
	int			wall_color;
	int			size;

	size = 500 / map_size.x > map_size.y ? map_size.x : map_size.y;
	pos.y = 0;
	while (pos.y < map_size.y)
	{
		pos.x = 0;
		while (pos.x < map_size.x)
		{
			if (map[pos.y][pos.x] > 0 && map_active)
			{
				start = new_vector2(pos.x * size,
									pos.y * size);
				end = new_vector2((pos.x + 1) * size,
								(pos.y + 1) * size);
				wall_color = map[pos.y][pos.x] == 1 ? 0x00FF0000 : 0x000000FF;
				draw_rect_filled(img, start, end, wall_color, win);
				draw_rect(img, start, end, 0x00FFFFFF, win);
			}
			++pos.x;
		}
		++pos.y;
	}
}

void		draw_sprites(char **map, t_game game, t_ivector2 map_size)
{
	t_ivector2	pos;
	t_data		texture;
	t_ivector2	texture_size;
	t_vector2	sprite_pos;

	texture.img = mlx_xpm_file_to_image(game.vars.mlx, "test.xpm",
								&texture_size.x, &texture_size.y);
	pos.y = 0;
	while (pos.y < map_size.y)
	{
		pos.x = 0;
		while (pos.x < map_size.x)
		{
			if (map[pos.y][pos.x] == 2)
			{
				sprite_pos = new_vector2(pos.x * GRID_SIZE + GRID_SIZE / 2,
							pos.y * GRID_SIZE + GRID_SIZE / 2);
				draw_sprite(texture, &game, sprite_pos, texture_size, game.config.win);
			}
			++pos.x;
		}
		++pos.y;
	}
}

void		draw_skybox(t_data *img, t_win win)
{
	t_vector2	sky_start;
	t_vector2	sky_end;
	t_vector2	floor_start;
	t_vector2	floor_end;

	sky_start = new_vector2(0, 0);
	sky_end = new_vector2(win.x, win.y / 2);
	floor_start = new_vector2(0, win.y / 2);
	floor_end = new_vector2(win.x, win.y);
	draw_rect_filled(img, sky_start, sky_end, SKY_COLOR, win);
	draw_rect_filled(img, floor_start, floor_end, FLOOR_COLOR, win);
}

int			draw_frame(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->vars.mlx, game->img.img);
	game->img.img = mlx_new_image(game->vars.mlx, game->config.win.x, game->config.win.y);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
									&game->img.line_length, &game->img.endian);
	draw_skybox(&game->img, game->config.win);
	cast_rays(game->player, game->config.map.map, &(game->img), game->rays_count, game->vars, game->config.win, new_ivector2(game->config.map.m, game->config.map.rows), *game);
	if (game->map_active)
	{
	//	draw_player(&(game->img), game->player, game->config.win);
		draw_map(game->config.map.map, &game->img, game->map_active, game->vars, game->config.win, new_ivector2(game->config.map.m, game->config.map.rows));
	}
	draw_sprites(game->config.map.map, *game, new_ivector2(game->config.map.m, game->config.map.rows));
	mlx_do_sync(game->vars.mlx);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win,
							game->img.img, 0, 0);
	return (0);
}
