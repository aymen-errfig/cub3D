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

# define GRID_SIZE 100
# define FOV_SCALE 0.66


# define WIDTH 900
# define HEIGHT 700

#define UP_KEYCODE  13
#define DOWN_KEYCODE  1
#define LEFT_KEYCODE  2
#define RIGHT_KEYCODE  0

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

typedef struct	s_cub3d
{
	char		**map;
	t_player	player;
	int			screen_w;
	int			screen_h;
	void		*mlx_ptr;
	void		*mlx_win;
	t_data     img_data;
}	t_cub3d;
#endif
