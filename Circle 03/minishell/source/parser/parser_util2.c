/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:19:56 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 20:22:01 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_len(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	check_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r')))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int	issymbol(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	moving(char *line, int *i)
{
	while (line[*i] == '<' || line[*i] == '>')
		(*i)++;
	while (line[*i] && (line[*i] == ' '
			|| (line[*i] >= '\t' && line[*i] <= '\r')))
		(*i)++;
}
