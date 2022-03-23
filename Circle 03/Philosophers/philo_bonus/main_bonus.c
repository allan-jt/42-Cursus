/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:22:07 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:22:11 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_checker(void *p)
{
	t_philo	*ph;

	ph = (t_philo *) p;
	while (1)
	{
		if (get_time() - ph->t_die > ph->info->t_die)
		{
			print(ph, "died\n", 1);
			sem_post(ph->info->end);
			return (NULL);
		}
	}
	return (NULL);
}

void	*eat_checker(void *p)
{
	t_info	*info;
	int		i;

	info = (t_info *) p;
	if (!info->n_eat)
		return (NULL);
	i = info->n_philos;
	while (i-- > 0)
		waitpid((*info->ph)[i].pid, NULL, 0);
	sem_post(info->end);
	return (NULL);
}

void	init_structs(t_info *info, char **argv, int argc, t_philo **ph)
{
	static int	i;

	info->n_philos = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_eat = 0;
	if (argc == 6)
		info->n_eat = ft_atoi(argv[5]);
	*ph = (t_philo *) malloc(sizeof(t_philo) * info->n_philos);
	info->ph = ph;
	sem_unlink("/print");
	sem_unlink("/frk");
	sem_unlink("/end");
	info->print = sem_open("/print", O_CREAT, S_IRUSR | S_IWUSR, 1);
	info->forks = sem_open("/frk", O_CREAT, S_IRUSR | S_IWUSR, info->n_philos);
	info->end = sem_open("/end", O_CREAT, S_IRUSR | S_IWUSR, 0);
	while (i < info->n_philos)
	{
		(*ph)[i].num = i + 1;
		(*ph)[i].n_eat = 0;
		(*ph)[i].dead = 0;
		(*ph)[i++].info = info;
	}
	info->time = get_time();
}

void	free_philo(t_info *info)
{
	sem_close(info->print);
	sem_close(info->forks);
	sem_close(info->end);
	sem_unlink("/print");
	sem_unlink("/frk");
	sem_unlink("/end");
	free(*(info->ph));
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_info	info;
	int		i;

	if (main_error(argc, argv))
		return (1);
	i = -1;
	init_structs(&info, argv, argc, &ph);
	while (++i < info.n_philos)
	{
		ph[i].pid = fork();
		if (ph[i].pid == 0)
		{
			ph[i].t_die = get_time();
			pthread_create(&(ph[i].death_check), NULL,
				&death_checker, &ph[i]);
			return (routine(&ph[i]));
		}
	}
	pthread_create(&(info.all_eat), NULL, &eat_checker, &info);
	sem_wait(info.end);
	while (i-- > 0)
		kill(ph[i].pid, SIGKILL);
	pthread_join(info.all_eat, NULL);
	free_philo(&info);
}
