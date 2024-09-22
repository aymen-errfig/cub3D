#include "cub3d.h"

int	keyboard_press_handler(int keycode, t_cub3d *prog)
{
	int speed;
	double speed_sin;
	double speed_cos;
	t_vector new_pos;

	(void)prog;
	if (keycode != 258 && keycode != UP_KEYCODE && keycode != DOWN_KEYCODE && keycode != RIGHT_KEYCODE && 
	keycode != LEFT_KEYCODE && keycode != 53 && keycode != RIGHT_ARROW_KEYCODE && keycode != LEFT_ARROW_KEYCODE)
		return (1);
	if (keycode == 53)
	{
		free(prog->map);
		destroy_window(prog);
		exit(1);
	}
	speed = 20;
	speed_sin = speed * sin(prog->player.player_angle);
	speed_cos = speed * cos(prog->player.player_angle);
	if (keycode == UP_KEYCODE)
	{
		new_pos.x = prog->player.player_pos.x + speed_cos;
		new_pos.y = prog->player.player_pos.y + speed_sin;
		if (is_hit_wall(*prog, new_pos))
			return (1);
		prog->player.player_pos = new_pos;
	}
	else if (keycode == DOWN_KEYCODE)
	{
		new_pos.x = prog->player.player_pos.x - speed_cos;
		new_pos.y = prog->player.player_pos.y - speed_sin;
		if (is_hit_wall(*prog, new_pos))
			return (1);
		prog->player.player_pos = new_pos;
	}
	else if (keycode == LEFT_KEYCODE)
	{
		new_pos.x = prog->player.player_pos.x - speed_sin;
		new_pos.y = prog->player.player_pos.y + speed_cos;

		if (is_hit_wall(*prog, new_pos))
			return (1);
		prog->player.player_pos = new_pos;
	}
	else if (keycode == RIGHT_KEYCODE)
	{
		new_pos.x = prog->player.player_pos.x + speed_sin;
		new_pos.y = prog->player.player_pos.y - speed_cos;
		if (is_hit_wall(*prog, new_pos))
			return (1);
		prog->player.player_pos = new_pos;
	}
	else if (keycode == RIGHT_ARROW_KEYCODE)
	{
		 prog->player.player_angle -= degree_to_rad(3);
	}
	else if (keycode == LEFT_ARROW_KEYCODE)
	{
		 prog->player.player_angle += degree_to_rad(3);
	}
	/* prog->player.player_angle = normalize_angle(prog->player.player_angle); */
	move_player(prog);
	return (0);
}
