/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:02:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/03 14:48:38 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_TYPES_H
# define V_TYPES_H
# define PI 3.141592
# define LINE_THRESHOLD .3
# define DR 0.0174533

typedef struct	s_vector2
{
	double		x;
	double		y;
}				t_vector2;

typedef struct	s_ivector2
{
	int		x;
	int		y;
}				t_ivector2;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_player
{
	t_vector2	pos;
	double		rotation;
}				t_player;

typedef struct	s_ray
{
	t_vector2	pos;
	double		rotation;
	double		length;
	t_vector2	offset;
}				t_ray;

typedef struct	s_map
{
	char	**map;
	int		x;
	int		y;
	int		rows;
	int		m;
}				t_map;

typedef struct	s_textures
{
	char *n_path;
	char *s_path;
	char *w_path;
	char *e_path;
	char *i_path;
}				t_textures;

typedef	struct	s_player_pos
{
	int		x;
	int		y;
	double	dir;
}				t_player_pos;

typedef	struct	s_win
{
	int		x;
	int		y;
	void	*win;
}				t_win;

typedef	struct	s_config
{
	t_win				win;
	t_textures			textures;
	t_map				map;
	t_player_pos		player;
	unsigned int		floor;
	unsigned int		ceiling;
	int					save;
}				t_config;

typedef struct	s_game
{
	t_config	config;
	t_player	player;
	t_vars		vars;
	t_data		img;
	int			map_active;
	int			rays_count;
}				t_game;

#endif
