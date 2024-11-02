/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:35:47 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/01 13:11:40 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	if (x > WIDTH || y > HEIGHT || y < 0 || x < 0)
		return ;
	dst = &data->addr[y * (data->line_length / 4) + x];
	*(int *)dst = color;
}

void	draw_rectangle(t_data *data, t_vec v, int color, int size)
{
	int	i;
	int	j;

	i = v.x;
	j = v.y;
	while (i < v.x + size)
	{
		j = v.y;
		while (j < v.y + size)
		{
			my_mlx_pixel_put(data, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cub3d *prog)
{
	int	i;
	int	i_map;
	int	j;
	int	j_map;

	i = (int)(prog->player.player_pos.y) - M_MAP_HALF;
	j = (int)(prog->player.player_pos.x) - M_MAP_HALF;
	i_map = 0;
	draw_rectangle(&prog->img_data, (t_vec){0, 0}, 0x000000, MINIPAM_H);
	while (i_map < MINIPAM_H)
	{
		j_map = 0;
		j = (int)prog->player.player_pos.x - M_MAP_HALF;
		while (j_map < MINIPAM_H)
		{
			if (j < 0 || i < 0 || j >= GRID_SIZE * (prog->map_size.x)
				|| i >= GRID_SIZE * (prog->map_size.y))
				my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0x0000FF);
			else
			{
				if (prog->map[(int)(i / GRID_SIZE)][(int)(j
						/ GRID_SIZE)] == '1')
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0xFF0000);
				else if (prog->map[(int)(i / GRID_SIZE)][(int)(j
						/ GRID_SIZE)] == ' ')
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0x0000FF);
				else if (prog->map[(int)(i / GRID_SIZE)][(int)(j
						/ GRID_SIZE)] == 'D')
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0x00FFF0);
				else
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0xFFFFFF);
			}
			j++;
			j_map++;
		}
		i++;
		i_map++;
	}
	draw_rectangle(&prog->img_data, (t_vec){(M_MAP_HALF), (M_MAP_HALF)},
		0x00FF00, 10);
}
