/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatel <mpatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:43:36 by athekkep          #+#    #+#             */
/*   Updated: 2022/03/21 17:46:24 by mpatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "../../includes/execution.h"

char	*shift_ln(char *ln)
{
	int		i;
	int		nl;
	char	*ret;

	i = 0;
	nl = alt_strchr(ln, '\n') + 1;
	ret = (char *) ft_calloc(BUFFER_SIZE + 1, 1);
	while (nl < BUFFER_SIZE && ln[nl] != '\0')
		ret[i++] = ln[nl++];
	free (ln);
	if (*ret == '\0')
	{
		free (ret);
		return (NULL);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*ln;
	char		*ans;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	ans = copy_line(NULL, ln);
	while (check_nl(ln) < 1)
	{
		free (ln);
		ln = (char *) ft_calloc(BUFFER_SIZE + 1, 1);
		ret = read(fd, ln, BUFFER_SIZE);
		if (ret <= 0 || signal_status(0, 2))
		{
			free (ln);
			ln = NULL;
			if (ans != NULL && ret != -1 && !signal_status(0, 2))
				return (ans);
			free (ans);
			return (NULL);
		}
		ans = copy_line(ans, ln);
	}
	ln = shift_ln(ln);
	return (ans);
}
