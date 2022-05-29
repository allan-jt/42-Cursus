/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:03:41 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 21:03:41 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "execution.h"
# include "parser.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	int		pid;
	char	*cmd;
	char	*cmd_path;
	char	*path;
	int		num_args;
	char	**args;
	int		in_pipe;
	int		out_pipe;
	int		l_pipe;
	int		r_pipe;
	int		right;
	int		left;
	int		lef_dir_left;
	int		lef_dir_right;
	t_cmd	*prev;
	t_cmd	*next;
}				t_cmd;

#endif
