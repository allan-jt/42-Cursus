/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:20:14 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:20:21 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	routine(t_philo *ph)
{
	if (ph->num % 2 == 0 && ph->info->n_philos != 1)
		ft_usleep(ph->info->t_eat);
	while (!ph->dead)
		if (!take_forks(ph) || !eat(ph) || !sleeping(ph) || !think(ph))
			break ;
	return (0);
}

int	take_forks(t_philo *ph)
{
	sem_wait(ph->info->forks);
	print(ph, "has taken a fork\n", 0);
	sem_wait(ph->info->forks);
	print(ph, "has taken a fork\n", 0);
	return (1);
}

int	eat(t_philo *ph)
{
	ph->t_die = get_time();
	print(ph, "is eating\n", 0);
	if (ph->info->n_eat > 0 && ++ph->n_eat == ph->info->n_eat)
	{
		ph->dead = 1;
		sem_post(ph->info->forks);
		sem_post(ph->info->forks);
		return (0);
	}
	ft_usleep(ph->info->t_eat);
	sem_post(ph->info->forks);
	sem_post(ph->info->forks);
	return (1);
}

int	sleeping(t_philo *ph)
{
	print(ph, "is sleeping\n", 0);
	ft_usleep(ph->info->t_sleep);
	return (1);
}

int	think(t_philo *ph)
{
	print(ph, "is thinking\n", 0);
	return (1);
}
