#include "cub3d.h"
#include <math.h>
#include <float.h>

double calculate_distance(t_vector v1, t_vector v2) 
{
    double distance;

    distance = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
    return distance;
}

t_vector horizontal_intersection(t_vector   current, t_cub3d prog, double angle, t_ray ray)
{
    t_vector h_intersection;
    t_vector h_step;
    int hitWall = 0;

    h_intersection.y = floor(prog.player.player_pos.y / GRID_SIZE) * GRID_SIZE; 
    if (ray.is_ray_down)
        h_intersection.y += GRID_SIZE;
    h_intersection.x = prog.player.player_pos.x + (h_intersection.y - prog.player.player_pos.y) / tan(angle); 
    h_step.y = GRID_SIZE;
    if (ray.is_ray_up)
        h_step.y *= -1;
    h_step.x = h_step.y / tan(angle);
    if (ray.is_ray_left && h_step.x > 0)
        h_step.x *= -1;
    if (ray.is_ray_right && h_step.x < 0)
        h_step.x *= -1;
    while (is_on_boundtry(prog, h_intersection))
    {
       
        if (is_hit_wall(prog,(t_vector) {.x=h_intersection.x,.y=h_intersection.y - ray.is_ray_up })) 
        {
             hitWall = 1;
            break;
        }
current = h_intersection;
        h_intersection.x += h_step.x; h_intersection.y += h_step.y; 
    }
     if (hitWall == 0)
        ray.distance = FLT_MAX;
    return (h_intersection);
}

t_vector vertical_intersection(t_vector   current, t_cub3d prog, double angle, t_ray ray)
{
    t_vector v_intersection;
    t_vector v_step;
    int    hitWall = 0;

     v_intersection.x = floor(prog.player.player_pos.x / GRID_SIZE) * GRID_SIZE;
    if (ray.is_ray_right)
        v_intersection.x += GRID_SIZE;
    v_intersection.y = prog.player.player_pos.y + (v_intersection.x - prog.player.player_pos.x) * tan(angle); 
    v_step.x = GRID_SIZE;
    if (ray.is_ray_left)
        v_step.x *= -1;
    v_step.y = v_step.x * tan(angle);
    if (ray.is_ray_up && v_step.y > 0)
        v_step.y *= -1;
    if (ray.is_ray_down && v_step.y < 0)
        v_step.y *= -1;
    while (is_on_boundtry(prog, v_intersection))
    {
          if (is_hit_wall(prog,(t_vector) {.x=v_intersection.x - ray.is_ray_left,.y=v_intersection.y})) 
  {
            hitWall = 1;
            break;
          }
           v_intersection.x += v_step.x; v_intersection.y += v_step.y; 
    }
    if (hitWall == 0)
        ray.distance = FLT_MAX;
     return (v_intersection);
}

void dda_algo(t_cub3d prog, double angle, t_ray *ray)
{
	t_vector h_intersection;
    	t_vector v_intersection;
    	t_vector player;

	player = prog.player.player_pos;
	ray->is_ray_up = (angle < 0 || angle > M_PI);
    	ray->is_ray_down = !ray->is_ray_up;
    	ray->is_ray_right = angle > 3 * M_PI / 2 || angle < M_PI / 2;
    	ray->is_ray_left = !ray->is_ray_right;
    	h_intersection = horizontal_intersection(player, prog, angle, *ray);
    	v_intersection = vertical_intersection(player, prog, angle, *ray);
	ray->ray_pos = h_intersection;
	ray->distance = calculate_distance(player, h_intersection);

	if (calculate_distance(player, v_intersection) < ray->distance) 
	{
		ray->ray_pos = v_intersection;
		ray->distance = calculate_distance(player, v_intersection);
	}
    // if (ray->distance < 35)
    //     ray->distance = 35;
    //  printf("%f\n", ray->distance);
    // double wall_height = ((GRID_SIZE * HEIGHT) / ray->distance);
    // printf("%f\n", wall_height);
    // t_vector begin;
    // begin.y = (HEIGHT / 2) - (wall_height / 2);
    // begin.x = ray->index;
    // t_vector end;
    // end.y = (HEIGHT / 2) + (wall_height / 2);
    // end.x = ray->index;
    
    // while (++y < end)
    // {
    //     draw_line(&prog.img_data, prog.player.player_pos, ray->ray_pos, 0xFF00FF);
    // }
	double distancePorjectionPlane = (WIDTH/2.) / tan(degree_to_rad(30));
	double wallStripHeight = (GRID_SIZE / (ray->distance * 25.0)) * distancePorjectionPlane;
    wallStripHeight *= 1.0;
	printf ("%f %f\n", distancePorjectionPlane, wallStripHeight);
	t_vector wall;
	wall.x = ray->index;
	wall.y = (HEIGHT/2.0) - (wallStripHeight / 2.0);
	t_vector width;
	width.x = 1;
	width.y = wallStripHeight;
	rec(&prog.game_img, wall, 0xFFFF00, width);
	// draw_line(&prog.game_img, begin, end, 0x00FF00);
	draw_line(&prog.img_data, prog.player.player_pos, ray->ray_pos, 0xFF00FF);
}

void	draw_rays(t_cub3d prog)
{
	int i;
	double angle;
	t_ray ray;

	i = -1;
	angle = prog.player.player_angle - FOV_SCALE / 2;
	while (++i < WIDTH)
	{
		angle = normalize_angle(angle);
		ray.index = i;
		dda_algo(prog, angle, &ray);
		angle += FOV_SCALE / WIDTH;
	}
}
