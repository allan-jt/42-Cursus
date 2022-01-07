/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solveralt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:39:07 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/21 10:43:53 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pushswap.h"

int	get_position(t_list *s, int val)
{
	t_list	*cur;
	int		i;

	cur = s;
	i = 0;
	while (cur != NULL)
	{
		if (cur->num == val)
			return (i);
		i++;
		cur = cur->next;
	}
	return (i);
}

int	get_closest_val(t_list *s, long long int val)
{
	t_list			*cur;
	long long int	diff;
	long long int	temp;
	int				ret;

	cur = s;
	diff = 9223372036854775807;
	ret = 2147483647;
	while (cur != NULL)
	{
		temp = (long long int)cur->num - val;
		if (temp < 0)
			temp *= -1;
		if (temp < diff)
		{
			diff = temp;
			ret = cur->num;
		}
		cur = cur->next;
	}
	return (ret);
}

void	finl_rotate(t_list **a, char *ret)
{
	int		val;
	int		pos;

	val = get_closest_val(*a, -2147483648);
	pos = get_position(*a, val);
	while (pos != 0)
	{
		if (pos <= ft_lstsize(*a) / 2)
			rotate(a, 'a', ret, 'w');
		else
			rev_rotate(a, 'a', ret, 'w');
		pos = get_position(*a, val);
	}
}

void	position_a(t_list **a, t_list **b, t_list *min, char *ret)
{
	int	val;
	int	position;

	val = get_closest_val(*a, min->num);
	while (1)
	{
		position = get_position(*a, val);
		if ((min->num <= val && position == 0)
			|| (min->num > val && position == (ft_lstsize(*a) - 1)))
			break ;
		if (position <= (ft_lstsize(*a) / 2))
			rotate(a, 'a', ret, 'w');
		else
			rev_rotate(a, 'a', ret, 'w');
	}
	push(b, a, 'a', ret);
	if (*b != NULL)
		sorter_b(a, b, ret);
	finl_rotate(a, ret);
}

void	b_to_a(t_list **a, t_list **b, char *ret)
{
	t_list	*cur;
	t_list	*min;
	int		position;

	cur = *b;
	min = *b;
	while (cur != NULL)
	{
		if (cur->inst < min->inst)
			min = cur;
		cur = cur->next;
	}
	position = get_position(*b, min->num);
	while (position != 0)
	{
		if (position == 1)
			swap(b, 'b', ret, 'w');
		else if (position <= (ft_lstsize(*b) / 2))
			rotate(b, 'b', ret, 'w');
		else
			rev_rotate(b, 'b', ret, 'w');
		position = get_position(*b, min->num);
	}
	position_a(a, b, min, ret);
}
