#include "cub3d.h"

int	is_hit_wall(t_cub3d prog, t_vector position)
{
	if (position.x >= WIDTH || position.y >= HEIGHT || position.x < 0 || position.y < 0)
	    return (1);
	return (prog.map[(int)floor(position.y/GRID_SIZE)][(int)floor(position.x/GRID_SIZE)]);
}
