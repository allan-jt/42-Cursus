/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:28:44 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/12 11:41:24 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			actlen;
	unsigned int	i;
	char			*substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s) - (int) start)
		substr = ft_calloc(ft_strlen(s) - (int) start + 1, 1);
	else
		substr = ft_calloc(len + 1, 1);
	if (substr == NULL)
		return (NULL);
	i = start;
	actlen = 0;
	while (s[i] != '\0' && actlen < len)
		substr[actlen++] = (char) s[i++];
	return (substr);
}
