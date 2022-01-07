/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:21:13 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/08 14:31:31 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "so_long.h"

int		**moves_init(t_vars *vars);
void	move_random(t_vars *vars, int i, int j, int **moves);
void	move_enemy(t_vars *vars, int **moves);
void	render_next_enemy(t_vars *vars);
int		render_next_player(t_vars *vars);

#endif
