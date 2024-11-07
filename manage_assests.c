/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_assests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:06:14 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/07 14:55:47 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_cub3d prog, t_data *img, char *path, int load_attribute)
{
	img->img = mlx_xpm_file_to_image(prog.mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
		return ;
	if (img->width == 0)
		return ;
	printf("size of image %s is %d %d\n", path, img->width, img->height);
	if (img->width >= WIDTH ||  img->height >= HEIGHT)
    {
        mlx_destroy_image(prog.mlx_ptr, img);
        img->img = NULL;
        return ;
    }
	if (load_attribute == 1)
		img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
}

int	load_texture(t_cub3d	*prog)
{
	load_image(*prog, &prog->wall_img, "assets/wall.xpm", 1);
	if (prog->wall_img.img == NULL)
		return (clear_resource(prog, 2), 1);
	load_image(*prog, &prog->gun_img, "assets/gun1.xpm", 0);
	if (prog->gun_img.img == NULL)
		return (clear_resource(prog, 3), 1);
	load_image(*prog, &prog->gun_img2, "assets/gun2.xpm", 0);
	if (prog->gun_img2.img == NULL)
		return (clear_resource(prog, 4), 1);
	load_image(*prog, &prog->door_img, "assets/door.xpm", 1);
	if (prog->door_img.img == NULL)
		return (clear_resource(prog, 5), 1);
	return (0);
}

void	destroy_window(t_cub3d *prog)
{
	mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	exit(0);
}
