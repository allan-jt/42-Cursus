/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:26:16 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/02 15:25:56 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	len = ft_strlen(s2);
	ret = malloc(i + ++len);
	if (ret == NULL)
		return (NULL);
	while (--len >= 0)
		ret[i + len] = s2[len];
	while (--i >= 0)
		ret[i] = s1[i];
	return (ret);
}
