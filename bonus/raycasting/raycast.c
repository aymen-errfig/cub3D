/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:04 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/13 15:26:12 by aerrfig          ###   ########.fr       */
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
	render_frame(prog, ray);
}

void	update_ray_state(t_ray *ray, int i, double angle, t_cub3d prog)
{
	ray->index = i;
	ray->is_door = 0;
	ray->o_door = 0;
	ray->is_door_h = 0;
	ray->is_door_v = 0;
	dda_algo(prog, angle, ray);
}

void	handle_door(t_cub3d *prog, t_ray *ray, t_door_info *door)
{
	if (ray->is_door && !(door->seen_door))
	{
		if (ray->distance > 50)
			prog->animate_do = door->anim > 0;
		door->seen_door = prog->animate_do;
		if (door->door_pos.x == 0 && door->door_pos.y == 0 && prog->animate_do)
		{
			door->door_pos.y = ray->door_pos.y / GRID_SIZE;
			door->door_pos.x = ray->door_pos.x / GRID_SIZE;
		}
		ray->see_beyond = floor((GRID_SIZE * HEIGHT) / ray->distance)
			* (door->anim / 100) * prog->animate_do;
	}
	if (ray->o_door)
	{
		ray->o_door_pos.x = ray->ray_pos.x / GRID_SIZE;
		ray->o_door_pos.y = ray->ray_pos.y / GRID_SIZE;
		if (prog->animate_do
			&& prog->assets.map[ray->o_door_pos.y][ray->o_door_pos.x] == 'O')
		{
			prog->assets.map[ray->o_door_pos.y][ray->o_door_pos.x] = 'D';
			prog->animate_do = 0;
		}
	}
}

void	handle_animate_door(t_cub3d *prog, t_door_info *door)
{
	door->anim += 5 * prog->animate_do;
	if ((int)floor(door->anim) >= 180 && prog->animate_do)
	{
		door->seen_door = 1;
		prog->assets.map[door->door_pos.y][door->door_pos.x] = 'O';
		door->door_pos.y = 0;
		door->door_pos.x = 0;
		door->anim = 0;
		prog->animate_do = 0;
	}
	prog->anim = door->anim;
}

void	draw_rays(t_cub3d *prog)
{
	int					i;
	double				angle;
	t_ray				ray;
	static t_door_info	door;

	i = -1;
	prog->fov_scale = 60 * (M_PI / 180);
	angle = prog->player.player_angle - prog->fov_scale / 2;
	ray.see_beyond = 0;
	door.seen_door = 0;
	while (++i < WIDTH)
	{
		angle = normalize_angle(angle);
		update_ray_state(&ray, i, angle, *prog);
		handle_door(prog, &ray, &door);
		ray.see_beyond -= (ray.see_beyond > 0);
		angle += prog->fov_scale / WIDTH;
	}
	handle_animate_door(prog, &door);
}
