/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:01:54 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/16 15:50:46 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i] != NULL)
		free(map[i]);
	free(map);
}

void	map_exist(int fd, t_vars *vars, char *str)
{
	char	c;
	int		count;
	int		i;

	if (read(fd, &c, 1) == -1 || (*str == '\0' || *str == '\n'))
		quit(vars, 2);
	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\n')
			count++;
		if (str[i] != '\n')
			count = 0;
		if (count > 1)
			quit(vars, 2);
	}
}

void	free_all(t_vars *vars)
{
	int	i;

	free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img.bhole.img);
	mlx_destroy_image(vars->mlx, vars->img.space.img);
	mlx_destroy_image(vars->mlx, vars->img.astroid.img);
	mlx_destroy_image(vars->mlx, vars->img.collect.img);
	i = -1;
	while (++i < 7)
		mlx_destroy_image(vars->mlx, vars->img.player[i].img);
	i = -1;
	while (++i < 5 && vars->bonus)
		mlx_destroy_image(vars->mlx, vars->img.enemy[i].img);
}
