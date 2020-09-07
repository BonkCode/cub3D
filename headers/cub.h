/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:47:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/07 16:30:01 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define GRID_SIZE_X 25
# define GRID_SIZE_Y 25
# define GRID_SIZE 25
# define PLAYER_SIZE 10
# define PLAYER_SPEED 1
# define SKY_COLOR 0x005000C8
# define FLOOR_COLOR 0x00C0C0C0
# define RAYS_COUNT 1<<12
# include "v_types.h"
# include <fcntl.h>
# include "mlx/mlx.h"
# include "parsing/libft/libft.h"

t_vector2	new_vector2(double x, double y);
t_ivector2	new_ivector2(int x, int y);
double		local_abs(double x);
void		draw_rect(t_game *game, t_vector2 start, t_vector2 end,
			int color);
void		draw_rect_filled(t_game *game, t_vector2 start,
							t_vector2 end, int color);
int			draw_line(t_game *game, t_vector2 start, t_vector2 end,
			int color);
void		my_mlx_pixel_put(t_data *data, t_ivector2 pos,
			int color, t_win win);
void		cast_rays(t_player player, int rays_count, t_game *game);
t_ray		cast_v_rays(t_player player, char **map, t_ivector2 map_size);
t_ray		cast_h_rays(t_player player, char **map, t_ivector2 map_size);
void		init_textures(t_game *game, t_texture_v4 *textures);
void		update_ray_rotation(int rays_count,
		t_raycasting_params rc_params, t_player *player);
void		setup_drawing_params(t_display_params *drawing_params,
		t_ray shortest_ray, t_raycasting_params rc_params, t_game *game);
void		init_raycasting(t_game *game, t_player *player,
				t_raycasting_params *params, int rays_count);
void		get_texture_params(t_display_params *drawing_params,
								t_data texture);
t_ray		get_s_ray(t_player player, t_game *game,
				t_raycasting_params *raycasting_params);
void		get_texture(t_raycasting_params rc_params,
			t_display_params *drawing_params, t_player player);
void		get_drawing_params_offset(t_raycasting_params rc_params,
				t_display_params *drawing_params, t_ray shortest_ray);
void		stop_casting(t_ray *ray, t_player player, int *dof);
double		get_distance(t_vector2 start, t_vector2 end);
int			same_value(double x, double y);
void		file_to_image(t_display_params params,
						t_data *image, t_vector2 coordinates);
void		draw_sprite(t_display_params params, t_game *game, t_sprite sprite);
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			draw_frame(t_game *game);
int			move_player(int key, t_game *game);
void		save_bmp(int width, int height, char *data);
void		swap_sprites(t_sprite *a, t_sprite *b);
void		setup_sprite_array(char **map, t_game *game, t_ivector2 map_size,
	t_sprite **sprites);
void		game_exit(int exit_code, t_game *game);
int			cross_exit(t_game *game);
void		config_exit(int exit_code, t_config *config);

void		make_config(int argc, char **argv, t_game *game);
void		validate_config(t_game *game);
char		*ft_strdup_cub3d(char *str);
void		check_args(int argc, char **argv, t_config *config);
int			is_space(int c);
int			check_extension(char *filename, char *extension);
int			check_file(char *filename, t_config *config);
int			skip_spaces(char *line, int *i);
int			ft_atoi_cub3d(char *line, int *i);
int			parse_file(char *filename, t_config *config);
void		get_color(char *line, unsigned int *color, int *i, t_config *config);
void		parse_resolution(char *line, t_config *config, int *i);
void		texture_path(char *line, char **path, int *i, t_config *config);
void		get_map(t_config *s, char *line);
void		config_error(char *message);
void		check_borders(t_config *config);
void		check_map_cells(char **map, int rows, int cols, t_config *config);
void		fill_map(t_config *conf);
void		get_player_pos(t_config *con, char **map, int rows, int cols);
void		check_window_resolution(t_game *game);
void		final_validation(t_config *c);
void		make_screen(t_config *config);

#endif
