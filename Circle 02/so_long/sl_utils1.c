/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 08:15:54 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/16 15:19:23 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_steps(int steps, t_vars *var)
{
	char	*ret;

	if (var->bonus == 0)
	{
		ft_putstr_fd("\rSteps: ", 1);
		ft_putnbr_fd(steps, 1);
	}
	else
	{
		ret = ft_strdup("Steps: ");
		ret = ft_strjoin(ret, ft_itoa(steps - 1));
		mlx_string_put(var->mlx, var->win, 20, 20, 0x00000000, ret);
		free (ret);
		ret = ft_strdup("Steps: ");
		ret = ft_strjoin(ret, ft_itoa(steps));
		mlx_string_put(var->mlx, var->win, 20, 20, 0x00FFFFFF, ret);
		free (ret);
	}
}

void	quit(t_vars *vars, int err)
{
	if (err == 0 && vars->bonus == 0)
	{
		print_steps(++(vars->count), vars);
		ft_putstr_fd("\nYou win!", 1);
	}
	if (err == 0 && vars->bonus == 1)
		ft_putstr_fd("You win!", 1);
	if (err == -2)
		ft_putstr_fd("You got caught! You loose!", 1);
	if (err > 0)
	{
		ft_putstr_fd("Error\n", 2);
		if (err == 1)
			ft_putstr_fd("Invalid map type\n", 2);
		if (err == 2)
			ft_putstr_fd("Invalid map content\n", 2);
		exit(1);
	}
	if (err >= 0 || err == -2 || !vars->bonus)
		ft_putchar_fd('\n', 1);
	free_all(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	find_obj(char **map, char obj)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
			if (map[i][j] == obj)
				count++;
	}
	return (count);
}

int	*find_obj_cord(char **map, char obj)
{
	int	*ret;
	int	i;
	int	j;

	ret = ft_calloc(3, 1);
	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == obj)
			{
				ret[0] = i;
				ret[1] = j;
				break ;
			}
		}
		if (map[i][j] == obj)
			break ;
	}
	return (ret);
}
