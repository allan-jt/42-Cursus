/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:48:27 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/06 16:09:06 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == 0)
		write(fd, "0", 1);
	if (n > 0)
	{
		c = (n % 10) + '0';
		if (n / 10 != 0)
			ft_putnbr_fd(n / 10, fd);
		write(fd, &c, 1);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		c = ((n % 10) * -1) + '0';
		if (n / 10 != 0)
			ft_putnbr_fd((n / 10) * -1, fd);
		write(fd, &c, 1);
	}
}
