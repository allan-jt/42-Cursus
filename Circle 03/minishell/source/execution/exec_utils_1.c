/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:16:30 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:16:31 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_other(t_cmd *inst, int *fd)
{
	char		*str;

	if (!inst->left)
	{
		execute_path(inst);
		if (!inst->cmd_path && !ft_strchr(inst->args[0], '/'))
			return (put_error(inst->args[0], NULL,
					"Command not found\n", 127));
		return (put_error(inst->args[0], NULL, NULL, 127));
	}
	if (inst->left == 1)
		fd[2] = open(inst->args[0], O_CREAT | O_RDWR | O_TRUNC);
	else
		fd[2] = open(inst->args[0], O_CREAT | O_RDWR | O_APPEND, 0700);
	if (fd[2] == -1)
		return (put_error(inst->args[0], NULL, NULL, 1));
	str = read_all_text(STDIN_FILENO, fd[0], NULL);
	if (inst->right && inst->prev)
		write(STDOUT_FILENO, str, ft_strlen(str));
	write(fd[2], str, ft_strlen(str));
	free(str);
	exit_file(inst, fd);
	return (1);
}

void	free_2d(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	d2_len(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	exit_file(t_cmd *inst, int *fd)
{
	close (fd[2]);
	if (!inst->right)
		return ;
	fd[0] = open(inst->args[0], O_WRONLY | O_TRUNC);
	close(fd[0]);
}

void	close_files(t_cmd *inst, int *fd)
{
	int	status;

	status = 0;
	if (inst->out_pipe != 1)
		close(inst->out_pipe);
	if (inst->in_pipe)
		close(inst->in_pipe);
	if (inst->next)
		return (exec_cmds(inst->next, fd));
	while (inst)
	{
		if (!inst->next && inst->pid != 1 && inst->pid != 0)
		{
			waitpid(inst->pid, &status, 0);
			exit_status(WEXITSTATUS(status));
			if (signal_status(0, 2))
				exit_status(130);
		}
		else if (inst->pid != 1 && inst->pid != 0)
			waitpid(inst->pid, NULL, 0);
		if (inst->args && inst->args[0]
			&& !ft_strncmp(inst->args[0], "./minishell", 12))
			signal_status(1, 0);
		inst = inst->prev;
	}
}
