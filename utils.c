#include "cub3d.h"

t_cub3d	*getData(t_cub3d *tosave)
{
	static t_cub3d	*saved;
	if (tosave != NULL)
		saved = tosave;
	return (saved);
}

int	is_hit_wall(t_cub3d prog, t_vector position)
{
	if (position.x >= MINIPAM_W || position.y >= MINIPAM_H || position.x < 0 || position.y < 0)
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
