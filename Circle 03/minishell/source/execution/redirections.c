/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:15:54 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:15:55 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_args(t_cmd *inst)
{
	char	**new_args;
	t_cmd	*cur;
	int		length;
	int		i;

	length = d2_len(inst->args);
	cur = inst;
	while (cur->right || cur->lef_dir_right)
	{
		cur = cur->next;
		length += d2_len(cur->args) - 1;
	}
	if (length == 0)
		return ;
	new_args = ft_calloc(length + 1, sizeof(char *));
	while (cur != inst->prev)
	{
		i = d2_len(cur->args);
		while (cur->args && i-- > (cur != inst))
			new_args[--length] = ft_strdup(cur->args[i]);
		cur = cur->prev;
	}
	free_2d(inst->args);
	inst->args = new_args;
}

void	eval_args(t_cmd *inst)
{
	if (!inst)
		return ;
	if ((inst->right || inst->lef_dir_right)
		&& (!inst->left && !inst->lef_dir_left))
	{
		expand_args(inst);
		if (inst->args && inst->args[0] && !inst->cmd_path)
			get_cmdpath(&inst);
	}
	if (inst->next)
		eval_args(inst->next);
}

static void	l_d(t_cmd **lst_c, t_cmd **c, t_cmd **fst_r, t_cmd **lst_r)
{
	t_cmd	*tmp;

	(*lst_c) = (*c);
	(*lst_r) = (*c)->next;
	(*fst_r) = (*c)->next;
	while ((*lst_r) && (*lst_r)->lef_dir_right)
		(*lst_r) = (*lst_r)->next;
	(*lst_c)->next = (*lst_r)->next;
	(*lst_c)->lef_dir_right = 0;
	(*lst_r)->right = 0;
	(*lst_r)->left = 0;
	(*lst_r)->l_pipe = 0;
	(*lst_r)->r_pipe = 0;
	if ((*lst_c)->next)
	{
		(*lst_c)->right = (*lst_c)->next->left;
		(*lst_c)->r_pipe = (*lst_c)->next->l_pipe;
		(*lst_c)->next->prev = *lst_c;
	}
	tmp = (*lst_r);
	while (tmp != (*fst_r))
	{
		tmp->next = tmp->prev;
		tmp = tmp->prev;
	}
}

void	cmd_reorg(t_cmd **inst)
{
	t_cmd	*cur;
	t_cmd	*lst_pipe;
	t_cmd	*lst_cmd;
	t_cmd	*fst_redir;
	t_cmd	*lst_redir;

	cur = *inst;
	lst_pipe = *inst;
	while (cur)
	{
		if (cur->l_pipe)
			lst_pipe = cur;
		if (cur->lef_dir_right)
		{
			l_d(&lst_cmd, &cur, &fst_redir, &lst_redir);
			fst_redir->next = lst_pipe;
			lst_redir->prev = lst_pipe->prev;
			if (lst_pipe->prev)
				lst_pipe->prev->next = lst_redir;
			else
				*inst = lst_redir;
		}
		cur = cur->next;
	}
}

void	cmd_prev(t_cmd *inst)
{
	if (!inst)
		return ;
	inst->prev = NULL;
	while (inst->next)
	{
		inst->next->prev = inst;
		inst = inst->next;
	}
}
