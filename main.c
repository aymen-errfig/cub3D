#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rectangle(t_data *data, t_vector v, int color, int size, int is_line)
{
	int i = v.x + (2 * !is_line);
	int j = v.y + (2 * !is_line);
	while (i < v.x+size)
	{
		j = v.y + (2 * !is_line);
		while (j < v.y+size)
		{
			my_mlx_pixel_put(data, i,j, color);
			j++;
		}
		i++;
	}
}

double degree_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

void draw_map(t_cub3d *prog)
{
	int i = 0;
	int j = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 9)
		{
			if (prog->map[i][j] == 1)
			{
				t_vector rectange = (t_vector) {.x = GRID_SIZE*j, .y=GRID_SIZE*i};
				draw_rectangle(&prog->img_data, rectange, 0xFF0000, GRID_SIZE, 0);
			}
			j++;
		}
		i++;
	}
}


void destroy_window(t_cub3d *prog)
{
	mlx_destroy_image(prog->mlx_ptr, prog->img_data.img);
	mlx_destroy_window(prog->mlx_ptr, prog->mlx_win);
	free(prog); // 
	exit(0);
}

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


int	keyboard_press_handler(int keycode, t_cub3d *prog)
{
	int speed;
	double speed_sin;
	double speed_cos;
	t_vector new_pos;

	(void)prog;
	if (keycode != 258 && keycode != UP_KEYCODE && keycode != DOWN_KEYCODE && keycode != RIGHT_KEYCODE && 
	keycode != LEFT_KEYCODE && keycode != 53)
		return (1);
	if (keycode == 53)
	{
		/* destroy_window(prog); */
		exit(1);
	}
	speed = 20;
	speed_sin = speed * sin(prog->player.player_angle);
	speed_cos = speed * cos(prog->player.player_angle);
	if (keycode == UP_KEYCODE)
	{
		new_pos.x = prog->player.player_pos.x + speed_cos;
		new_pos.y = prog->player.player_pos.y + speed_sin;
		printf ("new pos: %f %f\n", new_pos.x, new_pos.y);
		printf ("new pos: %d %d\n", (int)floor(new_pos.y / GRID_SIZE), (int)floor(new_pos.x / GRID_SIZE));
		if (prog->map[(int)floor(new_pos.y / (double)GRID_SIZE)][(int)floor(new_pos.x / (double)GRID_SIZE)] == 1)
		{
			return (1);
		}
		prog->player.player_pos = new_pos;
	}
	else if (keycode == DOWN_KEYCODE)
	{
		new_pos.x = prog->player.player_pos.x - speed_cos;
		new_pos.y = prog->player.player_pos.y - speed_sin;
		printf ("new pos: %f %f\n", new_pos.x, new_pos.y);
		printf ("new pos: %d %d\n", (int)floor(new_pos.y / (double)GRID_SIZE), (int)floor(new_pos.x / GRID_SIZE));
		if (prog->map[(int)floor(new_pos.y / (double)GRID_SIZE)][(int)floor(new_pos.x / (double)GRID_SIZE)] == 1)
		{
			return (1);
		}
		prog->player.player_pos = new_pos;
	}
	else if (keycode == LEFT_KEYCODE)
	{
		prog->player.player_angle += degree_to_rad(3);
	}
	else if (keycode == RIGHT_KEYCODE)
	{
		prog->player.player_angle -= degree_to_rad(3);
	}
	move_player(prog);
	return (0);
}

int main(void)
{
	t_cub3d	prog;

	int map[7][9] = {
		{1, 1, 1, 1 ,1, 1, 1, 1 ,1},
		{1, 0, 0, 0 ,0, 0, 0, 0 ,1},
		{1, 0, 1, 0 ,1, 1, 1, 0 ,1},
		{1, 0, 1, 1 ,1, 1, 1, 0 ,1},
		{1, 0, 0, 0 ,0, 0, 0, 0 ,1},
		{1, 0, 0, 1 ,0, 1, 0, 0 ,1},
		{1, 1, 1, 1 ,1, 1, 1, 1 ,1},
	};
	 // Allocate memory for rows
    prog.map = malloc(7 * sizeof(int *));
    for (int i = 0; i < 7; i++) {
        // Allocate memory for columns
         prog.map [i] = malloc(9 * sizeof(int)); // need to free
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
	prog.img_data.img = mlx_new_image(prog.mlx_ptr, WIDTH, 700);
	// to protect
	prog.img_data.addr = mlx_get_data_addr(prog.img_data.img, &prog.img_data.bits_per_pixel,
			&prog.img_data.line_length, &prog.img_data.endian);
	prog.player = player_init();
	draw_map(&prog);
	draw_rectangle(&prog.img_data, prog.player.player_pos, 0x0000FF, 20, 0);
	mlx_put_image_to_window(prog.mlx_ptr, prog.mlx_win, prog.img_data.img, 0, 0);
	mlx_hook(prog.mlx_win, 02, 1L<<1, keyboard_press_handler, &prog);
	mlx_loop(prog.mlx_ptr);
	free(prog.map); // 
	return (0);
}
