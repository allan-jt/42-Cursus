/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:53:27 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/02 11:17:16 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_car(t_flag *flags, char ret, int *count)
{
	int	width;

	width = (flags->preval);
	if (flags->minus == 1)
		print_char(ret, count);
	while (--width > 0)
		print_char(' ', count);
	if (flags->minus == 0)
		print_char(ret, count);
	free(flags);
}

void	print_str(t_flag *flags, char *ret, int *count)
{
	char	*retprint;
	int		i;

	if (!ret)
		ret = "(null)";
	retprint = ft_calloc(ft_strlen(ret) + 1, 1);
	ft_strlcpy(retprint, ret, flags->pstval + 1);
	if (!flags->period)
		ft_strlcpy(retprint, ret, ft_strlen(ret) + 1);
	while (!flags->minus && (int)ft_strlen(retprint) < flags->preval)
		retprint = ft_strjoin(ft_strdup(" "), retprint);
	while (flags->minus && (int)ft_strlen(retprint) < flags->preval)
		retprint = ft_strjoin(retprint, ft_strdup(" "));
	i = -1;
	while (retprint[++i] != '\0')
		print_char(retprint[i], count);
	free_all(&retprint);
	free (flags);
}

char	*hex_convert(unsigned long long ret, t_flag *flags)
{
	char	*hex;
	char	*temp;
	char	*hex_chars;

	hex_chars = "0123456789abcdef";
	if (flags->type == 'X')
		hex_chars = "0123456789ABCDEF";
	hex = ft_calloc(2, 1);
	temp = ft_calloc(2, 1);
	if (ret == 0 && flags->period && !flags->pstval && flags->type != 'p')
		hex = ft_strjoin(ft_strdup(""), hex);
	else if (ret == 0)
		hex = ft_strjoin(ft_strdup("0"), hex);
	while (ret > 0)
	{
		*temp = hex_chars[ret % 16];
		hex = ft_strjoin(ft_strdup(temp), hex);
		ret /= 16;
	}
	free_all(&temp);
	return (hex);
}

void	print_hex(t_flag *flags, unsigned long long ret, int *count)
{
	char	*pad;
	char	*hex;

	hex = hex_convert(ret, flags);
	if (ret == 0)
		flags->hash = 0;
	while ((int)ft_strlen(hex) < flags->pstval)
		hex = ft_strjoin(ft_strdup("0"), hex);
	if (flags->type == 'p' || (flags->hash && flags->type == 'x'))
		hex = ft_strjoin(ft_strdup("0x"), hex);
	if (flags->hash && flags->type == 'X')
		hex = ft_strjoin(ft_strdup("0X"), hex);
	pad = " ";
	if (flags->zero)
		pad = "0";
	while (!flags->minus && (int)ft_strlen(hex) < flags->preval)
		hex = ft_strjoin(ft_strdup(pad), hex);
	while (flags->minus && (int)ft_strlen(hex) < flags->preval)
		hex = ft_strjoin(hex, ft_strdup(" "));
	*count += ft_printf(hex);
	free(flags);
	free_all(&hex);
}
