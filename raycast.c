/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:04 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/02 17:05:28 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double calculate_distance(t_vec v1, t_vec v2)
{
	double distance;

	distance = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
	return (distance);
}

t_vec horizontal_intersection(t_vec current, t_cub3d prog, double angle,
							  t_ray *ray)
{
	t_vec h_intersection;
	t_vec h_step;
	int what;

	h_intersection.y = floor(prog.player.player_pos.y / GRID_SIZE) * GRID_SIZE;
	if (ray->is_ray_down)
		h_intersection.y += GRID_SIZE;
	h_intersection.x = prog.player.player_pos.x + (h_intersection.y - prog.player.player_pos.y) / tan(angle);
	h_step.y = GRID_SIZE;
	if (ray->is_ray_up)
		h_step.y *= -1;
	h_step.x = h_step.y / tan(angle);
	if (ray->is_ray_left && h_step.x > 0)
		h_step.x *= -1;
	if (ray->is_ray_right && h_step.x < 0)
		h_step.x *= -1;
	while (1)
	{
		what = is_hit_wall(prog, (t_vec){.x = h_intersection.x,
										 .y = h_intersection.y - ray->is_ray_up});
		if (what == '1' || (what == 'D' && !ray->see_beyond))
		{
			if (what == 'D')
			{
				ray->is_door_h = 1;
				ray->door_pos.x = h_intersection.x;
				ray->door_pos.y = h_intersection.y - ray->is_ray_up;
			}
			break;
		}
		current = h_intersection;
		h_intersection.x += h_step.x;
		h_intersection.y += h_step.y;
	}
	return (h_intersection);
}

t_vec vertical_intersection(t_vec current, t_cub3d prog, double angle,
							t_ray *ray)
{
	t_vec v_intersection;
	t_vec v_step;
	int what;

	v_intersection.x = floor(prog.player.player_pos.x / GRID_SIZE) * GRID_SIZE;
	if (ray->is_ray_right)
		v_intersection.x += GRID_SIZE;
	v_intersection.y = prog.player.player_pos.y + (v_intersection.x - prog.player.player_pos.x) * tan(angle);
	v_step.x = GRID_SIZE;
	if (ray->is_ray_left)
		v_step.x *= -1;
	v_step.y = v_step.x * tan(angle);
	if (ray->is_ray_up && v_step.y > 0)
		v_step.y *= -1;
	if (ray->is_ray_down && v_step.y < 0)
		v_step.y *= -1;
	while (1)
	{
		what = is_hit_wall(prog, (t_vec){.x = v_intersection.x - ray->is_ray_left, .y = v_intersection.y});
		if (what == '1' || (what == 'D' && !ray->see_beyond))
		{
			if (what == 'D')
			{
				ray->is_door_v = 1;
				ray->door_pos.x = v_intersection.x - ray->is_ray_left;
				ray->door_pos.y = v_intersection.y;
			}
			break;
		}
		v_intersection.x += v_step.x;
		v_intersection.y += v_step.y;
	}
	return (v_intersection);
}

void dda_algo(t_cub3d prog, double angle, t_ray *ray)
{
	t_vec h_intersection;
	t_vec v_intersection;
	t_vec player;

	player = prog.player.player_pos;
	ray->is_ray_up = (angle < 0 || angle > M_PI);
	ray->is_ray_down = !ray->is_ray_up;
	ray->is_ray_left = angle > M_PI / 2 && angle < 3 * M_PI / 2;
	ray->is_ray_right = !ray->is_ray_left;
	h_intersection = horizontal_intersection(player, prog, angle, ray);
	v_intersection = vertical_intersection(player, prog, angle, ray);
	ray->ray_pos = h_intersection;
	ray->distance = calculate_distance(player, h_intersection);
	ray->is_vertical = 0;
	ray->is_door = ray->is_door_h;
	if (calculate_distance(player, v_intersection) <= ray->distance)
	{
		ray->ray_pos = v_intersection;
		ray->is_vertical = 1;
		ray->is_door = ray->is_door_v;
		ray->distance = calculate_distance(player, v_intersection);
	}
	ray->distance *= cos(angle - prog.player.player_angle);
	render_frame(prog, angle, ray);
}

void draw_rays(t_cub3d *prog)
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
