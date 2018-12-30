/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 11:57:06 by skunz             #+#    #+#             */
/*   Updated: 2018/11/30 11:57:08 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SIZE_X 1000
# define SIZE_Y 1000

# include <stdlib.h>
# include <math.h>
# include "get_next_line/get_next_line.h"
# include "minilibx_macos/mlx.h"

typedef struct	s_point
{
	float		x;
	float		y;
	int			color;
}				t_point;

typedef struct	s_mod
{
	float		xoffset;
	float		yoffset;
	float		scale;
	float		div;
	float		xdegree;
	float		ydegree;
	float		theta_y;
	float		theta_x;
}				t_mod;

typedef struct	s_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			linedigcount;
	int			linecount;
}				t_info;

/*
** map.c functions
*/

int				ft_getlinenb(int fd, t_info *info);
char			**ft_readmap(const char *filename, t_info *info);
int				**ft_translate(char **map, t_info info);
t_point			*ft_convert(int **new, t_info info, t_mod mod);

/*
** draw.c functions
*/

void			ft_drawall(t_info info, t_point *points);
void			ft_drawline(t_info mlx, t_point p1, t_point p2, int color);
int				ft_color(int r, int g, int b);
void			ft_setcolorall(t_point **points, t_info info, char *colorcode);

#endif
