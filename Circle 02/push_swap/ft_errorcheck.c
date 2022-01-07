/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errorcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:44:38 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/21 16:03:57 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pushswap.h"

void	error_msg(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

void	check_invalid_num(char **argv)
{
	int				i;
	int				j;
	long long int	k;

	i = -1;
	while (argv[++i] != NULL)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
			{
				if (!((argv[i][j] == '-' || argv[i][j] == '+') && j == 0))
					error_msg();
			}
		}
		k = ft_atoi(argv[i]);
		if (k > 2147483647 || k < -2147483648)
			error_msg();
	}
}

void	check_duplicate(t_list **a)
{
	t_list	*cur;
	t_list	*temp;
	int		count;

	cur = *a;
	while (cur != NULL)
	{
		temp = *a;
		count = 0;
		while (temp != NULL)
		{
			if (temp->num == cur->num)
				count++;
			temp = temp->next;
		}
		if (count > 1)
			error_msg();
		cur = cur->next;
	}
}

void	free_lst(t_list **a)
{
	t_list	*cur;

	cur = *a;
	while (*a != NULL)
	{
		*a = (*a)->next;
		free (cur);
		cur = *a;
	}
}
