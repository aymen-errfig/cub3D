/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukouho <aoukouho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:04 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/12 15:08:38 by aoukouho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <float.h>

double calculate_distance(t_vec v1, t_vec v2) 
{
    double distance;

    distance = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
    return distance;
}

t_vec horizontal_intersection(t_vec   current, t_cub3d prog, double angle, t_ray ray)
{
    t_vec h_intersection;
    t_vec h_step;
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
       
        if (is_hit_wall(prog,(t_vec) {.x=h_intersection.x,.y=h_intersection.y - ray.is_ray_up })) 
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

t_vec vertical_intersection(t_vec   current, t_cub3d prog, double angle, t_ray ray)
{
    t_vec v_intersection;
    t_vec v_step;
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
          if (is_hit_wall(prog,(t_vec) {.x=v_intersection.x - ray.is_ray_left,.y=v_intersection.y})) 
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
	t_vec h_intersection;
    	t_vec v_intersection;
    	t_vec player;

	player = prog.player.player_pos;
	ray->is_ray_up = (angle < 0 || angle > M_PI);
    	ray->is_ray_down = !ray->is_ray_up;
    	ray->is_ray_right = angle > 3 * M_PI / 2 || angle < M_PI / 2;
    	ray->is_ray_left = !ray->is_ray_right;
    	h_intersection = horizontal_intersection(player, prog, angle, *ray);
    	v_intersection = vertical_intersection(player, prog, angle, *ray);
	ray->ray_pos = h_intersection;
	ray->distance = calculate_distance(player, h_intersection);
	ray->is_vertical = 0;
	if (calculate_distance(player, v_intersection) < ray->distance) 
	{
		ray->ray_pos = v_intersection;
		ray->is_vertical = 1;
		ray->distance = calculate_distance(player, v_intersection);
	}
       ray->distance *= cos(angle - prog.player.player_angle);
       /* double wall_height =  (GRID_SIZE / ray->distance) * (WIDTH / 2.0) / tan(degree_to_rad(60) / 2); */
       /* double wall_start =  (HEIGHT/2) - (wall_height/2); */
      /* wall_start *= (wall_start > 0); */
      /* double wall_end =  (HEIGHT/2) + (wall_height/2); */
      /* if (wall_end > HEIGHT) */
	    /* wall_end = HEIGHT; */
      /* t_vec ciel = (t_vec){ray->index, 0}; */
    /* // draw cieling */
     /* while (ciel.y < wall_start) */
    /* { */
	    /* my_mlx_pixel_put(&prog.game_img,  ciel.x, ciel.y, 0x2BFAFA); */
	    /* ciel.y++; */
    /* } */
    /* int texture_x; */
    /* if (ray->is_vertical) */
	/* texture_x = fmod((ray->ray_pos.y* (prog.wall_img.width/GRID_SIZE)), prog.wall_img.width); */
    /* else */
	/* texture_x = fmod((ray->ray_pos.x* (prog.wall_img.width/GRID_SIZE)), prog.wall_img.width); */
    /* double offsety; */
    /* double texture_y; */
    /* offsety = (double)prog.wall_img.width / wall_height; */
    /* double ycord = (wall_start - (HEIGHT / 2) + (wall_height / 2)) * offsety; */
    /* ycord *= (ycord > 0); */
    /* // draw walls */
    /* while (ciel.y < wall_end) */
    /* { */
	    /* int color = prog.wall_img.addr[(int) ycord * prog.wall_img.width + (int)texture_x]; */
	    /* my_mlx_pixel_put(&prog.game_img,  ciel.x, ciel.y, color); */
	    /* ycord += offsety; */
	    /* ciel.y++; */
    /* } */
    /* // drwa floors */
    /* while (ciel.y < HEIGHT) */
    /* { */
	    /* my_mlx_pixel_put(&prog.game_img,  ciel.x, ciel.y, 0xFF00FF); */
	    /* ciel.y++; */
    /* } */    	    	
    render_frame(prog, angle, ray);
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
