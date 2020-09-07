/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 17:58:50 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/07 16:04:05 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdio.h>
#include "mlx.h"

static void	init_config(t_config *config)
{
	config->win.x = 0;
	config->win.y = 0;
	config->save = 0;
	config->textures.e_path = NULL;
	config->textures.i_path = NULL;
	config->textures.n_path = NULL;
	config->textures.s_path = NULL;
	config->textures.w_path = NULL;
	config->floor = 0;
	config->ceiling = 0;
	config->map.map = NULL;
	config->map.x = 0;
	config->map.y = 0;
	config->map.rows = 0;
	config->map.m = 0;
	config->player.x = 0;
	config->player.y = 0;
}

void		make_config(int argc, char **argv, t_game *game)
{
	init_config(&game->config);
	check_args(argc, argv, &game->config);
	if (argc == 2)
		parse_file(argv[1], &game->config);
	if (argc == 3)
		parse_file(argv[2], &game->config);
	if (!game->config.map.map)
		game_exit(7, game);
}

void		validate_config(t_game *game)
{
	fill_map(&game->config);
	check_window_resolution(game);
	check_borders(&game->config);
	check_map_cells(game->config.map.map, game->config.map.rows,
					game->config.map.m, &game->config);
	get_player_pos(&game->config, game->config.map.map,
					game->config.map.rows, game->config.map.m);
	final_validation(&game->config);
	ft_putstr_fd("WELL DONE\nYOU MAP IS VALID\nTIME TO PLAY A GAME!\n", 1);
}
