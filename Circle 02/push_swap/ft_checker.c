/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:28:25 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/21 16:15:30 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pushswap.h"

void	execute_inst(t_list **a, t_list **b, char *ln, int i)
{
	if (!ft_strncmp(ln, "pa\n", i))
		push(b, a, 'z', NULL);
	if (!ft_strncmp(ln, "pb\n", i))
		push(a, b, 'z', NULL);
	if (!ft_strncmp(ln, "sa\n", i) || !ft_strncmp(ln, "ss\n", i))
		swap(a, 'z', NULL, 'z');
	if (!ft_strncmp(ln, "sb\n", i) || !ft_strncmp(ln, "ss\n", i))
		swap(b, 'z', NULL, 'z');
	if (!ft_strncmp(ln, "ra\n", i) || !ft_strncmp(ln, "rr\n", i))
		rotate(a, 'z', NULL, 'z');
	if (!ft_strncmp(ln, "rb\n", i) || !ft_strncmp(ln, "rr\n", i))
		rotate(b, 'z', NULL, 'z');
	if (!ft_strncmp(ln, "rra\n", i) || !ft_strncmp(ln, "rrr\n", i))
		rev_rotate(a, 'z', NULL, 'z');
	if (!ft_strncmp(ln, "rrb\n", i) || !ft_strncmp(ln, "rrr\n", i))
		rev_rotate(b, 'z', NULL, 'z');
}

void	send_inst(char *ln, t_list **a, t_list **b)
{
	int	i;

	i = 3;
	if (!ft_strncmp(ln, "pa\n", i) || !ft_strncmp(ln, "pb\n", i)
		|| !ft_strncmp(ln, "sa\n", i) || !ft_strncmp(ln, "sb\n", i)
		|| !ft_strncmp(ln, "ss\n", i) || !ft_strncmp(ln, "ra\n", i)
		|| !ft_strncmp(ln, "rb\n", i) || !ft_strncmp(ln, "rr\n", i)
		|| !ft_strncmp(ln, "rra\n", 4) || !ft_strncmp(ln, "rrb\n", 4)
		|| !ft_strncmp(ln, "rrr\n", 4))
		execute_inst(a, b, ln, i);
	else
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}

void	process_inst(t_list **a, t_list **b)
{
	char	*ln;
	char	*c;
	int		i;

	i = 0;
	ln = ft_calloc(1, 1);
	c = ft_calloc(2, 1);
	while (read(0, c, 1) > 0)
	{
		ln = ft_strjoin(ln, ft_strdup(c));
		if (*c == '\n')
		{
			send_inst(ln, a, b);
			free(ln);
			ln = ft_calloc(1, 1);
		}
	}
	if (*ln != '\0')
		send_inst(ln, a, b);
	free(ln);
	free(c);
	if (checker(*a, 'a') && *b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
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
		free(ptr);
	}
	check_duplicate(&a);
	process_inst(&a, &b);
	free_lst(&a);
	free_lst(&b);
}
