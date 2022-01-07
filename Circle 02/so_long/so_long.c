/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:14:22 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/15 13:50:03 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	vars.bonus = 0;
	vars.count = 0;
	vars.mlx = mlx_init();
	vars.map = m_to_a(argv[1], &vars);
	img_init(&vars.img, &vars);
	img_init_bonus(&vars.img, &vars);
	map_init(&vars, &vars.img, vars.map);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, closes, &vars);
	mlx_loop(vars.mlx);
	free_map(vars.map);
}
