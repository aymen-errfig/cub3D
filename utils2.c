/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:00:55 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/02 20:07:33 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_rad(double angle)
{
	return (angle * (M_PI / 180.0));
}

double	calculate_distance(t_vec v1, t_vec v2)
{
	double distance;

	distance = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
	return (distance);
}
