/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:40:37 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/29 15:31:50 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_name(t_data *data, int argc, char **argv)
{
	if (argc != 2)
		print_error(data, "Wrong number of args!");
	if (ft_strrchr(argv[1], '.'))
	{
		if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) \
		|| ft_strlen(argv[1]) == 4)
			print_error(data, "Wrong Input file!");
	}
	else
		print_error(data, "Wrong Input file!\n");
	data->config_fd = open(argv[1], O_RDWR);
	if (data->config_fd < 0)
		print_error(data, strerror(errno));
}

void	validate_map_contents(t_data *data)
{
	check_chars(data);
	resize_width(data);
	check_if_closed_by_walls(data);
	check_spaces_from_all_dir(data);
	check_if_valid_doors(data);
}

int	parse_map(t_data *data, int argc, char **argv)
{
	check_map_name(data, argc, argv);
	check_elements(data);
	if (!data->no_path || !data->so_path || !data->we_path || !data->ea_path || \
	!data->c_color_count || !data->f_color_count)
		print_error(data, "Wrong Config File");
	parse_map_contents(data);
	validate_map_contents(data);
	return (0);
}
