#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x > WIDTH || y > HEIGHT || y <0 || x < 0)
		return ;
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rectangle(t_data *data, t_vector v, int color, int size, int is_line)
{
	int i = v.x ;
	int j = v.y ;
	while (i < v.x+size)
	{
		j = v.y ;
		while (j < v.y+size)
		{
			my_mlx_pixel_put(data, i,j, color);
			j++;
		}
		i++;
	}
}

void draw_minimap(t_cub3d *prog)
{
	int i = 0;
	int j = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 9)
		{
			t_vector rectange = (t_vector) {.x = GRID_SIZE*j, .y=GRID_SIZE*i};
			if (prog->map[i][j] == 1)
			{
				draw_rectangle(&prog->img_data, rectange, 0xFF0000, GRID_SIZE, 1);
			}
			else
			{
				draw_rectangle(&prog->img_data, rectange, 0xFFFFFF, GRID_SIZE, 0);
			}
			j++;
		}
		i++;
	}
}

void swap(double *x, double *y)
{
	double tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void draw_line(t_data *data, t_vector start, t_vector end, int color) 
{
    int i;

    double x = end.x - start.x;
    double y = end.y - start.y;
    double length = sqrt(x * x + y * y);
    double addx = x / length;
    double addy = y / length;
    x = start.x;
    y = start.y;

    for (i = 0; i < length; i += 1) {
		if (x >= WIDTH || y >= HEIGHT || y <0 || x < 0)
			return ;
	    my_mlx_pixel_put(data,(int)round(x), (int)round(y),color );
        x += addx;
        y += addy;
    }
}
