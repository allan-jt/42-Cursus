/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:51:50 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 12:58:35 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strafe_r(t_data *data, double unit_x, double unit_y)
{
	int	index_x;
	int	index_y;

	index_y = ((int)round(data->player.y - -unit_x * 15 * SPEED) / BLOCK_SIZE);
	if (index_y > data->map_height - 1)
		index_y = data->map_height - 1;
	if (index_y < 0)
		index_y = 0;
	index_x = ((int)round(data->player.x - unit_y * 15 * SPEED) / BLOCK_SIZE);
	if (index_x > data->map_width - 1)
		index_x = data->map_width - 1;
	if (index_x < 0)
		index_x = 0;
	if ((data->map[index_y][index_x] - '0') % 2 != 1)
	{
		data->player.x -= unit_y * SPEED;
		data->player.y -= -unit_x * SPEED;
	}
}

void	strafe_l(t_data *data, double unit_x, double unit_y)
{
	int	index_x;
	int	index_y;

	index_y = ((int)round(data->player.y - unit_x * 15 * SPEED) / BLOCK_SIZE);
	if (index_y > data->map_height - 1)
		index_y = data->map_height - 1;
	if (index_y < 0)
		index_y = 0;
	index_x = ((int)round(data->player.x - -unit_y * 15 * SPEED) / BLOCK_SIZE);
	if (index_x > data->map_width - 1)
		index_x = data->map_width - 1;
	if (index_x < 0)
		index_x = 0;
	if ((data->map[index_y][index_x] - '0') % 2 != 1)
	{
		data->player.x -= -unit_y * SPEED;
		data->player.y -= unit_x * SPEED;
	}	
}

void	mv_bw(t_data *data, double unit_x, double unit_y)
{
	int	index_x;
	int	index_y;

	index_y = ((int)round(data->player.y - unit_y * 15 * SPEED) / BLOCK_SIZE);
	if (index_y > data->map_height - 1)
		index_y = data->map_height - 1;
	if (index_y < 0)
		index_y = 0;
	index_x = ((int)round(data->player.x - unit_x * 15 * SPEED) / BLOCK_SIZE);
	if (index_x > data->map_width - 1)
		index_x = data->map_width - 1;
	if (index_x < 0)
		index_x = 0;
	if ((data->map[index_y][index_x] - '0') % 2 != 1)
	{
		data->player.x -= unit_x * SPEED;
		data->player.y -= unit_y * SPEED;
	}
}

void	mv_fw(t_data *data, double unit_x, double unit_y)
{
	int	index_x;
	int	index_y;

	index_y = ((int)round(data->player.y + unit_y * 15 * SPEED) / BLOCK_SIZE);
	if (index_y > data->map_height - 1)
		index_y = data->map_height - 1;
	if (index_y < 0)
		index_y = 0;
	index_x = ((int)round(data->player.x + unit_x * 15 * SPEED) / BLOCK_SIZE);
	if (index_x > data->map_width - 1)
		index_x = data->map_width - 1;
	if (index_x < 0)
		index_x = 0;
	if ((data->map[index_y][index_x] - '0') % 2 != 1)
	{
		data->player.x += unit_x * SPEED;
		data->player.y += unit_y * SPEED;
	}
}

void	move(t_data *data, int dir)
{
	double	unit_x;
	double	unit_y;	

	unit_x = (data->player.rays[WIDTH / 2].ray_x - data->player.x) \
	/ (data->player.rays[WIDTH / 2].mag);
	unit_y = (data->player.rays[WIDTH / 2].ray_y - data->player.y) \
	/ (data->player.rays[WIDTH / 2].mag);
	if (dir == 1)
		mv_fw(data, unit_x, unit_y);
	else if (dir == -1)
		mv_bw(data, unit_x, unit_y);
	else if (dir == 2)
		strafe_r(data, unit_x, unit_y);
	else if (dir == -2)
		strafe_l(data, unit_x, unit_y);
	if (data->player.x < 0)
		data->player.x = 0;
	if (data->player.x >= (data->map_width) * BLOCK_SIZE)
		data->player.x = (data->map_width - 1) * BLOCK_SIZE;
	if (data->player.y < 0)
		data->player.y = 0;
	if (data->player.y >= (data->map_height) * BLOCK_SIZE)
		data->player.y = (data->map_height - 1) * BLOCK_SIZE;
	init_rays_mag(data);
}
