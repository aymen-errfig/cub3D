/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_intersection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:33:15 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 18:03:19 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_vec	calculate_initial_intersection(t_cub3d prog, double angle,
					t_ray *ray)
{
	t_vec	v_intersection;

	v_intersection.x = floor(prog.player.player_pos.x / GRID_SIZE)
		* GRID_SIZE;
	if (ray->is_ray_right)
		v_intersection.x += GRID_SIZE;
	v_intersection.y = prog.player.player_pos.y + (v_intersection.x
			- prog.player.player_pos.x) * tan(angle);
	return (v_intersection);
}

static t_vec	calculate_step(double angle, t_ray *ray)
{
	t_vec	v_step;

	v_step.x = GRID_SIZE;
	if (ray->is_ray_left)
		v_step.x *= -1;
	v_step.y = v_step.x * tan(angle);
	if (ray->is_ray_up && v_step.y > 0)
		v_step.y *= -1;
	if (ray->is_ray_down && v_step.y < 0)
		v_step.y *= -1;
	return (v_step);
}

static int	check_wall_hit(t_cub3d prog, t_ray *ray, t_vec *v_intersection)
{
	int	what;

	what = is_hit_wall(prog, (t_vec){.x = v_intersection->x - ray->is_ray_left,
			.y = v_intersection->y});
	if (what == '1')
		return (1);
	return (0);
}

t_vec	v_intersection(t_cub3d prog, double angle, t_ray *ray)
{
	t_vec	v_intersection;
	t_vec	v_step;

	v_intersection = calculate_initial_intersection(prog, angle, ray);
	v_step = calculate_step(angle, ray);
	while (1)
	{
		if (check_wall_hit(prog, ray, &v_intersection))
			break ;
		v_intersection.x += v_step.x;
		v_intersection.y += v_step.y;
	}
	return (v_intersection);
}
