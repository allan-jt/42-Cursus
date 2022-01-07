/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:01:41 by athekkep          #+#    #+#             */
/*   Updated: 2021/09/30 13:47:10 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = i;
			found = 1;
			while (needle[j - i] != '\0')
			{
				if (needle[j - i] != haystack[j] || j == len)
					found = 0;
				j++;
			}
			if (found == 1)
				return (&((char *)haystack)[i]);
		}
		i++;
	}
	return (NULL);
}
