/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:13 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 15:57:01 by aerrfig          ###   ########.fr       */
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

void	draw_gun(t_cub3d *prog, int time)
{
	if (time < 5)
		mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->gun_img.img,
			(WIDTH * 0.5) - (prog->gun_img.width / 2), HEIGHT
			- prog->gun_img.height);
	else
		mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win,
			prog->gun_img2.img, (WIDTH * 0.5) - (prog->gun_img2.width / 2),
			HEIGHT - prog->gun_img2.height);
}

int	move_player(t_cub3d *prog)
{
	static int	time = 0;
	static int	time2 = 0;
	static int	sign = 1;

	mlx_clear_window(prog->mlx_ptr, prog->mlx_win);
	draw_minimap(prog);
	draw_rays(prog);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->game_img.img, 0,
		0);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->img_data.img, 0,
		0);
	time2 += 1;
	if (time2 == 420)
	{
		time2 = 0;
		sign = -sign;
	}
	if (time == 10)
		prog->is_shooting = 0;
	time = (prog->is_shooting + time) * (time < 10);
	prog->assets.cell_c += (sign * (time2 / 250));
	draw_gun(prog, time);
	return (0);
}
