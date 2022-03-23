/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:50 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 11:23:50 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(t_cmd **c, t_par **p)
{
	lst_add(c);
	(*p)->tol = 1;
	if ((*c)->prev != NULL)
		(*c)->l_pipe = 1;
	if ((*c)->next != NULL)
	{
		(*c)->r_pipe = 1;
		(*c)->next->l_pipe = 1;
	}
	(*c) = (*c)->next;
	(*p)->i++;
}

void	parse_redir(t_cmd **c, t_par **p)
{
	lst_add(c);
	if ((*p)->line[(*p)->i] == '>' && (*p)->line[(*p)->i + 1] != '>')
	{
		(*c)->right = 1;
		(*c)->next->left = 1;
	}
	else if ((*p)->line[(*p)->i] == '>' && (*p)->line[(*p)->i + 1] == '>')
	{
		(*c)->right = 2;
		(*c)->next->left = 2;
	}
	else if ((*p)->line[(*p)->i] == '<' && (*p)->line[(*p)->i + 1] != '<')
	{
		(*c)->lef_dir_right = 1;
		(*c)->next->lef_dir_left = 1;
	}
	else if ((*p)->line[(*p)->i] == '<' && (*p)->line[(*p)->i + 1] == '<')
	{
		(*c)->lef_dir_right = 2;
		(*c)->next->lef_dir_left = 2;
		(*p)->end = 1;
	}
	while ((*p)->line[(*p)->i] == '<' || (*p)->line[(*p)->i] == '>')
		(*p)->i++;
	(*c) = (*c)->next;
}
