/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:36:25 by aoukouho          #+#    #+#             */
/*   Updated: 2024/11/07 14:15:18 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define N 0
# define S 1
# define W 2
# define E 3

# define GRID_SIZE 16
# define FOV_SCALE (60 * (M_PI / 180))

# define WIDTH 1920
# define HEIGHT 1080

# define MINIPAM_W (16 * GRID_SIZE)
# define M_MAP_HALF (8 * GRID_SIZE)
# define MINIPAM_H (16 * GRID_SIZE)

# define UP_KEYCODE 13
# define DOWN_KEYCODE 1
# define LEFT_KEYCODE 2
# define RIGHT_KEYCODE 0

# define LEFT_ARROW_KEYCODE 123
# define RIGHT_ARROW_KEYCODE 124

# define SPACE 49
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_data
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct s_num
{
	int			num;
	int			is_flow;
}				t_num;

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct s_vec_i
{
	int			x;
	int			y;
}				t_vec_i;

typedef struct s_player
{
	t_vec		player_pos;
	int			speed;
	int			fov;
	int			radius;
	int			turn_direction;
	int			walk_direction;
	double		player_angle;
}				t_player;

typedef struct s_ray
{
	int			is_ray_up;
	int			is_ray_down;
	int			is_ray_right;
	int			is_ray_left;
	int			index;
	double		distance;
	int			is_vertical;
	t_vec		ray_pos;
	int			is_door_h;
	int			is_door;
	int			is_door_v;
	t_vec_i		door_pos;
	int			see_beyond;
	int			o_door;
	t_vec_i		o_door_pos;
}				t_ray;

typedef struct s_assets
{
	int			err;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor_c;
	int			cell_c;
	char		**map;
	int			map_start;
	int			map_width;
	int			map_height;
	t_vec_i		player_pos;
	int			player_dir;
}				t_assets;

typedef struct s_cub3d
{
	char		**map;
	t_player	player;
	t_assets	assets;
	t_vec_i		map_size;
	int			screen_w;
	int			screen_h;
	void		*mlx_ptr;
	void		*mlx_win;
	t_data		img_data;
	t_data		game_img;
	t_data		gun_img;
	t_data		gun_img2;
	t_data		black_img;
	t_data		wall_img;
	t_data		door_img;
	int			animate_do;
	char		is_shooting;
	int			anim;
}				t_cub3d;

typedef struct s_door_info
{
    int         seen_door;
    double      anim;
    t_vec_i     door_pos;
}               t_door_info;

t_cub3d			*getData(t_cub3d *tosave);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_rectangle(t_data *data, t_vec v, int color, int size);
void			draw_minimap(t_cub3d *prog);
t_player		player_init(t_cub3d *prog);
int				move_player(t_cub3d *prog);
int				keyboard_press_handler(int keycode, t_cub3d *prog);
double			degree_to_rad(double angle);
void			destroy_window(t_cub3d *prog);
void			draw_line(t_data *data, t_vec start, t_vec end, int color);
int				is_hit_wall(t_cub3d prog, t_vec position);
void			draw_rays(t_cub3d *prog);
double			normalize_angle(double angle);
void			rec(t_data *data, t_vec v, int color, t_vec size);
int				is_on_boundtry(t_vec position);
unsigned int	get_color(t_data *data, int x, int y);
void			render_frame(t_cub3d prog, t_ray *ray);
int				mouse_handler(int x, int y, t_cub3d *prog);
t_vec			calculate_texture(t_cub3d *prog, t_ray *ray, double wheight);
int				get_pixel_color(t_cub3d *prog, t_vec texture, double ycord,
					t_ray ray);
int				ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
char			*get_next_line(int fd);
char			*ft_strjoin(char *s1, char *s2);
t_assets		parse_map(char *file_name);
char			**ft_split(char const *s, char c);
t_num			ft_atoi(const char *str);
int				ft_2dlen(char **str);
int				ft_strncmp(char *s1, char *s2, int n);
char			*ft_remspace(char *line);
int				fill_map(t_assets *data, int fd1, int fd2);
void			get_map_size(t_assets *data, int fd1);
int	load_texture(t_cub3d	*prog);
void	load_image(t_cub3d prog, t_data *img, char *path, int load_attribute);
void	destroy_window(t_cub3d *prog);
double	degree_to_rad(double angle);
int	load_map(t_cub3d *prog, int argc, char *argv[]);
int	init_game(t_cub3d *prog);
void	exit_failure();
void	clear_resource(t_cub3d *prog, int counter);
double	calculate_distance(t_vec v1, t_vec v2);
t_vec	h_intersection(t_cub3d prog, double angle, t_ray *ray);
t_vec	v_intersection(t_cub3d prog, double angle, t_ray *ray);
#endif
