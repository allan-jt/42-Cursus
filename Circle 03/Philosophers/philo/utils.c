/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:28:20 by athekkep          #+#    #+#             */
/*   Updated: 2022/02/10 17:28:24 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	print(int ph, t_info *info, char *str, int death)
{	
	pthread_mutex_lock(&info->print);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->print);
		return ;
	}
	printf("%lld %d %s", (get_time() - info->time), ph, str);
	if (death)
		info->dead = 1;
	pthread_mutex_unlock(&info->print);
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
