/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:39:28 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 20:17:09 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_data *data, int x, int y, int r)
{
	double	pi;
	double	i;
	double	angle;
	double	x1;
	double	y1;

	pi = 3.14159265359;
	while (r > 0)
	{
		i = 0.0;
		while (i < 360)
		{
			angle = i;
			x1 = r * cos(angle * pi / 180);
			y1 = r * sin(angle * pi / 180);
			my_mlx_pixel_put(data, x + x1, y + y1, 0x00FF0000);
			i += 0.1;
		}
		r--;
	}
}

void	draw_rect(t_data *data, int *position, int *dimensions, int color)
{
	int	i;
	int	j;

	j = -1;
	while (++j < dimensions[Y])
	{
		i = -1;
		while (++i < dimensions[X])
			my_mlx_pixel_put(data, position[X] + i,
				position[Y] + j, color);
	}
}
