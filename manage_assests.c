/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_assests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:06:14 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/02 20:07:58 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_cub3d prog, t_data *img, char *path, int load_attribute)
{
	img->img = mlx_xpm_file_to_image(prog.mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
		return ;
	/* if (img->width * img->height == 0) */
	/*     exit(1); */
	/* if (img->width >= WIDTH ||  img->height >= HEIGHT) */
	/*     exit(2); */
	if (load_attribute == 1)
		img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
}

int	load_texture(t_cub3d	*prog)
{
	load_image(*prog, &prog->wall_img, "assets/wall.xpm", 1);
	if (prog->wall_img.img == NULL)
		return (1);
	load_image(*prog, &prog->gun_img, "assets/gun1.xpm", 0);
	if (prog->gun_img.img == NULL)
		return (2);
	load_image(*prog, &prog->gun_img2, "assets/gun2.xpm", 0);
	if (prog->gun_img2.img == NULL)
		return (3);
	load_image(*prog, &prog->door_img, "assets/door.xpm", 1);
	if (prog->door_img.img == NULL)
		return (4);
	return (0);
}

void	destroy_window(t_cub3d *prog)
{
	mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	exit(0);
}
