/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:00:55 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 18:16:03 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_rad(double angle)
{
	return (angle * (M_PI / 180.0));
}

double	calculate_distance(t_vec v1, t_vec v2)
{
	double	distance;

	distance = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
	return (distance);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	if (x > WIDTH || y > HEIGHT || y < 0 || x < 0)
		return ;
	dst = &data->addr[y * (data->line_length / 4) + x];
	*(int *)dst = color;
}
