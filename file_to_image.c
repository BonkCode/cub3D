#include "cub.h"
#include "v_types.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

void	file_to_image(t_data img, t_data *image, t_vector2 coordinates, t_vector2 offset, t_vector2 size, int width, int height, int transparent, t_win win, int const_x)
{
	t_vector2	pos;
	t_vector2	scale;
	t_ivector2	closest_neighboor;
	char		*dst;
	int			color;

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	if (width == 0 || height == 0)
		return ;
	while (offset.x > width)
		offset.x -= width;
	while (offset.y > height)
		offset.y -= height;
	scale = new_vector2(size.x / width, size.y / height); 
	pos = new_vector2(-1, -1);
	if (pos.y + coordinates.y < -scale.y)
		pos.y = -scale.y - coordinates.y;
	while (++pos.y < size.y)
	{
		if (pos.y + coordinates.y > win.y)
			break;
		pos.x = -1;
		while (++pos.x < size.x)
		{
			closest_neighboor = new_ivector2(const_x == 0 ? (int)round(pos.x / scale.x) : 0, (int)round(pos.y / scale.y));
			closest_neighboor.x = closest_neighboor.x >= width ? width - 1 : closest_neighboor.x;
			closest_neighboor.y = closest_neighboor.y >= height ? height - 1 : closest_neighboor.y;
			dst = img.addr + ((closest_neighboor.y + (int)offset.y) * img.line_length + (closest_neighboor.x + (int)offset.x) * (img.bits_per_pixel / 8));
			color = *(unsigned int*)dst;
			if (get_r(color) > 0 || get_g(color) > 0 || get_b(color) > 0 || transparent == 0)
				my_mlx_pixel_put(image, new_ivector2((int)pos.x + (int)coordinates.x, (int)pos.y + (int)coordinates.y), color, win);
		}
	}
}
/*
int	draw_frame(t_game *game)
{
	t_data	texture;
	int		texture_x;
	int		texture_y;

	texture.img = mlx_xpm_file_to_image(game->vars.mlx, "test.xpm", &texture_x, &texture_y);
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
	//draw_rect_filled(&game->img, new_vector2(0, 0), new_vector2(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1), 0x0000FF00);
	file_to_image_new(texture, &game->img, new_vector2(0, 0), new_vector2(0, 0), new_vector2(64, 64), texture_x, texture_y, 1);
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
