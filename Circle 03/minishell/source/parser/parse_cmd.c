/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:24 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 11:27:24 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_split(t_cmd **c, char **cmd, char ***paths)
{
	char	*tmp;
	int		i;

	i = 0;
	*cmd = ft_strjoin(ft_strdup("/"), ft_strdup((*c)->args[0]));
	tmp = parse_env("$PATH", &i);
	if (!tmp)
	{
		free (tmp);
		free (*cmd);
		return (0);
	}
	*paths = ft_split(tmp, ':');
	free (tmp);
	return (1);
}

int	get_cmdpath(t_cmd **c)
{
	char	**paths;
	char	*cmd;
	int		i;

	if (!path_split(c, &cmd, &paths))
		return (0);
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], ft_strdup(cmd));
	i = -1;
	while (paths[++i])
	{
		if (!(access(paths[i], F_OK)))
		{
			(*c)->cmd_path = ft_strdup(paths[i]);
			break ;
		}
	}
	free_2d(paths);
	free(cmd);
	return (1);
}

void	save_env(char **env, char *line, int *i, int start)
{
	if (ft_isdigit(line[start]))
	{
		if (line[*i] && ft_isdigit(line[*i]))
			(*i)++;
	}
	else
	{
		while (line[*i] && ft_isalnum(line[*i]))
			(*i)++;
	}
	*env = ft_substr(line, start, (*i) - start);
	*env = ft_strjoin(*env, ft_strdup("="));
}

char	*parse_env(char *line, int *i)
{
	char	*buf;
	char	*env;
	int		start;
	int		len;
	char	**tmp_env;

	buf = NULL;
	(*i)++;
	start = *i;
	tmp_env = new_environ(NULL);
	save_env(&env, line, i, start);
	len = ft_strlen(env);
	start = -1;
	while (tmp_env[++start])
	{
		if (ft_strncmp(env, tmp_env[start], len) == 0)
		{
			buf = ft_substr(tmp_env[start],
					len, ft_strlen(tmp_env[start]) - len);
			free (env);
			return (buf);
		}
	}
	free(env);
	return (NULL);
}
