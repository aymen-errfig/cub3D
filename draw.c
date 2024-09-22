#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
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

/* void	bresenham_draw_line(t_vector start, t_vector end) */
/* { */
/* 	int step_x; */
/* 	int step_y; */
/* 	int d; */

/* 	step_x = abs((int)end.x - (int)start.x); */
/* 	step_y = abs((int)end.y - (int)start.y); */
/* 	d = 2 * step_y - step_x; */
/* 	while (1) */
/* 	{ */
/* 		if (d > 0) */
/* 		{ */
/* 			start.x += 1; */
/* 			start.y += 1; */
/* 		} */
/* 		else if (d < 0) */
/* 		{ */
/* 		} */
/* 		step_x = end.x - start.x; */
/* 		step_y = end.y - start.y; */
/* 		d = 2 * step_y - step_x; */

/* 	} */
/* } */

void swap(double *x, double *y)
{
	double tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void draw_line(t_data *data, t_vector start, t_vector end, int color)
{
    if (end.x == start.x && end.y == start.y)
    {
	    return ;
    }
    double diffX = fabs(end.x - start.x);
    double diffY = fabs(end.y - start.y);
    int step = (diffX < diffY);  // Check if the line is steep
    double err = diffX / 2.;
    if (step)
    {
        swap(&start.x, &start.y);
        swap(&end.x, &end.y);
    }
    if (start.x > end.x)
    {
        swap(&start.x, &end.x);
        swap(&start.y, &end.y);
    }
    diffX = end.x - start.x;
    diffY = fabs(end.y - start.y);
    int ystep = (start.y < end.y) ? 1 : -1;
    while (start.x <= end.x)  // Ensure last point is drawn
    {
        if (!step)
            my_mlx_pixel_put(data, (int)start.x, (int)start.y, color);
        else
            my_mlx_pixel_put(data, (int)start.y, (int)start.x, color);

        err -= diffY;
        if (err < 0)
        {
            start.y += ystep;
            err += diffX;
        }
        start.x += 1;
    }
}
