/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:46:56 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/10 09:46:03 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;

	len = ft_strlen(s1);
	copy = malloc(++len);
	if (copy == NULL)
		return (NULL);
	while (--len >= 0)
		copy[len] = s1[len];
	return (copy);
}
