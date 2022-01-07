/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:34:34 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/20 17:34:38 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pushswap.h"

void	swap(t_list **s, char c, char *ret, char cnd)
{
	t_list	*first;
	char	*cmd;

	first = *s;
	if (ft_lstsize(*s) < 2)
		return ;
	*s = (*s)->next;
	first->next = (*s)->next;
	(*s)->next = first;
	if (cnd != 'w')
		return ;
	cmd = ft_calloc(4, 1);
	cmd[0] = 's';
	cmd[1] = c;
	cmd[2] = '\n';
	if (*ret == 's' && ret[1] != c && ret[1] != 's')
		cmd[1] = 's';
	else
		write(1, ret, ft_strlen(ret));
	ft_strlcpy(ret, cmd, 4);
	free(cmd);
}

void	push(t_list **s, t_list **d, char c, char *ret)
{
	t_list	*first;

	first = *s;
	if (!ft_lstsize(*s))
		return ;
	*s = (*s)->next;
	ft_lstadd_front(d, first);
	if (c == 'z')
		return ;
	write(1, ret, ft_strlen(ret));
	ret[0] = 'p';
	ret[1] = c;
	ret[2] = '\n';
	ret[3] = '\0';
}

void	rotate(t_list **s, char c, char *ret, char cnd)
{
	t_list	*first;
	char	*cmd;

	first = *s;
	if (ft_lstsize(*s) < 2)
		return ;
	*s = (*s)->next;
	first->next = NULL;
	ft_lstadd_back(s, first);
	if (cnd != 'w')
		return ;
	cmd = ft_calloc(4, 1);
	cmd[0] = 'r';
	cmd[1] = c;
	cmd[2] = '\n';
	if (*ret == 'r' && ret[1] != c && ret[1] != 'r')
		cmd[1] = 'r';
	else
		write(1, ret, ft_strlen(ret));
	ft_strlcpy(ret, cmd, 4);
	free(cmd);
}

void	rev_rotate(t_list **s, char c, char *rt, char cnd)
{
	t_list	*first;
	char	*cmd;

	first = *s;
	if (ft_lstsize(*s) < 2)
		return ;
	while (first->next->next != NULL)
		first = first->next;
	ft_lstadd_front(s, ft_lstlast(*s));
	first->next = NULL;
	if (cnd != 'w')
		return ;
	cmd = ft_calloc(5, 1);
	cmd[0] = 'r';
	cmd[1] = 'r';
	cmd[2] = c;
	cmd[3] = '\n';
	if ((!ft_strncmp(rt, "rra", 3) || !ft_strncmp(rt, "rrb", 3)) && c != rt[2])
		cmd[2] = 'r';
	else
		write(1, rt, ft_strlen(rt));
	ft_strlcpy(rt, cmd, 5);
	free(cmd);
}
