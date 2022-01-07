/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_psutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:36:18 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/21 10:51:29 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pushswap.h"

int	checker(t_list *s, char c)
{
	t_list	*current;

	current = s;
	if (current == NULL)
		return (1);
	while (current->next != NULL)
	{
		if (current->num > current->next->num && c == 'a')
			return (0);
		if (current->num < current->next->num && c == 'd')
			return (0);
		current = current->next;
	}
	return (1);
}

void	srt_lst(int *lst, int size)
{
	int		ret;
	int		temp;
	int		i;

	i = 0;
	ret = 1;
	while (ret)
	{
		i = -1;
		ret = 0;
		while (++i < size - 1)
		{
			temp = lst[i];
			if (lst[i] < lst[i + 1])
			{
				lst[i] = lst[i + 1];
				lst[i + 1] = temp;
				ret = 1;
			}
		}
	}
}

int	*init_lst(t_list *s)
{
	int		*ret;
	t_list	*cur;
	int		i;

	ret = malloc(ft_lstsize(s) * 4);
	cur = s;
	i = 0;
	while (cur != NULL)
	{
		ret[i++] = cur->num;
		cur = cur->next;
	}
	srt_lst(ret, ft_lstsize(s));
	return (ret);
}

int	check_val(t_list *s, int val)
{
	while (s != NULL)
	{
		if (s->num < val)
			return (1);
		s = s->next;
	}
	return (0);
}

void	free_str(char **s)
{
	int		i;

	i = 0;
	while (s[i] != NULL)
		i++;
	while (i-- > 0)
		free(s[i]);
	free(s);
}
