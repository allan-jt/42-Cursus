/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:54 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 11:23:54 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_err(t_cmd **cmd)
{
	exit_status(258);
	ft_putstr_fd("syntax error near unexpected token\n", 1);
	del_lst(cmd);
}

static void	exit_everything(t_cmd *cmd)
{
	write(STDOUT_FILENO, "exit\n", 5);
	exit_clean(cmd, exit_status(-1));
}

static void	read_prompt(t_cmd *cmd, char *line)
{
	while (1)
	{
		rl_catch_signals = 0;
		sig_parent();
		lst_add(&cmd);
		line = readline("bash$ ");
		if (line == NULL )
			exit_everything(cmd);
		if (!check_empty(line))
			add_history(line);
		else
		{
			del_lst(&cmd);
			continue ;
		}
		if (!parser(line, &cmd))
		{
			parser_err(&cmd);
			continue ;
		}
		init_cmd(cmd);
		del_lst(&cmd);
	}
}

char	**new_environ(char **env)
{
	static char	**envir;

	if (!env)
		return (envir);
	envir = env;
	return (NULL);
}

int	main(int ac, char **av)
{
	extern char	**environ;
	char		**new_env;
	t_cmd		*cmd;
	char		*line;
	int			i;

	cmd = NULL;
	line = NULL;
	(void)av;
	if (ac == 1)
	{
		signal_status(1, 0);
		i = -1;
		new_env = ft_calloc(d2_len(environ) + 1, sizeof(char *));
		while (environ[++i])
			new_env[i] = ft_strdup(environ[i]);
		new_environ(new_env);
		read_prompt(cmd, line);
		rl_clear_history();
		free_2d(new_environ(NULL));
	}
	else
		write(STDOUT_FILENO, "Too many arguments.\n", 20);
	return (0);
}
