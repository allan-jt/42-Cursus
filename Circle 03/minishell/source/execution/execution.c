/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:17:59 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:18:09 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_pr(t_cmd *inst)
{
	inst->pid = 0;
	if (!inst->args || !inst->args[0] || inst->left
		|| inst->l_pipe || inst->r_pipe)
		return (0);
	if (ex_cd(inst) || ex_exit(inst) || inst->lef_dir_left
		|| ex_unset(inst) || ex_export_pr(inst))
		inst->pid = 1;
	return (inst->pid);
}

int	exec_cmd_ch(t_cmd *inst, int *fd)
{
	if (!inst->args || !inst->args[0])
		return (0);
	if (inst->left)
		return (ex_other(inst, fd));
	exit_status(0);
	if (ex_cd(inst) || ex_exit(inst) || ex_unset(inst)
		|| ex_export_pr(inst) || ex_echo(inst) || ex_pwd(inst)
		|| ex_export_ch(inst) || ex_env(inst) || ex_other(inst, fd))
		return (1);
	return (0);
}

void	exec_cmds(t_cmd *inst, int *fd)
{
	if (inst->args && inst->args[0]
		&& !ft_strncmp(inst->args[0], "./minishell", 12))
		signal_status(-1, 0);
	if (!exec_cmd_pr(inst) && !signal_status(0, 2))
		inst->pid = fork();
	if (inst->pid == 0 && !inst->lef_dir_left && !signal_status(0, 2))
	{
		if (inst->out_pipe != STDOUT_FILENO)
		{
			dup2(inst->out_pipe, STDOUT_FILENO);
			close (inst->out_pipe);
		}
		if (inst->in_pipe != STDIN_FILENO)
		{
			dup2(inst->in_pipe, STDIN_FILENO);
			close (inst->in_pipe);
		}
		if (!invalid_file(inst, fd))
			exec_cmd_ch(inst, fd);
		exit_clean(inst, exit_status(-1));
	}
	close_files(inst, fd);
}

void	init_left_dir(t_cmd *inst, int *fd)
{
	t_cmd	*tmp;

	cmd_struct(inst, 1);
	tmp = inst;
	inst->pid = fork();
	while (inst->pid == 0 && tmp && tmp->lef_dir_left)
	{
		process_leftdir(tmp, fd);
		tmp = tmp->prev;
	}
	if (inst->pid == 0)
		exit_clean(inst, exit_status(-1));
	wait(NULL);
}

void	init_cmd(t_cmd *inst)
{
	int		fd[3];
	t_cmd	*begin;

	signal_status(0, 1);
	wildcard(inst);
	eval_args(inst);
	cmd_reorg(&inst);
	cmd_prev(inst);
	open_pipes(inst);
	begin = inst;
	cmd_struct(inst, 1);
	while (inst && !signal_status(0, 2))
	{
		if (inst->left)
			close(open(inst->args[0], O_CREAT | O_RDWR | O_APPEND, 0700));
		while (inst->next && inst->lef_dir_left && inst->next->lef_dir_left)
			inst = inst->next;
		if (inst->lef_dir_left)
			init_left_dir(inst, fd);
		inst = inst->next;
	}
	exec_cmds(begin, fd);
	cmd_struct(NULL, 1);
}
