/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:20:36 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/13 14:04:53 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	emy(char map, t_vars *vars)
{
	if (map == 'M' && vars->bonus == 1)
		return (0);
	return (1);
}

void	move(int *p, t_vars *vars, t_imgs *img, char **map)
{
	int	*c;

	c = find_obj_cord(map, 'P');
	if (map[*c + *p][c[1] + p[1]] == '0' || map[*c + *p][c[1] + p[1]] == 'C')
	{
		mlx_put_image_to_window(vars->mlx, vars->win,
			img->space.img, c[1] * 32, (c[0] + vars->bonus) * 32);
		mlx_put_image_to_window(vars->mlx, vars->win, img->space.img,
			(c[1] + p[1]) * 32, (c[0] + vars->bonus + p[0]) * 32);
		mlx_put_image_to_window(vars->mlx, vars->win, img->player[0].img,
			(c[1] + p[1]) * 32, (c[0] + vars->bonus + p[0]) * 32);
		map[c[0]][c[1]] = '0';
		map[c[0] + p[0]][c[1] + p[1]] = 'P';
	}
	else if (map[c[0] + p[0]][c[1] + p[1]] == 'E' && !find_obj(map, 'C'))
		quit(vars, 0);
	else if (map[c[0] + p[0]][c[1] + p[1]] == 'M')
		quit(vars, -2);
	if (map[c[0]][c[1]] == '0')
		print_steps(++(vars->count), vars);
	free(c);
}

int	key_hook(int keycode, t_vars *vars)
{
	int	*p;

	p = ft_calloc(3, 1);
	p[0] = 0;
	p[1] = 0;
	if (keycode == 53)
		quit(vars, -1);
	if (keycode == 13)
		p[0] = -1;
	if (keycode == 0)
		p[1] = -1;
	if (keycode == 1)
		p[0] = 1;
	if (keycode == 2)
		p[1] = 1;
	if (p[1] || p[0])
		move(p, vars, &vars->img, vars->map);
	free(p);
	return (keycode);
}

int	closes(t_vars *vars)
{
	quit(vars, -1);
	return (0);
}
