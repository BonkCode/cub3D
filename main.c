/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:22:46 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/03 16:58:00 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include "v_types.h"
#include "cub.h"
#include "keys.h"
#include "x11_events.h"
#include "cub.h"
#include "libft.h"

int			exit_game(void)
{
	exit(0);
}

int			main(int argc, char **argv)
{
	t_game		game;
	int			line_width;
	t_ivector2	screen_size;
	int i = 0;
	int j = 0;

	game.map_active = 0;
	game.rays_count = RAYS_COUNT;
	make_config(argc, argv, &game);
	validate_config(&game);
	while (i < game.config.map.rows)
	{
		j = 0;
		while (j < game.config.map.m)
		{
			game.config.map.map[i][j] -= (int)'0';
			if (game.config.map.map[i][j] == -16)
				game.config.map.map[i][j] += 17;
			printf ("%i ", (int)game.config.map.map[i][j]);
			++j;
		}
		printf ("\n");
		++i;
	}
	screen_size = new_ivector2(game.config.win.x, game.config.win.y);
	printf ("screen_size: %i %i\n", screen_size.x, screen_size.y);
	while (!same_value((float)screen_size.x / (float)game.rays_count,
			(int)((float)screen_size.x / (float)game.rays_count)))
		--game.rays_count;
	line_width = (int)round((float)screen_size.x / (float)game.rays_count);
	printf("RC:%i rc:%i /:%f lw:%i\n", RAYS_COUNT, game.rays_count,
			(float)screen_size.x / (float)game.rays_count, line_width);
	game.player.pos = new_vector2(game.config.player.x * GRID_SIZE + (float)GRID_SIZE / 2, game.config.player.y * GRID_SIZE + (float)GRID_SIZE / 2);
	game.img.img = NULL;
	game.player.rotation = game.config.player.dir;
	game.vars.mlx = mlx_init();
	//printf ("x:%i y:%i  %f*", game.config.player.x, game.config.player.y, game.config.player.dir);
	printf ("x:%f y:%f  %f*\n", game.player.pos.x, game.player.pos.y, game.player.rotation);
	//printf ("", );
	game.vars.win = mlx_new_window(game.vars.mlx, screen_size.x,
								game.config.win.y, "Bonk");
	mlx_loop_hook(game.vars.mlx, draw_frame, &game);
	mlx_hook(game.vars.win, KEY_PRESS, KEY_PRESS_MASK, move_player, &game);
	mlx_hook(game.vars.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
			exit_game, &game);
	mlx_loop(game.vars.mlx);
	return (0);
}
