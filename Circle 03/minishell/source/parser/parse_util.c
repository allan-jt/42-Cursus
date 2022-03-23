/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:28 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 11:23:28 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quoted_end(char *str, int start, char c)
{
	int	i;

	i = start + 1;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

int	dollar_check(char *str, int *i)
{
	char	*env;
	int		start;
	char	**tmp_env;
	int		len;

	(*i)++;
	start = *i;
	tmp_env = new_environ(NULL);
	save_env(&env, str, i, start);
	len = ft_strlen(env);
	start = -1;
	while (tmp_env[++start])
	{
		if (ft_strncmp(env, tmp_env[start], len) == 0)
		{
			free (env);
			return (1);
		}
	}
	free(env);
	return (0);
}

void	null_strs(int **location, int pos, int len)
{
	if (!(*location))
	{
		(*location) = (int *)malloc((len + 1) * sizeof(int));
		while (len >= 0)
		{
			(*location)[len] = 0;
			len--;
		}
		(*location)[pos] = 1;
	}
	else
		(*location)[pos] = 1;
}

void	remove_null(char ***array, int *pos)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	k = 0;
	while ((*array)[++i])
	{
		if (pos[++k] == 1)
		{
			j = i - 1;
			tmp = (*array)[i];
			while ((*array)[++j])
				(*array)[j] = (*array)[j + 1];
			free (tmp);
			i--;
		}
	}
}
