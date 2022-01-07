/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:26:16 by athekkep          #+#    #+#             */
/*   Updated: 2021/11/02 09:07:13 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_num(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*ret;
	int		found;

	found = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = malloc(len1 + ++len2);
	if (*s1 == '0' && ft_isdigit(*s2) == 0)
	{
		*ret++ = *s2++;
		len2--;
		found = 1;
	}
	while (--len2 >= 0)
		ret[len1 + len2] = s2[len2];
	while (--len1 >= 0)
		ret[len1] = s1[len1];
	s2 -= found;
	ret -= found;
	free(s1);
	free(s2);
	return (ret);
}
