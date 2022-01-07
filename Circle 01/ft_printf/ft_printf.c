/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:25:31 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/02 09:16:52 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, str);
	count = 0;
	while (*str != '\0')
	{
		if (*str == '%')
			str = id_convert((char *) str, &count, &ap);
		else
			print_char(*str, &count);
		if (*str == '%')
			print_char(*str, &count);
		str++;
	}
	va_end(ap);
	return (count);
}
