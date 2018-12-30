/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skunz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:15:57 by skunz             #+#    #+#             */
/*   Updated: 2018/11/29 23:09:15 by skunz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_initmod(t_mod *mod)
{
	mod->div = 0.05;
	mod->xoffset = SIZE_X / 2;
	mod->yoffset = SIZE_Y / 3;
	mod->xdegree = 20;
	mod->ydegree = 20;
	mod->theta_y = mod->ydegree * 0.0174533;
	mod->theta_x = mod->xdegree * 0.0174533;
}

int		ft_keydown(int key, t_info *info)
{
	if (key == 53 || key == 12)
		exit(1);
	return (1);
}

int		ft_printerror(int code)
{
	if (code == 1)
		ft_putstr("Error On Readmap!\n");
	else if (code == 2)
		ft_putstr("Error On Translating!\n");
	return (-1);
}

void	ft_initwindow(t_info *info)
{
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, SIZE_X, SIZE_Y, "FDF");
	mlx_string_put(info->mlx_ptr, info->win_ptr, SIZE_X / 2.3, SIZE_Y / 10,
		ft_color(255, 255, 255), "Welcome to FDF");
}

int		main(int argc, char **argv)
{
	t_info		info;
	t_mod		mod;
	t_point		*points;
	char		**map;
	int			**new;

	if (argc == 2 || argc == 3)
	{
		ft_initwindow(&info);
		ft_initmod(&mod);
		if (!(map = ft_readmap(argv[1], &info)))
			return (ft_printerror(1));
		if (!(new = ft_translate(map, info)))
			return (ft_printerror(2));
		ft_free2d(map, info.linecount);
		points = ft_convert(new, info, mod);
		if (argc == 3)
			ft_setcolorall(&points, info, argv[2]);
		ft_drawall(info, points);
		mlx_key_hook(info.win_ptr, ft_keydown, &info);
		mlx_loop(info.mlx_ptr);
	}
	else
		ft_putstr("usage: [fdf map] [color]\n");
	return (0);
}
