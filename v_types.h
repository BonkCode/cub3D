//
// Created by Rockmelon Trant on 8/24/20.
//

#ifndef CUB3D_V_TYPES_H
# define CUB3D_V_TYPES_H
# define PI 3.141592
# define LINE_THRESHOLD .3
# define DR 0.0174533

typedef struct	s_vector2
{
    double		x;
    double		y;
}				t_vector2;

typedef struct	s_fvector2
{
	double		x;
	double		y;
}				t_fvector2;

typedef struct	s_vars
{
	void 		*mlx;
	void 		*win;
}				t_vars;

typedef struct  s_data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

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

typedef struct	s_game
{
	t_player	player;
	t_vars		vars;
	t_data		img;
	int			**map;
	int			map_active;
	int			rays_count;
}				t_game;

# endif
