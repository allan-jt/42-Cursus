/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:04:55 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/10 11:51:46 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	found_in_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i] != '\0')
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

static int	get_length(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		found;

	i = -1;
	len = 0;
	found = 0;
	while (s1[++i] != '\0')
		len++;
	while (found_in_set(s1[--i], set) == 1)
	{
		len--;
		if (len == 0)
			return (0);
	}
	while (found_in_set(*s1, set) == 1)
	{
		len--;
		s1++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	if (s1 == NULL)
		return (NULL);
	len = get_length(s1, set);
	ret = ft_calloc(len + 1, 1);
	if (ret == NULL)
		return (NULL);
	if (len == 0)
		return (ret);
	i = ft_strlen(s1) - 1;
	while (found_in_set(s1[i], set) == 1)
		i--;
	j = 0;
	while (found_in_set(s1[j], set) == 1)
		j++;
	while (i >= j)
		ret[--len] = s1[i--];
	return (ret);
}	
