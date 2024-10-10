/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:27:06 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/10 10:26:04 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_cieling(t_data img, double wall_start, t_vector *pixel)
{
	while (pixel->y < wall_start)
	{
		my_mlx_pixel_put(&img, pixel->x, pixel->y, 0x87CEEB);
		(pixel->y++);
	}
}

void	draw_wall_texture(t_cub3d prog, t_ray *ray, double wall_height, t_vector wall_border, t_vector *pixel)
{
	t_vector texture;
	int color;
	double ycord;

	if (ray->is_vertical)
		texture.x = fmod((ray->ray_pos.y * (prog.wall_img.width/GRID_SIZE)), prog.wall_img.width);
    	else
		texture.x = fmod((ray->ray_pos.x * (prog.wall_img.width/GRID_SIZE)), prog.wall_img.width);
    	texture.y = (double)prog.wall_img.width / wall_height;
    	ycord = (wall_border.x - (HEIGHT / 2) + (wall_height / 2)) * texture.y;

    	ycord *= (ycord > 0);
    	while (pixel->y < wall_border.y)
    	{
	    color = prog.wall_img.addr[(int) ycord * prog.wall_img.width + (int)texture.x];
	    my_mlx_pixel_put(&prog.game_img,  pixel->x, pixel->y, color);
	    ycord += texture.y;
	    pixel->y++;
    	}
}

void	draw_floor(t_cub3d prog, double wall_end, t_vector *pixel)
{
    while (pixel->y < HEIGHT)
    {
	    my_mlx_pixel_put(&prog.game_img,  pixel->x, pixel->y, 0x136d15);
	   (pixel->y++);
    }
}

void render_frame(t_cub3d prog, double angle, t_ray *ray)
{
	double wall_height;
	t_vector pixel;
	t_vector wall_border;
	t_vector texture;

	wall_height = floor((GRID_SIZE * HEIGHT) / ray->distance); 
        wall_border.x =  (HEIGHT/2) - (wall_height/2);
        wall_border.x *= (wall_border.x > 0);
        wall_border.y =  (HEIGHT/2) + (wall_height/2);
        if (wall_border.y > HEIGHT)
		wall_border.y = HEIGHT;
	pixel = (t_vector){ray->index, 0};
	draw_cieling(prog.game_img, wall_border.x, &pixel);
	draw_wall_texture(prog, ray, wall_height, wall_border, &pixel);
	draw_floor(prog, wall_border.y, &pixel);
}
