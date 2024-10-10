/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:26:35 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/10 20:48:33 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <sys/time.h>

int	mouse_handler(int keycode, int x, int y, t_cub3d *prog)
{
	int start_time;
	struct timeval	start;
	struct timeval	cur;

	if (keycode == 1)
	{
		prog->gun_img.img = mlx_xpm_file_to_image(prog->mlx_ptr, "assets/gun_2.xpm", &prog->gun_img.width, &prog->gun_img.height);
		move_player(prog);
	}
	return (0);
}
