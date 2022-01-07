/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:45:51 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/02 09:50:17 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_num(t_flag *flags, char *num, int *count, int sign)
{
	while ((int)ft_strlen(num) - sign < flags->pstval)
		num = ft_strjoin_num(ft_strdup("0"), num);
	while (flags->zero && (int)ft_strlen(num) < flags->preval)
		num = ft_strjoin_num(ft_strdup("0"), num);
	while (!flags->zero && !flags->minus && (int)ft_strlen(num) < flags->preval)
		num = ft_strjoin_num(ft_strdup(" "), num);
	while (flags->minus && (int)ft_strlen(num) < flags->preval)
		num = ft_strjoin(num, ft_strdup(" "));
	*count += ft_printf("%s", num);
	free(flags);
	free_all(&num);
}

void	num_process(t_flag *flags, int ret, int *count)
{
	char	*num;
	int		sign;

	if (ret == 0 && flags->period && flags->pstval <= 0)
	{
		print_num(flags, ft_strdup(""), count, 0);
		return ;
	}
	num = ft_itoa(ret);
	sign = 0;
	if (flags->plus && ret >= 0)
		num = ft_strjoin(ft_strdup("+"), num);
	else if (flags->space && ret >= 0)
		num = ft_strjoin(ft_strdup(" "), num);
	if (ft_isdigit(*num) == 0)
		sign = 1;
	print_num(flags, num, count, sign);
}

void	us_proc(t_flag *flags, unsigned long long ret, int *count)
{
	char				*num;
	int					len;
	unsigned long long	temp;

	if (ret == 0 && flags->period && flags->pstval <= 0)
	{
		print_num(flags, ft_strdup(""), count, 0);
		return ;
	}
	temp = ret;
	len = 0;
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	num = ft_calloc(len + 2, 1);
	if (ret == 0)
		*num = '0';
	while (ret > 0)
	{
		num[--len] = (ret % 10) + '0';
		ret /= 10;
	}
	print_num(flags, num, count, 0);
}
