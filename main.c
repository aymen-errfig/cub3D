/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:09 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/29 11:57:42 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void destroy_window(t_cub3d *prog)
{
	mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	exit(0);
}

double degree_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

int mouse_controls(int mouse_key, int x, int y, t_cub3d *prog)
{
	if (mouse_key == 1)
		prog->is_shooting = 1;
	return (0);
}
void f()
{
	system("leaks cub3d");
}
int main(int argc, char *argv[])
{
	t_cub3d	prog;

	// atexit(f);
	
	prog.assets = parse_map(argv[1]);
	if (prog.assets.err)
		exit(-1);
	getData(&prog);
	prog.map = prog.assets.map;
	prog.map_size = (t_vec_i){prog.assets.map_width, prog.assets.map_height};
	prog.is_shooting = 0;
	prog.mlx_ptr = mlx_init();
	if (!prog.mlx_ptr)
		exit(-1);
	prog.mlx_win = mlx_new_window(prog.mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	// to protect
	prog.img_data.img = mlx_new_image(prog.mlx_ptr, MINIPAM_W, MINIPAM_H);
	// to protect
	prog.img_data.addr = (int *)mlx_get_data_addr(prog.img_data.img, &prog.img_data.bits_per_pixel,
			&prog.img_data.line_length, &prog.img_data.endian);

	prog.game_img.img = mlx_new_image(prog.mlx_ptr, WIDTH, HEIGHT);
	// to protect
	prog.game_img.addr = (int *) mlx_get_data_addr(prog.game_img.img, &prog.game_img.bits_per_pixel,
			&prog.game_img.line_length, &prog.game_img.endian);
    prog.wall_img.img = mlx_xpm_file_to_image(prog.mlx_ptr, "assets/wall.xpm", &prog.wall_img.width, &prog.wall_img.height);
	if (!prog.wall_img.img)
		exit(1);
	if (prog.wall_img.width * prog.wall_img.height == 0)
		exit(1);
	prog.wall_img.addr = (int *) mlx_get_data_addr(prog.wall_img.img, &prog.wall_img.bits_per_pixel,
			&prog.wall_img.line_length, &prog.wall_img.endian);

	prog.player = player_init(&prog);
	prog.gun_img.img = mlx_xpm_file_to_image(prog.mlx_ptr, "assets/gun1.xpm", &prog.gun_img.width, &prog.gun_img.height);
	if (!prog.gun_img.img)
		exit(1);
	prog.gun_img2.img = mlx_xpm_file_to_image(prog.mlx_ptr, "assets/gun2.xpm", &prog.gun_img2.width, &prog.gun_img2.height);
	if (!prog.gun_img2.img)
		exit(1);

	prog.door_img.img = mlx_xpm_file_to_image(prog.mlx_ptr, "assets/door.xpm", &prog.door_img.width, &prog.door_img.height);
	if (!prog.door_img.img)
		exit(1);
	if (prog.door_img.width * prog.door_img.height == 0)
		exit(1);
	prog.door_img.addr = (int *) mlx_get_data_addr(prog.door_img.img, &prog.door_img.bits_per_pixel,
			&prog.door_img.line_length, &prog.door_img.endian);
	mlx_put_image_to_window(prog.mlx_ptr, prog.mlx_win, prog.img_data.img, 0, 0);
	mlx_mouse_hide();
	mlx_hook(prog.mlx_win, 6, 1L<<6, mouse_handler, &prog);
	mlx_mouse_hook(prog.mlx_win, mouse_controls, &prog);
	mlx_hook(prog.mlx_win, 2, 1L<<1, keyboard_press_handler, &prog);
	mlx_loop_hook(prog.mlx_ptr, move_player, &prog);
	mlx_loop(prog.mlx_ptr);
	return (0);
}
