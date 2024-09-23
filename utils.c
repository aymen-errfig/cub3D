#include "cub3d.h"

int	is_hit_wall1(t_cub3d prog, t_vector position, int is_ray_up, int is_ray_right)
{
	if (position.x >= WIDTH || position.y >= HEIGHT || position.x < 0 || position.y < 0)
	    return (1);
	return (prog.map[(int)floor(position.y/GRID_SIZE)][(int)floor(position.x/GRID_SIZE)]);
}


int	is_hit_wall(t_cub3d prog, t_vector position)
{
	if (position.x >= WIDTH || position.y >= HEIGHT || position.x < 0 || position.y < 0)
	    return (1);
	int y = (int)floor(position.y / GRID_SIZE);
	int x = (int)floor(position.x / GRID_SIZE);  // Corrected from position.y to position.x
	return (prog.map[y][x]);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
