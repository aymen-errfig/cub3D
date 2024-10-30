#include "../cub3d.h"

char	*gimme_spaces(int n)
{
	char	*spcs;
	int		i;

	i = 0;
	spcs = malloc(n + 1);
	while (i < n)
	{
		spcs[i] = ' ';
		i++;
	}
	spcs[i] = 0;
	return (spcs);
}

int	check_surrounded(t_assets *data, int i, int j)
{
	if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
		|| data->map[i][j] == 'S' || data->map[i][j] == 'E'
		|| data->map[i][j] == '0' || data->map[i][j] == 'D')
	{
		if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' '
			|| data->map[i][j + 1] == ' ' || data->map[i][j - 1] == ' ')
			return (1);
	}
	return (0);
}

int	is_valid_borders(t_assets *data)
{
	int	i;
	int	h;
	int	w;

	i = 0;
	h = data->map_height - 1;
	w = data->map_width - 1;
	while (i < data->map_width)
	{
		if ((data->map[0][i] != ' ' && data->map[0][i] != '1')
			|| (data->map[h][i] != ' ' && data->map[h][i] != '1'))
			return (0);
		i++;
	}
	i = 0;
	while (i < data->map_height)
	{
		if ((data->map[i][0] != ' ' && data->map[i][0] != '1')
			|| (data->map[i][w] != ' ' && data->map[i][w] != '1'))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map(t_assets *data)
{
	int	i;
	int	j;

	1 && (i = 1, j = 0);
	if (!is_valid_borders(data))
		return (0);
	while (i < data->map_height - 1)
	{
		j = 0;
		while (++j < data->map_width - 1)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E')
			{
				if (data->player_dir != 0)
					return (0);
				data->player_pos = (t_vec_i){.x = j, .y = i};
				data->player_dir = data->map[i][j];
			}
			if (check_surrounded(data, i, j))
				return (0);
		}
		i++;
	}
	return ((data->player_dir > 0));
}

int	fill_map(t_assets *data, int fd1, int fd2)
{
	int		off;
	int		y;
	char	*line;

	1 && (off = -1, y = 0);
	get_map_size(data, fd1, fd2);
	if (data->map_height < 1 || data->map_width < 1)
		return (-1);
	line = get_next_line(fd2);
	while (line && ++off < data->map_start)
	{
		free(line);
		line = get_next_line(fd2);
	}
	data->map = malloc(sizeof(char *) * data->map_height);
	if (!data->map)
		return (-1);
	line = get_next_line(fd2);
	while (line && ft_strncmp(line, "\n", 1))
	{
		if (ft_strlen(line) > 1 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		data->map[y++] = ft_strjoin(line, gimme_spaces(data->map_width
					- ft_strlen(line)));
		line = get_next_line(fd2);
	}
	return (!is_valid_map(data));
}
