/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:27:13 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:27:16 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *ph)
{
	pthread_mutex_lock(&(ph->lf_lock));
	print(ph->num, ph->info, "has taken a fork\n", 0);
	while (ph->info->n_philos == 1)
		if (ph->info->dead)
			return (0);
	pthread_mutex_lock(ph->rf_lock);
	print(ph->num, ph->info, "has taken a fork\n", 0);
	return (1);
}

int	check_all_eat(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
		if ((*info->ph)[i].n_eat < info->n_eat)
			return (0);
	return (1);
}

int	eat(t_philo *ph)
{
	ph->t_die = get_time();
	print(ph->num, ph->info, "is eating\n", 0);
	if (ph->info->n_eat > 0 && ++ph->n_eat && check_all_eat(ph->info))
	{
		ph->info->dead = 1;
		pthread_mutex_unlock(&(ph->lf_lock));
		pthread_mutex_unlock(ph->rf_lock);
		return (0);
	}
	ft_usleep(ph->info->t_eat);
	pthread_mutex_unlock(&(ph->lf_lock));
	pthread_mutex_unlock(ph->rf_lock);
	return (1);
}

int	sleeping(t_philo *ph)
{
	print(ph->num, ph->info, "is sleeping\n", 0);
	ft_usleep(ph->info->t_sleep);
	return (1);
}

int	think(t_philo *ph)
{
	print(ph->num, ph->info, "is thinking\n", 0);
	return (1);
}
