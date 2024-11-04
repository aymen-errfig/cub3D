/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:42:43 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/04 18:07:50 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

int	load_map(t_cub3d *prog, int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	prog->assets = parse_map(argv[1]);
	if (prog->assets.err)
		exit(1);
	getData(prog);
	prog->map = prog->assets.map;
	prog->map_size = (t_vec_i){prog->assets.map_width, prog->assets.map_height};
	prog->is_shooting = 0;
	return (0);
}

int	init_game(t_cub3d *prog)
{
	prog->mlx_ptr = mlx_init();
	if (!prog->mlx_ptr)
		return (exit_failure(), 1);
	prog->mlx_win = mlx_new_window(prog->mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	if (prog->mlx_win == NULL)
	{
		return (exit_failure(), 1);
	}
	prog->img_data.img = mlx_new_image(prog->mlx_ptr, MINIPAM_W, MINIPAM_H);
	if (prog->img_data.img == NULL)
	{
		clear_resource(prog, 0);
		return (exit_failure(), 1);
	}
	prog->img_data.addr = (int *)mlx_get_data_addr(prog->img_data.img,
			&prog->img_data.bits_per_pixel, &prog->img_data.line_length,
			&prog->img_data.endian);
	prog->game_img.img = mlx_new_image(prog->mlx_ptr, WIDTH, HEIGHT);
	if (prog->game_img.img == NULL)
	{
		clear_resource(prog, 1);
		return (exit_failure(), 1);
	}
}
