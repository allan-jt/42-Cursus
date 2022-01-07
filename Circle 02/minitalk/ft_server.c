/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:14:24 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/18 14:12:48 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static int	i;
	static int	s_pid;
	static char	c;	

	(void) context;
	s_pid = info->si_pid;
	c |= (signo == SIGUSR1);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(s_pid, SIGUSR2);
		else
		{
			ft_putchar_fd(c, 1);
			kill(s_pid, SIGUSR1);
		}
		c = 0;
		i = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	int					pid;
	struct sigaction	sh;

	pid = getpid();
	ft_putstr_fd("Server ID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sh.sa_sigaction = signal_handler;
	sh.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sh, NULL);
	sigaction(SIGUSR2, &sh, NULL);
	while (2 > 1)
		pause();
}
