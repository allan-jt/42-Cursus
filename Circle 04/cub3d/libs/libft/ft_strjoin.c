/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:08:34 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/28 22:22:13 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	b;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	b = 0;
	join = malloc(sizeof(*join) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1[i])
		join[b++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		join[b] = s2[i];
		i++;
		b++;
	}
	join[b] = '\0';
	free((char *)s1);
	return (join);
}
