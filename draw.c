/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:35:47 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/12 15:35:49 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x > WIDTH || y > HEIGHT || y <0 || x < 0)
		return ;
	int	*dst;
	dst = &data->addr[y * (data->line_length / 4) + x];
	*(int*)dst = color;
}

void draw_rectangle(t_data *data, t_vec v, int color, int size)
{
	int i = v.x ;
	int j = v.y ;
	while (i < v.x+size)
	{
		j = v.y ;
		while (j < v.y+size)
		{
			my_mlx_pixel_put(data, i,j, color);
			j++;
		}
		i++;
	}
}

void draw_minimap(t_cub3d *prog)
{
	int	i;
	int	i_map;
	int	j;
	int	j_map;

	i = (GRID_SIZE*6) - prog->player.player_pos.y;
	j = (GRID_SIZE*6) - prog->player.player_pos.x;
	i_map = MINIPAM_H;
	draw_rectangle(&prog->img_data, (t_vec){0,0}, 0x000000, MINIPAM_H);
	while (i_map > 0)
	{
		j_map = MINIPAM_H;
		j = (GRID_SIZE*6) - prog->player.player_pos.x;
		while (j_map > 0)
		{
			if (j < 0 || i < 0 || j >= GRID_SIZE*10 || i >= GRID_SIZE*10)
				my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0x0000FF);
			else
			{
				if (prog->map[9-(int)floor(i/GRID_SIZE)][9-(int)floor(j/GRID_SIZE)] == '1')
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0xFF0000);
				else if (prog->map[9-(int)floor(i/GRID_SIZE)][9-(int)floor(j/GRID_SIZE)] == '2')
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0x00FF00);
				else
					my_mlx_pixel_put(&prog->img_data, j_map, i_map, 0xFFFFFF);
			}
			j++;
			j_map--;
		}
		i++;
		i_map--;
	}
	draw_rectangle(&prog->img_data, (t_vec){(GRID_SIZE*4 - 5), (GRID_SIZE*4 - 5)}, 0x00FF00, 10);
}
