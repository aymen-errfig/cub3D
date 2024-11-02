/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:13 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/02 14:57:15 by aerrfig          ###   ########.fr       */
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
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.player_angle = degree_to_rad(0);
	player.speed = 4;
	return (player);
}

int	move_player(t_cub3d *prog)
{
	static int	time = 0;

	mlx_clear_window(prog->mlx_ptr, prog->mlx_win);
	draw_minimap(prog);
	draw_rays(prog);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->game_img.img, 0,
		0);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->img_data.img, 0,
		0);
	time += prog->is_shooting;
	if (time == 10)
	{
		prog->is_shooting = 0;
		time = 0;
	}
	if (time < 5)
		mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->gun_img.img,
			(WIDTH * 0.5) - (prog->gun_img.width / 2), HEIGHT
			- prog->gun_img.height);
	else
		mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win,
			prog->gun_img2.img, (WIDTH * 0.5) - (prog->gun_img2.width / 2),
			HEIGHT - prog->gun_img2.height);
	return (0);
}
