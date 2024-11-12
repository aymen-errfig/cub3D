/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:42:43 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/12 18:34:43 by aerrfig          ###   ########.fr       */
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
	get_data(prog);
	prog->map = prog->assets.map;
	prog->map_size = (t_vec_i){prog->assets.map_width, prog->assets.map_height};
	return (0);
}

int	init_game(t_cub3d *prog)
{
	prog->mlx_ptr = mlx_init();
	if (!prog->mlx_ptr)
		return (exit_failure(), 1);
	prog->mlx_win = mlx_new_window(prog->mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	if (prog->mlx_win == NULL)
		return (exit_failure(), 1);
	prog->game_img.img = mlx_new_image(prog->mlx_ptr, WIDTH, HEIGHT);
	if (prog->game_img.img == NULL)
	{
		clear_resource(prog, 1);
		return (exit_failure(), 1);
	}
	return (0);
}
