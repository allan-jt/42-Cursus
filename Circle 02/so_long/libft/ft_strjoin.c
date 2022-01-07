/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:26:16 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/30 13:27:31 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
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
	free(s1);
	free(s2);
	return (ret);
}
