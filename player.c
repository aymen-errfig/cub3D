/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:13 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/10 12:12:03 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player player_init(void)
{
	t_player  player;

	player.player_pos = (t_vector) {.x = 33.0, .y=33.0};
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.player_angle = degree_to_rad(0); 
	player.speed = 4;
	return (player);
}

int	move_player(t_cub3d *prog)
{
	draw_minimap(prog);
	draw_rays(*prog);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->game_img.img, 0, 0); 
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->img_data.img, 0, 0);
	return (0);
}
