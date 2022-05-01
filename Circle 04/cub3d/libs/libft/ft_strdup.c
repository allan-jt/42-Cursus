/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:10:39 by mal-guna          #+#    #+#             */
/*   Updated: 2021/09/29 18:15:13 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;

	new = malloc(sizeof(*new) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s, ft_strlen(s) + 1);
	new[ft_strlen(s)] = '\0';
	return (new);
}
