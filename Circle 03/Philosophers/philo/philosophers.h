/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:28:07 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:28:12 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

struct	s_info;

typedef struct s_philo
{
	pthread_t		th;
	int				num;
	int				n_eat;
	long long int	t_die;
	pthread_mutex_t	lf_lock;
	pthread_mutex_t	*rf_lock;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				n_philos;
	long long int	t_die;
	long long int	t_eat;
	long long int	t_sleep;
	int				n_eat;
	int				dead;
	long long int	time;
	t_philo			**ph;
	pthread_mutex_t	print;
}				t_info;

int		ft_atoi(const char *str);
int		get_time(void);
void	print(int ph, t_info *info, char *str, int death);
int		check_all_eat(t_info *info);
int		take_forks(t_philo *ph);
int		eat(t_philo *ph);
int		sleeping(t_philo *ph);
int		think(t_philo *ph);
int		eat_allowed(t_info *info, int num);
void	death_checker(t_philo *ph);
void	ft_usleep(int ms);
int		main_error(int argc, char **argv);

#endif
