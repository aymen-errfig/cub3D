/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_assests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:06:14 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/08 15:56:43 by aoukouho         ###   ########.fr       */
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
	if (load_attribute == 1)
		img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
}

int	load_texture(t_cub3d	*prog)
{
	load_image(*prog, &prog->wall_n_img, prog->assets.no, 1);
	if (prog->wall_n_img.img == NULL)
		return (clear_resource(prog, 2), 1);
	load_image(*prog, &prog->wall_e_img, "./assets/wall3.xpm", 1);
	if (prog->wall_e_img.img == NULL)
		return (clear_resource(prog, 3), 1);
	load_image(*prog, &prog->wall_s_img, "./assets/wall3.xpm", 1);
	if (prog->wall_s_img.img == NULL)
		return (clear_resource(prog, 4), 1);
	load_image(*prog, &prog->wall_w_img, "./assets/wall3.xpm", 1);
	if (prog->wall_w_img.img == NULL)
		return (clear_resource(prog, 5), 1);
	load_image(*prog, &prog->gun_img, "assets/gun1.xpm", 0);
	if (prog->gun_img.img == NULL)
		return (clear_resource(prog, 6), 1);
	load_image(*prog, &prog->gun_img2, "assets/gun2.xpm", 0);
	if (prog->gun_img2.img == NULL)
		return (clear_resource(prog, 7), 1);
	load_image(*prog, &prog->door_img, "assets/door.xpm", 1);
	if (prog->door_img.img == NULL)
		return (clear_resource(prog, 8), 1);
	return (0);
}
