#ifndef CUB3D_H
#define CUB3D_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>


# define N 0
# define S 1
# define W 2
# define E 3

# define GRID_SIZE 32
# define FOV_SCALE 0.69813170079

# define WIDTH 900
# define HEIGHT 700

# define MINIPAM_W (9 * GRID_SIZE)
# define MINIPAM_H (7 * GRID_SIZE)


#define UP_KEYCODE  13
#define DOWN_KEYCODE  1
#define LEFT_KEYCODE  2
#define RIGHT_KEYCODE  0

#define LEFT_ARROW_KEYCODE  124
#define RIGHT_ARROW_KEYCODE  123

typedef struct	s_data {
	void*	img;
	int*	    addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	player_pos;
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
    t_vector ray_pos;
}	t_ray;

typedef struct	s_cub3d
{
	char		**map;
	t_player	player;
	int			screen_w;
	int			screen_h;
	void		*mlx_ptr;
	void		*mlx_win;
	t_data     img_data;
	t_data     game_img;
	t_data     wall_img;
}	t_cub3d;

t_cub3d	*getData(t_cub3d *tosave);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_rectangle(t_data *data, t_vector v, int color, int size, int is_line);
void draw_minimap(t_cub3d *prog);
t_player player_init(void);
int	move_player(t_cub3d *prog);
int	keyboard_press_handler(int keycode, t_cub3d *prog);
double degree_to_rad(double angle);
void destroy_window(t_cub3d *prog);
void draw_line(t_data *data, t_vector start, t_vector end, int color);
int	is_hit_wall(t_cub3d prog, t_vector position);
void	draw_rays(t_cub3d prog);
double	normalize_angle(double angle);
void rec(t_data *data, t_vector v, int color, t_vector size);
int    is_on_boundtry(t_cub3d prog, t_vector position);
unsigned int	get_color(t_data *data, int x, int y);
#endif
