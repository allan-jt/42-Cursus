/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:40:11 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/21 16:04:54 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSHSWAP_H
# define FT_PUSHSWAP_H	

# include "libft/libft.h"

void	swap(t_list **s, char c, char *ret, char cnd);
void	push(t_list **s, t_list **d, char c, char *ret);
void	rotate(t_list **s, char c, char *ret, char cnd);
void	rev_rotate(t_list **s, char c, char *ret, char cnd);
int		checker(t_list *s, char c);
void	srt_lst(int *lst, int size);
int		*init_lst(t_list *s);
int		check_val(t_list *s, int val);
void	sorter_a(t_list **a, t_list **b);
int		get_position(t_list *s, int val);
int		get_closest_val(t_list *s, long long int val);
void	finl_rotate(t_list **a, char *ret);
void	b_to_a(t_list **a, t_list **b, char *ret);
void	sorter_b(t_list **a, t_list **b, char *ret);
void	ret_joiner(char *ret, char *fn, char c);
void	check_invalid_num(char **argv);
void	check_duplicate(t_list **a);
void	sorter_3(t_list **a, char *ret);
void	sorter_5(t_list **a, t_list **b, char *ret);
void	error_msg(void);
void	position_a(t_list **a, t_list **b, t_list *min, char *ret);
void	free_str(char **s);
void	free_lst(t_list **a);

#endif
