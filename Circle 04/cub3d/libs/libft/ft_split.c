/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:15:23 by mal-guna          #+#    #+#             */
/*   Updated: 2021/10/04 00:41:01 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_res_size(const char *str, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 1;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			size++;
		i++;
	}
	if (str[i - 1] == c)
		size--;
	return (size + 1);
}

static	void	ft_fill_str(char **res, char const *string, char ch)
{
	int		start;
	int		end;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (string[i])
	{
		while (string[i] == ch)
			i++;
		if (string[i] == '\0')
			break ;
		start = i;
		while (string[i] != ch && string[i] != '\0')
			i++;
		end = i;
		res[j] = ft_substr(string, start, end - start);
		j++;
	}
	res[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (s == NULL)
	{
		res = (char **)malloc(sizeof(char *) * 1);
		res[0] = 0;
		return (res);
	}
	res = (char **)malloc(sizeof(char *) * (ft_res_size(s, c) + 1));
	if (!res)
		return (NULL);
	ft_fill_str(res, s, c);
	return (res);
}
