#include "cub.h"
#include "v_types.h"
#include <math.h>

double	get_distance(t_vector2 start, t_vector2 end)
{
	return (sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y)));
}
