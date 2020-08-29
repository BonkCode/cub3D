#ifndef CUB_H
# define CUB_H
# define GRID_SIZE_X 25
# define GRID_SIZE_Y 25
# define GRID_SIZE 25
# define PLAYER_SIZE 10
# define PLAYER_SPEED 5
# define SCREEN_HEIGHT 1080
# define SCREEN_WIDTH 1920
# define SKY_COLOR 0x005000C8
# define FLOOR_COLOR 0x00C0C0C0
# define RAYS_COUNT 10000
# include "v_types.h"

t_vector2	new_vector2(double x, double y);
void		draw_rect(t_data *img, t_vector2 start, t_vector2 end, int color);
void		draw_rect_filled(t_data *img, t_vector2 start, t_vector2 end, int color);
int			draw_line(t_data *img, t_vector2 start, t_vector2 end, int thickness, int color);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	cast_rays(t_player player, int map[24][24], t_data *img, int rays_count, t_vars vars);
double	get_distance(t_vector2 start, t_vector2 end);
int		same_value(double x, double y);
void	file_to_image(t_data img, t_data *image, t_vector2 coordinates, t_vector2 offset, t_vector2 size, int width, int height, int transparent);
void	draw_sprite(t_data texture, t_data *img, t_vector2 sprite_pos, t_player player, int height, int width);
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif