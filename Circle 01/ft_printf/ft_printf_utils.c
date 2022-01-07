/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:17:13 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/02 09:49:08 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_all(char **s1)
{
	free(*s1);
	*s1 = NULL;
}

void	print_char(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

t_flag	*initialize_flag(char c)
{
	t_flag	*ret;

	ret = malloc(sizeof(t_flag));
	ret->type = c;
	ret->minus = 0;
	ret->period = 0;
	ret->zero = 0;
	ret->pstval = 0;
	ret->preval = 0;
	ret->hash = 0;
	ret->plus = 0;
	ret->space = 0;
	return (ret);
}

t_flag	*set_flags(char *str, char *ptr)
{
	t_flag	*ret;

	ret = initialize_flag(*str);
	if (ft_strchr(ptr, '-') < str)
		ret->minus = 1;
	else if (ft_strchr(ptr, '0') < str
		&& !ft_isdigit(*(ft_strchr(ptr, '0') - 1)))
		ret->zero = 1;
	if (ft_strchr(ptr, '+') < str)
		ret->plus = 1;
	else if (ft_strchr(ptr, ' ') < str)
		ret->space = 1;
	if (ft_strchr(ptr, '#') < str)
		ret->hash = 1;
	if (ft_strchr(ptr, '.') < str)
	{
		ret->period = 1;
		if (ret->type != 's' && ret->type != 'c')
			ret->zero = 0;
		ret->pstval = ft_atoi(ft_strchr(ptr, '.') + 1);
	}
	while (ft_isdigit(*ptr) != 1 && ptr < str && *ptr != '.')
		ptr++;
	ret->preval = ft_atoi(ptr);
	return (ret);
}

char	*id_convert(char *str, int *count, va_list *ap)
{
	char	*id_found;
	char	*ptr;

	ptr = str;
	while (*(++str) != '\0')
	{
		id_found = ft_strchr("cspdiuxX%", *str);
		if (*id_found == 'c')
			print_car(set_flags(str, ptr), va_arg(*ap, int), count);
		else if (*id_found == 's')
			print_str(set_flags(str, ptr), va_arg(*ap, char *), count);
		else if (*id_found == 'p')
			print_hex(set_flags(str, ptr),
				(unsigned long long) va_arg(*ap, void *), count);
		else if (*id_found == 'd' || *id_found == 'i')
			num_process(set_flags(str, ptr), va_arg(*ap, int), count);
		else if (*id_found == 'u')
			us_proc(set_flags(str, ptr), va_arg(*ap, unsigned int), count);
		else if (*id_found == 'x' || *id_found == 'X')
			print_hex(set_flags(str, ptr),
				(unsigned int) va_arg(*ap, unsigned long long), count);
		if (*id_found != '\0')
			break ;
	}
	return (str);
}
