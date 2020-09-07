/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 14:11:04 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/06 16:44:53 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_borders(t_config *c)
{
	size_t	i;
	int		j;
	int		last;

	i = 0;
	while (c->map.map[i])
	{
		last = c->map.m - 1;
		if (i == 0 || i == c->map.rows - 1)
		{
			j = 0;
			while (c->map.map[i][j])
			{
				if (c->map.map[i][j] == ' ' || c->map.map[i][j] == '1')
					j++;
				else
					config_error("Error\nInvalid map\n");
			}
		}
		else if (c->map.map[i][0] != ' ' && c->map.map[i][0] != '1')
			config_error("Error\nInvalid map\n");
		else if (c->map.map[i][last] != ' ' && c->map.map[i][last] != '1')
			config_error("Error\nInvalid map\n");
		i++;
	}
}

void	check_map_cells(char **map, int rows, int cols)
{
	int i;
	int	j;

	i = 1;
	while (map[i] && i < rows - 1)
	{
		j = 1;
		while (map[i][j] && j < cols - 1)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == '2'
				|| map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
					|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
					config_error("Error\nInvalid Map\n");
			}
			j++;
		}
		i++;
	}
}

void	define_player_dir(t_config *con, char c)
{
	if (c == 'N')
		con->player.dir = PI / 2;
	else if (c == 'S')
		con->player.dir = 3 * PI / 2;
	else if (c == 'E')
		con->player.dir = 0;
	else if (c == 'W')
		con->player.dir = PI;
}

void	get_player_pos(t_config *con, char **map, int rows, int cols)
{
	int i;
	int j;

	i = 1;
	while (map[i] && i < rows - 1)
	{
		j = 0;
		while (map[i][j++] && j < cols - 1)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (con->player.x != 0 && con->player.y != 0)
					config_error("Error\n2 players on map\n");
				else
				{
					define_player_dir(con, map[i][j]);
					map[i][j] = '0';
					con->player.x = j;
					con->player.y = i;
				}
			}
		}
		i++;
	}
}

void	check_window_resolution(t_game *game)
{
	int size_x;
	int size_y;

	mlx_get_screen_size(game->vars.mlx, &size_x, &size_y);
	if (game->config.win.x > size_x)
		game->config.win.x = size_x;
	if (game->config.win.y > size_y)
		game->config.win.y = size_y;
}
