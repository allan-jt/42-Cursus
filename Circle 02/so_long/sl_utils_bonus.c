/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:20:04 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/16 17:51:30 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	**moves_init(t_vars *vars)
{
	int	**ret;
	int	i;
	int	j;

	ret = malloc(sizeof(int *) * vars->m_ht);
	i = -1;
	while (++i < vars->m_ht)
	{
		j = -1;
		ret[i] = malloc(sizeof(int) * vars->m_wt);
		while (++j < vars->m_wt)
			ret[i][j] = 0;
	}
	return (ret);
}

void	move_random(t_vars *vars, int i, int j, int **moves)
{
	int	k;
	int	l;

	if (moves[i][j] == 1)
		return ;
	k = 0;
	l = 0;
	while (vars->map[i + k][j + l] != '0' && vars->map[i + k][j + l] != 'P')
	{
		l = 0;
		k = (rand() % (2 + 1 - 0) + 0) - 1;
		if (k == 0 && l == 0)
			l = (rand() % (2 + 1 - 0) + 0) - 1;
		if (k == 0 && l == 0)
			break ;
	}
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->img.space.img, j * 32, (i + vars->bonus) * 32);
	vars->map[i][j] = '0';
	if (vars->map[i + k][j + l] == 'P')
		quit(vars, -2);
	vars->map[i + k][j + l] = 'M';
	moves[i + k][j + l] = 1;
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->img.enemy[0].img, (j + l) * 32, (i + k + vars->bonus) * 32);
}

void	move_enemy(t_vars *vars, int **moves)
{
	static int	loop;
	int			i;
	int			j;

	if (++loop % 15 != 0)
		return ;
	i = -1;
	while (vars->map[++i] != NULL)
	{
		j = -1;
		while (vars->map[i][++j] != '\0')
			if (vars->map[i][j] == 'M')
				move_random(vars, i, j, moves);
	}
	i = -1;
	while (++i < vars->m_ht)
		free(moves[i]);
	free(moves);
}

void	render_next_enemy(t_vars *vars)
{
	static int	loop;
	int			i;
	int			j;

	loop++;
	i = -1;
	while (vars->map[++i] != NULL)
	{
		j = -1;
		while (vars->map[i][++j] != '\0')
		{
			if (vars->map[i][j] == 'M')
			{
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->img.space.img, j * 32, (i + vars->bonus) * 32);
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->img.enemy[loop].img, j * 32, (i + vars->bonus) * 32);
			}
		}
	}
	if (loop == 4)
		loop = 0;
	move_enemy(vars, moves_init(vars));
}

int	render_next_player(t_vars *vars)
{
	int			*cord;
	static int	loop;
	static int	timer;

	if (timer++ != 1250)
		return (0);
	cord = find_obj_cord(vars->map, 'P');
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->img.space.img, cord[1] * 32, (*cord + vars->bonus) * 32);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.player[++loop].img,
		cord[1] * 32, (*cord + vars->bonus) * 32);
	if (loop == 6)
		loop = 0;
	render_next_enemy(vars);
	timer = 0;
	return (0);
}
