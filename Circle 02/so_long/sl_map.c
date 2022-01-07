/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:19:52 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/16 17:48:12 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_valid(char **map, t_vars *vars)
{
	int	ht;
	int	wt;

	if (!find_obj(map, 'P') || !find_obj(map, 'C') || !find_obj(map, 'E')
		|| find_obj(map, 'P') > 1 || find_obj(map, 'E') > 1)
		quit(vars, 2);
	ht = -1;
	while (map[++ht] != NULL)
	{
		wt = -1;
		if ((int) ft_strlen(map[ht]) != vars->m_wt)
			quit(vars, 2);
		while (++wt < vars->m_wt)
		{
			if (map[ht][wt] != 'P' && map[ht][wt] != 'C' && map[ht][wt] != 'E'
				&& map[ht][wt] != '1' && map[ht][wt] != '0'
				&& emy(map[ht][wt], vars))
				quit(vars, 2);
			if ((ht == 0 || wt == 0 || ht == (vars->m_ht - 1)
					|| wt == (vars->m_wt - 1)) && map[ht][wt] != '1')
				quit(vars, 2);
		}
	}
}

void	map_type(char *file, t_vars *vars)
{
	char	*ext;
	int		i;

	ext = ft_strrchr(file, '.');
	if (ext == NULL || *file == *ext)
		quit(vars, 1);
	i = 1;
	while (*ext++ != '\0')
	{
		if ((i == 1 && *ext != 'b')
			|| (i == 2 && *ext != 'e') || (i == 3 && *ext != 'r'))
			quit(vars, 1);
		i++;
	}
	if (i != 5)
		quit(vars, 1);
}

char	**m_to_a(char *file, t_vars *vars)
{
	int		fd;
	char	**map;
	char	*str;
	char	*c;

	map_type(file, vars);
	fd = open(file, O_RDONLY);
	str = ft_calloc(2, 1);
	c = ft_calloc(2, 1);
	while (read(fd, c, 1) > 0)
		str = ft_strjoin(str, ft_strdup(c));
	map_exist(fd, vars, str);
	map = ft_split(str, '\n');
	fd = 0;
	while (map[fd] != NULL)
		fd++;
	vars->m_ht = fd;
	vars->m_wt = ft_strlen(*map);
	free(c);
	free(str);
	map_valid(map, vars);
	vars->win = mlx_new_window(vars->mlx, vars->m_wt * 32,
			(vars->m_ht + vars->bonus) * 32, "so_long");
	print_steps(vars->count, vars);
	return (map);
}

void	map_put(t_vars *vars, t_imgs *img, int wt, int ht)
{
	mlx_put_image_to_window(vars->mlx, vars->win,
		img->space.img, wt * 32, (ht + vars->bonus) * 32);
	if (vars->map[ht][wt] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win,
			img->astroid.img, wt * 32, (ht + vars->bonus) * 32);
	if (vars->map[ht][wt] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win,
			img->bhole.img, wt * 32, (ht + vars->bonus) * 32);
	if (vars->map[ht][wt] == 'C')
		mlx_put_image_to_window(vars->mlx, vars->win,
			img->collect.img, wt * 32, (ht + vars->bonus) * 32);
	if (vars->map[ht][wt] == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win,
			img->player[0].img, wt * 32, (ht + vars->bonus) * 32);
	if (vars->map[ht][wt] == 'M')
		mlx_put_image_to_window(vars->mlx, vars->win,
			img->enemy[0].img, wt * 32, (ht + vars->bonus) * 32);
}
