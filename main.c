/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:09 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/07 16:16:59 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_controls(int mouse_key, int x, int y, t_cub3d *prog)
{
	(void)x;
	(void)y;
	if (mouse_key == 1)
		prog->is_shooting = 1;
	return (0);
}

void	f()
{
	system("leaks  cub3d");
}

int	main(int argc, char *argv[])
{
	t_cub3d	prog;

	atexit(f);
	load_map(&prog, argc, argv);
	init_game(&prog);
	prog.player = player_init(&prog);
	prog.game_img.addr = (int *)mlx_get_data_addr(prog.game_img.img,
			&prog.game_img.bits_per_pixel, &prog.game_img.line_length,
			&prog.game_img.endian);
	if(load_texture(&prog))
		exit(1);
	mlx_put_image_to_window(prog.mlx_ptr, prog.mlx_win, prog.img_data.img, 0, 0);
	mlx_mouse_hide();
	mlx_hook(prog.mlx_win, 6, 1L << 6, mouse_handler, &prog);
	mlx_mouse_hook(prog.mlx_win, mouse_controls, &prog);
	mlx_hook(prog.mlx_win, 2, 1L << 1, keyboard_press_handler, &prog);
	mlx_loop_hook(prog.mlx_ptr, move_player, &prog);
	mlx_loop(prog.mlx_ptr);
	return (0);
}
