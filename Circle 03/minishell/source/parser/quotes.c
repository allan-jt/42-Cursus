/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:23:04 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 14:20:55 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_quotes(char *str, char *dst, int *i)
{
	char	*sq_str;
	char	*tmp;
	int		start;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		start = *i + 1;
		*i = quoted_end(str, *i, str[*i]) + 1;
		sq_str = ft_substr(str, start, (*i - 1) - start);
	}
	else
	{
		start = *i;
		while (str[*i])
			(*i)++;
		sq_str = ft_substr(str, start, (*i) - start);
	}
	tmp = dst;
	dst = ft_strjoin(ft_strdup(dst), sq_str);
	free (tmp);
	return (dst);
}

char	*double_quotes(char *str, char *dst, int *i)
{
	char	*dq_str;
	char	*tmp;
	int		start;

	start = *i + 1;
	*i = quoted_end(str, *i, str[*i]) + 1;
	dq_str = ft_substr(str, start, (*i - 1) - start);
	dq_str = replace_dollar(dq_str, sub_len(dq_str, ft_strlen(dq_str), 1), 1);
	tmp = dst;
	dst = ft_strjoin(ft_strdup(dst), dq_str);
	free (tmp);
	return (dst);
}

int	just_str(char *str, char **nqs, int *i)
{
	int		s;
	int		toggle;

	toggle = 0;
	s = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '"'))
			break ;
		if (str[*i] == '$')
			toggle = 1;
		(*i)++;
	}
	*nqs = ft_substr(str, s, *i - s);
	if (toggle)
		*nqs = replace_dollar((*nqs), sub_len((*nqs), ft_strlen(*nqs), 0), 0);
	return (s == 0 && (*i >= (int)ft_strlen(str)) && ((*nqs)[0] == '\0'));
}

char	*everything(t_par **p, char *str)
{
	int		i;
	char	*dst;
	char	*ptr;

	dst = (char *)ft_calloc(1, sizeof(char));
	ptr = NULL;
	i = 0;
	while (str[i] && i < (int) ft_strlen(str))
	{
		if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '"'))
			i++;
		if (str[i] == '"' && !((*p)->key))
			dst = double_quotes(str, dst, &i);
		else if (str[i] == '\'' || (*p)->key)
			dst = single_quotes(str, dst, &i);
		else
		{
			if (just_str(str, &ptr, &i))
				null_strs(&(*p)->ary, (*p)->pos, (*p)->len);
			dst = ft_strjoin(dst, ptr);
		}
	}
	free(str);
	return (dst);
}
