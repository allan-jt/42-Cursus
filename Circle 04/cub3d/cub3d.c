/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:32 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/29 12:48:38 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rays_mag(t_data *data)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
	{
		data->player.rays[i].ray_x = data->player.x + 0.1;
		data->player.rays[i].ray_y = data->player.y;
		data->player.rays[i].mag = sqrt(pow(data->player.rays[i].ray_x
					- data->player.x, 2) + pow(data->player.rays[i].ray_y
					- data->player.y, 2));
		rotate(data, 0, i);
	}
}

void	find_player(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] != 'N' && data->map[y][x] != 'S'
				&& data->map[y][x] != 'W' && data->map[y][x] != 'E')
				continue ;
			data->player.x = (x * BLOCK_SIZE) + (BLOCK_SIZE / 2);
			data->player.y = (y * BLOCK_SIZE) + (BLOCK_SIZE / 2);
			init_rays_mag(data);
			data->map[y][x] = '0';
			return ;
		}
	}	
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		print_error(data, "Malloc Error!");
	data->start_angle = 0.00000001;
	if (parse_map(data, argc, argv))
		return (1);
	data_init(data);
	find_player(data);
	change_door_status(data, 5);
	change_flame_status(data, 2);
	print_map(data);
	mlx_mouse_hook(data->win, mouse_rotate, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 0x2, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}
