#include "cub.h"
#include "v_types.h"
#include <math.h>
#include <stdio.h>

static double	local_abs(double x)
{
	return (x > 0 ? x : -x);
}

void	draw_sprite(t_data texture, t_data *img, t_vector2 sprite_pos, t_player player, int height, int width)
{
	t_vector2	sprite_offset;
	double	sprite_angle;
	double	sprite_dist;
	int	sprite_size;

	sprite_angle = atan2(player.pos.y - sprite_pos.y, sprite_pos.x - player.pos.x);
	sprite_angle = sprite_angle < 0 ? sprite_angle + 2 * PI : sprite_angle;
	sprite_angle = sprite_angle > 2 * PI ? sprite_angle - 2 * PI : sprite_angle;
	while (sprite_angle - player.rotation >  PI)
		sprite_angle -= 2 * PI; 
    while (sprite_angle - player.rotation < -PI)
		sprite_angle += 2 * PI;

	sprite_dist = sqrt((sprite_pos.x - player.pos.x) * (sprite_pos.x - player.pos.x) + (sprite_pos.y - player.pos.y) * (sprite_pos.y - player.pos.y));
	sprite_size = (GRID_SIZE * SCREEN_HEIGHT) / sprite_dist;
	sprite_angle = player.rotation - sprite_angle;
	sprite_angle += PI / 6;
	sprite_angle /= PI / 3;
	sprite_offset.x = SCREEN_WIDTH * sprite_angle - sprite_size / 2;
	sprite_offset.y = SCREEN_HEIGHT / 2 - sprite_size / 2;
	draw_rect(img, sprite_offset, new_vector2(sprite_offset.x + sprite_size, sprite_offset.y + sprite_size), 0x0000FF00);
	file_to_image(texture, img, sprite_offset, new_vector2(0, 0), new_vector2(sprite_size, sprite_size), width, height, 1);
}
