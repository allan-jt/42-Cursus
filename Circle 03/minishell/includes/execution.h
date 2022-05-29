/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allan.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:03:36 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 21:03:36 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLAN_H
# define ALLAN_H

typedef struct s_command	t_cmd;

// execution filters
void	init_cmd(t_cmd *inst);
void	exec_cmds(t_cmd *inst, int *fd);
void	cmd_reorg(t_cmd **inst);
void	cmd_prev(t_cmd *inst);
int		exec_cmd_ch(t_cmd *inst, int *fd);
int		exec_cmd_pr(t_cmd *inst);
void	exit_file(t_cmd *inst, int *fd);
void	eval_args(t_cmd *inst);
void	expand_args(t_cmd *inst);
void	open_pipes(t_cmd *inst);
char	**new_environ(char **env);
void	execute_path(t_cmd *inst);

// non-inbuilt funcctions
int		ex_other(t_cmd *inst, int *fd);

// inbuilt functions - parent
int		ex_cd(t_cmd *inst);

int		ex_exit(t_cmd *inst);
int		exit_status(int status);
void	exit_clean(t_cmd *inst, int code);

int		ex_unset(t_cmd *inst);
char	*get_var_name(char *str);
int		in_2d_array(char **ary, char *str);
char	**append_2d_array(char **ary, char *str);

int		ex_export_pr(t_cmd *inst);

// inbuilt functions - child
int		ex_echo(t_cmd *inst);
int		ex_pwd(t_cmd *inst);
int		ex_env(t_cmd *inst);
int		ex_export_ch(t_cmd *inst);

// utils
char	*read_all_text(int r_fd, int w_fd, char *end);
int		put_error(char *cmd, char *arg, char *message, int status);
void	free_2d(char **str);
int		d2_len(char **str);
void	close_files(t_cmd *inst, int *fd);
void	write_with_quote(int fd, char *str);
int		valid_var_name(char *name);
void	process_leftdir(t_cmd *inst, int *fd);
int		invalid_file(t_cmd *inst, int *fd);

// wildcards
int		is_match(char *nrml_str, char *test_str);
void	fill_wilcard(t_cmd *inst, char **contents);
void	wildcard(t_cmd *inst);
t_cmd	*cmd_struct(t_cmd *structure, int input);
int		signal_status(int value, int type);

#endif
