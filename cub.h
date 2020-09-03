/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:47:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/03 16:40:49 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define GRID_SIZE_X 25
# define GRID_SIZE_Y 25
# define GRID_SIZE 25
# define PLAYER_SIZE 10
# define PLAYER_SPEED 5
# define SKY_COLOR 0x005000C8
# define FLOOR_COLOR 0x00C0C0C0
# define RAYS_COUNT 100000
# include "v_types.h"
# include <fcntl.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

t_vector2	new_vector2(double x, double y);
t_ivector2	new_ivector2(int x, int y);
void		draw_rect(t_data *img, t_vector2 start, t_vector2 end, int color, t_win win);
void		draw_rect_filled(t_data *img, t_vector2 start,
							t_vector2 end, int color, t_win win);
int			draw_line(t_data *img, t_vector2 start, t_vector2 end, int color, t_win win);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color, t_win win);
void		cast_rays(t_player player, char **map, t_data *img,
				int rays_count, t_vars vars, t_win win, t_ivector2 map_size, t_game game);
double		get_distance(t_vector2 start, t_vector2 end);
int			same_value(double x, double y);
void		file_to_image(t_data img, t_data *image, t_vector2 coordinates,
	t_vector2 offset, t_vector2 size, int width, int height, int transparent, t_win win);
void		draw_sprite(t_data texture, t_game *game, t_vector2 sprite_pos,
					t_ivector2 sprite_dimensions, t_win win);
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			draw_frame(t_game *game);
void		draw_skybox(t_data *img, t_win win);
void		draw_sprites(char **map, t_game game, t_ivector2 map_size);
t_vector2	get_new_pos(int key, t_player player);
double		get_new_rotation(int key, t_player player);
int			no_potential_collosion(char **map, t_vector2 new_pos);
int			move_player(int key, t_game *game);


void		make_config(int argc, char **argv, t_game *game);
void		validate_config(t_game *game);
char		*ft_strdup_cub3d(char *str);
void		check_args(int argc, char **argv, t_config *config);
int			is_space(int c);
int			check_extension(char *filename, char *extension);
int			check_file(char *filename);
int			skip_spaces(char *line, int *i);
int			ft_atoi_cub3d(char *line, int *i);
int			parse_file(char *filename, t_config *config);
void		get_color(char *line, unsigned int *color, int *i);
void		parse_resolution(char *line, t_config *config, int *i);
void		texture_path(char *line, char **path, int *i);
void		get_map(t_config *s, char *line);
void		config_error(char *message);
void		check_borders(t_config *config);
void		check_map_cells(char **map, int rows, int cols);
void		feel_map_with_love(t_config *conf);
void		get_player_pos(t_config *con, char **map, int rows, int cols);
void		check_window_resolution(t_game *game);
void		final_validation(t_config *c);
void		make_screen(t_config *config);

#endif
