/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:14:07 by athekkep          #+#    #+#             */
/*   Updated: 2022/04/29 16:01:13 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	insdie_wall(t_data *data, int x, int y, int i)
{
	int	pos[3];

	if (y >= data->map_height)
		y = data->map_height - 1;
	if (y < 0)
		y = 0;
	if (x >= data->map_width)
		x = data->map_width - 1;
	if (x < 0)
		x = 0;
	pos[Y] = y;
	pos[X] = x;
	pos[2] = i;
	if (data->map[y][x] - '0' >= FLAME_MAP_F)
		raycast_sprite(data, i, pos);
	else if (data->map[y][x] - '0' >= DOOR_MAP_C)
		store_sprite(data, data->player.rays[i].hit_point,
			data->player.rays[i].mag, pos);
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

static int	check_wall(t_data *data, int i, int *dir, int *nxt_pt)
{
	int	x;
	int	y;
	int	side;

	side = dir[2];
	x = (int)(data->player.rays[i].ray_x + 0.00001) / 32;
	y = (int)(data->player.rays[i].ray_y + 0.00001) / 32;
	if (dir[Y] == SOUTH_TEXT && dir[X] == WEST_TEXT)
	{
		x = (int)(data->player.rays[i].ray_x) / 32;
		y = (nxt_pt[Y] / 32) - 1;
		if (side)
		{
			x = nxt_pt[X] / 32;
			y = (int)(data->player.rays[i].ray_y) / 32;
		}
	}
	else if (dir[Y] == SOUTH_TEXT && dir[X] == EAST_TEXT && !side)
		y -= 1;
	else if (dir[X] == EAST_TEXT && side)
		x -= 1;
	return (insdie_wall(data, x, y, i));
}

void	get_next_point(t_data *data, int i, int *nxt_pt, int *dir)
{
	nxt_pt[X] = (int)(((data->player.rays[i].ray_x + 0.00001) / 32) + 1) *32;
	nxt_pt[Y] = (int)(((data->player.rays[i].ray_y + 0.00001) / 32) + 1) *32;
	if (dir[X] == WEST_TEXT && dir[Y] == SOUTH_TEXT)
		nxt_pt[Y] = (((int)(data->player.rays[i].ray_y
						+ 0.00001) / 32) - 1) * 32;
	else if (dir[X] == EAST_TEXT && dir[Y] == SOUTH_TEXT)
	{
		nxt_pt[Y] = (((int)(data->player.rays[i].ray_y
						+ 0.00001) / 32) - 1) * 32;
		nxt_pt[X] = (((int)(data->player.rays[i].ray_x
						+ 0.00001) / 32) - 1) * 32;
	}
	else if (dir[X] == EAST_TEXT && dir[Y] == NORTH_TEXT)
		nxt_pt[X] = (((int)(data->player.rays[i].ray_x
						+ 0.00001) / 32) - 1) * 32;
	if (dir[X] == WEST_TEXT && dir[Y] == NORTH_TEXT)
		return ;
	if (data->player.rays[i].ray_y - (double) nxt_pt[Y] > 32)
		nxt_pt[Y] += 32;
	if (data->player.rays[i].ray_x - (double) nxt_pt[X] > 32)
		nxt_pt[X] += 32;
}

void	raycast(t_data *data, double *diff, int i, int *dir)
{
	double	factor[2];
	int		nxt_pt[2];
	int		j;

	diff[X] = data->player.rays[i].ray_x - data->player.x;
	diff[Y] = data->player.rays[i].ray_y - data->player.y;
	get_next_point(data, i, nxt_pt, dir);
	if (nxt_pt[Y] > data->map_height * 32 || nxt_pt[Y] < 0
		|| nxt_pt[X] > data->map_width * 32 || nxt_pt[X] < 0)
		return ;
	factor[X] = 1 + ((nxt_pt[X] - data->player.rays[i].ray_x)) / diff[X];
	factor[Y] = 1 + ((nxt_pt[Y] - data->player.rays[i].ray_y)) / diff[Y];
	j = (factor[X] <= factor[Y]);
	data->player.rays[i].mag = data->player.rays[i].mag * factor[j];
	rotate(data, 0, i);
	data->player.rays[i].direction = dir[j];
	data->player.rays[i].hit_point = (int)
		round(data->player.rays[i].ray_y) % 32;
	if (j == 0)
		data->player.rays[i].hit_point = (int)
			round(data->player.rays[i].ray_x) % 32;
	dir[2] = j;
	if (!check_wall(data, i, dir, nxt_pt))
		raycast(data, diff, i, dir);
}

/* Y: N/S texture | X: W/E texture */
void	check_line(t_data *data)
{
	double	diff[2];
	int		dir[3];
	int		i;

	i = -1;
	while (++i < WIDTH)
	{
		diff[X] = data->player.rays[i].ray_x - data->player.x;
		diff[Y] = data->player.rays[i].ray_y - data->player.y;
		data->player.rays[i].mag = 0.0001;
		rotate(data, 0, i);
		dir[Y] = NORTH_TEXT;
		dir[X] = WEST_TEXT;
		if (diff[X] >= 0 && diff[Y] < 0)
			dir[Y] = SOUTH_TEXT;
		else if (diff[X] < 0 && diff[Y] <= 0)
		{
			dir[Y] = SOUTH_TEXT;
			dir[X] = EAST_TEXT;
		}
		else if (diff[X] <= 0 && diff[Y] > 0)
			dir[X] = EAST_TEXT;
		raycast(data, diff, i, dir);
	}
}

/*void	check_line(t_data *data)
{
	double	dx;
	double	dy;
	int i = 0;
	while(i < WIDTH)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		
		if(dx > 0 && dy >= 0)// next_point = d * factor + data->player.linex
			ray_se(data, dx, dy, i);
		else if(dx >= 0 && dy < 0)// next_point = d * factor + data->player.linex
			ray_ne(data, dx, dy, i);
		else if(dx < 0 && dy <= 0)// next_point = d * factor + data->player.linex
			ray_nw(data, dx, dy, i);
		else if(dx <= 0 && dy > 0)// next_point = d * factor + data->player.linex
			ray_sw(data, dx, dy, i);
		i++;
	}
}
void ray_se(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	double  p1;
	double	p2;
	data->player.rays[i].mag = 0.1;
	rotate(data, 0, i);
	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		p1 = (data->player.rays[i].ray_x + 0.00001) / 32  + 1;
		p2 = (data->player.rays[i].ray_y + 0.00001) / 32  + 1;
		next_xpoint = (int) p1 * 32;
		next_ypoint = (int) p2 * 32;
		if(next_ypoint > data->map_height * 32 || next_xpoint
		> data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = WEST_TEXT;
			data->player.rays[i].hit_point = 
			(int)round(data->player.rays[i].ray_y) % data->img[WEST_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001)
			/ 32), (((int)(data->player.rays[i].ray_y+0.000001) )/ 32), i))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = NORTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x)
			% data->img[NORTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32),
			(((int)(data->player.rays[i].ray_y+0.000001) )/ 32), i))
				break;
		}
	}
}
void ray_ne(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.rays[i].mag = 0.1;
	
	rotate(data, 0, i);
	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		next_xpoint =(((int)(data->player.rays[i].ray_x + 0.00001) / 32) + 1) * 32;
		next_ypoint =(((int)(data->player.rays[i].ray_y + 0.00001) / 32) - 1) * 32;
		if(data->player.rays[i].ray_y - (double) next_ypoint > 32)
			next_ypoint += 32;
		if(data->player.rays[i].ray_x - (double) next_xpoint > 32)
			next_xpoint += 32;
		if(next_ypoint > data->map_height * 32 || next_xpoint > 
		data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			if(factorx == factory)
				printf("oho\n");
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = WEST_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y) 
			% data->img[WEST_TEXT].width;
			if(insdie_wall(data, next_xpoint/32, 
			(((int)(data->player.rays[i].ray_y) )/ 32), i))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = SOUTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x) 
			% data->img[SOUTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x) / 32), 
			(next_ypoint/32)-1, i))
				break;
		}
	}
}
void ray_nw(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	data->player.rays[i].mag = 0.1;
	rotate(data, 0, i);
	//printf("3\n");
	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		next_xpoint =(((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1) * 32;
		next_ypoint =(((int)(data->player.rays[i].ray_y + 0.00001) / 32) - 1) * 32;
		if(data->player.rays[i].ray_y - (double) next_ypoint > 32)
			next_ypoint += 32;
		if(data->player.rays[i].ray_x - (double) next_xpoint > 32)
			next_xpoint += 32;
		if(next_ypoint > data->map_height * 32 || 
		next_xpoint > data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = EAST_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y) 
			% data->img[EAST_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1, 
			(((int)(data->player.rays[i].ray_y+0.00001) )/ 32), i))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = SOUTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x)
			 % data->img[SOUTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32),
			 (((int)(data->player.rays[i].ray_y+0.00001) )/ 32) -1, i))
				break;
		}
	}
}
void ray_sw(t_data *data, double dx, double dy, int i)
{
	int		next_xpoint;
	int		next_ypoint;
	double	factorx;
	double	factory;
	//printf("4\n");
	data->player.rays[i].mag = 0.1;
	rotate(data, 0, i);
	while(1)
	{
		dx = data->player.rays[i].ray_x - data->player.x;
		dy = data->player.rays[i].ray_y - data->player.y;
		next_xpoint =(((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1) * 32;
		next_ypoint =(((int)(data->player.rays[i].ray_y + 0.00001) / 32) + 1) * 32;
		if(data->player.rays[i].ray_y - (double) next_ypoint > 32)
			next_ypoint += 32;
		if(data->player.rays[i].ray_x - (double) next_xpoint > 32)
			next_xpoint += 32;
		if(next_ypoint > data->map_height * 32 || next_xpoint > 
		data->map_width * 32 || next_ypoint < 0 || next_xpoint < 0)
			break ;
		factorx = 1 + ((next_xpoint - data->player.rays[i].ray_x)) / dx;
		factory = 1 + ((next_ypoint - data->player.rays[i].ray_y)) / dy;
		if(factorx <= factory)
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factorx;
			rotate(data, 0, i);
			data->player.rays[i].direction = EAST_TEXT;                           
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_y)
			% data->img[EAST_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32) - 1,
			 (((int)(data->player.rays[i].ray_y+0.00001) )/ 32), i))
				break;
		}
		else
		{
			data->player.rays[i].mag = data->player.rays[i].mag * factory;
			rotate(data, 0, i);
			data->player.rays[i].direction = NORTH_TEXT;
			data->player.rays[i].hit_point = (int)round(data->player.rays[i].ray_x)
			 % data->img[NORTH_TEXT].width;
			if(insdie_wall(data, ((int)(data->player.rays[i].ray_x + 0.00001) / 32),
			 (((int)(data->player.rays[i].ray_y+0.00001) )/ 32), i))
				break;
		}
	}
}*/