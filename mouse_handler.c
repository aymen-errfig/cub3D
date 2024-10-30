/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:26:35 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/15 15:20:53 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_handler(int x, int y, t_cub3d *prog)
{
	static int	last_x = 0;
	static int	last_y = 0;
	int			center_x;
	int			center_y;
	int			delta_x;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	delta_x = x - center_x;
	prog->player.player_angle += delta_x * 0.001;
	prog->player.player_angle = normalize_angle(prog->player.player_angle);
	mlx_mouse_move(prog->mlx_win, center_x, center_y);
	last_x = center_x;
	return (0);
}
