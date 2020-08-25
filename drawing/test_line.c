#include <mlx.h>
#include "v_types.h"
#include "cub.h"

int	draw_cas_one(t_vector2 pos1, t_vector2 pos2, t_data *img, int color)
{
  int	x;
  int	y;
  t_vector2 pos_i;

  x = pos1.x;
  while (x <= pos2.x)
    {
      y = pos1.y + ((pos2.y - pos1.y) * (x - pos1.x)) / (pos2.x - pos1.x);
	  pos_i = new_vector2(x, y);
      my_mlx_pixel_put(img, pos_i.x, pos_i.y, color);
      x++;
    }
  return (1);
}

int	draw_cas_two(t_vector2 pos1, t_vector2 pos2, t_data *img, int color)
{
  int	x;
  int	y;
  t_vector2	pos_i;

  x = pos1.y;
  while (x <= pos2.y)
    {
      y = pos1.x + ((pos2.x - pos1.x) * (x - pos1.y)) / (pos2.y - pos1.y);
      pos_i = new_vector2(x, y);
      my_mlx_pixel_put(img, pos_i.x, pos_i.y, color);
      x++;
    }
  return (1);
}

int	draw_straight_x(t_vector2 pos1, t_vector2 pos2, t_data *img, int color)
{
  int	x;
  t_vector2	pos_i;

  x = pos1.x;
  while (x <= pos2.x)
    {
      pos_i = new_vector2(x, pos1.y);
      my_mlx_pixel_put(img, pos_i.x, pos_i.y, color);
      x++;
    }
  return (1);
}

int	draw_straight_y(t_vector2 pos1, t_vector2 pos2, t_data *img, int color)
{
  int	y;
  t_vector2	pos_i;

  y = pos1.y;
  while (y <= pos2.y)
    {
      pos_i = new_vector2(pos1.x, y);
	  my_mlx_pixel_put(img, pos_i.x, pos_i.y, color);
      y++;
    }
  return (1);
}

double	my_abs(double x)
{
	return (x > 0 ? x : -x);
}

void	draw_line_test(t_vector2 pos1, t_vector2 pos2, t_data *img, int color)
{
  if (pos1.x == pos2.x)
    draw_straight_y(pos1, pos2, img, color);
  else if (pos1.x < pos2.x)
    {
      if (pos1.y == pos2.y)
	draw_straight_x(pos1, pos2, img, color);
      else if ((pos2.x - pos1.x) >= my_abs(pos2.y - pos1.y))
      	draw_cas_one(pos1, pos2, img, color);
      else if (pos2.x < pos2.y)
      	draw_cas_two(pos1, pos2, img, color);
      else
      	draw_cas_two(pos2, pos1, img, color);
    }
  if (pos1.x > pos2.x)
    {
      if (pos1.y == pos2.y)
	draw_straight_x(pos2, pos1, img, color);
      else if ((pos1.x - pos2.x) >= my_abs(pos1.y - pos2.y))
      	draw_cas_one(pos2, pos1, img, color);
      else if (pos2.x < pos2.y)
	draw_cas_two(pos1, pos2, img, color);
      else
	draw_cas_two(pos2, pos1, img, color);
    }
}