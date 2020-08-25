#ifndef CUB_H
# define CUB_H
# define GRID_SIZE_X 25
# define GRID_SIZE_Y 25
# define GRID_SIZE 25
# define PLAYER_SIZE 10
# define PLAYER_SPEED 5
# include "v_types.h"

t_vector2	new_vector2(double x, double y);
void		draw_rect(t_data *img, t_vector2 start, t_vector2 end, int color);
void		draw_rect_filled(t_data *img, t_vector2 start, t_vector2 end, int color);
void		draw_line(t_data *img, t_vector2 start, t_vector2 end, int thickness, int color);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	draw_line_test(t_vector2 pos1, t_vector2 pos2, t_data *img, int color);

void	cast_rays(t_player player, int map[24][24], t_data *img);
double	get_distance(t_vector2 start, t_vector2 end);

#endif