/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrfig <aerrfig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:02:28 by aerrfig           #+#    #+#             */
/*   Updated: 2024/11/12 16:03:43 by aerrfig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_assets(t_assets *data)
{
	*data = (t_assets){.no = 0, .so = 0, .ea = 0, .we = 0, .err = 0,
		.floor_c = -1, .cell_c = -1, .map = 0, .map_start = 0,
		.map_height = 0, .map_width = 0};
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
