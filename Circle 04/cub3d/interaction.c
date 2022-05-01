/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:13:50 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/28 20:13:51 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		close_window(data);
	if (key == KEY_W)
		data->player.move_fw = 1;
	else if (key == KEY_A)
		data->player.strafe_l = 1;
	else if (key == KEY_S)
		data->player.move_bw = 1;
	else if (key == KEY_D)
		data->player.strafe_r = 1;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 1;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.move_fw = 0;
	else if (key == KEY_A)
		data->player.strafe_l = 0;
	else if (key == KEY_S)
		data->player.move_bw = 0;
	else if (key == KEY_D)
		data->player.strafe_r = 0;
	else if (key == KEY_RIGHT)
		data->player.rotate_r = 0;
	else if (key == KEY_LEFT)
		data->player.rotate_l = 0;
	else if (key == DOORS)
		door_status(data);
	return (0);
}

int	mouse_rotate(int key, int x, int y, t_data *data)
{
	if (x || y)
		{}
	if (key == 1)
		rotate(data, -2, 0);
	if (key == 2)
		rotate(data, 2, 0);
	if (key == 4)
		rotate(data, 3, 0);
	if (key == 5)
		rotate(data, -3, 0);
	return (key);
}
