/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:35:52 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/29 14:00:16 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_resource(t_cub3d *prog)
{
	free(prog->map);
	destroy_window(prog);
	exit(1);
}

int	is_not_valid_key(int keycode)
{
	return (keycode != 258 && keycode != UP_KEYCODE && keycode != DOWN_KEYCODE
		&& keycode != RIGHT_KEYCODE && keycode != LEFT_KEYCODE && keycode != 53
		&& keycode != RIGHT_ARROW_KEYCODE && keycode != LEFT_ARROW_KEYCODE
		&& keycode != SPACE);
}

int	handle_player_movement(t_cub3d *prog, int rl_direction, int ud_direction)
{
	t_vec	new_pos;
	int		speed;

	speed = 5;
	new_pos = prog->player.player_pos;
	if (ud_direction != 0)
	{
		new_pos.x += ((cos(prog->player.player_angle) * ud_direction) * speed);
		new_pos.y += ((sin(prog->player.player_angle) * ud_direction) * speed);
	}
	if (rl_direction != 0)
	{
		new_pos.x += ((sin(prog->player.player_angle) * rl_direction) * speed);
		new_pos.y -= ((cos(prog->player.player_angle) * rl_direction) * speed);
	}
	if (is_hit_wall(*prog, new_pos) == '1' || is_hit_wall(*prog,
			new_pos) == 'D')
		return (1);
	prog->player.player_pos = new_pos;
	return (0);
}

void	handle_player_rotation(t_cub3d *prog, int keycode)
{
	int	move_angle;

	move_angle = 0;
	if (keycode == RIGHT_ARROW_KEYCODE)
		move_angle = 1;
	else if (keycode == LEFT_ARROW_KEYCODE)
		move_angle = -1;
	prog->player.player_angle += move_angle * degree_to_rad(3);
}

int	keyboard_press_handler(int keycode, t_cub3d *prog)
{
	int		move_angle;
	t_vec	new_pos;
	int		rl_direction;
	int		ud_direction;

	if (is_not_valid_key(keycode))
		return (1);
	if (keycode == 53)
		clear_resource(prog);
	ud_direction = 0;
	rl_direction = 0;
	ud_direction = ((keycode == UP_KEYCODE) * 1);
	ud_direction += ((keycode == DOWN_KEYCODE) * -1);
	rl_direction = ((keycode == RIGHT_KEYCODE) * 1);
	rl_direction += ((keycode == LEFT_KEYCODE) * -1);
	handle_player_movement(prog, rl_direction, ud_direction);
	handle_player_rotation(prog, keycode);
	return (0);
}
