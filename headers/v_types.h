/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:02:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/07 16:35:18 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_TYPES_H
# define V_TYPES_H
# define PI 3.141592
# define LINE_THRESHOLD .3
# define DR 0.0174533
# include <unistd.h>

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct		s_ivector2
{
	int		x;
	int		y;
}					t_ivector2;

typedef struct		s_vars
{
	void		*mlx;
	void		*win;
}					t_vars;

typedef struct		s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_ivector2	size;
}					t_data;

typedef struct		s_player
{
	t_vector2	pos;
	double		rotation;
	int			run;
}					t_player;

typedef struct		s_ray
{
	t_vector2	pos;
	double		rotation;
	double		length;
	t_vector2	offset;
}					t_ray;

typedef struct		s_map
{
	char		**map;
	int			x;
	int			y;
	size_t		rows;
	size_t		m;
}					t_map;

typedef struct		s_textures
{
	char *n_path;
	char *s_path;
	char *w_path;
	char *e_path;
	char *i_path;
}					t_textures;

typedef struct		s_texture_v4
{
	t_data	n;
	t_data	s;
	t_data	w;
	t_data	e;
}					t_texture_v4;

typedef struct		s_raycasting_params
{
	double				starting_rotation;
	double				current_rotation;
	float				line_height;
	float				line_offset;
	int					current_ray_number;
	int					color;
	int					line_width;
	int					fov;
	t_texture_v4		textures;
}					t_raycasting_params;

typedef	struct		s_player_pos
{
	int		x;
	int		y;
	double	dir;
}					t_player_pos;

typedef	struct		s_win
{
	int		x;
	int		y;
	void	*win;
}					t_win;

typedef	struct		s_config
{
	t_win				win;
	t_textures			textures;
	t_map				map;
	t_player_pos		player;
	unsigned int		floor;
	unsigned int		ceiling;
	int					save;
}					t_config;

typedef struct		s_sprite
{
	t_vector2	pos;
	float		distance;
}					t_sprite;

typedef struct		s_display_params
{
	t_data			source;
	t_vector2		offset;
	int				transparent;
	int				const_x;
	t_win			win;
	t_vector2		size;
}					t_display_params;

typedef struct		s_game
{
	t_config	config;
	t_player	player;
	t_vars		vars;
	t_data		img;
	int			sprites_count;
	int			map_active;
	int			rays_count;
	int			*depth_buffer;
}					t_game;

typedef struct		s_bitmap_file_header
{
	char			bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bitmap_file_header;

typedef struct		s_bitmap_image_header
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bitmap_image_header;

#endif
