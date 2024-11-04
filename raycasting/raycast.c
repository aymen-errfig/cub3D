/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:04 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/04 19:50:53 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



void	dda_algo(t_cub3d prog, double angle, t_ray *ray)
{
	t_vec	h_inter;
	t_vec	v_inter;
	t_vec	player;

	player = prog.player.player_pos;
	ray->is_ray_up = (angle < 0 || angle > M_PI);
	ray->is_ray_down = !ray->is_ray_up;
	ray->is_ray_left = angle > M_PI / 2 && angle < 3 * M_PI / 2;
	ray->is_ray_right = !ray->is_ray_left;
	h_inter = h_intersection(prog, angle, ray);
	v_inter = v_intersection(prog, angle, ray);
	ray->ray_pos = h_inter;
	ray->distance = calculate_distance(player, h_inter);
	ray->is_vertical = 0;
	ray->is_door = ray->is_door_h;
	if (calculate_distance(player, v_inter) < ray->distance)
	{
		ray->ray_pos = v_inter;
		ray->is_vertical = 1;
		ray->is_door = ray->is_door_v;
		ray->distance = calculate_distance(player, v_inter);
	}
	ray->distance *= cos(angle - prog.player.player_angle);
	render_frame(prog, angle, ray);
}

void	draw_rays(t_cub3d *prog)
{
	int i;
	double angle;
	t_ray ray;
	int wheight;
	static int seen_door;
	static double anim;
	static t_vec_i door_pos;

	i = -1;
	angle = prog->player.player_angle - FOV_SCALE / 2;
	ray.see_beyond = 0;
	seen_door = 0;
	while (++i < WIDTH)
	{
		angle = normalize_angle(angle);
		ray.index = i;
		ray.is_door = 0;
		ray.is_door_h = 0;
		ray.is_door_v = 0;
		dda_algo(*prog, angle, &ray);
		wheight = floor((GRID_SIZE * HEIGHT) / ray.distance);
		if (ray.is_door && !seen_door)
		{
			if (ray.distance > 50)
				prog->animate_do = anim > 0;
			seen_door = prog->animate_do;
			door_pos.y = ray.door_pos.y / GRID_SIZE;
			door_pos.x = ray.door_pos.x / GRID_SIZE;
			ray.see_beyond = wheight * (anim / 100) * prog->animate_do;
		}
		if (ray.is_vertical && ray.is_door)
			ray.is_door = 0;
		ray.see_beyond -= (ray.see_beyond > 0);
		angle += FOV_SCALE / WIDTH;
	}
	anim += (5 * seen_door) * prog->animate_do;
	if ((int)floor(anim) >= 180 && prog->animate_do)
	{
		seen_door = 1;
		prog->assets.map[door_pos.y][door_pos.x] = '0';
		door_pos.y = 0;
		door_pos.x = 0;
		anim = 0;
		prog->animate_do = 0;
	}
}
