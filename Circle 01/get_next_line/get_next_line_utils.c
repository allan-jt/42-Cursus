/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:43:51 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/17 18:06:38 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	return (i);
}

void	*ft_calloc(int count, int size)
{
	void	*ptr;
	int		i;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < (count * size))
		((char *) ptr)[i++] = '\0';
	return (ptr);
}

int	check_nl(char *ln)
{
	if (!ln)
		return (-1);
	while (*ln != '\0' && *ln != '\n')
		ln++;
	if (*ln == '\n')
		return (1);
	return (0);
}

char	*copy_line(char *ans, char *ln)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	if (!ans && !ln)
		return (NULL);
	i = ft_strchr(ln, '\n') + 1;
	j = ft_strlen(ans);
	ret = ft_calloc(j + i + 1, 1);
	k = -1;
	while (++k < (i + j))
	{
		if (k < j)
			ret[k] = ans[k];
		else
			ret[k] = *ln++;
	}
	free (ans);
	return (ret);
}
