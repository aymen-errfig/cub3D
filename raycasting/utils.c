/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:56:11 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/09 15:15:57 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_data	get_wall_texture(t_cub3d *prog, t_ray *ray)
{
	if (ray->is_vertical)
	{
		if (ray->is_ray_left)
			return (prog->wall_e_img);
		return (prog->wall_w_img);
	}
	if(ray->is_ray_down)
		return (prog->wall_s_img);
	return (prog->wall_n_img);
}

t_vec	calculate_texture(t_cub3d *prog, t_ray *ray, double wheight)
{
	t_vec	texture;
	t_data	img;

	img = prog->door_img;
	if (!ray->is_door)
		img = get_wall_texture(prog, ray);
	if (ray->is_vertical)
		texture.x = fmod((ray->ray_pos.y * (img.width / GRID_SIZE)), img.width);
	else
		texture.x = fmod((ray->ray_pos.x * (img.width / GRID_SIZE)), img.width);
	texture.x -= (prog->anim * 3) * (ray->is_door);
	texture.y = (double)img.height / wheight;
	return (texture);
}

int	get_pixel_color(t_cub3d *prog, t_vec texture, double ycord, t_ray ray)
{
	int		color;
	t_data	img;

	img = prog->door_img;
	if (!ray.is_door)
		img = get_wall_texture(prog, &ray);
	if (ray.is_door)
		img = prog->door_img;
	color = img.addr[(int)ycord * img.width + (int)texture.x];
	return (color);
}
