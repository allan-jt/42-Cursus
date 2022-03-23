/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:21:56 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:22:01 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	main_error(int argc, char **argv)
{
	int	i;
	int	j;
	int	temp;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguements\n"));
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
			if (argv[i][j] > 57 || argv[i][j] < 48)
				return (printf("Error: non/negative numbers\n"));
		temp = ft_atoi(argv[i]);
		if (temp < 1)
			return (printf("Error: non-integers present\n"));
	}
	return (0);
}
