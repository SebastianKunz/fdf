/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:19:35 by skunz             #+#    #+#             */
/*   Updated: 2018/12/03 15:19:37 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_color(int r, int g, int b)
{
	int c;

	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

void	ft_setcolorall(t_point **points, t_info info, char *colorcode)
{
	int i;
	int color;

	i = -1;
	if (ft_strcmp(colorcode, "white") == 0)
		color = ft_color(255, 255, 255);
	else if (ft_strcmp(colorcode, "red") == 0)
		color = ft_color(255, 0, 0);
	else if (ft_strcmp(colorcode, "yellow") == 0)
		color = ft_color(255, 255, 0);
	else if (ft_strcmp(colorcode, "blue") == 0)
		color = ft_color(0, 0, 255);
	while (++i < info.linecount * info.linedigcount)
		(*points)[i].color = color;
}

void	ft_drawline(t_info mlx, t_point p1, t_point p2, int color)
{
	int diff[2];
	int s[2];
	int e[2];

	diff[0] = abs((int)p2.x - (int)p1.x);
	diff[1] = abs((int)p2.y - (int)p1.y);
	s[0] = (int)p1.x < (int)p2.x ? 1 : -1;
	s[1] = (int)p1.y < (int)p2.y ? 1 : -1;
	e[0] = (diff[0] > diff[1] ? diff[0] : -diff[1]) / 2;
	while ((int)p1.x != (int)p2.x || (int)p1.y != (int)p1.y)
	{
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, (int)p1.x, (int)p1.y, color);
		e[1] = e[0];
		if (e[1] > -diff[0])
		{
			e[0] -= diff[1];
			p1.x += s[0];
		}
		if (e[1] < diff[1])
		{
			e[0] += diff[0];
			p1.y += s[1];
		}
	}
}

void	ft_drawall(t_info mapinfo, t_point *points)
{
	int i;
	int k;

	i = -1;
	while (++i < (mapinfo.linecount * mapinfo.linedigcount) - 1)
		if ((i + 1) % (mapinfo.linedigcount) != 0)
			ft_drawline(mapinfo, points[i], points[i + 1], points[i].color);
	i = -1;
	while (++i < mapinfo.linedigcount)
	{
		k = -1;
		while (++k < mapinfo.linecount - 1)
			ft_drawline(mapinfo, points[(k * mapinfo.linedigcount) + i],
				points[((k + 1) * mapinfo.linedigcount) + i],
				points[(k * mapinfo.linedigcount) + i].color);
	}
}
