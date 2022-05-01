/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:14:24 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/28 20:14:26 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	gradient_diff(double *grad1, double *grad2)
{
	double	gradient1;
	double	gradient2;

	if (grad1[X] == 0)
		gradient1 = INT_MAX;
	else
		gradient1 = grad1[Y] / grad1[X];
	if (grad2[X] == 0)
		gradient2 = INT_MAX;
	else
		gradient2 = grad1[Y] / grad1[X];
	return (gradient1 - gradient2);
}

void	store_sprite(t_data *data, int hitpoint, double mag, int *pos)
{
	int	index;
	int	new_size;
	int	i;

	i = pos[2];
	index = data->player.rays[i].obj_num++;
	data->player.rays[i].obj_direction[index]
		= obj_status(data, pos[X], pos[Y], 2);
	data->player.rays[i].obj_hit_point[index] = hitpoint;
	data->player.rays[i].obj_mag[index] = mag;
	data->player.rays[i].obj_x[index] = pos[X];
	data->player.rays[i].obj_y[index] = pos[Y];
	new_size = sizeof(int) * (index + 2);
	data->player.rays[i].obj_direction
		= realloc(data->player.rays[i].obj_direction, new_size);
	data->player.rays[i].obj_hit_point
		= realloc(data->player.rays[i].obj_hit_point, new_size);
	data->player.rays[i].obj_mag
		= realloc(data->player.rays[i].obj_mag, new_size);
	data->player.rays[i].obj_x
		= realloc(data->player.rays[i].obj_x, new_size);
	data->player.rays[i].obj_y
		= realloc(data->player.rays[i].obj_y, new_size);
}

void	raycast_sprite(t_data *data, int i, int *pos)
{
	double	mid_slope[2];
	double	mid_dist;
	double	ray_slope[2];
	int		dist;
	double	angle;

	mid_slope[Y] = (pos[Y] * 32) + 16 - data->player.y;
	mid_slope[X] = (pos[X] * 32) + 16 - data->player.x;
	ray_slope[Y] = data->player.rays[i].ray_y - data->player.y;
	ray_slope[X] = data->player.rays[i].ray_x - data->player.x;
	mid_dist = sqrt(pow(mid_slope[Y], 2) + pow(mid_slope[X], 2));
	angle = acos(((mid_slope[Y] * ray_slope[Y]) + (mid_slope[X] * ray_slope[X]))
			/ (sqrt(pow(ray_slope[Y], 2) + pow(ray_slope[X], 2)) * mid_dist));
	dist = (int) round(mid_dist * tan(angle));
	if (dist > 16)
		return ;
	if (dist == 0)
		dist = 16;
	else if (gradient_diff(ray_slope, mid_slope) < 0)
		dist = abs(dist - 16);
	else
		dist = abs(dist + 16);
	store_sprite(data, dist, mid_dist / cos(angle), pos);
}
