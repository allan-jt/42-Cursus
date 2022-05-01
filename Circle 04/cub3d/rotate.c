/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:53:09 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 12:53:20 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_data *data, int dir, int i)
{	
	int	j;

	if (dir == 0)
	{
		data->player.rays[i].ray_x = data->player.rays[i].mag
			* cos(data->player.rays[i].rot) + data->player.x;
		data->player.rays[i].ray_y = data->player.rays[i].mag
			* sin(data->player.rays[i].rot) + data->player.y;
		return ;
	}
	j = -1;
	while (++j < WIDTH)
	{
		data->player.rays[j].rot += (dir * ROTATION_SPEED);
		data->player.rays[j].ray_x = data->player.rays[j].mag
			* cos(data->player.rays[j].rot) + data->player.x;
		data->player.rays[j].ray_y = data->player.rays[j].mag
			* sin(data->player.rays[j].rot) + data->player.y;
	}
}
