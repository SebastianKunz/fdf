/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:21:26 by skunz             #+#    #+#             */
/*   Updated: 2018/12/03 19:21:36 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_getlinenb(int fd, t_info *info)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	int		counter;
	int		i;

	counter = 0;
	info->linedigcount = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		i = -1;
		buff[ret] = '\0';
		while (buff[++i])
		{
			if (buff[i] == '\n')
				counter++;
			if (ft_isdigit(buff[i]) && (buff[i + 1] == ' ' ||
				buff[i + 1] == '\n'))
				info->linedigcount++;
		}
	}
	info->linedigcount /= counter;
	if (close(fd) == -1 || ret == -1)
		return (-1);
	return (counter);
}

char	**ft_readmap(const char *filename, t_info *info)
{
	char	**map;
	int		fd;
	int		ret;
	int		i;

	i = 0;
	if ((fd = open(filename, O_RDWR)) == -1)
		return (NULL);
	if ((info->linecount = ft_getlinenb(fd, info)) == -1)
		return (NULL);
	if (!(map = malloc(sizeof(char*) * info->linecount + 1)))
		return (NULL);
	map[info->linecount] = NULL;
	if ((fd = open(filename, O_RDWR)) == -1)
		return (NULL);
	while ((ret = get_next_line(fd, &map[i])) > 0)
		i++;
	if (ret == -1)
	{
		ft_free2d(map, info->linecount);
		return (NULL);
	}
	if ((close(fd)) == -1)
		return (NULL);
	return (map);
}

int		**ft_translate(char **map, t_info info)
{
	char	**new;
	int		**conv;
	int		y;
	int		x;

	y = -1;
	if (!(conv = malloc(sizeof(int*) * info.linecount)))
		return (NULL);
	while (++y < info.linecount)
	{
		x = -1;
		new = ft_strsplit(map[y], ' ');
		if (!(conv[y] = malloc(sizeof(int) * info.linedigcount)))
		{
			ft_free2d(new, y + 1);
			return (NULL);
		}
		while (++x < info.linedigcount)
			conv[y][x] = ft_atoi(new[x]);
		ft_free2d(new, info.linedigcount);
	}
	return (conv);
}

t_point	*ft_convert(int **new, t_info info, t_mod mod)
{
	t_point	*point;
	int		i;
	int		y;
	int		x;

	i = -1;
	y = -1;
	if (!(point = malloc(sizeof(t_point) * info.linecount * info.linedigcount)))
		return (NULL);
	while (++y < info.linecount)
	{
		x = -1;
		while (++x < info.linedigcount)
		{
			point[++i].color = ft_color(255, 255 - new[y][x] * 10,
				255 - new[y][x] * 10);
			point[i].x = (x - y) * cos(mod.theta_x);
			point[i].y = -(new[y][x] * mod.div) + (x + y) * sin(mod.theta_y);
			point[i].x *= 500 / info.linedigcount;
			point[i].y *= 500 / info.linecount;
			point[i].x += mod.xoffset;
			point[i].y += mod.yoffset;
		}
	}
	return (point);
}
