/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:27:08 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/21 16:11:38 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pushswap.h"

void	sorter_3(t_list **a, char *ret)
{
	int	x[3];

	if (ft_lstsize(*a) != 3 || checker(*a, 'a'))
		return ;
	x[0] = (*a)->num;
	x[1] = (*a)->next->num;
	x[2] = (*a)->next->next->num;
	if (x[0] > x[1] && x[0] < x[2] && x[1] < x[2])
		swap(a, 'a', ret, 'w');
	else if (x[0] > x[1] && x[1] > x[2] && x[0] > x[2])
	{
		swap(a, 'a', ret, 'w');
		rev_rotate(a, 'a', ret, 'w');
	}
	else if (x[0] < x[1] && x[1] > x[2] && x[0] < x[2])
	{
		rev_rotate(a, 'a', ret, 'w');
		swap(a, 'a', ret, 'w');
	}
	else if (x[0] < x[1] && x[1] > x[2] && x[0] > x[2])
		rev_rotate(a, 'a', ret, 'w');
	else
		rotate(a, 'a', ret, 'w');
}

void	sorter_5(t_list **a, t_list **b, char *ret)
{
	int	x;

	x = ft_lstsize(*a);
	if (x > 5 || checker(*a, 'a'))
		return ;
	while (x-- > 3)
		push(a, b, 'b', ret);
	sorter_3(a, ret);
}

void	sorter_b(t_list **a, t_list **b, char *ret)
{
	t_list	*cur;
	int		steps;
	int		temp;

	cur = *b;
	while (cur != NULL)
	{
		steps = get_position(*b, cur->num);
		if (steps > (ft_lstsize(*b) / 2))
			steps = ft_lstsize(*b) - steps;
		temp = get_closest_val(*a, cur->num);
		if (get_position(*a, temp) <= (ft_lstsize(*a) / 2))
		{
			steps += (1 + get_position(*a, temp));
			if (cur->num > temp)
				steps++;
		}
		if (get_position(*a, temp) > (ft_lstsize(*a) / 2))
			steps += (1 + ft_lstsize(*a) - get_position(*a, temp));
		cur->inst = steps;
		cur = cur->next;
	}
	if (*b != NULL)
		b_to_a(a, b, ret);
}

void	sorter_a(t_list **a, t_list **b)
{
	int		mid;
	int		*lst;
	char	*ret;

	ret = ft_calloc(5, 1);
	sorter_5(a, b, ret);
	lst = init_lst(*a);
	mid = lst[ft_lstsize(*a) / 2];
	while (!checker(*a, 'a'))
	{
		if ((*a)->num < mid)
			push(a, b, 'b', ret);
		else if (ft_lstlast(*a)->num < mid)
			rev_rotate(a, 'a', ret, 'w');
		else
			rotate(a, 'a', ret, 'w');
		if (!check_val(*a, mid))
			mid = lst[ft_lstsize(*a) / 2];
	}
	free(lst);
	sorter_b(a, b, ret);
	write(1, ret, ft_strlen(ret));
	free(ret);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	char	**temp;
	char	**ptr;
	int		i;

	if (argc == 1)
		exit(1);
	i = 0;
	a = NULL;
	b = NULL;
	while (++i < argc)
	{
		temp = ft_split(argv[i], ' ');
		check_invalid_num(temp);
		ptr = temp;
		while (*temp != NULL)
			ft_lstadd_back(&a, ft_lstnew((int)ft_atoi(*temp++)));
		free_str(ptr);
	}
	check_duplicate(&a);
	sorter_a(&a, &b);
	free_lst(&a);
}
