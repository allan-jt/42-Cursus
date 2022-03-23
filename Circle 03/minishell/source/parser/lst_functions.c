/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:17 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 23:06:29 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_init(t_cmd **new)
{
	(*new) = ft_memset((*new), 0, sizeof(t_cmd));
	(*new)->out_pipe = 1;
	(*new)->in_pipe = 0;
	(*new)->next = NULL;
	(*new)->prev = NULL;
}

void	lst_add(t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*tmp;

	tmp = *cmd;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return ;
	if (new)
	{
		lst_init(&new);
		if (*cmd)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = NULL;
		}
		else
		{
			*cmd = new;
			return ;
		}
	}
}

static t_cmd	*del_beg(t_cmd **cmd)
{
	t_cmd	*ptr;

	ptr = *cmd;
	*cmd = (*cmd)->next;
	free(ptr);
	return (*cmd);
}

void	del_lst(t_cmd **cmd)
{
	t_cmd	*node;

	while ((*cmd) && (*cmd)->prev)
		(*cmd) = (*cmd)->prev;
	if (*cmd != NULL)
	{
		node = *cmd;
		while (node)
		{
			free((*cmd)->cmd);
			free((*cmd)->cmd_path);
			free_2d((*cmd)->args);
			*cmd = del_beg(&node);
			node = *cmd;
		}
		free(*cmd);
	}
}
