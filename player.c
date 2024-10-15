/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:13 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/14 18:07:50 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player player_init(void)
{
	t_player  player;

	player.player_pos = (t_vec) {.x = 33.0, .y=150.0};
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
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->gun_img.img, (WIDTH*0.5) - (prog->gun_img.width*0.5), HEIGHT-prog->gun_img.height);
	return (0);
}
