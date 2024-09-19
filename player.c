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
	mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	prog->img_data.img = mlx_new_image(prog->mlx_ptr, 900, 700);
	if (!prog->img_data.img)
		exit(1);
	prog->img_data.addr = mlx_get_data_addr(prog->img_data.img, &prog->img_data.bits_per_pixel,
			&prog->img_data.line_length, &prog->img_data.endian);
	draw_map(prog);
	/* draw_rays(*prog); */
	draw_rectangle(&prog->img_data, prog->player.player_pos, 0x0000FF, 20, 0);
	mlx_put_image_to_window(prog->mlx_ptr, prog->mlx_win, prog->img_data.img, 0, 0);
	return (0);
}
