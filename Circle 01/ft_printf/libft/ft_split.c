/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:30:25 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/10 09:54:28 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first_element_count(char const *s, char c)
{
	int	i;
	int	count;
	int	str_found;

	i = 0;
	count = 0;
	if (s[i] == c && *s != '\0')
		str_found = 0;
	else if (s[i] != c && *s != '\0')
	{
		str_found = 1;
		count++;
	}
	while (*s != '\0' && s[++i] != '\0')
	{
		if (s[i] != c && str_found != 1)
		{
			str_found = 1;
			count++;
		}
		if (s[i] == c && str_found != 0)
			str_found = 0;
	}
	return (count);
}

static void	str_clear(char **ret, int k)
{
	int	i;

	i = -1;
	while (++i < k)
		free(ret[i]);
	free (ret);
	ret = NULL;
}

static void	second_element_malloc(char const *s, char c, char **ret)
{
	int	str_start;
	int	i;
	int	k;

	str_start = -1;
	i = -1;
	k = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c && str_start == -1)
			str_start = i;
		if (s[i] == c && str_start != -1)
		{
			ret[k++] = ft_substr(s, str_start, i - str_start);
			if (ret[k - 1] == NULL)
				str_clear(ret, k - 1);
			str_start = -1;
		}
	}
	if (s[--i] != c)
	{
		ret[k++] = ft_substr(s, str_start, i - str_start + 1);
		if (ret[k - 1] == NULL)
			str_clear(ret, k - 1);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		array_count;

	if (s == NULL)
		return (NULL);
	array_count = first_element_count(s, c);
	ret = malloc(sizeof(char *) * (array_count + 1));
	if (ret == NULL)
		return (NULL);
	ret[array_count] = NULL;
	if (array_count == 0)
		return (ret);
	second_element_malloc(s, c, ret);
	return (ret);
}
