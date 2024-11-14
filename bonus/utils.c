/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:21 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/14 14:26:11 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*get_data(t_cub3d *tosave)
{
	static t_cub3d	*saved;

	if (tosave != NULL)
		saved = tosave;
	return (saved);
}

int	is_hit_wall(t_cub3d prog, t_vec position)
{
	int	x;
	int	y;

	if (!is_on_boundtry(position))
		return ('1');
	y = (int)floor(position.y / GRID_SIZE);
	x = (int)floor(position.x / GRID_SIZE);
	if (y >= prog.map_size.y || x >= prog.map_size.x || x < 0 || y < 0)
		return ('1');
	return (prog.map[y][x]);
}

int	is_on_boundtry(t_vec position)
{
	return (position.x < WIDTH && position.y < HEIGHT && position.x > 0
		&& position.y > 0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	rec(t_data *data, t_vec v, int color, t_vec size)
{
	int	i;
	int	j;

	i = (int)floor(v.x);
	j = (int)floor(v.y);
	while (i < (int)v.x + size.x && i < WIDTH)
	{
		j = (int)floor(v.y);
		while (j < (int)v.y + size.y && j < HEIGHT)
		{
			my_mlx_pixel_put(data, i, j, color);
			j++;
		}
		i++;
	}
}
