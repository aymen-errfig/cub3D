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

int main(void)
{
	t_cub3d	prog;

	getData(&prog);

	int map[7][9] = {
		{1, 1, 1, 1 ,1, 1, 1, 1 ,1},
		{1, 0, 0, 0 ,0, 0, 0, 0 ,1},
		{1, 0, 0, 0 ,1, 0, 0, 0 ,1},
		{1, 0, 1, 1, 1, 1, 1, 0 ,1},
		{1, 0, 0, 0 ,1, 0, 0, 0 ,1},
		{1, 0, 0, 0 ,0, 0, 0, 0 ,1},
		{1, 1, 1, 1 ,1, 1, 1, 1 ,1},
	};
	 // Allocate memory for rows
	prog.map = malloc(7 * sizeof(int *));
	for (int i = 0; i < 7; i++) {
         prog.map [i] = malloc(9 * sizeof(int)); 
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 9; j++) {
		    prog.map[i][j] = map[i][j];
		}
	}
	prog.mlx_ptr = mlx_init();
	if (!prog.mlx_ptr)
		exit(-1);
	prog.mlx_win = mlx_new_window(prog.mlx_ptr, WIDTH, HEIGHT, "Cub3d");
	// to protect
	prog.img_data.img = mlx_new_image(prog.mlx_ptr, MINIPAM_W, MINIPAM_H);
	// to protect
	prog.img_data.addr = mlx_get_data_addr(prog.img_data.img, &prog.img_data.bits_per_pixel,
			&prog.img_data.line_length, &prog.img_data.endian);

	prog.game_img.img = mlx_new_image(prog.mlx_ptr, WIDTH, HEIGHT);
	// to protect
	prog.game_img.addr = mlx_get_data_addr(prog.game_img.img, &prog.game_img.bits_per_pixel,
			&prog.game_img.line_length, &prog.game_img.endian);

	prog.player = player_init();
	// draw_minimap(&prog);
	// draw_rays(prog);
	move_player(&prog);
	//mlx_put_image_to_window(prog.mlx_ptr, prog.mlx_win, );prog.game_img.img, 0, 0
	mlx_put_image_to_window(prog.mlx_ptr, prog.mlx_win, prog.img_data.img, 0, 0);
	mlx_hook(prog.mlx_win, 02, 1L<<1, keyboard_press_handler, &prog);
	mlx_loop(prog.mlx_ptr);
	//free(prog.map); // 
	return (0);
}
