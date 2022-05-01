/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:14:16 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/28 20:14:18 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_movement(t_data *data)
{
	if (data->player.move_fw)
		move(data, 1);
	if (data->player.move_bw)
		move(data, -1);
	if (data->player.strafe_r)
		move(data, 2);
	if (data->player.strafe_l)
		move(data, -2);
	if (data->player.rotate_r)
		rotate(data, 1, 0);
	if (data->player.rotate_l)
		rotate(data, -1, 0);
}

int	render(t_data *data)
{
	static int	count;

	clear_ray_obj(data, 1);
	check_movement(data);
	print_map(data);
	change_door_status(data, count);
	change_flame_status(data, count);
	if (count++ == 1001)
		count = 0;
	return (0);
}
