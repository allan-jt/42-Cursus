/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 00:54:51 by mal-guna          #+#    #+#             */
/*   Updated: 2022/04/23 09:10:12 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start_index;
	size_t	end_index;

	if (!s1)
		return (NULL);
	start_index = 0;
	end_index = ft_strlen(s1) - 1;
	while (s1[start_index] && ft_strchr(set, s1[start_index]))
		start_index++;
	while (end_index >= start_index && ft_strchr(set, s1[end_index]))
		end_index--;
	str = ft_substr(s1, start_index, (end_index - start_index + 1));
	return (str);
}
