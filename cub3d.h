/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:36:25 by aoukouho          #+#    #+#             */
/*   Updated: 2024/10/15 14:52:23 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "minilibx_opengl/mlx.h"
# include <unistd.h>
# include <math.h>
# include <float.h>
 
# define N 0
# define S 1
# define W 2
# define E 3

# define GRID_SIZE 32
# define FOV_SCALE 0.69813170079

# define WIDTH 1920
# define HEIGHT 1080

# define MINIPAM_W (8 * GRID_SIZE)
# define MINIPAM_H (8 * GRID_SIZE)


#define UP_KEYCODE  13
#define DOWN_KEYCODE  1
#define LEFT_KEYCODE  2
#define RIGHT_KEYCODE  0

#define LEFT_ARROW_KEYCODE  123
#define RIGHT_ARROW_KEYCODE  124

#define SPACE 49

typedef struct	s_data {
	void*	img;
	int*	    addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_player
{
	t_vec	player_pos;
	int			speed;
	int			fov;
	int			radius;
	int			turn_direction;
	int			walk_direction;
	double			player_angle;
}	t_player;


typedef struct s_ray
{
    int is_ray_up;
    int is_ray_down;
    int is_ray_right;
    int is_ray_left;
    int index;
    double distance;
    int	is_vertical;
    t_vec ray_pos;
    int	  is_door;
}	t_ray;

typedef struct	s_cub3d
{
	char		**map;
	t_player	player;
	t_vec	map_size;
	int			screen_w;
	int			screen_h;
	void		*mlx_ptr;
	void		*mlx_win;
	t_data     img_data;
	t_data     game_img;
	t_data     gun_img;
	t_data     gun_img2;
	t_data     black_img;
	t_data     wall_img;
	t_data     door_img;
	char		is_shooting;
}	t_cub3d;

t_cub3d	*getData(t_cub3d *tosave);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_rectangle(t_data *data, t_vec v, int color, int size);
void draw_minimap(t_cub3d *prog);
t_player player_init(void);
int	move_player(t_cub3d *prog);
int	keyboard_press_handler(int keycode, t_cub3d *prog);
double degree_to_rad(double angle);
void destroy_window(t_cub3d *prog);
void draw_line(t_data *data, t_vec start, t_vec end, int color);
int	is_hit_wall(t_cub3d prog, t_vec position);
void	draw_rays(t_cub3d prog);
double	normalize_angle(double angle);
void rec(t_data *data, t_vec v, int color, t_vec size);
int    is_on_boundtry(t_cub3d prog, t_vec position);
unsigned int	get_color(t_data *data, int x, int y);
void 		render_frame(t_cub3d prog, double angle, t_ray *ray);
int		mouse_handler(int x, int y, t_cub3d *prog);
t_vec	calculate_texture(t_cub3d *prog, t_ray *ray, double wheight);
int	get_pixel_color(t_cub3d *prog, t_vec texture, double ycord,t_ray ray);
#endif
