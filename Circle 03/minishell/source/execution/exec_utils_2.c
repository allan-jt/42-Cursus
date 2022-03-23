/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:15:46 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:15:48 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_leftdir(t_cmd *inst, int *fd)
{
	char	*str;

	str = NULL;
	if (inst->lef_dir_left == 2)
		str = read_all_text(STDIN_FILENO, STDOUT_FILENO, inst->args[0]);
	if (inst->lef_dir_left == 1)
	{
		fd[2] = open(inst->args[0], O_RDONLY);
		str = read_all_text(fd[2], STDOUT_FILENO, NULL);
		if (fd[2] != -1)
			close(fd[2]);
	}
	if (!inst->lef_dir_right)
	{
		if (str && !signal_status(0, 2))
			write(inst->out_pipe, str, ft_strlen(str));
		close (inst->out_pipe);
	}
	if (inst->lef_dir_right)
	{
		close (inst->prev->out_pipe);
		inst->prev->out_pipe = inst->out_pipe;
	}
	free(str);
}

int	invalid_file(t_cmd *inst, int *fd)
{
	t_cmd	*cur;
	int		error;

	if (!inst->prev)
		return (0);
	cur = inst->prev;
	error = 0;
	while (cur && cur->lef_dir_left)
	{
		if (cur->lef_dir_left == 1)
		{
			fd[2] = open(cur->args[0], O_RDWR | O_APPEND);
			if (fd[2] == -1)
			{
				put_error(inst->args[0], cur->args[0], NULL, 1);
				error = 1;
			}
			else
				close(fd[2]);
		}
		cur = cur->prev;
	}
	return (error);
}

void	open_pipes(t_cmd *inst)
{
	int	fd[2];

	if (!inst)
		return ;
	if (inst->r_pipe || inst->right || inst->lef_dir_left)
	{
		pipe(fd);
		inst->out_pipe = fd[1];
		inst->next->in_pipe = fd[0];
	}
	open_pipes(inst->next);
}

void	execute_path(t_cmd *inst)
{
	t_cmd	*cur;

	cur = inst;
	while (cur->prev)
	{
		cur = cur->prev;
		close (cur->out_pipe);
		if (cur->in_pipe != 0)
			close (cur->in_pipe);
	}
	cur = inst;
	while (cur->next)
	{
		cur = cur->next;
		close (cur->in_pipe);
		if (cur->out_pipe != 1)
			close (cur->out_pipe);
	}
	if (!ft_strchr(inst->args[0], '/') && inst->cmd_path)
		execve(inst->cmd_path, inst->args, new_environ(NULL));
	else if (ft_strchr(inst->args[0], '/'))
		execve(inst->args[0], inst->args, new_environ(NULL));
}

char	*read_all_text(int r_fd, int w_fd, char *end)
{
	char	*str;
	char	*tmp;
	int		len;

	if (r_fd == -1)
		return (NULL);
	str = ft_calloc(1, 1);
	if (end)
		write(w_fd, "> ", 2);
	tmp = get_next_line(r_fd);
	while (tmp && !signal_status(0, 2))
	{
		len = ft_strlen(end);
		if (end && !ft_strncmp(tmp, end, len)
			&& (tmp[len] == '\0' || tmp[len] == '\n'))
		{
			free(tmp);
			break ;
		}
		str = ft_strjoin(str, tmp);
		if (end)
			write(w_fd, "> ", 2);
		tmp = get_next_line(r_fd);
	}
	return (str);
}
