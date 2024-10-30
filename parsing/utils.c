#include "../cub3d.h"

t_num	ft_atoi(const char *str)
{
	int		i;
	t_num	res;

	i = 0;
	res.num = 0;
	res.is_flow = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == ' ') && str[i])
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res.num *= 10;
		res.num += str[i] - '0';
		if (res.num > 255)
			res.is_flow = 1;
		i++;
	}
	return ((t_num){res.num, res.is_flow});
}

int	ft_2dlen(char **str)
{
	int	i;

	i = 0;
	if (!str && !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_remspace(char *line)
{
	char	*res;

	if (!line)
		return (0);
	res = ft_strdup(line);
	while (*res == ' ' || *res == '\r' || *res == '\t')
		res++;
	return (res);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
