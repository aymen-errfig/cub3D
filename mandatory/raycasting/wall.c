/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:27:06 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 15:32:48 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_cieling(t_data img, double wall_start, t_vec *pixel)
{
	t_cub3d	*prog;

	prog = get_data(NULL);
	while (pixel->y < wall_start)
	{
		my_mlx_pixel_put(&img, pixel->x, pixel->y, prog->assets.cell_c);
		(pixel->y++);
	}
}

void	draw_wall(t_ray *ray, double wheight, t_vec wborder, t_vec *pixel)
{
	t_vec	texture;
	int		color;
	double	ycord;
	t_cub3d	*prog;

	prog = get_data(NULL);
	texture = calculate_texture(prog, ray, wheight);
	ycord = (wborder.x - (HEIGHT / 2) + (wheight / 2)) * texture.y;
	ycord *= (ycord > 0);
	while (pixel->y < wborder.y)
	{
		color = get_pixel_color(prog, texture, ycord, *ray);
		my_mlx_pixel_put(&prog->game_img, pixel->x, pixel->y, color);
		ycord += texture.y;
		pixel->y++;
	}
}

void	draw_floor(t_cub3d prog, t_vec *pixel)
{
	while (pixel->y < HEIGHT)
	{
		my_mlx_pixel_put(&prog.game_img, pixel->x,
			pixel->y, prog.assets.floor_c);
		pixel->y++;
	}
}

void	render_frame(t_cub3d prog, t_ray *ray)
{
	double	wheight;
	t_vec	pixel;
	t_vec	wborder;

	wheight = floor((GRID_SIZE * HEIGHT) / ray->distance);
	wborder.x = (HEIGHT / 2) - (wheight / 2);
	wborder.x *= (wborder.x > 0);
	wborder.y = (HEIGHT / 2) + (wheight / 2);
	if (wborder.y > HEIGHT)
		wborder.y = HEIGHT;
	pixel = (t_vec){ray->index, 0};
	draw_cieling(prog.game_img, wborder.x, &pixel);
	draw_wall(ray, wheight, wborder, &pixel);
	draw_floor(prog, &pixel);
}
