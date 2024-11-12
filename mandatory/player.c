/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:13 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 18:00:41 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	player_init(t_cub3d *prog)
{
	t_player	player;

	player.player_pos.x = prog->assets.player_pos.x * GRID_SIZE + (GRID_SIZE
			/ 2);
	player.player_pos.y = prog->assets.player_pos.y * GRID_SIZE + (GRID_SIZE
			/ 2);
	if (prog->assets.player_dir == 'N')
		player.player_angle = degree_to_rad(0);
	else if (prog->assets.player_dir == 'W')
		player.player_angle = degree_to_rad(270);
	else if (prog->assets.player_dir == 'E')
		player.player_angle = degree_to_rad(90);
	else if (prog->assets.player_dir == 'S')
		player.player_angle = degree_to_rad(180);
	player.speed = 4;
	return (player);
}

int	move_player(t_cub3d *prog)
{
	mlx_clear_window(prog->mlx_ptr, prog->mlx_win);
	draw_rays(prog);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->game_img.img, 0,
		0);
	return (0);
}
