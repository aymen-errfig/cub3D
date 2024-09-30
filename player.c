#include "cub3d.h"

t_player player_init(void)
{
	t_player  player;

	player.player_pos = (t_vector) {.x = 250.0, .y=150.0};
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.player_angle = degree_to_rad(0); 
	player.speed = 4;
	return (player);
}

int	move_player(t_cub3d *prog)
{
	// mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	// mlx_destroy_image(prog->mlx_ptr, prog->game_img.img);
	// prog->img_data.img = mlx_new_image(prog->mlx_ptr, MINIPAM_H, MINIPAM_W);
	// if (!prog->img_data.img)
	// 	exit(1);
	// prog->img_data.addr = mlx_get_data_addr(prog->img_data.img, &prog->img_data.bits_per_pixel,
	// 		&prog->img_data.line_length, &prog->img_data.endian);

	// prog->game_img.img = mlx_new_image(prog->mlx_ptr, 900, 700);
	// if (!prog->game_img.img)
	// 	exit(1);
	// prog->game_img.addr = mlx_get_data_addr(prog->game_img.img, &prog->game_img.bits_per_pixel,
	// 		&prog->game_img.line_length, &prog->game_img.endian);
	draw_rays(*prog);
	draw_minimap(prog);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->game_img.img, 0, 0); 
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->img_data.img, 0, 0);
	return (0);
}
