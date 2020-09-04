#include "v_types.h"
#include "cub.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

static double	local_abs(double x)
{
	return (x > 0 ? x : -x);
}

int		same_value(double x, double y)
{
	if (local_abs(x - y) < 0.0001)
		return (1);
	return (0);
}

t_ray	cast_h_rays(t_player player, char **map, t_ivector2 map_size)
{
	t_ray		ray;
	t_vector2	max;
	float		atan;
	int			dof;

	ray.rotation = player.rotation;
	dof = 0;
	if (local_abs(tan(ray.rotation)) > 0.00001)
		atan = 1 / tan(ray.rotation);
	if (local_abs(cos(ray.rotation)) > 0.99999)
	{
		ray.pos.x = player.pos.x;
		ray.pos.y = player.pos.y;
		dof = 32;
	}
	else if (ray.rotation < PI)
	{
		ray.pos.y = (int)player.pos.y - (int)player.pos.y % GRID_SIZE;
		ray.pos.x = (player.pos.y - ray.pos.y) * atan + player.pos.x;
		ray.offset.y = -GRID_SIZE;
		ray.offset.x = -ray.offset.y * atan;
	}
	else if (ray.rotation > PI)
	{
		ray.pos.y = (int)player.pos.y - (int)player.pos.y % GRID_SIZE + GRID_SIZE;
		ray.pos.x = (player.pos.y - ray.pos.y) * atan + player.pos.x;
		ray.offset.y = GRID_SIZE;
		ray.offset.x = -ray.offset.y * atan;
	}
	while (dof < 32)
	{
		max.x = (int)(ray.pos.x / GRID_SIZE);
		max.y = (int)(ray.pos.y / GRID_SIZE);
		if (max.x < map_size.x && max.y < map_size.y && map[(int)max.y + (ray.rotation < PI ? (int)ray.offset.y / GRID_SIZE : 0)][(int)max.x] == 1)
			dof = 32;
		else if (ray.pos.x < 0)
		{
			dof = 32;
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
		}
		else if (get_distance(player.pos, ray.pos) > 2000)
		{
			dof = 32;
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
		}
		else
		{
			ray.pos.x += ray.offset.x;
			ray.pos.y += ray.offset.y;
		}
		++dof;
	}
	return (ray);
}

t_ray	cast_v_rays(t_player player, char **map, t_ivector2 map_size)
{
	int			i;
	t_ray		ray;
	t_vector2	max;
	float		ntan;
	int			dof;

	ray.rotation = player.rotation;
	i = -1;
	dof = 0;
	if (!same_value(ray.rotation, PI / 2) && !same_value(ray.rotation, 3 * PI / 2))
		ntan = tan(ray.rotation);
	else
	{
		ray.pos.x = player.pos.x;
		ray.pos.y = player.pos.y;
		dof = 32;
	}
	if (dof == 0)
	{
		if (ray.rotation > PI / 2 && ray.rotation < 3 * PI / 2)
		{
			ray.pos.x = (int)player.pos.x - (int)player.pos.x % GRID_SIZE;
			ray.pos.y = (player.pos.x - ray.pos.x) * ntan + player.pos.y;
			ray.offset.x = -GRID_SIZE;
			ray.offset.y = -ray.offset.x * ntan;
		}
		else if (ray.rotation < PI / 2 || ray.rotation > 3 * PI / 2)
		{
			ray.pos.x = (int)player.pos.x - (int)player.pos.x % GRID_SIZE + GRID_SIZE;
			ray.pos.y = (player.pos.x - ray.pos.x) * ntan + player.pos.y;
			ray.offset.x = GRID_SIZE;
			ray.offset.y = -ray.offset.x * ntan;
		}
	}
	while (dof < 32)
	{
		max.x = (int)(ray.pos.x / GRID_SIZE);
		max.y = (int)(ray.pos.y / GRID_SIZE);
		if (max.x < map_size.x && max.y < map_size.y && max.x >= 0 && max.y >= 0 && map[(int)max.y][(int)max.x + (ray.rotation > PI / 2 && ray.rotation < 3 * PI / 2 ? (int)ray.offset.x / GRID_SIZE : 0)] == 1)
			dof = 32;
		else if (ray.pos.y < 0)
		{
			dof = 32;
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
		}
		else if (get_distance(player.pos, ray.pos) > 2000)
		{
			dof = 32;
			ray.pos.x = player.pos.x;
			ray.pos.y = player.pos.y;
		}
		else
		{
			ray.pos.x += ray.offset.x;
			ray.pos.y += ray.offset.y;
		}
		++dof;
	}
	return (ray);
}

void	cast_rays(t_player player, char **map, t_data *img, int rays_count, t_vars vars, t_win win, t_ivector2 map_size, t_game *game)
{
	int		*depth_buffer;
	t_ray	h_ray;
	t_ray	v_ray;
	t_ray	shortest_ray;
	double	starting_rotation;
	float	line_height;
	float	line_offset;
	int		current_ray_number;
	int		color;
	int		drawn_count;
	int		line_width;
	int		texture_x;
	int		texture_y;
	t_data	n_texture;
	t_data	s_texture;
	t_data	w_texture;
	t_data	e_texture;
	int		fov;
	t_display_params	params;

	fov = win.x < 60 ? win.x : 60;
	if (!(depth_buffer = malloc(sizeof(int) * rays_count)))
		return ;
	starting_rotation = player.rotation;
	player.rotation += fov / 2 * DR;
	if (player.rotation > 2 * PI)
		player.rotation -= 2 * PI;
	else if (player.rotation < 0)
		player.rotation += 2 * PI;
	current_ray_number = -1;
	drawn_count = 0;
	line_width = (int)round((float)win.x / (float)rays_count);
	n_texture.img = mlx_xpm_file_to_image(vars.mlx, game->config.textures.n_path, &texture_x, &texture_y);
	s_texture.img = mlx_xpm_file_to_image(vars.mlx, game->config.textures.s_path, &texture_x, &texture_y);
	w_texture.img = mlx_xpm_file_to_image(vars.mlx, game->config.textures.w_path, &texture_x, &texture_y);
	e_texture.img = mlx_xpm_file_to_image(vars.mlx, game->config.textures.e_path, &texture_x, &texture_y);
	while (++current_ray_number < rays_count)
	{
		h_ray = cast_h_rays(player, map, map_size);
		v_ray = cast_v_rays(player, map, map_size);
		if ((int)(get_distance(player.pos, h_ray.pos)) < 1)
		{
			color = 0x000000FF;
			shortest_ray = v_ray;
		}
		else if ((int)(get_distance(player.pos, v_ray.pos)) < 1)
		{
			color = 0x0000FF00;
			shortest_ray = h_ray;
		}
		else
		{
			shortest_ray = get_distance(player.pos, h_ray.pos) < get_distance(player.pos, v_ray.pos) ? h_ray : v_ray;
			color = get_distance(player.pos, h_ray.pos) < get_distance(player.pos, v_ray.pos) ? 0x0000FF00 : 0x000000FF;
		}
		if (color == 0x0000FF00 && (player.rotation <= PI && player.rotation >= 0))
			params.source = s_texture;
		else if (color == 0x0000FF00)
			params.source = n_texture;
		else if (player.rotation >= PI / 2 & player.rotation <= 3 * PI / 2)
			params.source = e_texture;
		else
			params.source = w_texture;
		shortest_ray.length = get_distance(player.pos, shortest_ray.pos) * cos(starting_rotation - shortest_ray.rotation);
		shortest_ray.length = shortest_ray.length < 1 ? 1 : shortest_ray.length;
		line_height = (GRID_SIZE * win.y) / shortest_ray.length;
		line_offset = win.y / 2 - line_height / 2;
		if (color == 0x0000FF00)
			params.offset = new_vector2(((shortest_ray.pos.x - shortest_ray.pos.x / (float)GRID_SIZE) / (float)GRID_SIZE * texture_y), 0);
		else
			params.offset = new_vector2(((shortest_ray.pos.y - shortest_ray.pos.y / (float)GRID_SIZE) / (float)GRID_SIZE * texture_y), 0);
		params.transparent = 0;
		params.const_x = 1;
		params.win = game->config.win;
		params.source.size = new_ivector2(texture_x, texture_y);
		params.size = new_vector2(line_width, line_height);
		if (color == 0x0000FF00)
			file_to_image(params, img, new_vector2(current_ray_number * line_width, line_offset));
		else
			file_to_image(params, img, new_vector2(current_ray_number * line_width, line_offset));
		depth_buffer[current_ray_number] = shortest_ray.length;
		player.rotation -= DR / (rays_count / fov);
		if (player.rotation > 2 * PI)
			player.rotation -= 2 * PI;
		else if (player.rotation < 0)
			player.rotation += 2 * PI;
	}
	game->depth_buffer = depth_buffer;
}
