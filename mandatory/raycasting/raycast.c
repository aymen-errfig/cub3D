/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:04 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/13 10:54:45 by aerrfig          ###   ########.fr       */
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
	if (calculate_distance(player, v_inter) < ray->distance)
	{
		ray->ray_pos = v_inter;
		ray->is_vertical = 1;
		ray->distance = calculate_distance(player, v_inter);
	}
	ray->distance *= cos(angle - prog.player.player_angle);
	render_frame(prog, ray);
}

void	draw_rays(t_cub3d *prog)
{
	int					i;
	double				angle;
	t_ray				ray;

	i = -1;
	prog->fov_scale = 60 * (M_PI / 180);
	angle = prog->player.player_angle - prog->fov_scale / 2;
	while (++i < WIDTH)
	{
		angle = normalize_angle(angle);
		ray.index = i;
		dda_algo(*prog, angle, &ray);
		angle += prog->fov_scale / WIDTH;
	}
}
