/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:03:44 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 21:03:44 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATEL_H
# define PATEL_H

typedef struct s_command	t_cmd;

typedef struct s_par
{
	char	*line;
	int		i;
	int		end;
	int		tol;
	int		pos;
	int		len;
	int		key;
	int		size;
	int		*ary;
}			t_par;

//Parser

int		parser(char *line, t_cmd **cmd);
void	lst_add(t_cmd **cmd);
void	del_lst(t_cmd **cmd);
char	*quoted(char *str, int *i, char q);
int		quoted_end(char *str, int start, char c);
char	*dollar(char *str, int i);
char	*parse_env(char *line, int *i);
int		dollar_check(char *str, int *i);
void	parse_pipe(t_cmd **cmd, t_par **par);
void	parse_redir(t_cmd **cmd, t_par **par);
int		get_cmdpath(t_cmd **c);
int		issymbol(char c);

int		updated_split(char *s, t_cmd **cmd, int *i, int *len);

char	*everything(t_par **p, char *str);

void	remove_null(char ***array, int *pos);
void	null_strs(int **loc, int pos, int len);

void	sig_parent(void);

int		sub_len(char *str, int len, int toggle);
char	*replace_dollar(char *str, int len, int toggle);

int		nbr_len(int nbr);

void	save_env(char **env, char *line, int *i, int start);

int		check_empty(char *line);
void	moving(char *line, int *i);

#endif
