/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:27:36 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:27:39 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *p)
{
	t_philo	*ph;

	ph = (t_philo *) p;
	if (ph->num % 2 == 0 && ph->info->n_philos != 1)
		ft_usleep(ph->info->t_eat);
	while (!ph->info->dead)
		if (!take_forks(ph) || !eat(ph) || !sleeping(ph) || !think(ph))
			break ;
	return (NULL);
}

void	death_checker(t_philo *ph)
{
	int		i;

	while (1)
	{
		i = ph->info->n_philos;
		while (i-- > 0)
		{
			if (get_time() - ph[i].t_die > ph->info->t_die)
			{
				print(ph[i].num, ph[i].info, "died\n", 1);
				return ;
			}
		}
	}
}

void	init_info(t_info *info, char **argv, int argc, t_philo **ph)
{
	info->n_philos = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_eat = 0;
	if (argc == 6)
		info->n_eat = ft_atoi(argv[5]);
	info->ph = ph;
	info->dead = 0;
	*ph = (t_philo *) malloc(sizeof(t_philo) * info->n_philos);
	pthread_mutex_init(&info->print, NULL);
}

void	init_philo(t_philo *ph, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
		ph[i].rf_lock = NULL;
	i = -1;
	while (++i < info->n_philos)
	{
		ph[i].num = i + 1;
		ph[i].n_eat = 0;
		pthread_mutex_init(&(ph[i].lf_lock), NULL);
		if (i < info->n_philos - 1)
			ph[i + 1].rf_lock = &(ph[i].lf_lock);
		else if (i == info->n_philos - 1 && i != 0)
			ph[0].rf_lock = &(ph[i].lf_lock);
		ph[i].info = info;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_info	info;
	int		i;

	if (main_error(argc, argv))
		return (1);
	init_info(&info, argv, argc, &ph);
	init_philo(ph, &info);
	i = -1;
	info.time = get_time();
	while (++i < info.n_philos)
	{
		ph[i].t_die = get_time();
		pthread_create(&(ph[i].th), NULL, &routine, &(ph[i]));
	}
	death_checker(ph);
	while (i-- > 0)
	{
		pthread_join(ph[i].th, NULL);
		pthread_mutex_destroy(&ph[i].lf_lock);
	}
	pthread_mutex_destroy(&info.print);
	free(ph);
	return (0);
}
