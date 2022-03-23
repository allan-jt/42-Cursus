/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:31 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 18:39:40 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quoted_end(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	if (str[*i] == '\0')
		return (0);
	return (1);
}

static int	malloc_len(char *str, char sep, int i, int *words)
{
	int	toggle;

	toggle = 0;
	while (str[i] != '\0' && (sep == str[i]))
		i++;
	while (str[i] != '\0' && (str[i] != '<' && str[i] != '>' && str[i] != '|'))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i - 1] == ' ' || (str[0] == '"' || str[0] == '\''))
				(*words)++;
			if (!check_quoted_end(str, &i, str[i]))
				return (0);
		}
		else if ((sep != str[i]) && toggle == 0)
		{
			(*words)++;
			toggle = 1;
		}
		else if (sep == str[i])
			toggle = 0;
		i++;
	}
	return (1);
}

static char	**loop_split(char *s, char **array, int *i, int len)
{
	int	word;
	int	j;

	word = 0;
	while (word < (len) && *i <= (int)ft_strlen(s) && !issymbol(s[*i]))
	{
		j = 0;
		if (!ft_strchr(" \t\n\v\f\r", s[*i]))
		{
			while (!ft_strchr(" \t\n\v\f\r", s[*i + j])
				&& s[(*i) + j] && !issymbol(s[(*i) + j]))
			{
				if (s[(*i) + j] == '\'' || s[(*i) + j] == '"')
					j = (quoted_end(s, (j + (*i)), s[(*i) + j]) - (*i)) + 1;
				else
					j++;
			}
			(array)[word] = ft_substr(s + (*i), 0, j);
			if (!(array)[word++])
				return (NULL);
		}
		(*i) += j + 1;
	}
	array[word] = NULL;
	return (array);
}

int	updated_split(char *s, t_cmd **c, int *i, int *len)
{
	if (!s)
		return (0);
	if (*len)
		*len = 0;
	if (!malloc_len(s, ' ', *i, len))
		return (0);
	(*c)->args = (char **)malloc((*len + 1) * sizeof(char *));
	if (!(*c)->args)
		return (0);
	(*c)->args = loop_split(s, (*c)->args, i, *len);
	if (*i > 0)
		(*i)--;
	while (s[*i] && (s[*i] == ' ' || (s[*i] >= '\t' && s[*i] <= '\r')))
		(*i)++;
	return (1);
}
