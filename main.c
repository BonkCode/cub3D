#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include "v_types.h"
#include "cub.h"
#include "keys.h"

void	draw_player(t_data *img, t_player player)
{
	draw_rect_filled(img, new_vector2(player.pos.x - PLAYER_SIZE / 2, player.pos.y - PLAYER_SIZE / 2), new_vector2((int)player.pos.x + PLAYER_SIZE / 2, (int)player.pos.y + PLAYER_SIZE / 2), 0x0000FF00);
	draw_line(img, player.pos, new_vector2(player.pos.x + 20 * cos(player.rotation), player.pos.y - 20 * sin(player.rotation)), 1, 0x00FF0000);
}


void	draw_map(int map[24][24], t_data *img)
{
	t_vector2	pos;

	pos.y = 0;
	while (pos.y < 24)
	{
		pos.x = 0;
		while (pos.x < 24)
		{
			if (map[(int)pos.y][(int)pos.x] != 0)
				draw_rect_filled(img, new_vector2(pos.x * GRID_SIZE_X, pos.y * GRID_SIZE_Y), new_vector2((pos.x + 1) * GRID_SIZE_X ,(pos.y + 1) * GRID_SIZE_Y), 0x00FF0000);
			draw_rect(img, new_vector2(pos.x * GRID_SIZE_X, pos.y * GRID_SIZE_Y), new_vector2((pos.x + 1) * GRID_SIZE_X ,(pos.y + 1) * GRID_SIZE_Y), 0x00FFFFFF);
			++pos.x;
		}
		++pos.y;
	}
}

int map[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	draw_frame(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->vars.mlx, game->img.img);
	game->img.img = mlx_new_image(game->vars.mlx, 800, 600);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								 &game->img.endian);
	draw_player(&(game->img), game->player);
	draw_map(map, &(game->img));
	cast_rays(game->player, map, &(game->img));
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	return (0);
}

int	move_player(int key, t_game *game)
{
	if (key == KEY_W)
	{
		game->player.pos.y -= PLAYER_SPEED * sin(game->player.rotation);
		game->player.pos.x += PLAYER_SPEED * cos(game->player.rotation);
	}
	else if (key == KEY_S)
	{
		game->player.pos.y += PLAYER_SPEED * sin(game->player.rotation);
		game->player.pos.x -= PLAYER_SPEED * cos(game->player.rotation);
	}
	else if (key == KEY_A)
	{
		game->player.pos.y -= PLAYER_SPEED * sin(game->player.rotation + PI / 2);
		game->player.pos.x += PLAYER_SPEED * cos(game->player.rotation + PI / 2);
	}
	else if (key == KEY_D)
	{
		game->player.pos.y += PLAYER_SPEED * sin(game->player.rotation + PI / 2);
		game->player.pos.x -= PLAYER_SPEED * cos(game->player.rotation + PI / 2);
	}
	else if (key == KEY_Q)
		game->player.rotation += .1;
	else if (key == KEY_E)
		game->player.rotation -= .1;
	if (game->player.rotation > 2 * PI)
		game->player.rotation -= 2 * PI;
	else if (game->player.rotation < 0)
		game->player.rotation += 2 * PI;
	draw_frame(game);
	return (0);
}

int main(void)
{
	t_game	game;

	game.player.pos = new_vector2(100, 100);
	game.player.rotation = 0;
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, 800, 600, "Hello world!");
	mlx_loop_hook(game.vars.mlx, draw_frame, &game);
	mlx_hook(game.vars.win, 2, 1L<<0, move_player, &game);
	mlx_loop(game.vars.mlx);
    return 0;
}
