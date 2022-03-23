/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:22:41 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:22:44 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h> 
# include <semaphore.h>
# include <signal.h>

struct	s_info;

typedef struct s_philo
{
	int				pid;
	int				num;
	int				n_eat;
	long long int	t_die;
	struct s_info	*info;
	pthread_t		death_check;
	int				dead;
}				t_philo;

typedef struct s_info
{
	int				n_philos;
	long long int	t_die;
	long long int	t_eat;
	long long int	t_sleep;
	int				n_eat;
	long long int	time;
	t_philo			**ph;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*end;
	pthread_t		all_eat;
}				t_info;

int		routine(t_philo *ph);
int		ft_atoi(const char *str);
void	print(t_philo *ph, char *str, int death);
int		get_time(void);
void	ft_usleep(int ms);
int		take_forks(t_philo *ph);
int		eat(t_philo *ph);
int		sleeping(t_philo *ph);
int		think(t_philo *ph);
void	*death_checker(void *p);
int		main_error(int argc, char **argv);

#endif
