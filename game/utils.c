/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:49:25 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/06 18:47:28 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_failure(void)
{
	write(2, "no memory was found\n", 19);
	exit(1);
}

void	clear_assets(t_cub3d *prog)
{
	int	i;

	i = 0;
	while (i < prog->assets.map_height)
	{
		free(prog->assets.map[i]);
		i++;
	}
	free(prog->assets.map);
}

void	clear_resource(t_cub3d *prog, int counter)
{
	//if (counter >= 0)
		
	if (counter >= 1)
		mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	if (counter >= 2)
		mlx_destroy_image(prog->mlx_ptr, prog->game_img.img);
	if (counter >= 3)
		mlx_destroy_image(prog->mlx_ptr, prog->wall_img.img);
	if (counter >= 4)
		mlx_destroy_image(prog->mlx_ptr, prog->gun_img.img);
	if (counter >= 5)
		mlx_destroy_image(prog->mlx_ptr, prog->gun_img2.img);
	if (counter >= 6)
		mlx_destroy_image(prog->mlx_ptr, prog->door_img.img);
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	clear_assets(prog);
}
