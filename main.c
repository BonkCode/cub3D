#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "v_types.h"
#include "cub.h"
#include "keys.h"
#include "x11_events.h"

void	draw_player(t_data *img, t_player player)
{
	draw_rect_filled(img, new_vector2(player.pos.x - PLAYER_SIZE / 2, player.pos.y - PLAYER_SIZE / 2), new_vector2((int)player.pos.x + PLAYER_SIZE / 2, (int)player.pos.y + PLAYER_SIZE / 2), 0x0000FF00);
	draw_line(img, player.pos, new_vector2(player.pos.x + 20 * cos(player.rotation), player.pos.y - 20 * sin(player.rotation)), 1, 0x00FF0000);
}


void	draw_map(int map[24][24], t_data *img, int map_active, t_vars vars, t_player player)
{
	t_vector2	pos;
	t_data		texture;
	int			texture_x;
	int			texture_y;

	texture.img = mlx_xpm_file_to_image(vars.mlx, "chest.xpm", &texture_x, &texture_y);
	pos.y = 0;
	while (pos.y < 24)
	{
		pos.x = 0;
		while (pos.x < 24)
		{
			if (map[(int)pos.y][(int)pos.x] > 0 && map_active)
			{
				draw_rect_filled(img, new_vector2(pos.x * GRID_SIZE_X, pos.y * GRID_SIZE_Y), new_vector2((pos.x + 1) * GRID_SIZE_X ,(pos.y + 1) * GRID_SIZE_Y), map[(int)pos.y][(int)pos.x] == 1 ? 0x00FF0000 : 0x000000FF);
				draw_rect(img, new_vector2(pos.x * GRID_SIZE_X, pos.y * GRID_SIZE_Y), new_vector2((pos.x + 1) * GRID_SIZE_X ,(pos.y + 1) * GRID_SIZE_Y), 0x00FFFFFF);
			}
			++pos.x;
		}
		++pos.y;
	}
}

void	draw_sprites(int map[24][24], t_data *img, int map_active, t_vars vars, t_player player)
{
	t_vector2	pos;
	t_data		texture;
	int			texture_x;
	int			texture_y;

	texture.img = mlx_xpm_file_to_image(vars.mlx, "test.xpm", &texture_x, &texture_y);
	pos.y = 0;
	while (pos.y < 24)
	{
		pos.x = 0;
		while (pos.x < 24)
		{
			if (map[(int)pos.y][(int)pos.x] == 2)
				draw_sprite(texture, img, new_vector2(pos.x * GRID_SIZE + GRID_SIZE / 2, pos.y * GRID_SIZE + GRID_SIZE / 2), player, texture_y, texture_x);
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
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_skybox(t_data *img)
{
	draw_rect_filled(img, new_vector2(0, 0), new_vector2(SCREEN_WIDTH, SCREEN_HEIGHT / 2), SKY_COLOR);
	draw_rect_filled(img, new_vector2(0, SCREEN_HEIGHT / 2), new_vector2(SCREEN_WIDTH, SCREEN_HEIGHT), FLOOR_COLOR);
}

int	draw_frame(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->vars.mlx, game->img.img);
	game->img.img = mlx_new_image(game->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								 &game->img.endian);
	draw_skybox(&game->img);
	cast_rays(game->player, map, &(game->img), game->rays_count, game->vars);
	if (game->map_active)
	{
		draw_player(&(game->img), game->player);
		draw_map(map, &(game->img), game->map_active, game->vars, game->player);
	}
	draw_sprites(map, &(game->img), game->map_active, game->vars, game->player);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	return (0);
}

int	move_player(int key, t_game *game)
{
	t_vector2	new_pos;
	
	if (key == KEY_W)
	{
		new_pos.x = game->player.pos.x + PLAYER_SPEED * cos(game->player.rotation);
		new_pos.y = game->player.pos.y - PLAYER_SPEED * sin(game->player.rotation);
	}
	else if (key == KEY_S)
	{
		new_pos.y = game->player.pos.y + PLAYER_SPEED * sin(game->player.rotation);
		new_pos.x = game->player.pos.x - PLAYER_SPEED * cos(game->player.rotation);
	}
	else if (key == KEY_A)
	{
		new_pos.y = game->player.pos.y - PLAYER_SPEED * sin(game->player.rotation + PI / 2);
		new_pos.x = game->player.pos.x + PLAYER_SPEED * cos(game->player.rotation + PI / 2);
	}
	else if (key == KEY_D)
	{
		new_pos.y = game->player.pos.y + PLAYER_SPEED * sin(game->player.rotation + PI / 2);
		new_pos.x = game->player.pos.x - PLAYER_SPEED * cos(game->player.rotation + PI / 2);
	}
	else if (key == KEY_Q)
		game->player.rotation += .1;
	else if (key == KEY_E)
		game->player.rotation -= .1;
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
	if ((map[(int)(new_pos.y / GRID_SIZE)][(int)((new_pos.x - 1) / GRID_SIZE)] != 1) &&
		(map[(int)((new_pos.y - 1) / GRID_SIZE)][(int)(new_pos.x / GRID_SIZE)] != 1) &&
		(map[(int)((new_pos.y + 1) / GRID_SIZE)][(int)(new_pos.x / GRID_SIZE)] != 1) &&
		(map[(int)(new_pos.y / GRID_SIZE)][(int)((new_pos.x + 1) / GRID_SIZE)] != 1))
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
	return (0);
}

int	exit_game(void)
{
	exit(0);
}

int main(void)
{
	t_game	game;

	game.map_active = 0;
	game.rays_count = RAYS_COUNT;
	while (!same_value((float)SCREEN_WIDTH / (float)game.rays_count, (int)((float)SCREEN_WIDTH / (float)game.rays_count)))
		--game.rays_count;
	int line_width = (int)round((float)SCREEN_WIDTH / (float)game.rays_count);
	printf("RC:%i rc:%i /:%f lw:%i\n", RAYS_COUNT, game.rays_count, (float)SCREEN_WIDTH / (float)game.rays_count, line_width);
	game.player.pos = new_vector2(100, 100);
	game.img.img = NULL;
	game.player.rotation = PI / 2;
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	mlx_loop_hook(game.vars.mlx, draw_frame, &game);
	mlx_hook(game.vars.win, KEY_PRESS, KEY_PRESS_MASK, move_player, &game);
	mlx_hook(game.vars.win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, exit_game, &game);
	//draw_frame(&game);
	mlx_loop(game.vars.mlx);
    return 0;
}
