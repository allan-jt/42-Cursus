/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:12:45 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/18 14:07:14 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

static void	error(char *msg)
{
	ft_putstr_fd(msg, 1);
	exit(1);
}

static void	signal_handler(int signo, siginfo_t *info, void *context)
{
	static int	i;

	(void) info;
	(void) context;
	if (signo == SIGUSR1)
		i++;
	else
	{
		ft_putstr_fd("Success! Character(s) printed: ", 1);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('\n', 1);
	}
}

static void	sig_sender(int pid, char *msg)
{
	char		c;
	int			i;

	c = *msg;
	if (c != '\0')
		msg++;
	i = 8;
	while (i-- > 0)
	{
		if (c >> i & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				error("Invalid PID\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error("Invalid PID\n");
		}
		usleep(100);
	}
	if (c != '\0')
		sig_sender(pid, msg);
}

int	main(int argc, char **argv)
{
	struct sigaction	sh;

	if (argc != 3 || !argv[2])
		error("Incorrect parameters\n");
	sh.sa_sigaction = signal_handler;
	sh.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sh, NULL);
	sigaction(SIGUSR2, &sh, NULL);
	sig_sender(ft_atoi(argv[1]), argv[2]);
	return (0);
}
