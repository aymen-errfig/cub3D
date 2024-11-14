/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:49:25 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 18:35:08 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(2, &s[i++], 1);
}

void	exit_failure(void)
{
	ft_error("no memory was found\n");
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
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	if (counter >= 2)
		mlx_destroy_image(prog->mlx_ptr, prog->game_img.img);
	if (counter >= 3)
		mlx_destroy_image(prog->mlx_ptr, prog->wall_n_img.img);
	if (counter >= 4)
		mlx_destroy_image(prog->mlx_ptr, prog->wall_e_img.img);
	if (counter >= 5)
		mlx_destroy_image(prog->mlx_ptr, prog->wall_s_img.img);
	if (counter >= 6)
		mlx_destroy_image(prog->mlx_ptr, prog->wall_w_img.img);
	clear_assets(prog);
	free(prog->assets.ea);
	free(prog->assets.no);
	free(prog->assets.we);
	free(prog->assets.so);
}
