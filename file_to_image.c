#include "cub.h"
#include "v_types.h"
#include <mlx.h>
#include <stdio.h>
#include <math.h>

void	file_to_image(t_data img, t_data *image, t_vector2 coordinates, t_vector2 offset, t_vector2 size, int width, int height, int transparent)
{
	t_vector2	pos;
	t_vector2	file_pos;
	char	*dst;
	int		color;
	int		prev_x;
	t_vector2	size_diff;
	t_vector2	current_diff;

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while (offset.x > width)
		offset.x -= width;
	while (offset.y > height)
		offset.y -= height;
	pos = new_vector2(-1, -(size.y / (float)height));
	file_pos = new_vector2(offset.x - 1, offset.y - 1);
	size_diff = new_vector2(size.x - width, size.y - height);
	current_diff.y = size_diff.y;
	while ((int)pos.y < (int)size.y)
	{
		++file_pos.y;
		file_pos.y = file_pos.y >= height ? 0 : file_pos.y;
		pos.y += size.y / (float)height;
		pos.x = -1;
		file_pos.x = offset.x - 1;
		while ((int)pos.x < (int)size.x)
		{
			prev_x = pos.x;
			++file_pos.x;
			while (pos.x < prev_x + size.x / (float)width)
			{
				++pos.x;
				if ((int)pos.y + (int)coordinates.y < -(size.y / (float)height))
					continue ;
				else if ((int)pos.y + (int)coordinates.y > SCREEN_HEIGHT)
					break ;
				file_pos.x = file_pos.x >= width ? 0 : file_pos.x;
				dst = img.addr + ((int)file_pos.y * img.line_length + (int)file_pos.x * (img.bits_per_pixel / 8));
				color = *(unsigned int*)dst;
				if (get_r(color) > 0 || get_g(color) > 0 || get_b(color) > 0 || transparent == 0)
				{
					draw_line(image, new_vector2((int)pos.x + (int)coordinates.x, (int)pos.y + (int)coordinates.y), new_vector2((int)pos.x + (int)coordinates.x, (int)ceil(pos.y) + (int)coordinates.y + size.y / (float)height), 1, color);
					my_mlx_pixel_put(image, (int)pos.x + (int)coordinates.x, (int)pos.y + (int)coordinates.y, color);
				}
			}
		}
	}
}
/*
int	draw_frame(t_game *game)
{
	t_data	texture;
	int		texture_x;
	int		texture_y;

	texture.img = mlx_xpm_file_to_image(game->vars.mlx, "chest.xpm", &texture_x, &texture_y);
	if (game->img.img)
		mlx_destroy_image(game->vars.mlx, game->img.img);
	game->img.img = mlx_new_image(game->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length,
								 &game->img.endian);

	//for (int i = 0; i < SCREEN_WIDTH; i += 4)
	//{
	//	file_to_image(texture, &game->img, new_vector2(i, 0), new_vector2(i, 0), new_vector2(4, 1100), texture_x, texture_y);
		//draw_rect(&game->img, new_vector2(i, 0), new_vector2(i + 4, 100), 0x0000FF00);
	//}
	//draw_line(&game->img, new_vector2(100, 100), new_vector2(101, 1000), 1, 0x000000FF);
	draw_rect_filled(&game->img, new_vector2(0, 0), new_vector2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1), 0x0000FF00);
	file_to_image(texture, &game->img, new_vector2(0, 0), new_vector2(0, 0), new_vector2(1000, 501), texture_x, texture_y, 1);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->img.img, 0, 0);
	return (0);
}

int main(void)
{
	t_game	game;

	game.map_active = 0;
	game.rays_count = RAYS_COUNT;
	while (!same_value((float)SCREEN_WIDTH / (float)game.rays_count, (int)((float)SCREEN_WIDTH / (float)game.rays_count)))
		--game.rays_count;
	//printf("RC:%i rc:%i /:%f\n", RAYS_COUNT, game.rays_count, (float)SCREEN_WIDTH / (float)game.rays_count);
	game.player.pos = new_vector2(100, 100);
	game.img.img = 0;
	game.player.rotation = 3.5203;
	game.vars.mlx = mlx_init();
	game.vars.win = mlx_new_window(game.vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!");
	draw_frame(&game);
	//mlx_loop_hook(game.vars.mlx, draw_frame, &game);
	//mlx_key_hook(game.vars.win, move_player, &game);
	//mlx_key_hook(game.vars.win, move_player, &game);
	//mlx_hook(game.vars.win, 2, 1L<<0, move_player, &game);
	mlx_loop(game.vars.mlx);
    return 0;
}
*/