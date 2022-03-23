/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:23:01 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 18:03:18 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static unsigned int	ret_check(unsigned int i, int sign)
{
	if (i > 2147483647 && sign == 1)
		return (-1);
	if (i > 2147483648 && sign == -1)
		return (0);
	else
		return (i * sign);
}

int	ft_atoi(const char *str)
{
	unsigned int	num;
	int				found;
	int				sign;

	num = 0;
	found = 0;
	sign = 1;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			found = 1;
			num = (num * 10) + (*str - '0');
		}
		else if ((*str == '+' || *str == '-') && found == 0)
		{
			found = 1;
			sign = 44 - *str;
		}
		else if ((*str != ' ' && !(*str >= '\t' && *str <= '\r')
				&& found == 0) || found == 1)
			break ;
		str++;
	}
	return ((int) ret_check(num, sign));
}

void	print(t_philo *ph, char *str, int death)
{	
	sem_wait(ph->info->print);
	printf("%lld %d %s", (get_time() - ph->info->time), ph->num, str);
	if (death)
		return ;
	sem_post(ph->info->print);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	int	times;

	times = get_time();
	while (get_time() - times < ms)
		usleep(100);
}
