/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:38 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 11:23:38 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_par	*init_parser(char *line)
{
	t_par	*par;

	par = (t_par *)malloc(sizeof(t_par));
	par->line = line;
	par->i = 0;
	par->end = 0;
	par->pos = 0;
	par->len = 0;
	par->key = 0;
	par->size = 0;
	par->ary = NULL;
	return (par);
}

static int	path_free(t_par *par, t_cmd **cmd, t_cmd *node)
{
	if (par->ary)
		free (par->ary);
	free(par);
	par = NULL;
	*cmd = node;
	return (1);
}

static int	err_check(t_cmd **cmd, t_cmd *node, t_par *par, char *line)
{
	int	i;

	i = par->i;
	if ((line[0] != '<' || (line[0] != '<' && line[1] != '<'))
		|| (line[0] != '>' || (line[0] != '>' && line[1] != '>')))
	{
		if (line[i] == '<' || line[i] == '>')
		{
			moving(line, &i);
			if (check_empty(line + i) || issymbol(line[i]))
				return (path_free(par, cmd, node));
		}
		else if (line[i] == '|')
			if (check_empty(line + (i + 1)))
				return (path_free(par, cmd, node));
		if (((*cmd)->args[0] == NULL && issymbol(line[i])))
			return (path_free(par, cmd, node));
	}
	else
	{
		moving(line, &i);
		if (check_empty(line + i))
			return (path_free(par, cmd, node));
	}
	return (0);
}

static int	get_args(t_cmd **cmd, t_par *par)
{
	par->pos = -1;
	if (!updated_split(par->line, cmd, &(par->i), &(par->size)))
	{
		free(par);
		par = NULL;
		return (0);
	}
	if (par->end)
		par->key = 1;
	while ((*cmd)->args[++(par->pos)])
	{
		if (par->pos != 0)
			par->key = 0;
		(*cmd)->args[(par->pos)] = everything(&par, (*cmd)->args[par->pos]);
	}
	if (par->ary)
		remove_null(&(*cmd)->args, par->ary);
	par->end = 0;
	return (1);
}

int	parser(char *line, t_cmd **cmd)
{
	t_par	*par;
	t_cmd	*node;

	par = init_parser(line);
	par->len = ft_strlen(line);
	node = *cmd;
	while (line[par->i] && par->i < par->len)
	{
		if ((*cmd)->args == NULL)
			if (!get_args(cmd, par))
				return (0);
		if ((*cmd)->cmd_path == NULL && ((*cmd)->args[0] != NULL))
			get_cmdpath(cmd);
		if (err_check(cmd, node, par, line))
			return (0);
		if (line[par->i] == '|')
			parse_pipe(cmd, &par);
		else if (line[par->i] == '<' || line[par->i] == '>')
			parse_redir(cmd, &par);
	}
	return (path_free(par, cmd, node));
}
