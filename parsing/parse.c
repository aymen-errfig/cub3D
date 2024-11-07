/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:07:19 by aerrfig           #+#    #+#             */
/*   Updated: 2024/11/07 12:18:33 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ext(char *fname)
{
	int		len;
	char	*ext;

	len = ft_strlen(fname);
	if (len < 4)
		return (-1);
	ext = fname + len - 4;
	if (ft_strncmp(ext, ".cub", 4))
		return (-1);
	return (open(fname, O_RDONLY));
}

void	free2d(char **arr)
{
	int	k;

	k = 0;
	while (arr && arr[k])
	{
		free(arr[k]);
		k++;
	}
	free(arr);
}

int	rgb_parsing(char *line)
{
	char	**code;
	int		color;
	t_num	r;
	t_num	g;
	t_num	b;

	code = ft_split(line, ',');
	color = -1;
	if (!code)
		return (-1);
	if (ft_2dlen(code) == 3)
	{
		r = ft_atoi(code[0]);
		g = ft_atoi(code[1]);
		b = ft_atoi(code[2]);
		if (r.num >= 0 && r.num <= 255 && g.num >= 0 && g.num <= 255
			&& b.num >= 0 && b.num <= 255)
			color = (r.num << 16) | ((g.num & 0x0ff) << 8) | (b.num & 0x0ff);
	}
	return (free2d(code), color);
}

void	check_assets(char *line, t_assets *data)
{
	if (!ft_strncmp(line, "\n", 1))
		data->err = data->err;
	else if (!ft_strncmp(line, "WE ", 3))
		data->we = ft_remspace(line + 2);
	else if (!ft_strncmp(line, "NO ", 3))
		data->no = ft_remspace(line + 2);
	else if (!ft_strncmp(line, "EA ", 3))
		data->ea = ft_remspace(line + 2);
	else if (!ft_strncmp(line, "SO ", 3))
		data->so = ft_remspace(line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		data->cell_c = rgb_parsing(line + 1);
	else if (!ft_strncmp(line, "F ", 2))
		data->floor_c = rgb_parsing(line + 1);
	else
		data->err = 1;
}

int	is_all_assets(t_assets data)
{
	return (data.floor_c > 0 && data.cell_c > 0 && ft_strlen(data.we) > 0
		&& ft_strlen(data.ea) > 0 && ft_strlen(data.no) > 0
		&& ft_strlen(data.so) > 0);
}

void	get_map_size(t_assets *data, int fd1)
{
	char	*line;

	line = get_next_line(fd1);
	while (line && !ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(fd1);
		data->map_start++;
	}
	while (line && ft_strncmp(line, "\n", 1))
	{
		if (ft_strlen(line) > data->map_width)
			data->map_width = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(fd1);
		data->map_height++;
	}
}

t_assets	parse_map(char *file_name)
{
	int			fd;
	int			fd2;
	t_assets	data;
	char		*line;

	fd = check_ext(file_name);
	fd2 = check_ext(file_name);
	data.map_start = 0;
	data = (t_assets){.no = 0, .so = 0, .ea = 0, .we = 0, .err = 0,
		.floor_c = -1, .cell_c = -1, .map = 0, .map_start = 0,
		.map_height = 0, .map_width = 0};
	if (fd < 0 || fd2 < 0)
		exit(-1);
	line = get_next_line(fd);
	while (line && !is_all_assets(data))
	{
		check_assets(line, &data);
		free(line);
		line = get_next_line(fd);
		data.map_start++;
	}
	free(line);
	if (!is_all_assets(data))
		data.err = 1;
	else
		data.err = fill_map(&data, fd, fd2);
	return (data);
}
