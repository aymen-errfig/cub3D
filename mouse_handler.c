/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:26:35 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/15 14:49:32 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <sys/time.h>

int	mouse_handler(int x, int y, t_cub3d *prog)
{
	double	mouse_angle;
	t_vec	player;

	player = prog->player.player_pos;
	mouse_angle = atan2(x - player.x, y - player.y);
	mouse_angle = normalize_angle(mouse_angle);
	prog->player.player_angle = mouse_angle;
	return (0);
}
