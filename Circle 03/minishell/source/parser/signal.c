/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:46 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 11:23:46 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_struct(t_cmd *structure, int input)
{
	static t_cmd	*str;

	if (input)
	{
		str = structure;
		return (str);
	}
	return (str);
}

int	signal_status(int value, int type)
{
	static int	num;
	static int	read;

	if (type == 0)
	{
		num += value;
		return (num);
	}
	else if (type == 1)
		read = value;
	return (read);
}

static void	sigint_handler(int signal)
{
	t_cmd	*cur;

	if (signal)
		cur = NULL;
	exit_status(1);
	cur = cmd_struct(NULL, 0);
	signal_status(1, 1);
	if ((!cur || (cur && cur->pid != 0)) && signal_status(0, 0))
		write(1, "\n", 1);
	if (!cur)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (cur && cur->pid == 0)
		exit_clean(cur, exit_status(-1));
}

static void	sigquit_handler(int sig)
{
	t_cmd	*cur;

	cur = cmd_struct(NULL, 0);
	if (sig == SIGQUIT)
	{
		if (cur && cur->pid != 0 && signal_status(0, 0))
			ft_putstr_fd("Quit\n", 1);
		rl_redisplay();
	}
}

void	sig_parent(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
