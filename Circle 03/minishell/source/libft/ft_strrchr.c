/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:23:24 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/06 15:26:44 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == (char) c && i == 0)
			i = 1;
		s++;
	}
	if (*s == (char) c && i == 0)
		i = 1;
	while (i != 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
	}
	return (NULL);
}
