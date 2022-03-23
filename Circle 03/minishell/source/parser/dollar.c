/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:22:59 by mpatel            #+#    #+#             */
/*   Updated: 2022/03/21 18:03:07 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_check(int *len, char *str, int *i, int start)
{
	char	*tmp;

	*len -= (start - (*i));
	tmp = parse_env(str, i);
	*len += ft_strlen(tmp);
	free (tmp);
}

static int	len_change(char *str, int *len, int *i)
{
	int	start;

	if (str[*i] == '$' && ft_isalnum(str[*i + 1]))
	{
		start = (*i);
		if (dollar_check(str, &start))
			var_check(len, str, i, start);
		else
		{
			*len -= (start - (*i));
			dollar_check(str, i);
			(*i)--;
		}
	}
	else if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		*len -= 2;
		(*i) += 2;
		*len += nbr_len(exit_status(-1));
	}
	else
		return (0);
	return (1);
}

int	sub_len(char *str, int len, int toggle)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!toggle && (str[i] == '"' || str[i] == '\''))
			break ;
		if (str[i] == '$')
			if (!len_change(str, &len, &i))
				i++;
		if (str[i] && str[i] != '$')
			i++;
	}
	return (len);
}

static char	*loop_replace(char *str, char *ptr, int *i, int toggle)
{
	int		len;
	int		k;

	k = 0;
	len = sub_len(ptr, ft_strlen(ptr), toggle);
	while (ptr[(*i)])
	{
		if (!toggle && (ptr[(*i)] == '"' || ptr[(*i)] == '\''))
			break ;
		if (ptr[(*i)] == '$' && ft_isalnum(ptr[(*i) + 1]))
			k += ft_strlcpy(str + k, parse_env(ptr, i), len + 1);
		else if (ptr[(*i)] == '$' && ptr[(*i) + 1] == '?')
		{
			(*i) += 2;
			k += ft_strlcpy(str + k, ft_itoa(exit_status(-1)), len + 1);
		}
		else
			str[k++] = ptr[(*i)++];
	}
	str[k] = '\0';
	return (str);
}

char	*replace_dollar(char *str, int len, int toggle)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = str;
	if (len == 0)
	{
		free (str);
		str = (char *)malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	str = loop_replace(str, ptr, &i, toggle);
	free(ptr);
	return (str);
}
