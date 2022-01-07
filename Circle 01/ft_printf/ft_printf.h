/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:22:05 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/02 12:07:32 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct flg
{
	char	type;
	int		minus;
	int		zero;
	int		period;
	int		pstval;
	int		preval;
	int		hash;
	int		space;
	int		plus;
}				t_flag;

void	free_all(char **s1);
void	print_char(char c, int *count);
t_flag	*initialize_flag(char c);
t_flag	*set_flag(char *str);
void	num_process(t_flag *flags, int ret, int *count);
void	print_car(t_flag *flags, char ret, int *count);
void	print_str(t_flag *flags, char *ret, int *count);
void	print_num(t_flag *flags, char *num, int *count, int sign);
void	us_proc(t_flag *flags, unsigned long long ret, int *count);
void	print_hex(t_flag *flags, unsigned long long ret, int *count);
char	*id_convert(char *str, int *count, va_list *ap);
int		ft_printf(const char *str, ...);
#endif
