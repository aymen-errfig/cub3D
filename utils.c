#include "cub3d.h"

t_cub3d	*getData(t_cub3d *tosave)
{
	static t_cub3d	*saved;
	if (tosave != NULL)
		saved = tosave;
	return (saved);
}

int    is_hit_wall(t_cub3d prog, t_vector position)
{
    if (!is_on_boundtry(prog, position))
        return (1);
    int y = (int)floor(position.y / GRID_SIZE);
    int x = (int)floor(position.x / GRID_SIZE);
    return (prog.map[y][x]);
}

int    is_on_boundtry(t_cub3d prog, t_vector position)
{
    return (position.x < WIDTH && position.y < HEIGHT && position.x > 0 && position.y > 0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void rec(t_data *data, t_vector v, int color, t_vector size)
{
    int i = (int)floor(v.x);
    int j = (int)floor(v.y);
	
    while (i < (int)v.x+size.x && i < WIDTH)
    {
        j = (int)floor(v.y);
        while (j < (int)v.y+size.y && j < HEIGHT)
        {
            my_mlx_pixel_put(data, i, j, color);
            j++;
        }
        i++;
    }
 }