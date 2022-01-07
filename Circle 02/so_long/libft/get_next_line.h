/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:52:11 by athekkep          #+#    #+#             */
/*   Updated: 2021/12/08 14:33:50 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 2

char	*get_next_line(int fd);
int		ft_strchrr(const char *s, int c);
int		ft_strlenn(const char *str);
int		check_nl(char *ln);
char	*copy_line(char *ans, char *ln);
char	*shift_ln(char *ln);

#endif
