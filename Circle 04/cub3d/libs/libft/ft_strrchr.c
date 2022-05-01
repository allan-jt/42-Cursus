/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:08:47 by mal-guna          #+#    #+#             */
/*   Updated: 2021/10/07 21:41:57 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ch;

	ch = (char *)s;
	i = 0;
	while (*ch != '\0')
	{
		ch++;
		i++;
	}
	if (c == '\0')
		return (ch);
	while (i >= 0)
	{
		if (*ch == (char)c)
			return (ch);
		ch--;
		i--;
	}
	return (NULL);
}
