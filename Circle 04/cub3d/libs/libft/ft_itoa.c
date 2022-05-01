/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 07:19:05 by mal-guna          #+#    #+#             */
/*   Updated: 2021/10/03 16:12:43 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	signs(int n)
{
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	return (sign);
}

static int	ft_length(long num, int sign)
{
	int	length;

	length = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 10;
		length++;
	}
	if (sign == -1)
	{
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	int		len;
	long	temp;

	temp = n;
	sign = signs(n);
	if (n < 0)
		temp = -temp;
	len = ft_length(temp, sign);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (sign == -1)
		res[0] = '-';
	res[len--] = '\0';
	while (temp != 0)
	{
		res[len--] = ((long)temp % 10) + '0';
		temp = temp / 10;
	}
	return (res);
}
