#include "cub3d.h"
#include <math.h>

double calculate_distance(t_vector v1, t_vector v2) 
{
    double distance;

    distance = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
    return distance;
}

t_vector horizontal_intersection(t_vector   current, t_cub3d prog, double angle)
{
    int is_ray_up = (angle < 0 || angle > M_PI);
    int is_ray_down = !is_ray_up;
    int is_ray_right = angle > 3 * M_PI / 2 || angle < M_PI / 2;
    int is_ray_left = !is_ray_right;

    t_vector h_intersection;
    t_vector h_step;
    // Horizontal intersection
    h_intersection.y = floor(prog.player.player_pos.y / GRID_SIZE) * GRID_SIZE; 
    if (is_ray_down)
        h_intersection.y += GRID_SIZE;
    h_intersection.x = prog.player.player_pos.x + (h_intersection.y - prog.player.player_pos.y) / tan(angle); 
    h_step.y = GRID_SIZE;
    if (is_ray_up)
        h_step.y *= -1;
    h_step.x = h_step.y / tan(angle);
    if (is_ray_left && h_step.x > 0)
        h_step.x *= -1;
    if (is_ray_right && h_step.x < 0)
        h_step.x *= -1;

    while (1)
    {
         if (is_ray_up)
            h_intersection.y -= 1;
        if (is_hit_wall(prog, h_intersection)) break;
        current.x = h_intersection.x;
        current.y = h_intersection.y;
        h_intersection.x += h_step.x; h_intersection.y += h_step.y; 
    }
    return (h_intersection);
}

t_vector vertical_intersection(t_vector   current, t_cub3d prog, double angle)
{
     int is_ray_up = (angle < 0 || angle > M_PI);
    int is_ray_down = !is_ray_up;
    int is_ray_right = angle > 3 * M_PI / 2 || angle < M_PI / 2;
    int is_ray_left = !is_ray_right;
    t_vector v_intersection;
    t_vector v_step;

     v_intersection.x = floor(prog.player.player_pos.x / GRID_SIZE) * GRID_SIZE;
    if (is_ray_right)
        v_intersection.x += GRID_SIZE;
    v_intersection.y = prog.player.player_pos.y + (v_intersection.x - prog.player.player_pos.x) * tan(angle); 
    v_step.x = GRID_SIZE;
    if (is_ray_left)
        v_step.x *= -1;
    v_step.y = v_step.x * tan(angle);
    if (is_ray_up && v_step.y > 0)
        v_step.y *= -1;
    if (is_ray_down && v_step.y < 0)
        v_step.y *= -1;
    while (1)
    {
        if (is_ray_left)
            v_intersection.x -= 1;
        if (is_hit_wall(prog, v_intersection)) break;
        current.x = v_intersection.x;
        current.y = v_intersection.y;
        v_intersection.x += v_step.x; v_intersection.y += v_step.y; 
      
    }
    return (v_intersection);
}

void dda_algo(t_cub3d prog, double angle)
{
    int is_ray_up = (angle < 0 || angle > M_PI);
    int is_ray_down = !is_ray_up;
    int is_ray_right = angle < M_PI_2 || angle > 3 * M_PI_2;
    int is_ray_left = !is_ray_right;
    t_vector h_intersection;
    t_vector h_step;
    t_vector v_intersection;
    t_vector v_step;

    // Horizontal intersection

    t_vector current = prog.player.player_pos;

    h_intersection = horizontal_intersection(current,prog, angle);
    v_intersection = vertical_intersection(current,prog, angle);
    if (calculate_distance(current, h_intersection) < calculate_distance(current, v_intersection))
        current = h_intersection;
    else
         current = v_intersection;
    draw_line(&prog.img_data, prog.player.player_pos, current, 0xFF00FF);
}

void	draw_rays(t_cub3d prog)
{
	int i;
	double angle;

	i = -1;
	angle = prog.player.player_angle - FOV_SCALE / 2;
	while (++i < WIDTH)
	{
		angle = normalize_angle(angle);
		dda_algo(prog, angle);
		angle += FOV_SCALE / WIDTH;
	}
}
