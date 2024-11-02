/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:09 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/02 14:50:08 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_window(t_cub3d *prog)
{
	mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	exit(0);
}

double	degree_to_rad(double angle)
{
	return (angle * (M_PI / 180.0));
}

int	mouse_controls(int mouse_key, int x, int y, t_cub3d *prog)
{
	if (mouse_key == 1)
	{
		prog->is_shooting = 1;
	}
	else if (mouse_key == 2)
		prog->animate_do = 1;
	return (0);
}

void	load_image(t_cub3d prog, t_data *img, char *path, int load_attribute)
{
	img->img = mlx_xpm_file_to_image(prog.mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
		return ;
	/* if (img->width * img->height == 0) */
	/*     exit(1); */
	/* if (img->width >= WIDTH ||  img->height >= HEIGHT) */
	/*     exit(2); */
	if (load_attribute == 1)
		img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
				&img->line_length, &img->endian);
}

int	main(int argc, char *argv[])
{
	t_cub3d	prog;

	// atexit(f);
	if (argc != 2)
		return (1);
	prog.assets = parse_map(argv[1]);
	if (prog.assets.err)
		exit(1);
	getData(&prog);
	prog.map = prog.assets.map;
	prog.map_size = (t_vec_i){prog.assets.map_width, prog.assets.map_height};
	prog.is_shooting = 0;
	prog.mlx_ptr = mlx_init();
	if (!prog.mlx_ptr)
		exit(3);
	prog.mlx_win = mlx_new_window(prog.mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	// to protect
	prog.img_data.img = mlx_new_image(prog.mlx_ptr, MINIPAM_W, MINIPAM_H);
	// to protect
	prog.img_data.addr = (int *)mlx_get_data_addr(prog.img_data.img,
			&prog.img_data.bits_per_pixel, &prog.img_data.line_length,
			&prog.img_data.endian);
	prog.game_img.img = mlx_new_image(prog.mlx_ptr, WIDTH, HEIGHT);
	if (!prog.game_img.img)
		exit(4);
	prog.player = player_init(&prog);
	prog.game_img.addr = (int *)mlx_get_data_addr(prog.game_img.img,
			&prog.game_img.bits_per_pixel, &prog.game_img.line_length,
			&prog.game_img.endian);
	load_image(prog, &prog.wall_img, "assets/wall.xpm", 1);
	load_image(prog, &prog.gun_img, "assets/gun1.xpm", 0);
	load_image(prog, &prog.gun_img2, "assets/gun2.xpm", 0);
	load_image(prog, &prog.door_img, "assets/door.xpm", 1);
	mlx_put_image_to_window(prog.mlx_ptr, prog.mlx_win, prog.img_data.img, 0,
		0);
	mlx_mouse_hide();
	mlx_hook(prog.mlx_win, 6, 1L << 6, mouse_handler, &prog);
	mlx_mouse_hook(prog.mlx_win, mouse_controls, &prog);
	mlx_hook(prog.mlx_win, 2, 1L << 1, keyboard_press_handler, &prog);
	mlx_loop_hook(prog.mlx_ptr, move_player, &prog);
	mlx_loop(prog.mlx_ptr);
	return (0);
}
