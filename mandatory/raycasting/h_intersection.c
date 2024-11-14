/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:33:15 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 18:01:48 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_vec	calculate_initial_h_intersection(t_cub3d prog, double angle,
					t_ray *ray)
{
	t_vec	h_intersection;

	h_intersection.y = floor(prog.player.player_pos.y / GRID_SIZE)
		* GRID_SIZE;
	if (ray->is_ray_down)
		h_intersection.y += GRID_SIZE;
	h_intersection.x = prog.player.player_pos.x + (h_intersection.y
			- prog.player.player_pos.y) / tan(angle);
	return (h_intersection);
}

static t_vec	calculate_h_step(double angle, t_ray *ray)
{
	t_vec	h_step;

	h_step.y = GRID_SIZE;
	if (ray->is_ray_up)
		h_step.y *= -1;
	h_step.x = h_step.y / tan(angle);
	if (ray->is_ray_left && h_step.x > 0)
		h_step.x *= -1;
	if (ray->is_ray_right && h_step.x < 0)
		h_step.x *= -1;
	return (h_step);
}

static int	check_h_wall_hit(t_cub3d prog, t_ray *ray, t_vec *h_intersection)
{
	int	what;

	what = is_hit_wall(prog, (t_vec){.x = h_intersection->x,
			.y = h_intersection->y - ray->is_ray_up});
	if (what == '1')
		return (1);
	return (0);
}

t_vec	h_intersection(t_cub3d prog, double angle, t_ray *ray)
{
	t_vec	h_intersection;
	t_vec	h_step;

	h_intersection = calculate_initial_h_intersection(prog, angle, ray);
	h_step = calculate_h_step(angle, ray);
	while (1)
	{
		if (check_h_wall_hit(prog, ray, &h_intersection))
			break ;
		h_intersection.x += h_step.x;
		h_intersection.y += h_step.y;
	}
	return (h_intersection);
}
