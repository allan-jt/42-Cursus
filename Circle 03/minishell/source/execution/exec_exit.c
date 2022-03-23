/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:16:14 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 20:16:15 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_error(char *cmd, char *arg, char *message, int status)
{
	char	*error;

	error = ft_strjoin(ft_strdup("minishell: "), ft_strdup(cmd));
	if (arg)
	{
		error = ft_strjoin(error, ft_strdup(": "));
		error = ft_strjoin(error, ft_strdup(arg));
	}
	if (!message)
		perror(error);
	else
	{
		error = ft_strjoin(error, ft_strdup(": "));
		error = ft_strjoin(error, ft_strdup(message));
		write(STDERR_FILENO, error, ft_strlen(error));
	}
	free(error);
	return (exit_status(status));
}

int	is_num(char *num)
{
	int					i;
	int					j;
	unsigned long long	x;

	i = 0;
	while (num[i] == ' ' || num[i] == '	')
		i++;
	if (num[i] == '-' || num[i] == '+')
		i++;
	j = -1;
	while (num[i + ++j] != '\0')
		if (num[i + j] < '0' || num[i + j] > '9')
			return (0);
	i = (*num == '-' || *num == '+') - 1;
	x = 0;
	while (num[++i] != '\0')
	{
		x = (x * 10) + (num[i] - '0');
		if ((x > 9223372036854775807 && *num != '-')
			|| (x > 9223372036854775808U && *num == '-'))
			return (-1);
	}
	return (1);
}

int	exit_status(int status)
{
	static int	ex_sts;

	if (status != -1)
		ex_sts = status;
	return (ex_sts);
}

void	exit_clean(t_cmd *inst, int code)
{
	t_cmd		*cur;

	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);
	cur = inst;
	while (cur->prev)
		cur = cur->prev;
	while (cur)
	{
		close(inst->in_pipe);
		close(inst->out_pipe);
		cur = cur->next;
	}
	free_2d(new_environ(NULL));
	free(inst->path);
	del_lst(&inst);
	rl_clear_history();
	exit(exit_status(code));
}

int	ex_exit(t_cmd *inst)
{
	int	code;
	int	temp;

	if (ft_strncmp(inst->args[0], "exit", 5))
		return (0);
	write(STDOUT_FILENO, "exit\n", 5);
	if (!inst->args[1])
		exit_clean(inst, exit_status(-1));
	if (!is_num(inst->args[1]))
		exit_clean(inst, put_error("exit", NULL,
				"numeric argument required\n", 2));
	if (is_num(inst->args[1]) == -1)
		exit_clean(inst, put_error("exit", NULL,
				"numeric argument required\n", 255));
	if (d2_len(inst->args) > 2)
		return (put_error("exit", NULL, "too many arguments\n", 1));
	code = ft_atoi(inst->args[1]);
	temp = code;
	if (code > 255)
		code = (code % 255) - 1;
	while (code < 0)
		code += 255;
	if (temp < 0)
		code += 1;
	exit_clean(inst, code);
	return (code);
}
